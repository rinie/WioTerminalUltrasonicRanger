/*
    WioTerminalUltrasonicRanger.ino
    Example sketch for ultrasonic ranger with Wio Terminal

    Copyright (c) 2020 Rinie Kervel
    Based on UltrasonicDisplayOnTerm.ino
    and WioTerminal_USB2Serial_Burn8720.ino (LCD and fonts)
    and https://wiki.seeedstudio.com/Grove-Ultrasonic_Ranger/#play-with-wio-terminal-ardupy

    Change Log :

    The MIT License (MIT)

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.
*/


/***************************************************************************/
//	Function: Measure the distance to obstacles in front and print the distance
//			  value to the serial terminal.The measured distance is from
//			  the range 0 to 400cm(157 inches).
//	Hardware: Grove - Ultrasonic Ranger
//	Arduino IDE: Arduino-1.8.12
/*****************************************************************************/
#include "TFT_eSPI.h"
#include "Free_Fonts.h" //include the header file
#include "Ultrasonic.h"
TFT_eSPI tft;
//TFT_eSprite spr(&tft);

Ultrasonic ultrasonic(0);
static long RangeInCentimeters;
static long RangeInInches;
static long PrevRangeInCentimeters;
static long PrevRangeInInches;

void setup() {
    Serial.begin(115200);
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK); //Black background
    tft.setFreeFont(FSSBO12);  //select Free, Sans, Bold, Oblique, 12pt.
	tft.setTextColor(TFT_RED);
	tft.drawString("Ultrasonic Sensor", 55, 10);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("- Centimeters: ", 20, 50);
	tft.drawString("- Inches: ", 20, 80);
}

void loop() {
	RangeInCentimeters = ultrasonic.MeasureInCentimeters();
	if (PrevRangeInCentimeters != RangeInCentimeters) {
		if (PrevRangeInCentimeters > RangeInCentimeters) {
			tft.drawString("        ", 200, 50);
		}
		tft.drawNumber(RangeInCentimeters, 200,50);
		PrevRangeInCentimeters = RangeInCentimeters;
		Serial.print("The distance to obstacles in front is: ");
		Serial.print(RangeInCentimeters);
		Serial.println(" centimeter");
	}
	delay(250); // Needed for data to be read again
	RangeInInches = ultrasonic.MeasureInInches();
	if (PrevRangeInInches != RangeInInches) {
		if (PrevRangeInInches > RangeInInches) {
			tft.drawString("        ", 130, 80);
		}
		tft.drawNumber(RangeInInches, 130,80);
		PrevRangeInInches = RangeInInches;
		Serial.print("The distance to obstacles in front is: ");
		Serial.print(RangeInInches);
		Serial.println(" inches");
	}
	delay(250);

}
