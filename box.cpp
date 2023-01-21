#include <iostream>
#include <string>
#include "boxes.h"
#include <math.h>
#include <unistd.h>
#include <time.h>

using namespace std;

void leftwards(int length) {
	for (int i = 0; i < length; i++) 
		cout<< "\033[1D";
}

void rightwards(int length) {
	for (int i = 0; i < length; i++) 
		cout<< "\033[1C";
}

void upwards(int length) {
	for (int i = 0; i < length; i++) 
		cout<< "\033[1A";
}

void downwards(int length) {
	for (int i = 0; i < length; i++) 
		cout<< "\033[1B";
}


void horizonLine(int length) {
	for (int i = 0; i < length; i++) {
		cout<< "-";
	}
}

void vertLine(int height) {
	for (int i = 0; i < height; i++) {
		cout<< "|";
		downwards(1);
		leftwards(1);
	}
}

void line(int length, int height) {
	cout<<"0";
	leftwards(1);
	int ogLength = length;
	int ogHeight = height;
	const float slope = (length != 0)? (float(height) / float(length)) : height;
	if (height<0 & length<0) {
		height = abs(height);
		length = abs(length);
		downwards(height-1);
		leftwards(length-1);
	} else 
	if ((height<0) & (length!=0)) {
		height = abs(height);
		if (length!=0)
			downwards(height);
	} else
	if (length<0) {
		length = abs(length);
		leftwards(length-1);
		if (height!=0)
			downwards(1);
	}

	if (length == 0) {
		upwards(height);
        	vertLine(height);
		upwards(height);
        } else
        if (height == 0) {
		leftwards(length);
        	horizonLine(length);
		leftwards(length);
        } else {
	
		for (int x = ((slope>0)? 0 : (0 - length)); x< ((slope>0)? length : 0); x++) {
			upwards(round(x*slope));
			if (abs(slope)>(3.0/2)) {
				cout<< "|";
			} else if (abs(slope)<(2.0/3)) {			
				cout<< "-";
			} else if (slope>0) {
				cout<< "/";
			} else if (slope<0) {
				cout<< char(92);
			} else {
				cout<< "#";
			}
			downwards(round(x*slope));
		}
		if (ogLength > 0)
			leftwards(length);
		if (ogHeight < 0)
			upwards(height);
	}
}

void lineCLR(int length, int height) {
	cout<<"\033[30m";
	line(length, height);	
	cout<<"\033[0m";
}

void arc(int x1, int y1, int x2, int y2) {
	if (x1>x2){
		int swap = x1;
		x1 = x2;
		x2 = swap;
		swap = y1;
		y1 = y2;
		y2 = swap;
	}
	float radius1 = sqrt(pow(x1,2.0) + pow(y1,2.0));
	float radius2 = sqrt(pow(x2,2.0) + pow(y2,2.0));
	float radiusAVG = (radius1 + radius2)/2.0;

	for(int x = x1; x <= x2; x++) {
		int y = sqrt(pow(radiusAVG,2.0) - pow(x,2.0));
		line(x, y);
		sleep(1);
		lineCLR(x,y);
	}
	line(x1, y1);
	sleep(1);
	lineCLR(x1,y1);

	
}

void box(int length, int height) {
	cout<<"/";
	horizonLine(length-2);
	cout<< char(92);
	downwards(1);
	leftwards(1);
	vertLine(height-2);
	leftwards(length-1);
	upwards(height-2);
	vertLine(height-2);
	cout<< char(92);
	horizonLine(length-2);
	cout<<"/";
	rightwards(1);
}
	
void box_display(string displ,const int length,const int height) {
	leftwards(length);
        upwards(height-2);
        int i = 0;
	for (i = 0; i <= displ.length(); i+=(length-2)) {
                cout<< displ.substr(i, length-2);
                leftwards(displ.substr(i, length-2).length());
                downwards(1);
                        }
	i-=(length-2);
        upwards((i/(length-2))+2);
        rightwards(length-1);
	downwards(height-1);
}
