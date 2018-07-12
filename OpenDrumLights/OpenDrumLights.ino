#include "MIDIUSB.h"
#include "FastLED.h"

//inputs
int analogIn1 = 3; 
int analogIn2 = 4;

//outputs
int pwmLEDout1 = 6;
int pwmLEDout2 = 7;

int val1 = 0;  
int val2 = 0;
     
#define NUM_LEDS    150
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];

void setup()
{
  Serial.begin(9600);
  pinMode(pwmLEDout1, OUTPUT);
  pinMode(pwmLEDout2, OUTPUT);
  FastLED.addLeds<WS2812B, 6>(leds1, NUM_LEDS);
  FastLED.addLeds<WS2812B, 7>(leds2, NUM_LEDS);
}


void loop()
{
 
  
  val1 = analogRead(analogIn1);
  val2 = analogRead(analogIn2);
  
  if (val1 > 100) {
    //digitalWrite(ledPin, HIGH);
    //FastLED.showColor(CRGB::White);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds1[i] = CRGB::White;
    }
    
    noteOn(0, 48, 100);
  } else {
    //digitalWrite(ledPin, LOW);
    //FastLED.showColor(CRGB::Black);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds1[i] = CRGB::Black;
    }
    
    noteOff(0, 48, 100);
  }

  if (val2 > 100) {
    //digitalWrite(ledPin, HIGH);
    //FastLED.showColor(CRGB::White);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds2[i] = CRGB::Green;
    }
    
    noteOn(0, 49, 100);
  } else {
    //digitalWrite(ledPin, LOW);
    //FastLED.showColor(CRGB::Black);
    for (int i = 0; i < NUM_LEDS; i++) {
      leds2[i] = CRGB::Black;
    }
    
    noteOff(0, 49, 100);
  }
  
  FastLED.show();
  Serial.print(val1);
  Serial.print(",");
  Serial.println(val2);

  
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
