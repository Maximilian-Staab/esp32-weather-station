# ESP32 based Weather-Station

A small project to create a esp32 based weather stations for monitoring humidity and temperature inside your home.

<p float="left" align="middle">
  <img src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/87/Arduino_Logo.svg/1080px-Arduino_Logo.svg.png" width="100" align="middle" />
  <img src="https://upload.wikimedia.org/wikipedia/commons/7/7b/ESP32_Espressif_ESP-WROOM-32_Shielded.jpg" width="100" align="middle" /> 
  <img src="https://www.espressif.com/sites/all/themes/espressif/logo-black.svg" width="100" align="middle" />
</p>

Use the Arduino-IDE or VSCode + Arduino Extension.
The influxdb endpoint and WiFi configuration need to be changed to your network structure.

## Dependencies

[Adafruit DHT sensor lib](https://github.com/adafruit/DHT-sensor-library)

[WiFi and HTTP stuff](https://github.com/espressif/arduino-esp32)

[influxDB](https://github.com/tobiasschuerg/InfluxDB-Client-for-Arduino)

## Future

Migrate the Project to [PlatformIO](https://platformio.org/) for a better dependency management.
