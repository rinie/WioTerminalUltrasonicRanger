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
#include "Free_Fonts.h" //include the header file
#include "Ultrasonic.h"
//TFT_eSprite spr(&tft);

#if defined (ESP32) || (CONFIG_IDF_TARGET_ESP32)
	#if defined( ARDUINO_M5Stick_C )
		#include <LovyanGFX.hpp>
		typedef LGFX TFT;
		static int grovePin = G33;
		static const lgfx::IFont* ffont = FSSBO9;
		struct {
			int x;
			int y;
		} aPos[] = {{0,10}, {0, 30}, {0, 50}, {80, 30}, {80, 50}};
	#endif
#elif defined (__SAMD51__)
 #if defined( LGFX_WIO_TERMINAL ) || defined (ARDUINO_WIO_TERMINAL) || defined(WIO_TERMINAL)
	#include "TFT_eSPI.h"
	typedef	TFT_eSPI TFT;
	static int grovePin = 0;
	static const GFXfont* ffont = FSSBO12;
	struct {
		int x;
		int y;
	} aPos[] = {{55,10}, {20, 50}, {20, 80}, {130, 50}, {130, 80}};
 #endif
#endif

TFT tft;
Ultrasonic ultrasonic(grovePin);

static long RangeInCentimeters;
static long RangeInInches;
static long PrevRangeInCentimeters;
static long PrevRangeInInches;

void setup() {
    Serial.begin(115200);
    tft.begin();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK); //Black background
    tft.setFreeFont(ffont);  //select Free, Sans, Bold, Oblique, 12pt.
	tft.setTextColor(TFT_RED);
	tft.drawString("Ultrasonic Sensor", aPos[0].x, aPos[0].y);
	tft.setTextColor(TFT_WHITE, TFT_BLACK);
	tft.drawString("- Cm: ", aPos[1].x, aPos[1].y);
	tft.drawString("- Inch: ", aPos[2].x, aPos[2].y);
}

void loop() {
	RangeInCentimeters = ultrasonic.MeasureInCentimeters();
	if (PrevRangeInCentimeters != RangeInCentimeters) {
		if (PrevRangeInCentimeters > RangeInCentimeters) {
			tft.drawString("        ", aPos[3].x, aPos[3].y);
		}
		tft.drawNumber(RangeInCentimeters, aPos[3].x, aPos[3].y);

		PrevRangeInCentimeters = RangeInCentimeters;
		Serial.print("The distance to obstacles in front is: ");
		Serial.print(RangeInCentimeters);
		Serial.println(" centimeter");
	}
	delay(250); // Needed for data to be read again
	RangeInInches = ultrasonic.MeasureInInches();
	if (PrevRangeInInches != RangeInInches) {
		if (PrevRangeInInches > RangeInInches) {
			tft.drawString("        ", aPos[4].x, aPos[4].y);
		}
		tft.drawNumber(RangeInInches, aPos[4].x, aPos[4].y);
		PrevRangeInInches = RangeInInches;
		Serial.print("The distance to obstacles in front is: ");
		Serial.print(RangeInInches);
		Serial.println(" inches");
	}
	delay(250);

}
