  // feed time 0900hrs
  // Blue LED blinking - wifi connected, failied to obtain time
  // blue LED on when NOT connected to wifi

#include <ESP32Servo.h>
#include <WiFiMulti.h>
#include <time.h>

// Wifi details
#define SSID "******"
#define PASS "********"

// On board status led
int LED = 8;

//Time for feeding
int feedHour = 9;
int feedMinute = 0;

//Logic runners 
int previousMinute=-1;

//Wifi stuff 

WiFiMulti wifiMulti;
unsigned long lastPrint = 0;


Servo feederServo;

int servoPin = 5;

// Servo positions
int closedPos = 85;
int openPos = 125;

// Shake range
int shakeLeft = 65;
int shakeRight = 105;

// ====================

void setup() {

  Serial.begin(115200);
  pinMode(LED, OUTPUT);
  wifiMulti.addAP(SSID, PASS);
  Serial.println("Connecting to WiFi...");
  // Reconnecting logic
  while (wifiMulti.run() != WL_CONNECTED) {

    Serial.print(".");

    delay(200);
  }

  Serial.println();
  Serial.println("WiFi Connected");

  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  configTime(19800, 0, "pool.ntp.org");

  feederServo.setPeriodHertz(50);

  // Attach servo initially
  feederServo.attach(servoPin, 500, 2400);

  // Move to closed position
  feederServo.write(closedPos);

  Serial.println("Fish feeder started");

  delay(1000);

  // Detach to reduce heating
  feederServo.detach();
}

void loop() {

// Wifi status check logic
 wifiMulti.run();
  digitalWrite(LED, WiFi.status() == WL_CONNECTED );  
  if (millis() - lastPrint >= 1000) {

    lastPrint = millis();

    struct tm timeinfo;

    if (getLocalTime(&timeinfo)) {

      Serial.println(&timeinfo, "%A %H:%M:%S");
      int currentHour = timeinfo.tm_hour;
      int currentMinute = timeinfo.tm_min;
      int currentDay = timeinfo.tm_wday;
      if (currentMinute != previousMinute){
        previousMinute = currentMinute;
        
        // Not feeding on Sunday 0=Sunday, 0-6 days of the week
        if (currentHour == feedHour && currentMinute == feedMinute && currentDay != 0){ 
          Serial.println("feed time");
          feedFish();
          

        }

      }

    }

    else {

      Serial.println("Failed to obtain time");
      digitalWrite(LED,HIGH);
      delay(500);
      digitalWrite(LED,LOW);
      delay(500);
    }
  }
}


// ===== FEED FUNCTION =====
void feedFish() {

  // Re-attach servo before movement
  feederServo.attach(servoPin, 500, 2400);

  Serial.println("VIOLENT SHAKING");

  // ===== STRONG VIBRATION =====
  for (int i = 0; i < 40; i++) {

    feederServo.write(shakeLeft);
    delay(20);

    feederServo.write(shakeRight);
    delay(20);
  }

  delay(300);

  // ===== OPEN FEEDER =====
  Serial.println("OPENING");

  feederServo.write(openPos);

  // Food dispensing time             
  delay(100);

  // ===== CLOSE FEEDER =====
  Serial.println("CLOSING");

  feederServo.write(closedPos);

  // Give servo time to settle
  delay(300);

  // Detach servo to reduce heating
  feederServo.detach();

  Serial.println("Servo detached");
  Serial.println("Cycle complete");
}
