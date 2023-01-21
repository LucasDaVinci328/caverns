#ifndef BOX_DEF
#define BOX_DEF

#include <string>

using namespace std;

void leftwards(int length);

void rightwards(int length);

void upwards(int length);

void downwards(int length);

void horizonLine(int length);

void vertLine(int height);

void line(int length, int height);

void lineCLR(int length, int height);

void arc(int x1, int y1, int x2, int y2);

void box(int length, int height);

void box_display(string displ,const int length,const int height);

#endif
