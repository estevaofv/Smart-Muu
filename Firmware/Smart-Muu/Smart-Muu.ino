
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DELAY_MOCKUP  10000

#define QTD_ANIMAIS   V2
#define ANIMAIS       10
#define LOCATION      V0
#define TEMPERATURE   V4
#define TEMP_VALUE    36
#define PESO          V5
#define PESO_VALUE    "850 Kg"


float lon[10] = {-49.265743, -49.261443, -49.261243, -49.26273, -49.26164, -49.26674, -49.266743, -49.261763, -49.262743, -49.26193};
float lat[10] = {-16.667587, -16.667687, -16.667287, -16.666087, -16.667487, -16.661087, -16.667057, -16.662087, -16.664087, -16.667687};
String Animal_Name[10] = {"A:12354", "A:14512", "A:12785", "A:16584","A:98554", "A:18542","A:18544", "A:18952","A:12370", "A:12360"};
int index_Type =1;

WidgetMap myMap(LOCATION);
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "nzbz1Bpj52lzhkjPSptjznXgSVfAsSqx";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "ALHN-0D56";
char pass[] = "5047254679";

void setup()
{
  // Debug console
  Serial.begin(115200);

  Blynk.begin(auth, ssid, pass);

//  //Localização  
  for (int i=0; i < 10; i++){
    myMap.location(i, lat[i], lon[i], Animal_Name[i]);
    delay(200);
  }
}

void loop()
{
  Blynk.run();

  //Quantidade Animais
  Blynk.virtualWrite(QTD_ANIMAIS, ANIMAIS);

  //Temperatura do animal
  Blynk.virtualWrite(TEMPERATURE, TEMP_VALUE);
  
  
  //Peso do animal
  Blynk.virtualWrite(PESO, PESO_VALUE);
  
  delay(DELAY_MOCKUP);


 
  
  
}
