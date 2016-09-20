//if(whatColor(getColor()) == 3) //this means blue
//while(1) debugWaitForGo(); //test values for watching for green light go
//initColor(); while(1) debugColor(); //use for calibrating color sensor // test sensor line
  
#include <Arduino.h>

struct RGB {
  float r;
  float g;
  float b;
};

volatile RGB currentColor;
volatile int colorStatus = 0;
volatile float colorDarkValue;

//RGB LED pin defines
#define LRED 53
#define LGREEN 49
#define LBLUE 51

#define PHOTO A5

#define MAXDISTANCE 75



//EDIT THESE to match read values when sitting on the colors
RGB calNothing = {0.0, 0.0, 0.0};
RGB calWhite = {774.0, 734.0, 731.0};
RGB calBlack = {455.0, 374.0, 422.0};
RGB calBlue = {545.0, 561.0, 705.0};
RGB calRed = {665.0, 448.0, 419.0};

#define NUMCOLORS 4
RGB * correlate[] = {&calNothing, &calWhite, &calBlack, &calBlue, &calRed};
char * colorNames[] = {"Nothing", "White", "Black", "Blue", "Red"};

void colorInterrput(); //call me 4 times per second

//runme to check for reasonable threshold values
void debugWaitForGo();

//call me while sitting ready to go with the LEDs off
//I block until I see a large light change
void waitForGo();

//setup the pins
void initColor();

//while(1) debugColor(); to read the sensors
void debugColor();

//print the color name from a whatColor() call
void printColor(int colorNum);

//returns the number of the color when given an RGB value
//returns -1 on bad color
int whatColor(RGB currColor);

//internal function for color guessing
float colorDistance(RGB currColor, RGB std);

//use for debugging color output
void rgbPrint(RGB);

//do an actual read of the color sensor
RGB getColor(void);

