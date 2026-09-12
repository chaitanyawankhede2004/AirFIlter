# AirFilter

An ESP8266-based Air Quality Monitoring system using an SDS011 Dust Sensor, 16x2 I2C LCD Display, and ThingSpeak Cloud Integration.

## Hardware Components
- **Microcontroller**: ESP8266 NodeMCU
- **Particulate Matter Sensor**: SDS011 / Nova Fitness PM Sensor (SoftwareSerial on D6 TX / D5 RX)
- **Display**: 16x2 LiquidCrystal LCD via I2C (SDA -> D2, SCL -> D1)
- **Connectivity**: WiFi (ESP8266WiFi)

## Pinout Connections

| Component | ESP8266 Pin | Notes |
| --- | --- | --- |
| PM Sensor TX | D6 (GPIO12) | SoftwareSerial RX |
| PM Sensor RX | D5 (GPIO14) | SoftwareSerial TX |
| LCD SDA | D2 (GPIO4) | Hardware I2C SDA |
| LCD SCL | D1 (GPIO5) | Hardware I2C SCL |
| LCD VCC / GND | 5V / GND | Power supply |

## Features
- Real-time measurement of **PM2.5** and **PM10** particulate matter levels.
- Live display of readings on a 16x2 I2C LCD screen.
- Automated data logging to **ThingSpeak Cloud** at configurable intervals (default: 20 seconds).
- WiFi connection manager with auto-reconnect fallback.

## Software Setup
1. Open `AirFilter.ino` in Arduino IDE or PlatformIO.
2. Select target board: `NodeMCU 1.0 (ESP-12E Module)`.
3. Install required libraries via Library Manager:
   - `ESP8266WiFi`
   - `ThingSpeak` by MathWorks
   - `LiquidCrystal_I2C` by Frank de Brabander
   - `SoftwareSerial` (Included with ESP8266 core)
4. Update WiFi credentials (`WIFI_SSID`, `WIFI_PASSWORD`) and ThingSpeak details (`CHANNEL_ID`, `WRITE_API_KEY`) if needed.
5. Upload sketch to ESP8266.
