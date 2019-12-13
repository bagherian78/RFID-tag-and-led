/*yohahaha
 * i'm here with a project for my daughter project's
 * first i find pins from below table
 * Typical pin layout used:
   -----------------------------------------------------------------------------------------
               MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
               Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
   Signal      Pin          Pin           Pin       Pin        Pin              Pin
   -----------------------------------------------------------------------------------------
   RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
   SPI SS      SDA(SS)      10            53        D10        10               10
   SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
   SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
   SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 *after that i most connect leds to pin 6,7
 *for first time u can run this program and after see member id in serial monitor 
 *add it to memberID
 */
 
#include <SPI.h>
#include <MFRC522.h>
// set pins
#define ResetPin 9
#define CSPin 10

String memberID = "43C939A"; //set your cart id here!!!!
String tagID = "";
MFRC522 RFIDmodule(CSPin, ResetPin);

boolean readTagID()
{
  if (!RFIDmodule.PICC_IsNewCardPresent())
    return false;
  if (!RFIDmodule.PICC_ReadCardSerial())
    return false;
  tagID = "";
  for (uint8_t i = 0; i < 4; i++)
    tagID.concat(String(RFIDmodule.uid.uidByte[i], HEX));
  tagID.toUpperCase();
  RFIDmodule.PICC_HaltA();
  return true;
}

void setup()
{
  Serial.begin(9600);
  SPI.begin();
  RFIDmodule.PCD_Init();
  Serial.println("Approximate your RFID tag ...");
  Serial.println("");
  pinMode(7,OUTPUT);
  pinMode(6,OUTPUT);
}
void loop()
{
  while (readTagID())
  {
    if (tagID == memberID)
    {
      Serial.println("You're Welcome!");
      for (int j=0;j<=3;j++){
         digitalWrite(6,HIGH);
         delay(300);
         digitalWrite(6,LOW);
         delay(300);
      }
      
    }
    else
    {
      Serial.println("You're not registered!");
      for(int i = 0;i<=4;i++){
      digitalWrite(7,HIGH);
      delay(400);
      digitalWrite(7,LOW);
      delay(400);
      }
    }
    Serial.print(" ID : ");
    Serial.println(tagID);
    Serial.println("");
    delay(1000);
    Serial.println("Approximate your RFID tag ...");
    Serial.println("");
  }
}
