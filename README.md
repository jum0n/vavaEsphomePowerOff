# vavaEsphomeRemotePower
Use an esp32 to control the power switch on your vava projector


1. Acquire an ESP32 dev board.  Recommended: ESP32-WROOM-32D, if you use another, you MIGHT need to modify the board type in vavaremote.yaml below.
2. Install ESPHome on homeassistant (HA). If you dont already have HA, you should!
3. Add the "inc" folder and its contents to your ESPHome folder (typically /config/esphome/).
4. Add the proper entries for wifi_ssid, wifi_password, ota_password, and api_password to your secrets.yaml file in this same directory (might already have done this if you used esphome before).
5. In ESPhome create a new device using the code from the "vavaremote.yaml" file.  This will require you to cable the ESP32 to your system (the first time) and use the Chrome browser to program it.  There is usually a small button on the ESP32 devices that might need to be held when powering it on to put it into programming mode.  Lots of info on these devices over here: https://microcontrollerslab.com/esp32-development-board/
6. Once the ESP32 board is online, move it near the vava projector, power it on, and then add it as a bluetooth device in the projector menu (may need to power cycle projector if its not playing nice).
7. In HA add the newly discovered "vavaremote" device using the password specified in api_password.
8. Create a script to send KEY_MEDIA_POWER as text to the vavaremote entity with any delay time you wish (1ms recommended).
9. Create your automation and call this script to power on or power off the vava projector.
10. PROFIT!
