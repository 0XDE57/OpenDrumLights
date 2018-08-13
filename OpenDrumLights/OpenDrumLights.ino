#include "MIDIUSB.h"
#include "FastLED.h"

//piezo inputs
#define analogIn1 1
#define analogIn2 2
#define analogIn3 3
#define analogIn4 4
int val1 = 0;  
int val2 = 0;
int val3 = 0;
int val4 = 0;

//led outputs
#define pwmLEDout1 2
#define pwmLEDout2 3
#define pwmLEDout3 4
#define pwmLEDout4 5
#define NUM_LEDS 150
CRGB leds1[NUM_LEDS];
CRGB leds2[NUM_LEDS];
CRGB leds3[NUM_LEDS];
CRGB leds4[NUM_LEDS];

void setup()
{
  Serial.begin(9600);
  pinMode(pwmLEDout1, OUTPUT);
  pinMode(pwmLEDout2, OUTPUT);
  pinMode(pwmLEDout3, OUTPUT);
  pinMode(pwmLEDout4, OUTPUT);
  FastLED.addLeds<WS2812B, pwmLEDout1>(leds1, NUM_LEDS);
  FastLED.addLeds<WS2812B, pwmLEDout2>(leds2, NUM_LEDS);
  FastLED.addLeds<WS2812B, pwmLEDout3>(leds3, NUM_LEDS);
  FastLED.addLeds<WS2812B, pwmLEDout4>(leds4, NUM_LEDS);
}


void loop()
{
 
  
  val1 = analogRead(analogIn1);
  val2 = analogRead(analogIn2);
  val3 = analogRead(analogIn3);
  val4 = analogRead(analogIn4);
  
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


if (val3 > 100) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds3[i] = CRGB::Red;
    }   
    noteOn(0, 50, 100);
  } else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds3[i] = CRGB::Black;
    }
    
    noteOff(0, 50, 100);
  }

  if (val4 > 100) {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds4[i] = CRGB::Blue;
    }
    
    noteOn(0, 51, 100);
  } else {
    for (int i = 0; i < NUM_LEDS; i++) {
      leds4[i] = CRGB::Black;
    }
    
    noteOff(0, 51, 100);
  }
  
  FastLED.show();

  
  Serial.print(val1);
  Serial.print(",");
  Serial.print(val2);
  Serial.print(",");
  Serial.print(val3);
  Serial.print(",");
  Serial.println(val4); 
}

void noteOn(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
}

void noteOff(byte channel, byte pitch, byte velocity) {
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
}
