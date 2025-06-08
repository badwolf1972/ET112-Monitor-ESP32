/*
ET112 Energy Meter Monitor
For use with Victron ET112 Energy Meter

This script reads power and energy data from an ET112 meter via Modbus RTU
and reports it to Home Assistant. Tested with ESP32.

Key Features:
- Real-time power monitoring (Watts)
- Total energy consumption (kWh)
- Home Assistant integration
- Modbus RTU communication

Hardware Requirements:
- ESP32
- ET112 Energy Meter
- RS485 to TTL converter

Connection:
- ESP32 GPIO16 -> RS485 RX
- ESP32 GPIO17 -> RS485 TX
- RS485 A+ and B- to ET112
*/

#include <WiFi.h>
#include <HTTPClient.h>
#include <ModbusMaster.h>

// WiFi Configuration
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";

// Home Assistant Configuration
const char* homeAssistantServerWatts = "http://YOUR_HA_IP:8123/api/states/sensor.et112_data";
const char* homeAssistantServerKwh = "http://YOUR_HA_IP:8123/api/states/sensor.et112_data_kwh";
const char* longLivedToken = "YOUR_LONG_LIVED_TOKEN";

// Modbus RTU Configuration
#define TX_PIN 17          // ESP32 TX pin
#define RX_PIN 16          // ESP32 RX pin
#define BAUD_RATE 9600     // ET112 default baud rate

ModbusMaster node;

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");
    
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println("\nConnected to WiFi");

    Serial2.begin(BAUD_RATE, SERIAL_8N1, RX_PIN, TX_PIN);
    node.begin(1, Serial2);  // Modbus slave ID = 1

    if (node.readInputRegisters(0, 2) == node.ku8MBSuccess) {
        Serial.println("Modbus communication successful.");
    } else {
        Serial.println("Modbus communication failed.");
    }
}

void sendToHomeAssistant(const char* server, float value, const char* unit) {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;
        http.begin(server);
        http.addHeader("Content-Type", "application/json");
        http.addHeader("Authorization", "Bearer " + String(longLivedToken));

        String payload = "{ \"state\": \"" + String(value, 1) + "\", \"attributes\": { \"unit_of_measurement\": \"" + String(unit) + "\" }}";
        
        Serial.println("Sending JSON: " + payload);
        int httpResponseCode = http.POST(payload);

        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        
        http.end();
    } else {
        Serial.println("WiFi not connected. Cannot send data.");
    }
}

void loop() {
    uint8_t result;
    float power;
    float kWh;

    // Read Power (Register 0x0005)
    result = node.readInputRegisters(0x0005, 2);
    if (result == node.ku8MBSuccess) {
        uint32_t pf = (node.getResponseBuffer(0) << 16) | node.getResponseBuffer(1);
        power = pf / 10.0;
        Serial.print("Power: ");
        Serial.print(power);
        Serial.println(" W");
        sendToHomeAssistant(homeAssistantServerWatts, power, "W");
    }

    // Read Total Energy (Register 273)
    result = node.readInputRegisters(273, 2);
    if (result == node.ku8MBSuccess) {
        uint16_t rawValue = node.getResponseBuffer(1);  // Use second register value
        kWh = rawValue / 10.0;
        Serial.print("Energy Usage: ");
        Serial.print(kWh, 1);
        Serial.println(" kWh");
        sendToHomeAssistant(homeAssistantServerKwh, kWh, "kWh");
    }

    delay(5000);  // Update every 5 seconds
}
