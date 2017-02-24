#include <Adafruit_SSD1306.h>
#include "8x12Font.h"

#include "CurrentPositionScreen.h"

extern Adafruit_SSD1306 display;

void CurrentPositionScreen::drawScreen()
{
	display.setFont(&Monospace8x12Font); //TODO: Use 8x12 font to effectively use screen space
	display.setCursor(0,20);
	display.println(F("12345:67890")); //TODO Print actual coordinates
//	display.println(F("12345:67890")); //TODO Print actual coordinates
//	display.println(F("LA:  --\"--'--.--")); //TODO Print actual coordinates
//	display.println(F("LO: ---\"--'--.--")); //TODO Print actual coordinates
}

CurrentPositionScreen::~CurrentPositionScreen()
{
}

const char * CurrentPositionScreen::getOkButtonText()
{
	static const char text[] PROGMEM = "POI";
	return text;
}
