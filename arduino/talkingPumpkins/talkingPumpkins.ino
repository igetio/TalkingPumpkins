
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(10, 11); // RX, TX
int myPins[] = {2, 3, 4, 5, 6}; // pins for the pumpkins
int inPIR = 7; //pin for the PIR sensor
int serialIn; // stores serial values from Pi
int lastPick = 100; //variable for last dialogue played
int currPick; //current dialogue choosen for playback

void setup()
{
 // Initializes output pins for pumpkins
  for (int pinNum = 0; pinNum < 5; pinNum++){
    pinMode(myPins[pinNum], OUTPUT);
  }
  Serial.begin (9600);
  mySerial.begin (9600);
  mp3_set_serial (mySerial);	//set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (20);
  pinMode(inPIR, INPUT); // intialize PIR sensor pin
  randomSeed(analogRead(9)); // seeds the random function to give more "random" results
}

void loop() {
  // Checks if the PIR is seeing motion and the pumpkins are currently not talking
  if (digitalRead(inPIR) == HIGH){
    currPick = random(5); // selects which dialogue chain to run
    Serial.println(currPick);
    // check to make sure that the last chain is not repeated
    if (currPick != lastPick){
      lastPick = currPick;
      Serial.println("Ready to run the pumpkins");
      runPumpkinSrcipt(currPick);
    }

  }
}

void lightPumpkins(String pumpkins, int track) {
  //loops through serial string and sets pumpkins to either talking or idle
  for (int i = 0; i < 5; i++){ 
    if (pumpkins[i] == '1'){ //sets pumpkin to talking
      digitalWrite(myPins[i], HIGH);
    }else{ //sets pumpkins to idle
      digitalWrite(myPins[i], LOW);
    }
  }
  if (pumpkins != "00000" ) {
    Serial.println("Playing a track");
    mp3_play (track);
    delay(100);
    int var = 1;
    while(digitalRead(12) == LOW){
      delay(100);
    }
  }
  delay(200);
}

void runPumpkinSrcipt (int pick) {
  if (pick == 0) {
    Serial.println("Pumpkin script 0");
    lightPumpkins("00100",1);
    lightPumpkins("10000",2);
    lightPumpkins("00100",3);
    lightPumpkins("00001",4);
    lightPumpkins("10000",5);
    lightPumpkins("00001",6);
    lightPumpkins("00000",0);
  }

  if (pick == 1) {
    Serial.println("Pumpkin script 1");
    lightPumpkins("00100",101);
    lightPumpkins("01000",102);
    lightPumpkins("00100",103);
    lightPumpkins("01000",104);
    lightPumpkins("10000",105);
    lightPumpkins("01100",106);
    lightPumpkins("00000",0);
  }
  
  if (pick == 2) {
    Serial.println("Pumpkin script 2");
    lightPumpkins("11111",201);
    lightPumpkins("00100",202);
    lightPumpkins("00010",203);
    lightPumpkins("00000",0);
  }

  if (pick == 3) {
    Serial.println("Pumpkin script 3");
    lightPumpkins("00001",301);
    lightPumpkins("01000",302);
    lightPumpkins("00100",303);
    lightPumpkins("01000",304);
    lightPumpkins("00001",305);
    lightPumpkins("00000",0);
  }

  if (pick == 4) {
    Serial.println("Pumpkin script 4");
    lightPumpkins("00010",401);
    lightPumpkins("00100",402);
    lightPumpkins("00010",403);
    lightPumpkins("00100",404);
    lightPumpkins("00010",405);
    lightPumpkins("00100",406);
    lightPumpkins("00000",0);
  }
}
