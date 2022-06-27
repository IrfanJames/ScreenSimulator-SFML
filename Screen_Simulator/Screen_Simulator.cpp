#pragma once
/*
taskkill /F /IM Screen_Simulator.exe
*/

#include <iostream>
#include "Screen_Classes.h"
#include <list>
#include <fstream>

using namespace sf;
using namespace std;

struct colorValue {
	int r = 0;
	int g = 0;
	int b = 0;
};
string decToHex(int n);
int B0123(colorValue n);
int hexToDec(string hexVal);

int main() {

	/*int ir = 5, ja = 5;
	int irfan = 0, james = 0;

	for (unsigned int i = 0; i < 1000;) {

		irfan = i % 100 + ir;
		james = i / 100 + ja;

		cout << "(" << irfan << ", " << james << ")\n";

		i++;
	}


	system("pause");*/

	fstream dataFile, hexFile;

	RenderWindow app(VideoMode(W, H), "ScreenSim", Style::Default, ContextSettings(0));
	app.setVerticalSyncEnabled(1);
	W = app.getSize().x; H = app.getSize().y;
	app.setFramerateLimit(60);
	srand(time(NULL));

	time_t frame = clock();
	bool End = 0, Pause = 0, Stimuli = 1;
	int OneTwoThree = 1;
///////////////////////////////////////////////

	list<Entity*> entities;
	int X = 100, Y = 75, m_R = 45, m_G = 100, m_B = 80, boxW = 1, boxH = 1, boxOffX = 0, boxOffY = 0;

	vector<sf::Color> FrameColor;
	FrameColor.resize(X * Y);

	//resultImage.create(1100, 840);

	//vector<vector<sf::RectangleShape>> ScreenArr;
	//ScreenArr.resize(Y, vector<sf::RectangleShape>(X));

	bool UploadResults = 0, ReadResults = 0, makeHex = 0, readHex = 0;
///////////////////////////////////////////////1100
while (!End) {

	sf::Image frameImage, boxImage, resultImage, generatedImage;
	cout << "tot " << frameImage.loadFromFile("Images/pic.png") << " tot\n";
	sf::Texture t, texBox;
	t.loadFromImage(frameImage);
	sf::Sprite s(t), spriteBox;
	

	while (app.isOpen() && !End) {
		sf::Sprite spriteBox;

		Event evnt;
		while (app.pollEvent(evnt)) {
			if (evnt.type == evnt.Closed) {
				app.close();
				End = 1;
				entities.clear();
			}
			if (evnt.type == evnt.KeyPressed) {
				if (evnt.key.code == Keyboard::Escape) { app.close(); End = 1; cout << "\n------------------ESC Pressed-----------------\n"; goto END; }
				if (evnt.key.code == Keyboard::Space)  { Pause = !Pause; cout << "\n------------------   Pause   -----------------\n"; }
				if (evnt.key.code == Keyboard::R)      { cout << "\n------------------   RESET   -----------------\n"; goto END; }

				if (evnt.key.code == Keyboard::Num1 || evnt.key.code == Keyboard::Numpad1) { OneTwoThree = (OneTwoThree != 1) * (1); }
				if (evnt.key.code == Keyboard::Num2 || evnt.key.code == Keyboard::Numpad2) { OneTwoThree = (OneTwoThree != 2) * (2); }
				if (evnt.key.code == Keyboard::Num3 || evnt.key.code == Keyboard::Numpad3) { OneTwoThree = (OneTwoThree != 3) * (3); }
				
				int t_off = 10;
				if (evnt.key.code == Keyboard::Up) { 
					switch (OneTwoThree) {
					case 1: boxOffY = (boxOffY - t_off >= 0) * (boxOffY - t_off) + (boxOffY - t_off < 0) * boxOffY; break;
					case 2: Y = (Y - 1 > 0) * (Y - 1) + !(Y - 1 > 0) * Y; break;
					case 3: boxH = (boxH - 1 >= 1) * (boxH - 1) + (boxH - 1 < 1) * boxH; break;
					default: break;
					};
				}
				if (evnt.key.code == Keyboard::Down) {
					switch (OneTwoThree) {
					case 1: boxOffY = (boxH * Y + boxOffY + t_off <= frameImage.getSize().y) * (boxOffY + t_off) + (boxH * Y + boxOffY + t_off > frameImage.getSize().y) * boxOffY; break;
					case 2: Y = (boxH * (Y + 1) + boxOffY <= frameImage.getSize().y) * (Y + 1) + (boxH * (Y + 1) + boxOffY > frameImage.getSize().y) * Y; break;
					case 3: boxH = ((boxH + 1) * Y + boxOffY <= frameImage.getSize().y) * (boxH + 1) + ((boxH + 1) * Y + boxOffY > frameImage.getSize().y) * boxH; break;
					default: break;
					};
				}
				if (evnt.key.code == Keyboard::Right) {
					switch (OneTwoThree) {
					case 1: boxOffX = (boxW * X + boxOffX + t_off <= frameImage.getSize().x) * (boxOffX + t_off) + (boxW * X + boxOffX + t_off > frameImage.getSize().x) * boxOffX; break;
					case 2: X = (boxW * (X + 1) + boxOffX <= frameImage.getSize().x) * (X + 1) + (boxW * (X + 1) + boxOffX > frameImage.getSize().x) * X; break;
					case 3: boxW = ((boxW + 1) * X + boxOffX <= frameImage.getSize().x) * (boxW + 1) + ((boxW + 1) * X + boxOffX > frameImage.getSize().x) * boxW; break;
					default: break;
					};
				}
				if (evnt.key.code == Keyboard::Left) {
					switch (OneTwoThree) {
					case 1: boxOffX = (boxOffX - t_off >= 0) * (boxOffX - t_off) + (boxOffX - t_off < 0) * boxOffX; break;
					case 2: X = (X - 1 > 0) * (X - 1) + !(X - 1 > 0) * X; break;
					case 3: boxW = (boxW - 1 >= 1) * (boxW - 1) + (boxW - 1 < 1) * boxW; break;
					default: break;
					};
				}

				/*if (evnt.key.code == Keyboard::A) { boxW = (boxW - 1 >= 1)                                      * (boxW - 1) + (boxW - 1 < 1) * boxW; }
				if (evnt.key.code == Keyboard::D) { boxW = ((boxW + 1) * X + boxOffX <= frameImage.getSize().x) * (boxW + 1) + ((boxW + 1)    * X + boxOffX > frameImage.getSize().x) * boxW; }
				if (evnt.key.code == Keyboard::S) { boxH = ((boxH + 1) * Y + boxOffY <= frameImage.getSize().y) * (boxH + 1) + ((boxH + 1)    * Y + boxOffY > frameImage.getSize().y) * boxH; }
				if (evnt.key.code == Keyboard::W) { boxH = (boxH - 1 >= 1)                                      * (boxH - 1) + (boxH - 1 < 1) * boxH; }

				if (evnt.key.code == Keyboard::Home)     { Y = (Y - 1 > 0) * (Y - 1) + !(Y - 1 > 0) * Y; }
				if (evnt.key.code == Keyboard::End)      { X = (X - 1 > 0) * (X - 1) + !(X - 1 > 0) * X; }
				if (evnt.key.code == Keyboard::PageUp)   { Y = (boxH * (Y + 1) + boxOffY <= frameImage.getSize().y) * (Y + 1) + (boxH * (Y + 1) + boxOffY > frameImage.getSize().y) * Y; }
				if (evnt.key.code == Keyboard::PageDown) { X = (boxW * (X + 1) + boxOffX <= frameImage.getSize().x) * (X + 1) + (boxW * (X + 1) + boxOffX > frameImage.getSize().x) * X; }

				if (evnt.key.code == Keyboard::Up)    { boxOffY = (boxOffY - t_off >= 0)                                 * (boxOffY - t_off) + (boxOffY - t_off < 0) * boxOffY; }
				if (evnt.key.code == Keyboard::Down)  { boxOffY = (boxH * Y + boxOffY + t_off <= frameImage.getSize().y) * (boxOffY + t_off) + (boxH * Y + boxOffY + t_off > frameImage.getSize().y) * boxOffY; }
				if (evnt.key.code == Keyboard::Right) { boxOffX = (boxW * X + boxOffX + t_off <= frameImage.getSize().x) * (boxOffX + t_off) + (boxW * X + boxOffX + t_off > frameImage.getSize().x) * boxOffX; }
				if (evnt.key.code == Keyboard::Left)  { boxOffX = (boxOffX - t_off >= 0)                                 * (boxOffX - t_off) + (boxOffX - t_off < 0) * boxOffX; }*/

				if (evnt.key.code == Keyboard::LControl || evnt.key.code == Keyboard::RControl) { UploadResults = 1; resultImage.create(10 * X, 10 * Y); }
				if (evnt.key.code == Keyboard::LShift || evnt.key.code == Keyboard::RShift) { makeHex = 1; }
				if (evnt.key.code == Keyboard::G) {
					ReadResults = 1;
					int xx = 0, yy = 0;
					dataFile.open("Images/0 Data.txt", ios::in);
					dataFile >> xx >> yy;
					dataFile.close();
					generatedImage.create(10 * xx, 10 * yy);
				}
				if (evnt.key.code == Keyboard::B) {
					readHex = 1;
					generatedImage.create(1000, 750);
				}
				Stimuli = 1;
			}
		}

		if(Stimuli) boxImage.create(X * boxW, Y * boxH);
		
		
///////////////////////////////////////////////

if(Stimuli){
	int xi = 0, yi = 0;
	if (makeHex) {
		cout << "\nX: "; cin >> xi >> X;
		cout << "Y: "; cin >> yi >> Y;
	}

	if (makeHex) { hexFile.open("Images/0 Bin.txt", ios::out); hexFile << "unsigned char arr[" << Y << "][" << X << "] = {"; }
	if (UploadResults) { dataFile.open("Images/0 Data.txt", ios::out); /*dataFile.clear();*/ dataFile << "\n" << X << " " << Y << "\n"; }
	
	for (int y = yi; y < Y; y++) {
		if (UploadResults) { dataFile << "\n"; }
		if (makeHex) { hexFile << "\n\t{"; }

		for (int x = xi; x < X; x++) {
			
			//ScreenArr[y][x].setSize(sf::Vector2f(boxW, boxH));
			//ScreenArr[y][x].setPosition(boxOffX + boxW * x, boxOffY + boxH * y);

			m_R = 0, m_G = 0, m_B = 0;
			for (int c = 0; c < boxH; c++) {
				for (int cc = 0; cc < boxW; cc++) {
					m_R += ((int)frameImage.getPixel(boxOffX + x * boxW + cc, boxOffY + y * boxH + c).r);
					m_G += ((int)frameImage.getPixel(boxOffX + x * boxW + cc, boxOffY + y * boxH + c).g);
					m_B += ((int)frameImage.getPixel(boxOffX + x * boxW + cc, boxOffY + y * boxH + c).b);
				}
			}

			m_R /= boxH * boxW;
			m_G /= boxH * boxW;
			m_B /= boxH * boxW;
			
			//BoxImage
			for (int c = 0; c < boxH; c++) {
				for (int cc = 0; cc < boxW; cc++) {
					boxImage.setPixel(boxW * x + cc, boxH * y + c, sf::Color(m_R, m_G, m_B));
				}
			}
			//ScreenArr[y][x].setFillColor(sf::Color(m_R, m_G, m_B));
			
			colorValue tempColor;
			tempColor.r = m_R; tempColor.g = m_G; tempColor.b= m_B;
			if (makeHex) { hexFile << B0123(tempColor); if(x < X - 1) hexFile << ", "; }
			if (UploadResults) {
				dataFile << "\t" << m_R << " " << m_G << " " << m_B;

				/*float rboxH = resultImage.getSize().y / ((Y >= X) * Y + (X > Y) * X);
				float rboxW = resultImage.getSize().x / ((Y >= X) * Y + (X > Y) * X);*/

				//float rboxH = 10 + y * 0.1, rboxW = 10 + x * 0.1;
				float rboxH = 10, rboxW = 10;
				for (int c = 0; c < rboxH; c++) {
					for (int cc = 0; cc < rboxW; cc++) {
						resultImage.setPixel(rboxW * x + cc, rboxH * y + c, sf::Color(m_R, m_G, m_B));
					}
				}
			}
		}

		if (makeHex) { hexFile << "}"; if(y < Y - 1) hexFile << ","; }
		if (UploadResults) { dataFile << "\n"; }
	}
	
	if (makeHex) { hexFile << "\n};"; hexFile.close(); }
	if (UploadResults) { dataFile.close(); resultImage.saveToFile("Images/0 Result.png"); }

}

	if (ReadResults) {

		int i = 0, j = 0, R = 89, G = 0, B = 40;
		vector<vector<colorValue>> read;
		
		dataFile.open("Images/0 Data.txt", ios::in);
		dataFile >> i >> j;
		cout << "i: " << i << ", j: " << j << "\n";
		read.resize(j, vector<colorValue>(i));

		for (int cc = 0; cc < j; cc++) {
			for (int c = 0; c < i; c++) {
				dataFile >> read[cc][c].r >> read[cc][c].g >> read[cc][c].b;
			}
		}

		/*for (int cc = 0; cc < j; cc++) {
			for (int c = 0; c < i; c++) {
				cout << read[cc][c].r << " " << read[cc][c].g << " " << read[cc][c].b << "\n";
			}
		}*/

		for (int y = 0; y < j; y++) {
			for (int x = 0; x < i; x++) {

				R = read[y][x].r; G = read[y][x].g; B = read[y][x].b;
				float rboxH = 10, rboxW = 10;
				for (int c = 0; c < rboxH; c++) {
					for (int cc = 0; cc < rboxW; cc++) {
						generatedImage.setPixel(rboxW * x + cc, rboxW * y + c, sf::Color(R, G, B));
					}
				}
			}
		}

		dataFile.close();
		generatedImage.saveToFile("Images/0 Generated.png");
	}
	;

	if (readHex) {

		int i = 100, j = 75, R = 89, G = 0, B = 40;

		/*dataFile.open("Images/0 Bin.txt", ios::in);
		dataFile >> j >> i;
		cout << "i: " << i << ", j: " << j << "\n";*/

		vector<vector<colorValue>> genColor;
		genColor.resize(j, vector<colorValue>(i));

		/*vector<vector<string>> read;
		read.resize(j, vector<string>(i));*/

		vector<vector<int>> read;
		read.resize(j, vector<int>(i));

		hexFile.open("Images/0 Bin.txt", ios::in);
		for (int cc = 0; cc < j; cc++) {
			for (int c = 0; c < i; c++) {
				hexFile >> read[cc][c];
				//int tempDec = hexToDec(read[cc][c]);
				int tempDec = read[cc][c];
				genColor[cc][c].r = tempDec / 16;
				genColor[cc][c].g = (tempDec % 16) / 4;
				genColor[cc][c].b = tempDec % 4;
				
				genColor[cc][c].r = (genColor[cc][c].r == 0) * 0 + (genColor[cc][c].r == 1) * 85 + (genColor[cc][c].r == 2) * 170 + (genColor[cc][c].r == 3) * 255;
				genColor[cc][c].g = (genColor[cc][c].g == 0) * 0 + (genColor[cc][c].g == 1) * 85 + (genColor[cc][c].g == 2) * 170 + (genColor[cc][c].g == 3) * 255;
				genColor[cc][c].b = (genColor[cc][c].b == 0) * 0 + (genColor[cc][c].b == 1) * 85 + (genColor[cc][c].b == 2) * 170 + (genColor[cc][c].b == 3) * 255;

				cout << read[cc][c] << "\t";
			}
		}
		hexFile.close();

		/*for (int cc = 0; cc < j; cc++) {
			for (int c = 0; c < i; c++) {
				cout << genColor[cc][c].r << " " << genColor[cc][c].g << " " << genColor[cc][c].b << "\n";
			}
		}*/

		for (int y = 0; y < j; y++) {
			for (int x = 0; x < i; x++) {

				R = genColor[y][x].r; G = genColor[y][x].g; B = genColor[y][x].b;
				float rboxH = 10, rboxW = 10;
				for (int c = 0; c < rboxH; c++) {
					for (int cc = 0; cc < rboxW; cc++) {
						generatedImage.setPixel(rboxW * x + cc, rboxW * y + c, sf::Color(R, G, B));
					}
				}
			}
		}

		dataFile.close();
		generatedImage.saveToFile("Images/0 Generated.png");
	}

///////////////////////////////////////////////
	

// ----------------------------------------	Update
		/*for (auto c = entities.begin(); !Pause && c != entities.end();) {
			Entity* e = *c;

			e->update();

			if (e->life <= 0) {
				c = entities.erase(c);
				delete e;
			}
			else c++;
		}*/

	if (Stimuli) {
		texBox.loadFromImage(boxImage);
		spriteBox.setTexture(texBox);
		spriteBox.setPosition(boxOffX, boxOffY);
	}

// ----------------------------------------	Draw
if(Stimuli) {
		app.clear();
		//for (auto d : entities) d->draw(app);

		app.draw(s);
		app.draw(spriteBox);
		/*for (int y = 0; y < Y; y++) {
			for (int x = 0; x < X; x++) {
				app.draw(ScreenArr[y][x]);
			}
		}*/

		app.display();
}
		
		app.setTitle("ScreenSim   " + to_string((float)(CLOCKS_PER_SEC/((float)clock() - (float)frame))));
		frame = clock();
		UploadResults = 0; ReadResults = 0; Stimuli = 0; makeHex = 0, readHex = 0;
	}

END:
	;
	X = 100, Y = 75, m_R = 45, m_G = 100, m_B = 80, boxW = 5, boxH = 5, boxOffX = 0, boxOffY = 0;
}

	system("pause");
}

