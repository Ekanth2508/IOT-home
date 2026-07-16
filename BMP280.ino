#include <Adafruit_BMP280.h>
#include <Wire.h>

#define SDA 21
#define SCL 22

Adafruit_BMP280 bmp;

void setup() {
  // put your setup code here, to run once:
  Wire.begin(SDA,SCL);
  Serial.begin(115200);
  bmp.begin(0x76);
 bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     // Operating Mode. 
                  Adafruit_BMP280::SAMPLING_X2,     // Temp. oversampling 
                  Adafruit_BMP280::SAMPLING_X16,    // Pressure oversampling 
                  Adafruit_BMP280::FILTER_X16,      // Filtering. 
                  Adafruit_BMP280::STANDBY_MS_500); // Standby time. 
}

void loop() {
  // put your main code here, to run repeatedly:
   float temperature = bmp.readTemperature();
   Serial.print("Temperature: ");
   Serial.print(temperature);
   Serial.println(" °C");

   Serial.print("Pressure: ");
   Serial.print(bmp.readPressure());
   Serial.println(" Pa");

   Serial.print("Altitude: ");
   Serial.print(bmp.readAltitude(1009.25));
   Serial.println(" m"); 


   delay(2000);  // avoids overheading sensing head
}
