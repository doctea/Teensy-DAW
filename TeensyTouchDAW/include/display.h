#include "ILI9341_t3.h"
#include "font_Arial.h"
extern ILI9341_t3 tft;

#include "SD.h"
extern SDClass SD;

extern int trackColor[9];

//touchscreen response; to be changed
const long interval = 200;
