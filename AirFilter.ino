#include <ESP8266WiFi.h>
#include <ThingSpeak.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// ---------- WiFi ----------
const char* WIFI_SSID = "POCO X3";
const char* WIFI_PASSWORD = "1234567890";

// ---------- ThingSpeak ----------
unsigned long CHANNEL_ID = 3491820;

// Put your NEW Write API Key here
const char* WRITE_API_KEY = "UT3XLNOAPUNBOKT3";

// ---------- PM Sensor ----------
// Sensor TX -> D6 (GPIO12)
// Sensor RX -> D5 (GPIO14)
SoftwareSerial pmSerial(D6, D5);

// ---------- LCD ----------
// SDA -> D2 (GPIO4)
// SCL -> D1 (GPIO5)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------- WiFi Client ----------
WiFiClient client;

// ---------- PM values ----------
float PM25 = 0;
float PM10 = 0;

unsigned long lastUpload = 0;
const unsigned long uploadInterval = 20000;

// Function Prototypes
bool readPM();
void showLCD();
void connectWiFi();
void uploadData();

// =====================================================
// SETUP
// =====================================================

void setup()
{
  Serial.begin(115200);

  // PM sensor serial
  pmSerial.begin(9600);

  // LCD initialization
  Wire.begin(D2, D1);
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Air Quality");
  lcd.setCursor(0, 1);
  lcd.print("Starting...");
  delay(2000);

  // Connect to WiFi
  connectWiFi();

  // Initialize ThingSpeak
  ThingSpeak.begin(client);

  lcd.clear();
  lcd.print("Sensor Ready");
  delay(1000);
}

// =====================================================
// LOOP
// =====================================================

void loop()
{
  if (readPM())
  {
    // Print to Serial Monitor
    Serial.print("PM2.5: ");
    Serial.print(PM25);
    Serial.println(" ug/m3");

    Serial.print("PM10 : ");
    Serial.print(PM10);
    Serial.println(" ug/m3");

    // Update LCD screen
    showLCD();

    // Periodic upload to ThingSpeak
    if (millis() - lastUpload >= uploadInterval)
    {
      uploadData();
      lastUpload = millis();
    }
  }

  delay(100);
}

// =====================================================
// READ PM SENSOR (SDS011 Packet Protocol)
// =====================================================

bool readPM()
{
  uint8_t data[10];

  // Wait for start byte AA
  if (pmSerial.available())
  {
    if (pmSerial.read() != 0xAA)
      return false;

    // Wait for second byte C0
    unsigned long start = millis();

    while (!pmSerial.available())
    {
      if (millis() - start > 100)
        return false;
    }

    if (pmSerial.read() != 0xC0)
      return false;

    data[0] = 0xAA;
    data[1] = 0xC0;

    // Read remaining 8 bytes
    for (int i = 2; i < 10; i++)
    {
      start = millis();

      while (!pmSerial.available())
      {
        if (millis() - start > 100)
          return false;
      }

      data[i] = pmSerial.read();
    }

    // Check ending byte
    if (data[9] != 0xAB)
      return false;

    // Check checksum
    uint8_t checksum = 0;

    for (int i = 2; i <= 7; i++)
      checksum += data[i];

    if (checksum != data[8])
      return false;

    // PM2.5 calculation
    int pm25Raw = data[2] | (data[3] << 8);

    // PM10 calculation
    int pm10Raw = data[4] | (data[5] << 8);

    PM25 = pm25Raw / 10.0;
    PM10 = pm10Raw / 10.0;

    return true;
  }

  return false;
}

// =====================================================
// DISPLAY ON LCD
// =====================================================

void showLCD()
{
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("PM2.5:");
  lcd.print(PM25, 1);

  lcd.setCursor(0, 1);
  lcd.print("PM10 :");
  lcd.print(PM10, 1);
}

// =====================================================
// WIFI CONNECTION
// =====================================================

void connectWiFi()
{
  Serial.print("Connecting WiFi");

  lcd.clear();
  lcd.print("Connecting WiFi");

  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  int count = 0;

  while (WiFi.status() != WL_CONNECTED && count < 30)
  {
    delay(500);
    Serial.print(".");
    count++;
  }

  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println();
    Serial.println("WiFi Connected");

    lcd.clear();
    lcd.print("WiFi Connected");

    delay(1000);
  }
  else
  {
    Serial.println();
    Serial.println("WiFi Failed");

    lcd.clear();
    lcd.print("WiFi Failed");

    delay(1000);
  }
}

// =====================================================
// UPLOAD DATA TO THINGSPEAK
// =====================================================

void uploadData()
{
  if (WiFi.status() != WL_CONNECTED)
  {
    connectWiFi();
  }

  // Field 1 = PM2.5
  ThingSpeak.setField(1, PM25);

  // Field 2 = PM10
  ThingSpeak.setField(2, PM10);

  int result = ThingSpeak.writeFields(
    CHANNEL_ID,
    WRITE_API_KEY
  );

  if (result == 200)
  {
    Serial.println("ThingSpeak: Upload successful");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Uploaded");

    delay(1000);

    showLCD();
  }
  else
  {
    Serial.print("ThingSpeak Error: ");
    Serial.println(result);

    lcd.clear();
    lcd.print("Upload Error");

    delay(1000);

    showLCD();
  }
}
