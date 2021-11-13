#include<iostream>
#include<conio.h>
#include<windows.h>

using namespace std;

bool gameover;

const int width = 20;
const int height = 20;

int x, y;
int fruitX;
int fruitY;
int score;
int tailX[100], tailY[100];
int nTail;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;

HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

void setup(){

	gameover = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}

void draw(){

	system("cls");
	
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	for (int i = 0; i < width; i++){
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			if (j == 0){
				cout << "#";
			}
			if (i == y && j == x){
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				cout << "0";
			}
			else if (i == fruitY && j == fruitX){
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				
				cout << "@";
			}
			else{
				HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);
				
				bool print = false;
				
				for (int k = 0; k < nTail; k++){

					if (tailX[k] == j && tailY[k] == i){
						cout << "o";
						print = true;
					}
				}
				if (!print){
					cout << " ";
				}

			}
			
			HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(h, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
			
			if (j == width - 1){
				cout << "#";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++){
		cout << "#";
	}
	cout << endl;
	cout << "Score= " << score << endl;
}

void input(){

	if (_kbhit()){
		
		switch (_getch()){
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			gameover = true;
			break;
		}
	}

}

void logic(){

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	
	for (int i = 1; i < nTail; i++){
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir){
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}

	if (x > width || x < 0 || y > height || y < 0){
		gameover = true;
		cout << "Game Ended !!!" << endl;
	}

	if (x == fruitX && y == fruitY){
		score += 10;
		fruitX = rand() % width;
		fruitY = rand() % height;
		nTail++;
	}
}

void PlayGame() {
	setup();
	while (!gameover) {
		draw();
		input();
		logic();
		Sleep(10);
	}
}

int main(){
	PlayGame();
	char op;
	while(true){
		cout << "Want to Play Again?(y/n): ";
		cin >> op;
		if (op == 'y') {
			PlayGame();
		}
		else if (op == 'n') {
			break;
		}
	}
	
	system("pause");
}
