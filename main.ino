#include <InfluxDbClient.h>

// Deep Sleep version

#include <WiFi.h>
#include <WiFiClient.h>
#include <Update.h>
#include <DHT.h>
#include <HTTPClient.h>

#define DHTTYPE DHT22
#define SENSOR_PIN 4

#define INFLUXDB_URL "http://example.com/influxdb"
#define INFLUXDB_DATABASE "home"

DHT dth(SENSOR_PIN, DHTTYPE);

float humidity;
float temperature;

const char *ssid = "Example";
const char *password = "secret";

const char *debugRemote = "http://example.com/data";

const uint64_t sleepTime = 2;
const uint64_t hourToMicroSeconds = 3600000000;
const uint64_t minuteToMicroSeconds = 60000000;

String name = "";

// HTTPClient http;

InfluxDBClient client(INFLUXDB_URL, INFLUXDB_DATABASE);

Point weather("weather");

void connectToWifi()
{
    // Connect to WiFi network
    WiFi.begin(ssid, password);
    delay(100);

    uint8_t counter = 0;
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED)
    {
        if (counter++ == 3)
        {
            Serial.println("");
            Serial.print("Not connected: ");
            Serial.println(WiFi.status());
            goToSleep(100);
        }
        delay(500);
    }
    Serial.println("Connected " + WiFi.localIP().toString());

    if (name == "")
    {
        name = WiFi.localIP().toString();
    }
}

String createMessage(const float temperature, const float humidity, const String &name)
{
    return "{\"temp\":" + String(temperature, 2) + ", \"hum\":" + String(humidity, 1) + ", \"name\": \"" + name + "\"}";
}

void sendDebugMessage(const String &message)
{
    http.begin(debugRemote);
    http.addHeader("Content-Type", "application/json");
    http.POST(message);
}

void sensorSetup()
{
    pinMode(SENSOR_PIN, INPUT);
    dth.begin();
}

void setup()
{
    Serial.begin(115200);
    connectToWifi();
    sensorSetup();

    weather.addTag("ip", WiFi.localIP().toString());

    humidity = dth.readHumidity();
    temperature = dth.readTemperature();

    weather.clearFields();
    weather.addField("temperature", temperature);
    weather.addField("humidity", humidity);

    // Check server connection
    if (!client.validateConnection())
    {
        Serial.print("InfluxDB connection failed: ");
        Serial.println(client.getLastErrorMessage());
    }

    if (!client.writePoint(weather))
    {
        Serial.print("InfluxDB write failed: ");
        Serial.println(client.getLastErrorMessage());
    }

    // String message = createMessage(temperature, humidity, name);
    // sendDebugMessage(message);

    // Serial.println("Going to sleep");
    goToSleep(sleepTime * 60, true);
}

void goToSleep(uint64_t time)
{
    goToSleep(time, false);
}

void goToSleep(uint64_t time, bool seconds)
{
    if (seconds)
    {
        time *= 1000000;
    }
    WiFi.disconnect();
    esp_sleep_enable_timer_wakeup(time);
    esp_deep_sleep_start();
}

void loop()
{
    // do nothing
}
