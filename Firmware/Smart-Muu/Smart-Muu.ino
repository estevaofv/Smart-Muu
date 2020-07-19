
#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define DELAY_MOCKUP  10000

#define QTD_ANIMAIS   V2
#define ANIMAIS       14
#define LOCATION      V0
#define TEMPERATURE   V4
#define TEMP_VALUE    36
#define PESO          V5
#define PESO_VALUE    "850 Kg"
#define MOVIMENTACAO  V6
#define MOVIMENTADO   "3.3 Km"
#define SELECT_ANIMAL V3
#define ALARME        V7
#define SAUDE         V1
#define NIVEL_SAUDE   95





//const int TAMPER_PIN = 4;  // SENSOR DE RUPTURA
//const int BUZZER_PIN = 5;  // BUZZER


int TamperState = 1;
//float lon[10] = { -49.265743, -49.261443, -49.261243, -49.26273, -49.26164, -49.26674, -49.266743, -49.261763, -49.262743, -49.26193};
//float lat[10] = { -16.667587, -16.667687, -16.667287, -16.666087, -16.667487, -16.661087, -16.667057, -16.662087, -16.664087, -16.667687};
//loat lat[41] = {-18.736893,-18.736815,-18.736756,-18.736719,-18.736707,-18.736783,-18.736955,-18.736918,-18.736893,-18.736822,-18.736832,-18.736843,-18.736812,-18.736789,-18.736970,-18.736950,-18.736998,-18.737040,-18.736947,-18.736997,-18.737017,-18.736952,-18.736972,-18.736574,-18.736508,-18.736523,-18.735928,-18.735211,-18.732545,-18.732508,-18.732519,-18.732516,-18.732480,-18.732493,-18.732484,-18.732415,-18.732413,-18.731669,-18.864602,-18.864613,-18.864624};
float lat[14] = { -18.736893, -18.736949, -18.736776, -18.736504, -18.736519, -18.735917, -18.735191, -18.732597, -18.732491, -18.732473, -18.732478, -18.732615, -18.731652, -18.864933};
//float lon[41] = {-48.979856,-48.979818,-48.979966,-48.980074,-48.980103,-48.980129,-48.980091,-48.980113,-48.980128,-48.980180,-48.980204,-48.980221,-48.980233,-48.980240,-48.980144,-48.980179,-48.980179,-48.980114,-48.980266,-48.980295,-48.980307,-48.980408,-48.980464,-48.979912,-48.980003,-48.980490,-48.979541,-48.979640,-48.979296,-48.979306,-48.979348,-48.979365,-48.979336,-48.979195,-48.978741,-48.979280,-48.979297,-48.975832,-48.870356,-48.870378,-48.870406};
float lon[14] = { -48.979852, -48.980406, -48.980247, -48.980000, -48.980492, -48.979541, -48.979643, -48.979379, -48.979194, -48.979346, -48.978742, -48.977681, -48.975914, -48.870284};
//String Animal_Name[41] = {"A:12354", "A:14512", "A:12785", "A:16584", "A:98554", "A:18542", "A:18544", "A:18952", "A:12370", "A:12360","A:12355", "A:14513", "A:12786", "A:16585", "A:98555", "A:18543", "A:18555", "A:18953", "A:12371", "A:12361","A:12356", "A:14514", "A:12787", "A:16586", "A:98556", "A:18546", "A:18548", "A:18954", "A:12372", "A:12362","A:12357", "A:14515", "A:12788", "A:16587", "A:98557", "A:18545", "A:18547", "A:18955", "A:12373", "A:12363","A:12364"};
String Animal_Name[14] = {"A:12354", "A:14512", "A:12785", "A:16584", "A:98554", "A:18542", "A:18544", "A:18952", "A:12370", "A:12360", "A:12355", "A:14513", "A:12786", "A:16585"};
int index_Type = 1;

const int BUZZER_PIN = 5;
const int TAMPER_PIN = 4;

BlynkTimer timer;
void checkPhysicalTamper();

int buzzerState = LOW;
int tamperState = HIGH;

//// Every time we connect to the cloud...
//BLYNK_CONNECTED() {
//  // Request the latest state from the server
//  Blynk.syncVirtual(ALARME);
//
//  // Alternatively, you could override server state using:
//  //Blynk.virtualWrite(ALARME, buzzerState);
//}
//
//// When App button is pushed - switch the state
//BLYNK_WRITE(ALARME) {
//  buzzerState = param.asInt();
//  digitalWrite(BUZZER_PIN, buzzerState);
//}

