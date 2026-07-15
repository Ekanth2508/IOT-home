// Red led ON = Not Connected to WiFi
// Red led OFF = Connected to WiFi

#define BLYNK_TEMPLATE_ID "******"
#define BLYNK_TEMPLATE_NAME "*****"
#define BLYNK_AUTH_TOKEN "*******"

#include <BlynkSimpleEsp32.h>
#include <WiFi.h>
#include <WiFiMulti.h>



//GPIO pins
#define Primary_r1 10
#define Secondary_r2 3
#define stat_led  0      // Red WiFi status led

#define ssid "WiFi"
#define pass "PassWord"

WiFiMulti wifiMulti;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); 

  pinMode(Primary_r1, OUTPUT);
  pinMode(Secondary_r2, OUTPUT);
  pinMode(stat_led, OUTPUT);

  // setting relays off intially
  digitalWrite(Primary_r1,LOW);
  digitalWrite(Secondary_r2,LOW);
  
  //client mode
  WiFi.mode(WIFI_STA);
  delay(100);

  wifiMulti.addAP(ssid,pass);
  while (wifiMulti.run() != WL_CONNECTED){
    digitalWrite(stat_led, HIGH);
    delay(500);


  }
  Serial.println("\n CONNECTED");
  digitalWrite(stat_led, LOW);

  Blynk.config(BLYNK_AUTH_TOKEN);
  if (Blynk.connect()){
    Serial.println("Blynk Connected");
    Blynk.syncVirtual(V0);
    Blynk.syncVirtual(V1);
    
  }
  else{
    Serial.println("Blynk Connection Failed");
  }

}


void loop() {
  if(!Blynk.connected()){
    Blynk.connect();
  }
  Blynk.run();
  }
  
  BLYNK_WRITE(V0){
    int state = param.asInt();
    if (state==1){
      digitalWrite(Primary_r1,HIGH);
      Serial.println("Relay 1 ON");
    }
    else{
      digitalWrite(Primary_r1,LOW);
    }
  }

  BLYNK_WRITE(V1){
    int state = param.asInt();
    if (state==1){
      digitalWrite(Secondary_r2,HIGH);
      Serial.println("Relay 2 ON");
    }
    else{
      digitalWrite(Secondary_r2,LOW);
    }
  }










 

