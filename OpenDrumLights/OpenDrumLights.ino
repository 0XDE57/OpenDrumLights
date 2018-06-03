#include "MIDIUSB.h"
#include "FastLED.h"

int analogPin = 3;  
int ledPin = 6;

int val = 0;  
     
#define NUM_LEDS    150
CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  FastLED.addLeds<WS2812B, 6>(leds, NUM_LEDS);
}


void loop() {  
  val = analogRead(analogPin);
  
  if (val > 100) {
     //digitalWrite(ledPin, HIGH);
     FastLED.showColor(CRGB::White);
     noteOn(0, 48, 100);
  } else {
     //digitalWrite(ledPin, LOW);
     FastLED.showColor(CRGB::Black);
     noteOff(0, 48, 100);
  }
  
  Serial.println(val);
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
