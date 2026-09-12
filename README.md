# AirFilter - Smart Home Monitoring & Purification System

An end-to-end Air Quality Monitoring & Purification system featuring an **ESP8266 Microcontroller**, **SDS011 Particulate Matter Sensor**, **16x2 I2C LCD**, **ThingSpeak Cloud Integration**, and a modern **Web App & Mobile PWA (Progressive Web App)**.

---

## 🌟 Web & Mobile Application Features

- **Modern Glassmorphic UI**: Minimalist, interactive design tailored for both desktop and mobile smartphones.
- **PWA Mobile App Support**: Can be installed directly onto your Android or iPhone home screen with a single click (**"Install App"**).
- **ThingSpeak Live Cloud Sync**: Automatically fetches live PM2.5 and PM10 telemetry from ThingSpeak Channel `3491820`.
- **Live AQI Gauge & Classification**: Real-time US EPA standard AQI calculator (0–300 range with color-coded status pills: *Good, Moderate, Unhealthy, Hazardous*).
- **Interactive Chart.js Analytics**: Visual time-series graph for PM2.5 & PM10 trends over real-time, 24h, and 7-day intervals.
- **Multi-Room Controller**: Switch between Living Room, Bedroom, Kitchen, and Kids Room monitoring points.
- **Smart Health Advisory Engine**: Provides real-time health recommendations based on current indoor air quality.
- **Auth & User Profile Simulation**: Secure login/registration experience for individual home installations.

---

## 🛠️ Project Structure

```
AirFilter/
├── AirFilter.ino        # ESP8266 Arduino Sketch (Hardware Telemetry & LCD)
├── index.html           # Single Page Application (Landing, Auth, Dashboard)
├── css/
│   └── styles.css       # Design system, glassmorphism, mobile responsive layout
├── js/
│   └── app.js           # Auth, ThingSpeak API engine, AQI math, Chart.js, PWA install
├── manifest.json        # Web App Manifest for mobile installation
├── sw.js                # Service Worker for PWA caching & offline support
├── README.md            # System documentation
└── .gitignore           # Git ignore settings
```

---

## 📱 How to Install the Mobile App on Your Phone

1. Host the project using GitHub Pages or a local web server (e.g. `npx http-server ./`).
2. Open the URL in Google Chrome (Android) or Safari (iOS) on your mobile phone.
3. Tap the **"Install App"** button in the top navigation bar, or select **"Add to Home Screen"** in your browser menu.
4. The **AirFilter** app icon will appear on your phone home screen and open as a standalone app!

---

## ⚡ Hardware Wiring & ESP8266 Setup

| Component | ESP8266 Pin | Function |
| --- | --- | --- |
| PM Sensor TX | D6 (GPIO12) | SoftwareSerial RX |
| PM Sensor RX | D5 (GPIO14) | SoftwareSerial TX |
| LCD SDA | D2 (GPIO4) | Hardware I2C SDA |
| LCD SCL | D1 (GPIO5) | Hardware I2C SCL |
| VCC / GND | 5V / GND | Power supply |

---

## 🚀 Running locally

To view and test the Web Dashboard locally:

```bash
npx http-server ./
```

Open `http://localhost:8080` in your web browser.
