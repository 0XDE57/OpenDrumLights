# Open Drum Lights

An open source reactive drum lighting and midi project.


### Libraries
* [FastLED](http://fastled.io/)
* [MIDIUSB](https://www.arduino.cc/en/Reference/MIDIUSB)
 


## Building the Hardware

#### components
* Microcontroller: Arduino Due
* Power supply: 5V-12V @ 3A-5A (depends on LED type and amount)
	* Must be enough current to power the LED's. 
	
    	> In our case we are using WS2812B which draw about ~60mA @ 5V per led (white & full brightness). Using 5 x 144LED/M (LED per Meter) strips our worst case scenario is 60mA * 144 LED's * 5 strips = ~4.3A. Realistic usage is typically much lower as draw is dependent on color, brightness level, and not the full strip was used in each drum due to trimming the strip for the diameter of the drum. Also during typical usage not all strips are on at the same time. Usually only 1 or 2 as they are triggered. Average draw may look like ~2A at a given time.
	
	* A power draw estimate per drum (worst case scenario white color @ full brightness):
    
	    | Drum Diameter  | LED per meter | Power draw |
		| ------------- | --------- | --------- |
		| x" | x | ~x.xA |
* Voltage Regulator: 5V @ 3A-5A buck converter 
	* exact output required will depend on LED type and amount
	
    	> **note:** We found in our testing that a linear regulator such as an LM317 or LM1084 is not recommended as they will dissipate excess energy as heat. In our case a 12v supply -> 12V-5V=7v. Power = 7Vx5A = 35W dissipated as heat. Ouch.  

* PER DRUM:
	* LED Strip
	* Piezoelectric Sensor
	* 100Ω-500Ω resistor
	* 1MΩ resistor 




------------------------------------------------------------------
### Trouble Shooting

#### Lights
If you find the lights to be turning on and off, flickering randomly, or otherwise behaving incorrectly, this usually a symptom of:
* **software** - ensure correct LED type is used and supported eg:

	| LED Type  | Code |
	| ------------- | ------------- |
	|WS2812B | `FastLED.addLeds<WS2812B, outputPin>(leds, NUM_LEDS);`|
	|NEOPIXEL |`FastLED.addLeds<NEOPIXEL, outputPin>(leds, NUM_LEDS);`|
    |TM1809 |`FastLED.addLeds<TM1809, outputPin>(leds, NUM_LEDS);`|
	https://github.com/FastLED/FastLED#supported-led-chipsets
* **timing issues** - some Arduino's cannot handle the timing of PWM output and serial input at the same time. See interrupts: </br> https://github.com/FastLED/FastLED/wiki/Interrupt-problems

* **power delivery** 
  	* input specifications - check the specs of your led lights/strips, ensure they are receiving the correct voltage. Incorrect input voltage may cause strange behavior or destroy the LED's.	
	* multiple strips / many led's - if powering a large amount of LED's, external power source will be required to drive them.
	* external power - if lights are powered with an external power supply instead of from the arduino's, the ground from the external power also needs to go to the ground pin of the arduino. Also recommended to use a voltage regulator to cap input voltage to LED's.
	* recommend placing a 100-500 Ohm resistor between the microcontroller's data output PWM pin and the data input of the LED strip to protect from voltage spikes.

#### Piezoelectric Vibration Sensors (triggers)
If you find the analog value read from the sensor to continually rise or lower in value or otherwise be unstable 
and inconsistent while no vibration is occurring, place a resistor in parallel for why?
https://learn.sparkfun.com/tutorials/piezo-vibration-sensor-hookup-guide

Drums not triggering or triggering too often -> sensitivity tuning with thresholds


## Alternatives
Using other led stips such as neopixel...
Using microphones instead of Piezoelectric sensors: https://learn.adafruit.com/gemma-powered-neopixel-led-sound-reactive-drums


### TODO: DMX support...
http://playground.arduino.cc/Learning/DMX
https://playground.arduino.cc/DMX/Ardmx

https://resolume.com/support/en/dmx#using-a-manual-ip