#define BLYNK_TEMPLATE_ID "TMPLZ_D-iy3o"                        // Blynk emplate ID
#define BLYNK_DEVICE_NAME "Metal Detector"                      // Device Name in Blynk
#define BLYNK_AUTH_TOKEN "UiR2mwT1_sPZ5KJ-mZTqLzk3kOIrdmKM"     // Access token from Blynk to read and write to Cloud
#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <rgb_lcd.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Shiva";
char passwd[] = "ShIvA@123";

rgb_lcd lcd;

int state = 0;

#define LASER 12

BLYNK_WRITE(V0)
{
  state = param.asInt();
}

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(LASER, OUTPUT);
  Blynk.begin(auth, ssid, passwd);
  lcd.setRGB(200, 0, 0);
  //  lcd.println("   OFF   ");
  lcd.print("Please Turn ON");
  lcd.autoscroll();

  digitalWrite(LASER, HIGH);
  delay(500);
  digitalWrite(LASER, LOW);

}


void loop() {
  // put your main code here, to run repeatedly:
  if (state == HIGH)
  {
    digitalWrite(LASER, HIGH);
    Blynk.virtualWrite(V1, HIGH);
    lcd.setRGB(0, 150, 100);
    //    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Metal Detection System");
    //    delay(100);
  }
  else
  {
    digitalWrite(LASER, LOW);

  }
  for (int positionCounter = 0; positionCounter < 16; positionCounter++) {
    // scroll one position left:
    lcd.scrollDisplayLeft();
    // wait a bit:
    delay(150);
  }

  Blynk.run();
}
