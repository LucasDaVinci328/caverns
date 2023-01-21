// cavernsGame.cpp
// Name: Caverns Game
// Author: Luke Devenney
// Date:9/10/21 Updated this backup: 9/21/2021

#include <iostream>
#include <array>
#include <time.h>
#include <string>
#include <unistd.h>
#include <math.h>

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
	for (i = 0; i <= displ.length(); i+=8) {
                cout<< displ.substr(i, i+8);
                leftwards(displ.substr(i, i+8).length());
                downwards(1);
                        }
	i-=8;
        upwards((i/8)+2);
        rightwards(length-1);
	downwards(height-1);
}


int main()
{


/*
for(int y=height;y>=0;y--) {
        for(int x=1;x<=length-2;x++) {
                c = character[x][y];
                cout<< c;
                                }
        cout<< endl;
}
cout<< endl;
*/

//controls

string response;
string right = "d";
string left = "a";
string up = "w";
string down = "s";
string esc = "^[";
cout<< "Do you want custom controls? (Y/N) \n (standard keys are WASD and esc) \n \n";
//cin>>response;
if (response=="Y") {
cout<< "What will be your right key? \n";
cin>> right;
cout<< "What will be your left key? \n";
cin>> left;
cout<< "What will be your up key? \n";
cin>> up;
cout<< "What will be your down key? \n";
cin>> down;
cout<< "What will be your esc key? \n";
cin>> esc;
}

int seed = time(0);
srand (seed);
int run = 0;

int length = 75;
int height = 40;
int chunkNumLim = 90;
int enemyLim = 15;

char c;
int tempRan;
string display = " ";
int playing = 1;
int growing = 0;
int showing = 0;
int rounds = 0;
int changeChunk = 0;
int beginningGame = 1;
int playerX = 50;
int chunkPlayerX = 50;
int playerY = 20;
int camX = 0;
int chunkCamX = 0;
int jumping = 0;
int falling = 0;
int direction = 1;
int health = 50;
int maxHealth = 50;
int enemyX[20] = {0};
int enemyY[20] = {0};
int enemyTag[20][10] = {0};//0=;1=type;2=direction;3=health;4=attack;5=defense;6=accuracy;7=evasion;8=x;9=y;
bool onUnderscore = 0;
int debug = 0;

int range = 1;
int attack = 1;
int accuracy = 70;
string inventory[3][31];
bool onInventory = 0;
int equipment[8] = {0};

inventory[0][1] = "rusty longsword";
inventory[1][1] = "a very fine sword made of iron long ago";
equipment[3] = 1;

int seeds[chunkNumLim];
for (int i=0; i<chunkNumLim; i++) {
	seeds[i] = rand();
}

seeds[0] = 100;

int boreGoal[chunkNumLim];
for (int i=0; i<chunkNumLim; i++) {
	boreGoal[i] = rand()%(height/2)+(height/4);
}

int character[150][height];
int screen[150][height];
int screenCol[150][height];
int colors[150][height];

int chunk1[length][height];
int chunk2[length][height];
int chunk3[length][height];

int growth[length][height];


while (playing==1) { //start of game while loop
	
	bool attacking = 0;
	int damage[150][height] = {0};	
	int playerXDelt = 0;
	int playerYDelt = 0;
	
	rounds++;
	if (changeChunk>0) { 
		growing = showing+2;
	} else if (changeChunk<0) {
		growing = showing-1;
	}
	growing = (growing%chunkNumLim);
	srand(seed * rounds);
	
while (growing>=0) { //start of growing while loop
srand(seeds[growing]);
cout<< "growing chunk: " << growing << endl;

//randomly plants growths and the ceiling and wall
for(int y=height-1;y>=0;y--) { 
	for(int x=0;x<length;x++) {
		if (y==height-1) {
			growth[x][y] = (rand()%4)+2;
	/*	} else if (y==0) {
			growth[x][y] = growth[x][height-1]; */
		} else {
			tempRan = rand()%750;
			if (tempRan==0) {
				growth[x][y] = (rand()%2)+2;
			} else {
				growth[x][y] = 0;
			}}
	
	}

}

int growth2[length][height];   //clears data of growth2
for(int y=height-1;y>=0;y--) {
        for(int x=0;x<length;x++) {
		growth2[x][y] = 0;
	}}

int working = 1; //growth of the cave patterns
while(working==1) {
	working = 0;
	for(int y=height-1;y>=0;y--) {
        	for(int x=0;x<length;x++) {
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
	
	for(int v=height-1;v>=0;v--) {
                for(int u=0;u<length;u++) {
                       growth[u][v] = growth2[u][v];
                }
	}
}


//sand fill-in
tempRan = rand()%5 + 5;
for (int x = 0; x<length; x++) {
        if (x%(length/4)==0)
                tempRan = rand()%5 + 5;
        for (int y = tempRan; y>=0; y--) {
                if (growth[x][y] == 0) {
                        growth[x][y] = 1;
                } else {
                        y = 0;
                }
        }
}

//tunnel borer
int boreX = 0;
int boreY = boreGoal[growing];
int boreXDelt = 0;
int boreYDelt = 0;
int boreGoalY = boreGoal[(growing+1)%(chunkNumLim)];
/*
while (growth[0][boreY]!=0) {
	boreY++;
}
boreY++;
*/
while (boreX<length) {
	tempRan = rand()%4 - 1;
	if (boreY>(boreGoalY)/2) {
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

while (boreY < boreGoalY) {
	boreY++;
	growth[boreX][boreY] = 0;
        growth[boreX-1][boreY] = 0;
        growth[boreX+1][boreY] = 0;
        growth[boreX][boreY+1] = 0;
        growth[boreX][boreY-1] = 0;
}

while (boreY > boreGoalY) {
        boreY--;
        growth[boreX][boreY] = 0;
        growth[boreX-1][boreY] = 0;
        growth[boreX+1][boreY] = 0;
        growth[boreX][boreY+1] = 0;
        growth[boreX][boreY-1] = 0;
}

int collision[length][height];
for(int y=height-1;y>=0;y--) {
        for(int x=0;x<length;x++) {
		if ((growth[x][y]==1) && (growth[x][y-1]+growth[x-1][y]+growth[x+1][y]+growth[x][y+1]==0)) {
			growth[x][y] = 0;
		}
		if ((growth[x][y]==0) && (growth[x][y-1]+growth[x-1][y]+growth[x+1][y]+growth[x][y+1]==4)) {
			growth[x][y] = 1;
		}
		if (growth[x][y]>0) {
			growth[x][y] = 1;
		} else {
			growth[x][y] = 0;
		}
		collision[x][y] = growth[x][y];
	}}


switch (growing%3) {
	case 1:
		for(int y=height-1;y>=0;y--) {
       			for(int x=0;x<length;x++) {
               			 chunk1[x][y] = collision[x][y];
			}
		}
		break;
	case 2:
		for(int y=height-1;y>=0;y--) {
                        for(int x=0;x<length;x++) {
                                 chunk2[x][y] = collision[x][y];
                        }
                }
                break;  
	case 0:
		for(int y=height-1;y>=0;y--) {
                        for(int x=0;x<length;x++) {
                                 chunk3[x][y] = collision[x][y];
                        }
                }
                break;
}
if (beginningGame != 0) {//preloads the first three chunks
	beginningGame++;
	growing++;
	beginningGame = beginningGame%3;
} else {
growing = -1;
changeChunk = 0;
}

}//end of growing while loop

//make the screen
for(int y=height-1;y>=0;y--) {
	for(int x=chunkCamX;x<150+chunkCamX;x++) {
		int u = x-chunkCamX;
	switch (showing%3) {
		case 1:
			if (x<length) {
				screen[u][y] = chunk1[x][y];
			} else if (x>=length & x<length*2) {
				screen[u][y] = chunk2[x%length][y];
			} else {
				screen[u][y] = chunk3[x%length][y];
			}
			break;
		case 2:
			if (x<length) {
                                screen[u][y] = chunk2[x%length][y];
                        } else if (x>=length &  x<length*2) {
                                screen[u][y] = chunk3[x%length][y];
                        } else {
				screen[u][y] = chunk1[x%length][y];
			}
			break;  
		case 0:
			if (x<length) {
                                screen[u][y] = chunk3[x%length][y];
                        } else if (x>=length & x<length*2) {
                                screen[u][y] = chunk1[x%length][y];
                        } else {
				screen[u][y] = chunk2[x%length][y];
			}
                	break;
	}}}

//screen collision matrix
for(int y=height-1;y>=0;y--) {
        for(int x=0;x<150;x++) {
		screenCol[x][y] = screen[x][y];
	}
}

//character encoder
int charID[10];
int charIDSum;
char charIDsquare;
for(int y=height-1;y>=0;y--) {
        for(int x=0;x<150;x++) {
			colors[x][y] = 0;
		
			charID[1] = screen[x-1][y-1];
			charID[2] = screen[x][y-1];
			charID[3] = screen[x+1][y-1];
			charID[4] = screen[x-1][y];
	                charID[5] = screen[x][y];
        	        charID[6] = screen[x+1][y];
			charID[7] = screen[x-1][y+1];
        	        charID[8] = screen[x][y+1];
                	charID[9] = screen[x+1][y+1];
			charIDSum = (1*charID[2])+(2*charID[4])+(4*charID[5])+(8*charID[6])+(16*charID[8]);			

			switch(charIDSum) {
				case 30:
				case 31:
					tempRan = rand()%50 - 3;
					if (tempRan<=0) {
						switch(tempRan) {
							case 0:
								charIDsquare = '~';
								break;
							case -1:
								charIDsquare = '+';
								break;
							case -2:
								charIDsquare = '%';
								break;
							case -3:
								charIDsquare = '#';
								break;
						}
						tempRan = rand()%20 - 6;
						if (tempRan<0) {
							colors[x][y] = 30 - tempRan;
						} else {
							colors[x][y] = 47;
						}
					} else {
						colors[x][y] = 47;
						charIDsquare = ' ';
					}
					break;
				case 16:
				case 16+8:
                                case 16+2:
                                case 2+8+16:
					if ((charID[7]==1) & (charID[9]==1)) {
						charIDsquare = -6;
					} else {
						charIDsquare = ' ';
					}
					break;
				case 1+2+8+16:
					charIDsquare = -7;
					break;
				case 8:
				case 2:
				case 0:
				case 4:
				case 8+2:
					charIDsquare = ' ';
					break;
				case 15:
					colors[x][y] = 47;
					charIDsquare = ' ';
					break;
				case 12:
					charIDsquare = '<';
					break;
				case 6:
					charIDsquare = '>';
					break;
				case 21:
					if ((charID[1]==1) && (charID[3]==1)) {
						charIDsquare = 'X';
					} else {
						charIDsquare = -1;
					}
					break;
				case 14:
					colors[x][y] = 47;
					charIDsquare = '_';
					break;	
				case 1+2:
				case 1+8:
					if ((charID[1]==0) || (charID[3]==0)) {
					       charIDsquare = ' ';
					} else {
				 		charIDsquare = '_';
					}
					break;	
				case 7:
				case 28:
					charIDsquare = 92;
					break;
				case 13:
				case 22:
					charIDsquare = '/';
					break;
				case 1:
				case 1+16:
				case 1+8+16:
                                case 1+2+16:
                                case 1+2+8:
					if (charID[1]==1 && charID[3]==1) {
						charIDsquare = '_';
					} else {
						charIDsquare = ' ';
					}
					break;
				case 1+2+4+16:
				case 1+4+8+16:
					charIDsquare = '|';
					break;
				case 4+16:
					charIDsquare = 'V';
					break;
				case 5:
					charIDsquare = -2;
					break;
				default:
				        charIDsquare = '&';
			}	       
		character[x][y] = charIDsquare;
	}}

for(int y=height-1;y>=0;y--) {
        for(int x=0;x<150;x++) {
                screen[x][y] = character[x][y];
        }
}
/*
chunkPlayerX = 50;
*/


//makes player on top of rock
while ((screenCol[chunkPlayerX][playerY]==1) & (screenCol[chunkPlayerX][playerY+1]==0)) {
	playerY++;
}


//put player in screen
if (screen[chunkPlayerX][playerY] == '_') {
	onUnderscore = 1;
} else {
	onUnderscore = 0;
}
screen[chunkPlayerX][playerY] = -3;

for (int i = 1; i<=range; i++) {
	if ((screenCol[chunkPlayerX+(i*direction)][playerY] != 1) & (((chunkPlayerX+(i*direction))<=150)&(chunkPlayerX+(i*direction)>=0))) { 
      		screen[chunkPlayerX+(i*direction)][playerY] = '-';
		colors[chunkPlayerX+(i*direction)][playerY] = 232;
        } else {
		i += range;
	}
}




/*
if ((direction == 1) & (screenCol[chunkPlayerX+1][playerY] == 0)) {
	screen[chunkPlayerX + 1][playerY] = '-';
	colors[chunkPlayerX + 1][playerY] = 232;
} else if ((direction == -1) & (screenCol[chunkPlayerX-1][playerY] == 0)) {
	screen[chunkPlayerX - 1][playerY] = '-';
	colors[chunkPlayerX - 1][playerY] = 232;
}
*/

//screenCol[chunkPlayerX][playerY] = 1;

//enemy spawner
if (rand()%20==0) {
	display += " enemy spawned";
	int tag = 0;
	while (enemyTag[tag][1]!=0) {
                tag++;
                if (tag > enemyLim) 
                        tag = -1;
        }
	if (tag>=0) {
		enemyTag[tag][1] = 1;
		enemyTag[tag][2] = 5;
		enemyTag[tag][3] = 1;
		int x = rand()%148 + 1;
		int y = rand()%(height-2) +1;
		int count = 0;
		while (((((abs (chunkPlayerX-x)) < 20) || ((abs (playerY-y)) < 20)) || (screenCol[x][y]!=0)) & (count < 15)) {
			x = rand()%148 + 1;
	       		y = rand()%(height-2) + 1;
			count++;
	 	}
		while(screenCol[x][y-1]==0) {
			y--;
		}
		if (count < 15) {
		enemyX[tag] = x + camX;
		enemyY[tag] = y;
		}
	}
}


//enemy AI
for (int i = 0; i < enemyLim; i++) {
	if (enemyTag[i][1] > 0) {
		if (enemyTag[i][2] > 0) {
		switch (enemyTag[i][1]) {
			case 1:
				if (screenCol[enemyX[i] - camX][enemyY[i] - 1] == 0) {
					enemyY[i]--;
				}
				if (enemyY[i] == playerY) {
					if (enemyX[i] < playerX) {
						enemyTag[i][3] = 1;
					} else if (enemyX[i] > playerX) {
						enemyTag[i][3] = -1;
					}
				}
				if (enemyTag[i][3] == 1) {
					if (screenCol[(enemyX[i] - camX) + 1][enemyY[i]] == 0) {
						if ((playerX != enemyX[i]+1) | (playerY != enemyY[i]))
							enemyX[i]++;
					} else {
						enemyTag[i][3] = -1;
					}
				} else if (enemyTag[i][3] == -1) {
					if (screenCol[(enemyX[i] - camX) - 1][enemyY[i]] == 0) {
						 if ((playerX != enemyX[i]-1) | (playerY != enemyY[i]))
							enemyX[i]--;
					} else {
						enemyTag[i][3] = 1;
					}
				}

				damage[enemyX[i] - camX][enemyY[i]] = 1;
                                damage[enemyX[i] - camX][enemyY[i] + 1] = 1;
				if (enemyTag[i][3] == 1)
					damage[(enemyX[i] - camX) + 1][enemyY[i]] = 1;
				if (enemyTag[i][3] == -1)
                                        damage[(enemyX[i] - camX) - 1][enemyY[i]] = 1;
				break;
		}} else {
			display+= " you killed him";
			enemyTag[i][1] = 0;
		}
	}
}

//puts enemies on the screen
int numEnemies = 0;
for (int i = 0; i < enemyLim; i++) {
	if (enemyTag[i][1] > 0) {
		if (((enemyX[i]  - camX) < 0) | ((enemyX[i] - camX) > 150)) {
			enemyTag[i][1] = 0;
			enemyX[i] = 0;
			enemyY[i] = 0;
		} else {
			numEnemies++;
			screen[enemyX[i] - camX][enemyY[i]] = 'g';
			screenCol[enemyX[i] - camX][enemyY[i]] = 2;
			colors[enemyX[i] - camX][enemyY[i]] = 231;
			
			if (((enemyTag[i][3] == 1) && (screenCol[(enemyX[i] - camX) + 1][enemyY[i]] == 0)) & (enemyX[i] + 1 != playerX)) {
				screen[(enemyX[i] - camX) + 1][enemyY[i]] = '-';
				if ((enemyX[i] - camX) < 150)
				colors[(enemyX[i] - camX) + 1][enemyY[i]] = 231;
			} else if (((enemyTag[i][3] == -1) && (screenCol[(enemyX[i] - camX) - 1][enemyY[i]] == 0)) & (enemyX[i] - 1 != playerX)) {
				screen[(enemyX[i] - camX) - 1][enemyY[i]] = '-';
                                if ((enemyX[i] - camX) > 0)
				colors[(enemyX[i] - camX) - 1][enemyY[i]] = 231;
			}
			
		}
	}
}


//print the screen
system("clear");
cout<< "/";
for(int i=0; i<74; i++) 
	cout<< "* ";
cout<< char(92) << endl;

for(int y=height-1;y>=0;y--) {
        cout<< "*";
	for(int x=1;x<149;x++) {
		cout<< "\033[0m";
		if (screen[x][y]>=0) {
			if (colors[x][y]>0) {//colors display
			cout<< "\033[1m";
                	switch (colors[x][y]) {
				case 7:
					cout<< "\033[7m";
					break;
				case 47:
					cout<< "\033[47m";
					break;
				case 31:
					cout<< "\033[31;47m";
					break;
				case 32:
                                        cout<< "\033[32;47m";
                                        break;
				case 33:
                                        cout<< "\033[33;47m";
                                        break;
				case 34:
                                        cout<< "\033[34;47m";
                                        break;
				case 35:
                                        cout<< "\033[35;47m";
                                        break;
				case 36:
                                        cout<< "\033[36;47m";
                                        break;
				case 201:
					cout<< "\033[30;47m";
					break;
				case 231:
					cout<< "\033[31m";
					break;
				case 232:
					cout<< "\033[1;32m";
					break;
				default:
					cout<< "\033[0m";
					break;
		}}
		c = screen[x][y];
                cout<< c;
                cout<< "\033[0m";
		} else if (screen[x][y]==-1) {
			cout<< "॥";
		} else if (screen[x][y]==-2) {
			cout<< "Λ";
		} else if (screen[x][y]==-3) {
			cout<< "\033[1;32m";
			
			if (onUnderscore == 1)
				cout<< "\033[4m";
			cout<< "♙";
		} else if (screen[x][y]==-6) {
			cout<< "‾";
		} else if (screen[x][y]==-7) {
			cout<< "\033[4m";
		        cout<< "‾";	
		} else if (screen[x][y]==-4) {
			cout<< "◢";
		} else if (screen[x][y]==-5) {
			cout<< "◣";
		
		} else {
			cout<< " ";
		}
                                }
        cout<< "* \n";
}
cout << char(92);
for(int i=0; i<74; i++) 
	cout<< "* ";
cout<< "/ \n \n";

/*
for(int y=height-1;y>=0;y--) {
        for(int x=0;x<150;x++) {
		if (screenCol[x][y]>0) {
                	cout<< screenCol[x][y];
		} else {
			cout<< " ";
		}
	}
	cout<< endl;
}

cout<<endl;
*/

/*
for(int y=height-1;y>=0;y--) {
        for(int x=0;x<150;x++) {
                if (damage[x][y]>0) {
                        cout<< damage[x][y];
                } else {
                        cout<< " ";
                }
        }
        cout<< endl;
}

cout<<endl;
*/


//damage detection
if (damage[chunkPlayerX][playerY] != 0)
	health -= damage[chunkPlayerX][playerY];

//damage clear
for(int y=height-1;y>=0;y--) {
        for(int x=0;x<150;x++) {
                damage[x][y] = 0;
        }
}




//Health Display
cout<< "Health: ";
for(int i = 0; i < maxHealth; i++) {
	if (i<health) {
		cout<< "\033[102m";
	} else {
		cout<< "\033[41m";
	} 	
	cout<< " " << "\033[0m" << " ";
}
//cout<< " health: " << health;
cout<< endl << endl;


//debugger
cout<< "NumEn: " <<numEnemies << endl;
cout<< debug << endl;
cout<< "X: " << playerX<< endl;
cout<< "Y: " << playerY<< endl;
cout<< "Cam: " << camX<< endl;


cout<< display<<endl;
display = " ";

//inputer
cout<< "Make a move." << endl;
system("stty raw");
response = getchar();
system("stty cooked");
cout<< endl;
if (response == esc) {
	playing = 0;
} else if (response == right) { 
	playerXDelt++;
	direction = 1;
} else if (response == left) {
	playerXDelt--;
	direction = -1;
} else if ((response == up) && (screenCol[chunkPlayerX][playerY-1] == 1)) {
	jumping = 1;
} else if (response == ".") {
} else if (response == "s") {
	jumping = 0;
	if (screenCol[chunkPlayerX][playerY] == 1) {
		playerYDelt--;
	} else if (screenCol[chunkPlayerX][playerY] == 2) {
		playerYDelt--;
	}
} else if (response == "S") {
	playing = 0;
} else if (response == "h") {
	health--;
} else if (response == "k") {
	attacking = 1;
} else if (response == "A") {
	direction = -1;
} else if (response == "D") {
	direction = 1;
} else if (response == "r") {
	range--;
} else if (response == "R") {
	range++;
} else if (response == "i") {
	onInventory = 1;
}

//inventory manager
int invX = 0;
int invY = 0;
while (onInventory) {
	const int numBoxesX = 5;
	const int numBoxesY = 6;
	const int boxesWidth = 10;
	const int boxesHeight = 5;

	system("clear");
	//inventory boxes
	for (int y = 0; y < numBoxesY; y++) {
		for (int x = 0; x < numBoxesX; x++) {
			if ((y == invY) & (x == invX)) {
				cout<< "\033[7m";
			} else {
				cout<< "\033[0m";
			}
			box(boxesWidth,boxesHeight);
			cout<< "\033[0m";
			box_display(inventory[0][(y*numBoxesX)+x+1], boxesWidth, boxesHeight);
			upwards(boxesHeight-1);
			rightwards(2);
		}
		downwards(boxesHeight);
		cout<<"\n";
	}
	
	//equippable slots
	upwards((boxesHeight+1)*numBoxesY);
	rightwards((boxesWidth+2)*numBoxesX);
	
	//head slot
	downwards(3);
	rightwards(20);
	box(boxesWidth,boxesHeight);
	box_display(inventory[0][equipment[0]], boxesWidth, boxesHeight);
        downwards(1);
        leftwards(boxesWidth);
        cout<< " Hd Notch ";

	//chest slot
	downwards(5);
	leftwards(boxesWidth);
	box(boxesWidth,boxesHeight);
	box_display(inventory[0][equipment[1]], boxesWidth, boxesHeight);
	downwards(1);
        leftwards(boxesWidth);
        cout<< " Ch Notch ";

	//offhand/lefthand slot
	upwards(boxesHeight+3);
	leftwards((2*boxesWidth)+2);
	box(boxesWidth, boxesHeight);
	box_display(inventory[0][equipment[2]], boxesWidth, boxesHeight);
        downwards(1);
        leftwards(boxesWidth);
        cout<< " LH Notch ";

	//mainhand/righthand slot
	upwards(boxesHeight);
	rightwards(boxesWidth+4);
	box(boxesWidth, boxesHeight);
	box_display(inventory[0][equipment[3]], boxesWidth, boxesHeight);
        downwards(1);
        leftwards(boxesWidth);
        cout<< " RH Notch ";


	downwards(8);
	leftwards((boxesWidth*3)+(boxesWidth/2)+5);
	
	for (int i = 1; i <= 4; i++) {//amulet slots
		box(boxesWidth, boxesHeight);
		box_display(inventory[0][equipment[3+i]], boxesWidth, boxesHeight);
		downwards(1);
		leftwards(boxesWidth);
		cout<< " Amulet " << i;
                upwards(boxesHeight);
                rightwards(3);
	}

	downwards(boxesHeight+2);
	leftwards((boxesWidth+2)*4);

	//description of items
	cout<< inventory[1][(invY*numBoxesX)+invX+1];
	downwards(5);
	cout<<"\n";

	//inputer
	system("stty raw");
	response = getchar();
	system("stty cooked");
	if (response == "i") {
		onInventory = 0;
	} else if (response == "d") {
		invX++;
	} else if (response == "a") {
		invX--;
	} else if (response == "w") {
		invY--;
	} else if (response == "s") {
		invY++;
	}
	
	//boundary movement
	if (invX > numBoxesX - 1)
		invX = numBoxesX - 1;
	if (invX < 0)
		invX = 0;
	if (invY > numBoxesY - 1)
		invY = numBoxesY -1;
	if (invY < 0)
		invY = 0;

}//end of inventory manager while loop

//attacking logic
if (attacking) {
	if (rand()%100 <= accuracy) {
		damage[chunkPlayerX][playerY-1] = attack;
		for (int i = 0; i<=range; i++) {
			if ((screenCol[chunkPlayerX+(i*direction)][playerY] != 1) & (((chunkPlayerX+(i*direction))<=150)&(chunkPlayerX+(i*direction)>=0))) { 
				damage[chunkPlayerX+(i*direction)][playerY] = attack;
			} else {
				i +=range;
			}
		}
	}
}
attacking = 0;


//attack check
for (int i = 0; i<enemyLim; i++) {
	if (enemyTag[i][1] > 0) {
		if (damage[enemyX[i] - camX][enemyY[i]] != 0) {
       			enemyTag[i][2] -= damage[chunkPlayerX][playerY];
			display += " you attacked goblin " + to_string(enemyTag[i][2]);
		}	
	}
}


//damage clear
for(int y=height-1;y>=0;y--) {
        for(int x=0;x<150;x++) {
                damage[x][y] = 0;
        }
}




//jumping
if (jumping>0) {
	jumping++;
	playerYDelt++;
} else if (screenCol[chunkPlayerX][playerY-1]==0) {
	playerYDelt--;
}
jumping = jumping%10;

//collision detection for X
if (playerXDelt!=0) {
	int colID[10];
	//cout<< "X: " << playerX << endl;
	//cout<< "Y: " << playerY << endl;
	colID[1] = screenCol[chunkPlayerX-1][playerY-1];
	colID[2] = screenCol[chunkPlayerX][playerY-1];
	colID[3] = screenCol[chunkPlayerX+1][playerY-1];
	colID[4] = screenCol[chunkPlayerX-1][playerY];
	colID[5] = screenCol[chunkPlayerX][playerY];
	colID[6] = screenCol[chunkPlayerX+1][playerY];
	colID[7] = screenCol[chunkPlayerX-1][playerY+1];
	colID[8] = screenCol[chunkPlayerX][playerY+1];
	colID[9] = screenCol[chunkPlayerX+1][playerY+1];
	int colIDsum = colID[2]+colID[4]+colID[6]+colID[8];

	if (playerXDelt>0) {
		if (colID[6]==0) {
			playerX++;
			display +=  " You went right.";
			playerXDelt = 0;
		} else if (colID[9]==0) {
			playerX++;
			playerXDelt = 0;
			playerYDelt++;
			display += " You walked right up the ramp.";
		} else if (colID[8]==0) {
			playerXDelt = 0;
			playerYDelt++;
			playerYDelt++;
			display += " You climbed up the right.";
		}
		if ((playerX-50)%length==0)
			changeChunk = 1;
	} else if (playerXDelt<0) {
		if (colID[4]==0) {
                        playerX--;
			display += " You went left.";
                        playerXDelt = 0;
                } else if (colID[7]==0) {
                        playerX--;
                        playerXDelt = 0;
                        playerYDelt++;
			display += " You walked left up the ramp.";
                } else if (colID[8]==0) {
                        playerXDelt = 0;
                        playerYDelt++;
			playerYDelt++;
			display += " You climbed up the left.";
                }
		if ((playerX-50)%length==0)
                        changeChunk = -1;
	}
}

//collission detection for Y
if (playerYDelt!=0) {
	int colID[10];
        //cout<< "X: " << playerX << endl;
        //cout<< "Y: " << playerY << endl;
        colID[1] = screenCol[chunkPlayerX-1][playerY-1];
        colID[2] = screenCol[chunkPlayerX][playerY-1];
        colID[3] = screenCol[chunkPlayerX+1][playerY-1];
        colID[4] = screenCol[chunkPlayerX-1][playerY];
        colID[5] = screenCol[chunkPlayerX][playerY];
        colID[6] = screenCol[chunkPlayerX+1][playerY];
        colID[7] = screenCol[chunkPlayerX-1][playerY+1];
        colID[8] = screenCol[chunkPlayerX][playerY+1];
        colID[9] = screenCol[chunkPlayerX+1][playerY+1];
        int colIDsum = colID[2]+colID[4]+colID[6]+colID[8];

	if (colID[5]==1)
		playerYDelt++;

	if (playerYDelt>0) {
		if (colID[8]==0) {
			playerY++;
			display += " You went up.";
		} else {
			display += " You can't go up.";
			jumping = 0;
		}
		playerYDelt = 0;
	} else if (playerYDelt<0) {
		if (colID[2]==0) {
                        playerY--;
			display +=  " You went down.";
		} else {
			display +=  " You can't go down.";
		}
		playerYDelt = 0;
	}
}


playerXDelt = 0;
playerYDelt = 0;

camX = playerX-50;
chunkPlayerX = playerX - camX;

/*
if (camX<0) {
        camX = length*chunkNumLim;
}
*/

chunkCamX = camX%length;
/*
//chunk growth control
if (showing<(camX/length)) {
        changeChunk = 1;
	debug = 1;
} else if (showing>(camX/length)) {
        changeChunk = -1;
	debug = -1;
}
*/

debug = changeChunk;
showing = camX/length;

if (health<=0)
	playing = 0;

} //end of game while loop
cout<< endl<< "you have died"<< endl;

//♙
return 0;
}

