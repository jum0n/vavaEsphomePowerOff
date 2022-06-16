# vavaEsphomeRemotePower
Use an ESP32 dev board with Home Assistant to control the power state on the original vava projector which requires a bluetooth remote

-All credit to Cosmos_Explorer1 for figuring this out, this is just a more concise and easier method based on his post on reddit.

1. Acquire an ESP32 dev board.  Recommended: ESP32-WROOM-32D, if you use another, you MIGHT need to modify the board type in vavaremote.yaml below.
2. Install ESPHome on Home Assistant (HA).  Lots of detailed info here: https://esphome.io/guides/getting_started_hassio.html
3. Add the "inc" folder and its contents to your ESPHome folder (typically /config/esphome/).
4. Add the proper entries for wifi_ssid, wifi_password, ota_password, and api_password to your secrets.yaml file in this same directory (you might already have done this if you used esphome before, you can alternatively just put your plain text entries in the config but thats bad security).
5. In ESPhome create a new device using the code from the "blekeyboard.yaml" file.  This will require you to cable the ESP32 to your system (the first time) and use the Chrome browser to program it.  There is usually a small button on the ESP32 devices that might need to be held when powering it on to put it into programming mode.
6. Once the ESP32 board is online, move it near the vava projector, power it on, and then add it as a bluetooth device in the projector menu and ensure it shows "connected" (may need to power cycle the projector after pairing to get the status to "connected").
7. In HA add the newly discovered "blekeyboard" device using the password specified in api_password.
8. Create a script to send KEY_MEDIA_POWER as text to the vavaremote entity with any delay time you wish (1ms recommended).
9. Create your automation and call this script to power on or power off the vava projector.
10. PROFIT!
