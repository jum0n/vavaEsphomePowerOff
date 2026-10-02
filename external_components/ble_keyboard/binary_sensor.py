import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import binary_sensor
from esphome.const import CONF_ID

from . import Esp32BLEKeyboard

CONF_BLE_KEYBOARD_ID = "ble_keyboard_id"

CONFIG_SCHEMA = binary_sensor.binary_sensor_schema().extend(
    {
        cv.GenerateID(CONF_BLE_KEYBOARD_ID): cv.use_id(Esp32BLEKeyboard),
    }
)


async def to_code(config):
    parent = await cg.get_variable(config[CONF_BLE_KEYBOARD_ID])
    sens = await binary_sensor.new_binary_sensor(config)
    cg.add(parent.set_connected_binary_sensor(sens))