int B0123(colorValue Col) {

	/*Col.r = (Col.r == 0) * 0 + (Col.r == 85) * 16 + (Col.r == 170) * 32 + (Col.r == 255) * 48;
	Col.g = (Col.g == 0) * 0 + (Col.g == 85) * 4  + (Col.g == 170) * 8  + (Col.g == 255) * 12;
	Col.b = (Col.b == 0) * 0 + (Col.b == 85) * 1  + (Col.b == 170) * 2  + (Col.b == 255) * 3;

	return decToHex(Col.r + Col.g + Col.b);*/

	Col.r = (Col.r == 0) * 0 + (Col.r == 85) * 16 + (Col.r == 170) * 32 + (Col.r == 255) * 48;
	Col.g = (Col.g == 0) * 0 + (Col.g == 85) * 4  + (Col.g == 170) * 8  + (Col.g == 255) * 12;
	Col.b = (Col.b == 0) * 0 + (Col.b == 85) * 1  + (Col.b == 170) * 2  + (Col.b == 255) * 3;

	return Col.r + Col.g + Col.b;

}

string decToHex(int n)
{
	// char array to store hexadecimal number
	char hexaDeciNum[100];
	string returnHex;
	if (n < 16) returnHex = "0";
	// counter for hexadecimal number array
	int i = 0;
	if (n == 0) return "00";

	while (n != 0) {
		// temporary variable to store remainder
		int temp = 0;

		// storing remainder in temp variable.
		temp = n % 16;

		// check if temp < 10
		if (temp < 10) {
			hexaDeciNum[i] = temp + 48;
			i++;
		}
		else {
			hexaDeciNum[i] = temp + 55;
			i++;
		}

		n = n / 16;
	}

	// printing hexadecimal number array in reverse order
	for (int j = i - 1; j >= 0; j--) {
		//cout << "(" << hexaDeciNum[j] << ")";
		returnHex += hexaDeciNum[j];
	}


	return returnHex;
}

