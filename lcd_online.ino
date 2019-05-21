#include <SPI.h>
#include <MFRC522.h>
#include <LiquidCrystal.h>

#define RST_PIN 9
#define SS_PIN 10

MFRC522 mfrc522(SS_PIN, RST_PIN);

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
int a;
void setup()
{


SPI.begin();
mfrc522.PCD_Init();
Serial.begin(9600);
lcd.begin(16, 2);
Serial.println("Scan your Tag");
}

void loop() {
RfidScan();
}


String dump_byte_array(byte *buffer, byte bufferSize) {
 unsigned long uiddec = 0;
for (byte i = (bufferSize > 4 ? (bufferSize - 4) : 0); i < bufferSize; i++) {
unsigned long k = 1;
for (int j = 0; j < bufferSize - i - 1; j++){
  k = k*256;
    
}
uiddec += k * buffer[i];

}
return String(uiddec);

}

void RfidScan(){
lcd.setCursor(0,0);
lcd.print("Scan your Tag");
if ( ! mfrc522.PICC_IsNewCardPresent())
{
  return;
}
if ( ! mfrc522.PICC_ReadCardSerial())
{
  return;
}

String content = "";
content = dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
Serial.print("UID: ");
lcd.setCursor(0,1);
lcd.print("UID:");

Serial.print(mfrc522.uid.uidByte[a] < 0x10 ? " 0" : " ");
Serial.print(content);
lcd.print(content);
delay(700);
lcd.clear();
Serial.println();
 
}
