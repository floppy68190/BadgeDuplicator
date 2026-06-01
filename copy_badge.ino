#include "badge.hpp"

byte copy[64][16];
const int pinButton = 2;
const int pinLed = 3;
int  sound = 500;
boolean lastButton = HIGH;
boolean etat = false;
boolean soundMode = true;
boolean press = false;
Badge badge;
unsigned long start = 0;
unsigned long end = 0;
boolean				check = false;

void setup() {
  // put your setup code here, to run once:
	Serial.begin(9600);
  SPI.begin();
  badge.init();
  pinMode(pinLedValid, OUTPUT);
	pinMode(pinButton, INPUT_PULLUP);
	pinMode(pinLed, OUTPUT);
	pinMode(pinError, OUTPUT);
	pinMode(pinBuzz, OUTPUT);
	for (byte i = 0; i < 64; i++)
		for (byte a = 0; a < 16; a++)
    		copy[i][a] = 0;
	Serial.println("init ok");
}

void loop() {
	byte buffer[18];
	byte size = sizeof(buffer);
	boolean button = digitalRead(pinButton);
	if (!button && !press)
	{
		check = false;
		start = millis();
		press = !press;
	}
	if ( !button && press)
	{
		end = millis();
		Serial.println("lalala");
		if (end - start >= 2000 && (start != 0))
		{
			check = true;
			soundMode = !soundMode;
			if (soundMode)
				tone(pinBuzz, 1000);
			digitalWrite(pinLedValid, HIGH);
			digitalWrite(pinError, HIGH);
			digitalWrite(pinLed, HIGH);
			delay(200);
			noTone(pinBuzz);
			digitalWrite(pinLedValid, LOW);
			digitalWrite(pinError, LOW);
			digitalWrite(pinLed, LOW);
			end = 0;
			start = 0;
		}
	}
	if (press && button)
		press = !press;
	Serial.println(lastButton);
	if (lastButton == LOW &&  button && !check)
	{
	  etat = !etat;
		if (etat)
		{
			if (soundMode)
			{
				for (int i = 0; i < 2; i++)
				{
					tone(pinBuzz, sound);
					delay(100);
					noTone(pinBuzz);
					sound += 200;
				}
				sound = 700;
				Serial.println(sound);
			}
		}
		else
		{
			if (soundMode)
			{
				for (int i = 0; i < 2; i++)
				{
					tone(pinBuzz, sound);
					delay(100);
					noTone(pinBuzz);
					sound -= 200;
				}
				sound = 500;
				Serial.println(sound);
			}
		}
	  digitalWrite(pinLed, etat ? HIGH : LOW);
	}
	lastButton = button;
	if (etat)
		badge.write(copy, soundMode);
	else 
	{
		badge.read(copy, soundMode);
	// 	for (byte i = 0; i < 64; i++)
  //   	{
  //   		Serial.print("Block: ");
  //   		Serial.print(i);
  //   		Serial.print(": ");
  //   		for (byte a = 0; a < 16; a++)
  //   		{
  //   			Serial.print(copy[i][a], HEX);
  //   			Serial.print(" ");
  //   		}
  //   		Serial.println();
  //   	}
	// }
  }
}