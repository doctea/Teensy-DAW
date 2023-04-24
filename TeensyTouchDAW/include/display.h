#include "ILI9341_t3.h"
#include "font_Arial.h"
extern ILI9341_t3 tft;

#include "SD.h"
extern SDClass SD;

extern int trackColor[9];

//touchscreen response; to be changed
const long interval = 200;

void drawCursor();
void drawCursorPixel();
void startUpScreen();
void clearWorkSpace();
void showCoordinates();
void show_tempo();
void drawbarPosition();
void drawstepPosition(int current);
//===========================================================
// Try Draw using writeRect
#define BUFFPIXEL 80
void bmpDraw(const char* filename, uint8_t x, uint16_t y);
//scale selector
void gridScaleSelector();
void scaleSelector();
//soongmode stuff
void drawsongmodepageselector();
void drawarrengmentLines(int songpageNumber);
void drawarrengmentLine(int songpageNumber, byte trackTouchY, byte touched_phrase);
void clearArrangment();
void draw_start_of_loop();
void draw_end_of_loop();
void gridSongMode(int songpageNumber);

//step sequencer stuff
void drawStepSequencerStatic(int stepWidth);
void draw_Notenames();
void draw_Drumnotes();
void drawActiveDrumSteps();
void drawActivePolySteps();
void drawActivePolyPixel();
void drawActivePolyStepsY(int X_Axis);
void drawActivePolyPixelY(int X_Axis);
void clearStepsGrid();
void clearPixelGrid();

void clearStepsGridY(int X_Axis);
void clearPolyGridY(int X_Axis);
void clearPixelGridY(int X_Axis);
void draw_Clipselector();
void draw_SeqMode();
void drawOctaveNumber();
void drawOctaveTriangle();
void drawMIDIchannel();

//plugin stuff
//these are some function you might want to use like the drawpot or any of the draw-rect functions

//draw sub_pages buttons of a plugin, max 4 -- drawActiveRect is recommended
void draw_sub_page_buttons(int maxpages);
//draw a rectangle, if the state is high the rect gets filled
void drawActiveRect(int xPos, byte yPos, byte xsize, byte ysize, bool state, char* name, int color);
void drawPot(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color);
void drawPotDrum(int XPos, byte YPos, byte fvalue, int dvalue, byte dname, int color);
void drawPot(int XPos, byte YPos, byte fvalue, char* dvalue_char, char* dname, int color);
void drawPot_2(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color);
void drawPot_3(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color);
void drawPot_4(int XPos, byte YPos, byte fvalue, int dvalue, char* dname, int color);
void drawPotCC(int XPos, byte YPos, byte fvaluecc, byte dvaluecc, int color);
//draws a number into a rect of 2x1grids
void drawNrInRect(int xPos, byte yPos, byte dvalue, int color);
void drawNrInRect2(int xPos, byte yPos, byte dvalue, int color);
//draws a number into a rect of 2x1grids
void drawChar(int xPos, byte yPos, char* dvalue_char, int color);


void drawPot(int XPos, byte YPos, byte fvalue, int dvalue, const char* dname, int color);
