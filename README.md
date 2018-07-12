# Open Drum Lights

An open source reactive drum lighting and midi project.


### Libraries
* [FastLED](http://fastled.io/)
* [MIDIUSB](https://www.arduino.cc/en/Reference/MIDIUSB)
 


## Building the Hardware

#### components


------------------------------------------------------------------
### Trouble Shooting

#### Lights
If you find the lights to be turning on and off, flickering randomly, or otherwise behaving incorrectly, this usually a symptom of:
* **software** - ensure correct LED type is used and supported eg:

	| LED Type  | Code |
	| ------------- | ------------- |
	|WS2812B | `FastLED.addLeds<WS2812B, outputPin>(leds, NUM_LEDS);`|
	|NEOPIXEL |`FastLED.addLeds<NEOPIXEL, outputPin>(leds, NUM_LEDS);`|
	https://github.com/FastLED/FastLED#supported-led-chipsets
* **timing issues** - some Arduino's cannot handle the timing of PWM output and serial input at the same time. See interrupts: </br> https://github.com/FastLED/FastLED/wiki/Interrupt-problems

* **power delivery** 
  	* input specifications - check the specs of your led lights/strips, ensure they are receiving the correct voltage. Incorrect input voltage may cause strange behavior or destroy the LED's.	
	* multiple strips / many led's - if powering a large amount of LED's, external power source will be required to drive them.
	* external power - if lights are powered with an external power supply instead of from the arduino's, the ground from the external power also needs to go to the ground pin of the arduino. Also recommended to use a voltage regulator to cap input voltage to LED's.
	* recommend placing a 300-500 Ohm resistor between the microcontroller's data output PWM pin and the data input of the LED strip to protect from voltage spikes.

#### Piezoelectric Vibration Sensors (triggers)
If you find the analog value read from the sensor to continually rise or lower in value or otherwise be unstable 
and inconsistent while no vibration is occuring, place a resistor in parralel for why?
https://learn.sparkfun.com/tutorials/piezo-vibration-sensor-hookup-guide

Drums not triggering or triggering too often -> sensitivity tuning with thresholds


## Alternatives
Using other led stips such as neopixel...
Using microphones instead of Piezoelectric sensors: https://learn.adafruit.com/gemma-powered-neopixel-led-sound-reactive-drums


### TODO: implement DMX support for show lighting integration
https://playground.arduino.cc/DMX/Ardmx

https://resolume.com/support/en/dmx#using-a-manual-ip