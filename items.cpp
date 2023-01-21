#include <string>
#include <time.h>
#include <iostream>
#include <math.h>
#include "items.h"
#include <ctype.h>

using namespace std;

//{ "Initial Name", "Brief Description ", to_string(0), to_string(0), to_string(0), to_string(0), to_string(0), to_string(0), to_string(0)},
//			        		Health	      Attack	    Defense	  Accuracy      Evasion       Range         Type



void makeItem(int newItem[][11], string newItemDes[][2], const int ARRAY_LIM, int x, int y) {
	int qualityDOUCONV = pow(8.0, 5.0);
	int quality = (log(rand()%qualityDOUCONV) / log(8.0)) + 1;
	//quality = rand()%5 + 1;

	class item {
		string name;
		string descript;
		int health;
		int attack;
		int defense;
		int accuracy;
		int evasion;
		int range;
		int type;
	};

	string helm[][9] = {
                { "Helm", "Keep your gnoggin. ", to_string(0), to_string(0), to_string(rand()%3+2), to_string(rand()%2-1), to_string(0), to_string(0), to_string(3)},
                { "Hood", "Hide in the darkness. ", to_string(0), to_string(0), to_string(0), to_string(0), to_string(rand()%3+1), to_string(rand()%2), to_string(3)},
        	{ "Cap", "Small and fragile. ", to_string(0), to_string(0), to_string(rand()%2+1), to_string(0), to_string(0), to_string(0), to_string(3)},
                { "Goggles", "Protect your eyes. ", to_string(0), to_string(0), to_string(0), to_string(rand()%4+3), to_string(rand()%2), to_string(rand()%2+1), to_string(3)},
	};

	string chest[][9] = {
                { "Chestplate", "Made for defense, but slow. ", to_string(0), to_string(0), to_string(rand()%5+7), to_string(0), to_string(rand()%3-2), to_string(0), to_string(4)},
                { "Cloak", "Catches the stray blade. ", to_string(0), to_string(0), to_string(rand()%2), to_string(0), to_string(rand()%5+5), to_string(0), to_string(4)},
                { "Tunic", "Quickens your attacks. ", to_string(0), to_string(0), to_string(rand()%2), to_string(rand()%3), to_string(rand()%3+1), to_string(0), to_string(4)},
                { "Gambeson", "Padded armor. ", to_string(0), to_string(0), to_string(rand()%4+4), to_string(0), to_string(rand()%2), to_string(0), to_string(4)}
	};

	string offHand[][9] = {
                { "Shield", "Protects alot. ", to_string(0), to_string(0), to_string(rand()%4+3), to_string(0), to_string(0), to_string(0), to_string(2)},
                { "Buckler", "Protects the essentials. ", to_string(0), to_string(0), to_string(rand()%2+1), to_string(0), to_string(rand()%3+2), to_string(0), to_string(2)},
        	{ "Tome", "Book lined with runes.  ", to_string(rand()%3+1), to_string(0), to_string(rand()%2), to_string(rand()%2+1), to_string(rand()%2+1), to_string(0), to_string(5)},
		{ "Scabbard", "Keeps your blade sharp. ", to_string(0), to_string(rand()%5+2), to_string(0), to_string(rand()%2+1), to_string(0), to_string(0), to_string(6)}
	};

	string mainHand[][9] = { 
		{ "Longsword", "Long and stabby. ", to_string(0), to_string(rand()%3+4), to_string(0), to_string(rand()%2+2), to_string(0), to_string(1), to_string(1)},
		{ "Shortsword", "Accurate but weak. ", to_string(0), to_string(rand()%3+1), to_string(0), to_string(rand()%4+6), to_string(0), to_string(0), to_string(1)},
                { "Halberd", "Long handled ending in a sharp head. ", to_string(0), to_string(rand()%3+3), to_string(0), to_string(rand()%3-1), to_string(0), to_string(rand()%2+2), to_string(1)},
		{ "Spear", "Stick sharpened at a point. ", to_string(0), to_string(rand()%3+2), to_string(rand()%2), to_string(rand()%3+1), to_string(0), to_string(rand()%2+1), to_string(1)},
		{ "Bow", "Shoot enemies from a distance. ", to_string(0), to_string(rand()%4+2), to_string(0), to_string(rand()%2+1), to_string(rand()%2-1), to_string(rand()%4+4), to_string(2)},
		{ "Crossbow", "Mechanized bow with crank. ", to_string(0), to_string(rand()%5+1), to_string(0), to_string(rand()%3+2), to_string(rand()%3-2), to_string(rand()%4+3), to_string(2)},
	};

	string amulet[][9] = {
                { "Bracelet", "Magic is within. ", to_string(rand()%2), to_string(rand()%3), to_string(rand()%3), to_string(rand()%2), to_string(rand()%2), to_string(rand()%2), to_string(5)},
                { "Necklace", "Kept close to your throat. ", to_string(rand()%3+1), to_string(rand()%2), to_string(rand()%2), to_string(rand()%2), to_string(rand()%2), to_string(rand()%2), to_string(5)},
		{ "Ring", "A single band with intricate designs. ", to_string(rand()%4), to_string(rand()%3+1), to_string(rand()%4), to_string(rand()%3+1), to_string(rand()%4-2), to_string(rand()%3-1), to_string(5)},
		{ "Totem", "Small carved object. ", to_string(rand()%5-2), to_string(rand()%5-2), to_string(rand()%5-2), to_string(rand()%5-2), to_string(rand()%5-2), to_string(rand()%5-2), to_string(5)}
        };
	
	string quality1[] = {"Charles'", "Perfection", "Legendary", "Tide", "Vitality", "Zenith",  "Precious", "Ascended", "Savage" };
	string quality2[] = {"Eucalyptus", "Diamond", "Cactus", "Mountains", "Snail", "Sharktooth", "Zephyr",  "Silver", "Dwarfkind", "Bear", "Bjorn", "Blackheart" };
	string quality3[] = {"Bronze", "Fine", "Ceramic", "Crimson", "Force", "Dusty", "Jet", "Zero", "Copper" };
	string quality4[] = {"Handy", "Heirloom", "Spoke", "Practice", "Dull", "Noah's", "Underworld", "Seven" };
	string quality5[] = {"Dove", "Peaceful", "Rust", "Broken", "Fruit", "Poor", "Torn", "Stone", "Common", "Ordinary", "Regular", "Normal", "Leather", "Cursed" };

	const int QUALITY1SIZE = sizeof(quality1) / sizeof(quality1[0]);
        const int QUALITY2SIZE = sizeof(quality2) / sizeof(quality2[0]);
        const int QUALITY3SIZE = sizeof(quality3) / sizeof(quality3[0]);
        const int QUALITY4SIZE = sizeof(quality4) / sizeof(quality4[0]);
        const int QUALITY5SIZE = sizeof(quality5) / sizeof(quality5[0]);
	//int itemLists[2] = {*mainHand[][9], *offHand[][9]};
	
	int i = 1;
	for (i = 1; i <= ARRAY_LIM; i++) {
		if (newItem[i][10] == 0)
			break;
	}
	if (i != ARRAY_LIM+1) {

		newItem[i][8] = x;
		newItem[i][9] = y;
		int itemType = rand()%5+1;
		int numRows;
		switch(itemType) {
			case 1:
				numRows = sizeof helm / sizeof helm[0];
				break;
			case 2:
				numRows = sizeof helm / sizeof chest[0];
				break;
			case 3:
				numRows = sizeof offHand / sizeof offHand[0];
				break;
			case 4:
				numRows = sizeof mainHand / sizeof mainHand[0];
				break;
			case 5:
				numRows = sizeof amulet / sizeof amulet[0];
				break;
		}
		string assigner[numRows][9];
		for (int a = 0; a < numRows; a++) {
			for (int b = 0; b < 9; b++) {
				switch(itemType) {
					case 1:
						assigner[a][b] = helm[a][b];
						break;
					case 2:
						assigner[a][b] = chest[a][b];
						break;
					case 3:
						assigner[a][b] = offHand[a][b];
						break;
					case 4:
						assigner[a][b] = mainHand[a][b];
						break;
					case 5:
						assigner[a][b] = amulet[a][b];
						break;
				}
			}
		}
		newItem[i][6] = itemType;
                int itemIndex = rand()%numRows;
                newItemDes[i][0] = assigner[itemIndex][0];
                newItemDes[i][1] = assigner[itemIndex][1];
                for (int a = 0; a < 6; a++) {
			if (stoi(assigner[itemIndex][a+2], nullptr) > 0) {
				newItem[i][a] = stoi(assigner[itemIndex][a+2], nullptr) * ((7-quality) / 4.0);
				newItem[i][a] = (newItem[i][a] == 0)? 1 : newItem[i][a];
			} else if (stoi(assigner[itemIndex][a+2], nullptr) < 0) {
				newItem[i][a] = stoi(assigner[itemIndex][a+2], nullptr) * ((1+quality) / 4.0);
			} else {
				newItem[i][a] = 0;
			}
		}
		newItem[i][10] = -1 * stoi(assigner[itemIndex][8], nullptr);
		int nameOrder = rand()%2;
		string nameMod;
		switch(quality) {//quality name selector
			case 1:
				nameMod = quality1[rand()%QUALITY1SIZE];
				break;
			case 2:
				nameMod = quality2[rand()%QUALITY2SIZE];
                                break;
			case 3:
				nameMod = quality3[rand()%QUALITY3SIZE];
                                break;
			case 4:
				nameMod = quality4[rand()%QUALITY4SIZE];
				break;
			case 5:
				nameMod = quality5[rand()%QUALITY5SIZE];
				break;
			default:
				nameMod = "Standard";
				break;
		}
		if (nameOrder == 0) {
			newItemDes[i][0] += " of " + nameMod;
		} else {
			newItemDes[i][0] = nameMod + " " + newItemDes[i][0];
		}
	}
}
