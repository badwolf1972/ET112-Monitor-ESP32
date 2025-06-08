# ET112 Energy Meter Monitor

ESP32-based monitor for Victron ET112 Energy Meter with Home Assistant integration.

## Features
- Real-time power monitoring (Watts)
- Total energy consumption (kWh)
- Home Assistant integration
- Modbus RTU communication

## Hardware Requirements
- ESP32
- Victron ET112 Energy Meter
- RS485 to TTL converter

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