int hexToDec(char hexVal)
{
	switch (hexVal) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	case 'A': return 10;
	case 'B': return 11;
	case 'C': return 12;
	case 'D': return 13;
	case 'E': return 14;
	case 'F': return 15;
	default:  return 0; cout << "\nError: hexToDec(Not 0-15) = 0\n"; break;
	}
}

int hexToDec(string hexVal)
{
	int len = hexVal.size();

	// Initializing base value to 1, i.e 16^0
	int base = 1;

	int dec_val = 0;

	// Extracting characters as digits from last
	// character
	for (int i = len - 1; i >= 0; i--) {
		// if character lies in '0'-'9', converting
		// it to integral 0-9 by subtracting 48 from
		// ASCII value
		if (hexVal[i] >= '0' && hexVal[i] <= '9') {
			dec_val += (int(hexVal[i]) - 48) * base;

			// incrementing base by power
			base = base * 16;
		}

		// if character lies in 'A'-'F' , converting
		// it to integral 10 - 15 by subtracting 55
		// from ASCII value
		else if (hexVal[i] >= 'A' && hexVal[i] <= 'F') {
			dec_val += (int(hexVal[i]) - 55) * base;

			// incrementing base by power
			base = base * 16;
		}
	}
	return dec_val;
}

/*

0,0,0	0,0,85		0,0,170		0,0,255			0,85,0		0,85,85		0,85,170	0,85,255		0,170,0		0,170,85	0,170,170	0,170,255			0,255,0	0,255,85	0,255,170	0,255,255

85,0,0	85,0,85		85,0,170	85,0,255		85,85,0		85,85,85	85,85,170	85,85,255		85,170,0	85,170,85	85,170,170	85,170,255			85,255,0	85,255,85	85,255,170	85,255,255

170,0,0	170,0,85	170,0,170	170,0,255		170,85,0	170,85,85	170,85,170	170,85,255		170,170,0	170,170,85	170,170,170	170,170,255			170,255,0	170,255,85	170,255,170	170,255,255

255,0,0	255,0,85	255,0,170	255,0,255		255,85,0	255,85,85	255,85,170	255,85,255		255,170,0	255,170,85	255,170,170	255,170,255			255,255,0	255,255,85	255,255,170	255,255,255

*/