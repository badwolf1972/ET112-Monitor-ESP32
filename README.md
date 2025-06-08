# ET112-Monitor-ESP32

ESP32-based monitor for Victron ET112 Energy Meter with Home Assistant integration.

## Model Compatibility
This code has been tested and verified working with:
- ET112-DIN.AV0.1X.S1.X.01 (UK Version)

**Important Note:** If you use this code with a different ET112 variant, please create an issue to report:
- Your ET112 model number
- Whether the code worked or not
- Any modifications needed
- Your location/region

This will help build a compatibility database for different ET112 variants.

## Features
- Real-time power monitoring (Watts)
- Total energy consumption (kWh)
- Home Assistant integration
- Modbus RTU communication
- Daily/Weekly/Monthly/Yearly energy tracking

## Hardware Requirements
- ESP32
- Victron ET112 Energy Meter
- RS485 to TTL converter
- Power supply for ESP32

## Installation
1. Install required libraries:
   - ModbusMaster
   - WiFi
   - HTTPClient

2. Configure settings:
   - WiFi credentials
   - Home Assistant IP address
   - Home Assistant long-lived token

3. Wire connections:
   - ESP32 GPIO16 -> RS485 RX
   - ESP32 GPIO17 -> RS485 TX
   - RS485 A+ and B- to ET112

## Home Assistant Configuration
Add to configuration.yaml:
```yaml
utility_meter:
  daily_energy:
    source: sensor.et112_data_kwh
    cycle: daily
  weekly_energy:
    source: sensor.et112_data_kwh
    cycle: weekly
  monthly_energy:
    source: sensor.et112_data_kwh
    cycle: monthly
  yearly_energy:
    source: sensor.et112_data_kwh
    cycle: yearly
```
