#include <Adafruit_SSD1306_STM32.h>
#include <NMEAGPS.h>

#include "OdometerScreen.h"
#include "GPSOdometer.h"
#include "TimeFont.h"
#include "8x12Font.h"
#include "GPSDataModel.h"
#include "Utils.h"

extern Adafruit_SSD1306 display;

OdometerScreen::OdometerScreen(uint8 idx)
{
	odometerIdx = idx;
	inDetailsMode = false;
}

void OdometerScreen::drawScreen() const
{
	if(inDetailsMode)
		drawDetailsScreen();
	else
		drawBriefScreen();
}

void OdometerScreen::drawBriefScreen() const
{
	GPSOdometer odometer = gpsDataModel.getOdometer(odometerIdx);
	
	display.setFont(&TimeFont);
	display.setCursor(0,31);
	
	if(odometer.isActive())
		display.print(FloatPrinter(odometer.getOdometerValue(), 4));
	else
		display.print("0000"); // TODO: print '----' when there is such symbol in the font
		
	// Draw distance units
	display.setFont(&Monospace8x12Font); // TODO: Use slightly larger bold font
	display.setCursor(64, 20);
	display.print("km");
		
	display.setFont(NULL);
	display.setCursor(64,22);
	display.print("dH: ");
	display.print(FloatPrinter(odometer.getAltitudeDifference(), 4));
	display.print("m");
}

void OdometerScreen::drawDetailsScreen() const
{
	GPSOdometer odometer = gpsDataModel.getOdometer(odometerIdx);

	display.setFont(NULL);

	display.setCursor(0,8);
	display.print("Dist: ");
	display.print(FloatPrinter(odometer.getOdometerValue(), 4));
	
	display.setCursor(64,8);
	display.print("dH: ");
	display.print(FloatPrinter(odometer.getAltitudeDifference(), 4));

	display.setCursor(0,16);
	display.print("Vavg: ");
	display.print(FloatPrinter(odometer.getAvgSpeed(), 4));

	display.setCursor(64,16);
	display.print("Vmax: ");
	display.print(FloatPrinter(odometer.getMaxSpeed(), 4));

	display.setCursor(0,24);
	display.print("T:");
	display.print(TimePrinter(odometer.getTotalTime())); // TODO: This may not fit if total time is more that 1 day

	display.setCursor(64,24);
	display.print("A:");
	display.print(TimePrinter(odometer.getActiveTime()));  // TODO: This may not fit if active time is more that 1 day
}

const char * OdometerScreen::getOkButtonText() const
{
	static const char details[] = "DETAILS";
	static const char back[] = "BACK";

	if(inDetailsMode)
		return back;
		
	return details;
}

void OdometerScreen::onSelButton()
{
	// We will be in brief mode when next time get back to this screen
	inDetailsMode = false;
	
	// Do usual stuff
	Screen::onSelButton();
}


void OdometerScreen::onOkButton()
{
	// just toggle mode
	inDetailsMode = !inDetailsMode;
}