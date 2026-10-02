#pragma once

#include "esphome.h"
using namespace esphome;

#include "esphome/components/binary_sensor/binary_sensor.h"
#include "esphome/components/sensor/sensor.h"
#include <BleKeyboard.h>
#include <string>
#include "keymap.h"

namespace esphome {

class Esp32BLEKeyboard : public PollingComponent {
   private:
    int defaultDelay = 100;

    void press(std::string message) {
        ESP_LOGD("Esp32BLEKeyboard", "Sending key: %s, Length: %d", message.c_str(), message.length());

        if (message.find("KEY_MEDIA_") != std::string::npos && BLE_KEYBOARD_MEDIA_KEY_MAP.count(message)) {
            MediaKeyStruct key = BLE_KEYBOARD_MEDIA_KEY_MAP.find(message)->second;
            MediaKeyReport mediaKey = {key.left, key.right};

            bleKeyboard.press(mediaKey);

            return;
        }

        if (message.find("KEY_") != std::string::npos && BLE_KEYBOARD_KEY_MAP.count(message)) {
            bleKeyboard.press((uint8_t) BLE_KEYBOARD_KEY_MAP.find(message)->second);

            return;
        }

        if (message.length() >= 5) {
            for (unsigned i = 0; i < message.length(); i += 5) {
                bleKeyboard.print(message.substr(i, 5).c_str());

                delay(defaultDelay);
            }

            return;
        }

        bleKeyboard.print(message.c_str());
    }

   public:
    BleKeyboard bleKeyboard;
    binary_sensor::BinarySensor *connected_binarysensor = nullptr;
    sensor::Sensor *delay_sensor = nullptr;

    Esp32BLEKeyboard(std::string name, std::string manufacturer) : PollingComponent(1000), bleKeyboard(name, manufacturer, 100) {}

    void set_connected_binary_sensor(binary_sensor::BinarySensor *sensor) { connected_binarysensor = sensor; }
    void set_delay_sensor(sensor::Sensor *sensor) { delay_sensor = sensor; }

    void setup() override {
        ESP_LOGD("Esp32BLEKeyboard", "Setting up BLE Keyboard...");

        bleKeyboard.begin();
        bleKeyboard.releaseAll();

        if (delay_sensor != nullptr)
            delay_sensor->publish_state(8);
    }

    void update() override {
        if (connected_binarysensor != nullptr)
            connected_binarysensor->publish_state(bleKeyboard.isConnected());
    }

    void release(std::string message, uint32_t delay_ms = 8) {
        if (!bleKeyboard.isConnected()) {
            ESP_LOGD("Esp32BLEKeyboard", "Disconnected");

            return;
        }

        ESP_LOGD("Esp32BLEKeyboard", "Set delay: %u", (unsigned) delay_ms);

        bleKeyboard.setDelay(delay_ms);
        if (delay_sensor != nullptr)
            delay_sensor->publish_state(delay_ms);

        std::string delimiter = "\\+";
        size_t pos = 0;
        while ((pos = message.find(delimiter)) != std::string::npos) {
            press(message.substr(0, pos));
            message.erase(0, pos + delimiter.length());
        }

        if (message.length() > 0) {
            press(message);
        }

        delay(defaultDelay);

        bleKeyboard.releaseAll();
    }
};

}  // namespace esphome