void checkPhysicalTamper()
{
  if (digitalRead(TAMPER_PIN) == LOW) {
    // tamperState is used to avoid sequential toggles
    if (tamperState != LOW) {

      // Toggle LED state
      buzzerState = !buzzerState;
      digitalWrite(BUZZER_PIN, buzzerState);

      // Update Button Widget
      Blynk.virtualWrite(ALARME, buzzerState);
    }
    tamperState = LOW;




  } else {
    tamperState = HIGH;
    digitalWrite(BUZZER_PIN, HIGH); //Conexão do tamper rompida

  }
}


WidgetMap myMap(LOCATION);


void populateMap() {
  //  //Localização
  for (int i = 0; i < 14; i++) {
    myMap.location(i, lat[i], lon[i], Animal_Name[i]);
    //delay(200);
  }
}


BLYNK_WRITE(SELECT_ANIMAL) {
  switch (param.asInt())
  {
    case 1: // Item 1
      Serial.println("Item 1 selected");
      myMap.clear();
      myMap.location(0, lat[0], lon[0], Animal_Name[0]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;
    case 2: // Item 2
      Serial.println("Item 2 selected");
      myMap.clear();
      myMap.location(1, lat[1], lon[1], Animal_Name[1]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;
    case 3: // Item 3
      Serial.println("Item 3 selected");
      myMap.clear();
      myMap.location(2, lat[2], lon[2], Animal_Name[2]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;
    case 4: // Item 4
      Serial.println("Item 4 selected");
      myMap.clear();
      myMap.location(3, lat[3], lon[3], Animal_Name[3]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;
    case 5: // Item 5
      Serial.println("Item 5 selected");
      myMap.clear();
      myMap.location(4, lat[4], lon[4], Animal_Name[4]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;
    case 6: // Item 6
      Serial.println("Item 6 selected");
      myMap.clear();
      myMap.location(5, lat[5], lon[5], Animal_Name[5]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;
    case 7: // Item 7
      Serial.println("Item 7 selected");
      myMap.clear();
      myMap.location(6, lat[6], lon[6], Animal_Name[6]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;

    case 8: // Item 8
      Serial.println("Item 8 selected");
      myMap.clear();
      myMap.location(7, lat[7], lon[7], Animal_Name[7]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;

    case 9: // Item 9
      Serial.println("Item 9 selected");
      myMap.clear();
      myMap.location(8, lat[8], lon[8], Animal_Name[8]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;

    case 10: // Item 10
      Serial.println("Item 10 selected");
      myMap.clear();
      myMap.location(9, lat[9], lon[9], Animal_Name[9]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;

    case 11: // Item 11
      Serial.println("Item 11 selected");
      myMap.clear();
      myMap.location(10, lat[10], lon[10], Animal_Name[10]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;

    case 12: // Item 12
      Serial.println("Item 12 selected");
      myMap.clear();
      myMap.location(11, lat[11], lon[11], Animal_Name[11]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;

    case 13: // Item 13
      Serial.println("Item 13 selected");
      myMap.clear();
      myMap.location(12, lat[12], lon[12], Animal_Name[12]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;

    case 14: // Item 14
      Serial.println("Item 14 selected");
      myMap.clear();
      myMap.location(13, lat[13], lon[13], Animal_Name[13]);
      delay(DELAY_MOCKUP);
      populateMap();
      break;

    default:
      Serial.println("Unknown item selected");
  }
}



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
  populateMap();


  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(TAMPER_PIN, INPUT);
  //digitalWrite(BUZZER_PIN, buzzerState);

  //timer.setInterval(100L, checkPhysicalTamper);

}

void loop()
{

  TamperState = digitalRead(TAMPER_PIN);

  if (TamperState == HIGH) {

    digitalWrite(BUZZER_PIN, HIGH); //Conexão do tamper rompida

  } else {
    digitalWrite(BUZZER_PIN, LOW); //Conexão do tamper normal
    Blynk.notify("Lacre Rompido! Possível violação do sensor ou tentativa de furto!");
    myMap.clear();
    myMap.location(0, lat[0], lon[0], Animal_Name[0]);
    //delay(DELAY_MOCKUP);
    Blynk.virtualWrite(ALARME, HIGH);
  }

  Blynk.run();

  //Quantidade Animais
  Blynk.virtualWrite(QTD_ANIMAIS, ANIMAIS);

  //Temperatura do animal
  Blynk.virtualWrite(TEMPERATURE, TEMP_VALUE);

  //Peso do animal
  Blynk.virtualWrite(PESO, PESO_VALUE);


  //Peso do animal
  Blynk.virtualWrite(MOVIMENTACAO, MOVIMENTADO);

  //Saúde
  Blynk.virtualWrite(SAUDE, NIVEL_SAUDE);


  //bar-graph
  Blynk.virtualWrite(V20, 3300);
  Blynk.virtualWrite(V60, 850);
  Blynk.virtualWrite(V70, 36);


  //delay(DELAY_MOCKUP);








}
