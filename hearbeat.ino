#define USE_ARDUINO_INTERRUPTS true
#include <PulseSensorPlayground.h>
#include<LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

byte heart[8] =
{
0b00000,
0b01010,
0b11111,
0b11111,
0b11111,
0b01110,
0b00100,
0b00000
};

const int PulseWire = 0;
const int LED13 = 13;
int Threshold = 550;

PulseSensorPlayground pulseSensor;

void setup() {

Serial.begin(9600);
pinMode(7,INPUT);
digitalWrite(7,HIGH);
lcd.createChar(1, heart);
lcd.begin(16,2);

lcd.print(“Heart Beat “);
lcd.write(1);
lcd.setCursor(0,1);
lcd.print(“Monitering”);

pulseSensor.analogInput(PulseWire);
pulseSensor.blinkOnPulse(LED13);
pulseSensor.setThreshold(Threshold);

if (pulseSensor.begin()) {
Serial.println(“We created a pulseSensor Object !”);
}
}

void loop() {
int myBPM = pulseSensor.getBeatsPerMinute();
//if(!(digitalRead(7))){
//lcd.clear();
// lcd.print(“Please wait…”);

if (pulseSensor.sawStartOfBeat()) {
Serial.println(“♥ A HeartBeat Happened ! “);
Serial.print(“BPM: “);
Serial.println(myBPM);
lcd.clear();
lcd.print(“Heart Beat Rate:”);
lcd.setCursor(0,1);
lcd.print(myBPM);
lcd.print(” “);
lcd.write(1);
}

delay(20);

}

}