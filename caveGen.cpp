// caveGen.cpp
// Name: Cave Generation
// Author: Luke Devenney
// Date:9/9/21

#include <iostream>
#include <array>
using namespace std;

int main()
{
int seed;
cout<< "Seed? ";
cin>>seed;
int length;
cout<< "Length? (max 150) ";
cin>>length;
length+3;
int height;
cout<< "Height? (max 75) ";
cin>>height;
cout<< endl;
srand (seed);
char c;
int tempRan;

if (length>150) {
	length = 150;
}
if (height>75) {
	height = 75;
}

int growth[length][height];

//randomly plants growths and the ceiling and wall
for(int y=height;y>=0;y--) { 
	for(int x=0;x<length-1;x++) {
		if ((y==0) | (y==height)) {
			growth[x][y] = (rand()%3)+2;
		} else {
			tempRan = rand()%500;
			if (tempRan==0) {
				growth[x][y] = (rand()%2)+1;
			} else {
				growth[x][y] = 0;
			}}
			if (growth[x][y]==0) {
				cout<< " ";
			} else {
			cout<< growth[x][y];
	}}
	cout<< endl;
}
cout<< endl;

int growth2[length][height];   //clears data of growth2
for(int y=height;y>=0;y--) {
        for(int x=0;x<length-1;x++) {
		growth2[x][y] = 0;
	}}

int working = 1; //growth of the cave patterns
while(working==1) {
	working = 0;
	for(int y=height;y>=0;y--) {
        	for(int x=0;x<length-1;x++) {
                	if (growth[x][y]>1) {
				tempRan = rand()%(growth[x][y]);
				if (growth[x+1][y]<1) {
					growth2[x+1][y] = growth[x][y] - tempRan;
					working = 1;
				}
				if (growth[x-1][y]<1) {
                                        growth2[x-1][y] = growth[x][y] - tempRan;
                                	working = 1;
				}
				if (growth[x][y+1]<1) {
                                        growth2[x][y+1] = growth[x][y] - rand()%(growth[x][y]);
                                	working = 1;
				}
				if (growth[x][y-1]<1) {
                                        growth2[x][y-1] = growth[x][y] - rand()%(growth[x][y]);
                                	working = 1;
				}
				growth[x][y] = 1;
				growth2[x][y] = 1;
			}
			if (growth2[x][y]<growth[x][y]) { 
			growth2[x][y] = growth[x][y];
        		}}
		}
	
	for(int v=height;v>=0;v--) {
                for(int u=0;u<length-1;u++) {
                       growth[u][v] = growth2[u][v];
		       if (working==0) {
		       if (growth[u][v]==0) {
                                        cout<< " ";
                                } else {
                                        cout<< growth[u][v];
				}}
                }
		if (working==0) {
		cout<< endl;
		}
	}
	if (working==0) {
		cout<< endl;
	}
}

//tunnel borer
int boreX = 0;
int boreY = 0;
int boreXDelt = 0;
int boreYDelt = 0;
while (growth[0][boreY]!=0) {
	boreY++;
}
boreY++;

while (boreX<length) {
	tempRan = rand()%4 - 1;
	if (boreY>height/2) {
		tempRan = tempRan - 1;
	}
	boreYDelt = tempRan;
	boreXDelt = 1;
	
	growth[boreX][boreY] = 0;
	growth[boreX-1][boreY] = 0;
	growth[boreX+1][boreY] = 0;
	growth[boreX][boreY+1] = 0;
	growth[boreX][boreY-1] = 0;
	boreX = boreX + boreXDelt;
	boreY = boreY + boreYDelt;
	boreXDelt = 0;
	boreYDelt = 0;
	if (boreY<3) {
		boreY = 2;
	}
	if (boreY>(height-3)) {
		boreY = height-3;
	}
}
for(int y=height;y>=0;y--) {
        for(int x=0;x<length-1;x++) {
		if (growth[x][y]==0)  {
			cout<< " ";
		} else {
			cout<< growth[x][y];
		}}
		cout<< endl;
	}
cout<< endl;

//collision matrix for growth
int collision[length][height];
for(int y=height;y>=0;y--) {
        for(int x=0;x<length-1;x++) {
		collision[x][y] = growth[x][y];
	}}

//character encoder
int character[length][height];
int charID[10];
int charIDSum;
for(int y=height;y>=0;y--) {
        for(int x=0;x<length-1;x++) {
		if ((y==0) | (y==height)) {
                        character[x][y] = '-';
		} else {
			
			charID[1] = growth[x-1][y-1];
			charID[2] = growth[x][y-1];
			charID[3] = growth[x+1][y-1];
			charID[4] = growth[x-1][y];
	                charID[5] = growth[x][y];
        	        charID[6] = growth[x+1][y];
			charID[7] = growth[x-1][y+1];
        	        charID[8] = growth[x][y+1];
                	charID[9] = growth[x+1][y+1];
			charIDSum = (1*charID[2])+(2*charID[4])+(4*charID[5])+(8*charID[6])+(16*charID[8]);
			
			switch(charIDSum) {
				case 31:
					tempRan = rand()%50 - 2;
					if (tempRan<=0) {
						switch(tempRan) {
							case 0:
								character[x][y] = '~';
								break;
							case -1:
								character[x][y] = '+';
								break;
							case -2:
								character[x][y] = '%';
								break;
						}
					} else {
						character[x][y] = ' ';
					}
					break;
				case 16:
				case 8:
				case 2:
				case 0:
				case 4:
				case 15:
				case 10:
				case 16+8:
				case 16+2:
				case 2+8+16:
					character[x][y] = ' ';
					break;
				case 12:
					character[x][y] = '<';
					break;
				case 6:
					character[x][y] = '>';
					break;
				case 21:
					character[x][y] = 'X';
					break;
				case 14:
					character[x][y] = '_';
					break;	
				case 1+2:
				case 1+8:
					if ((charID[1]==0) || (charID[3]==0)) {
					       character[x][y] = ' ';
					} else {
				 		character[x][y] = '_';
					}
					break;	
				case 30:
					character[x][y] = '_';
					break;
				case 7:
				case 28:
					character[x][y] = 92;
					break;
				case 13:
				case 22:
					character[x][y] = '/';
					break;
				case 1:
				case 1+16:
				case 1+8+16:
                                case 1+2+16:
				case 27:
                                case 1+2+8:
					if (charID[1]==1 && charID[3]==1) {
						character[x][y] = '_';
					} else {
						character[x][y] = ' ';
					}
					break;
				case 1+2+4+16:
				case 1+4+8+16:
					character[x][y] = '|';
					break;
				case 4+16:
					character[x][y] = 'V';
					break;
				case 5:
					character[x][y] = 'A';
					break;
				default:
				       character[x][y] = '#';
			}	       
		
		
		}
		
	}}


for(int y=height;y>=0;y--) {
        for(int x=1;x<length-2;x++) {
                c = character[x][y];
		cout<< c;
				}
	cout<< endl;
}
cout<< endl;



return 0;
}
