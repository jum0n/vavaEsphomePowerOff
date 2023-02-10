# vavaEsphomePowerOff
Use an ESP32 dev board with Home Assistant to automate power off of the original vava projector which requires a bluetooth remote.
  
  NOTE: This does NOT power ON the projector since the bluetooth connection is disconnected by the projector when it powers off.
  
  -All credit to Cosmos_Explorer1 for figuring this out, this is just a more concise and easier method based on his post on reddit.

* You should already have Home Assistant (HA) https://www.home-assistant.io/ setup/running on some platform before you start the steps below.  If you do not, there may be a learning curve with some of the steps.  This guide assumes you have access to HA, a way to access the storage of HA directly (use "samba share" add-on perhaps), and working knowledge of how to create an automation based on a state/value change.  

1. Acquire an ESP32 dev board (and buy an appropriate power supply for it, most will be fine due to low amperage requirements).  Recommended: ESP32-WROOM-32D, if you use another, you MIGHT need to modify the board type in blekeyboard.yaml file.  These are about $5 shipped to the USA via Aliexpress, but available elsewhere (and faster) for more money.  Vendors keep changing pricing, so I cannot provide any links to them that are consistently reliable/inexpensive.
2. Install ESPHome on Home Assistant (HA).  Lots of detailed info here: https://esphome.io/guides/getting_started_hassio.html
3. Add the "inc" folder and its contents to your ESPHome folder on your Home Assistant instance/device/storage (typically /config/esphome/).
4. Add the proper entries for wifi_ssid, wifi_password, and ota_password to your secrets.yaml file in the ESPhome folder.  I have included an example if you dont already have these, but it must be customized with your desired passwords.  The ESPhome web interface now has a button for this in the upper right corner, but you may need to create the file first for this button to appear.
5. In the ESPhome web interface, create a new device using the code from the "blekeyboard.yaml" file.  You will have to update the API key manually in this file to one you would like to use.  There is a reference to the ESPHome site that will auto-generate one for you.  You will also need to connect the ESP32 to your system using a USB cable (the first time) and use the Chrome browser to program it.  There is usually a small button on the ESP32 devices that might need to be held when powering it on to put it into programming mode.  You may create the device with all defaults, then edit the config and replace default content and re-install to the device.
6. Once the ESP32 board is online, move it near the vava projector, power it on, and then add it as a bluetooth device in the projector menu and ensure it shows "connected" (may need to power cycle the projector after pairing to get the status to "connected").  !!Please be sure it shows "connected" before continuing on, this can take many attempts but once done, it is stable.
7. In HA add the newly discovered "blekeyboard" device.  The api key should be automatically imported/used.
8. Create a script in HA to send KEY_MEDIA_POWER as text to the blekeyboard entity. (example included: HAPowerOffScript.txt)
9. Create your automation in HA and call the new script created above to power off the vava projector.  I trigger this automation to happen when my receiver is shut down using the power monitoring values of a Kasa KP115 I added inline (and using the "TP-Link Kasa Smart" integration), but you could trigger it off any unique event that means you want the projector powered off.
10. Done!
