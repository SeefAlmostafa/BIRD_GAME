
#include "bird_game.h"

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
COORD CursorPosition;

BIRD_GAME::BIRD_GAME() : 
screen_width(90),
screen_height(26),
window_width(70),
menu_width(20),
gap_size(7),
pipe_dif(45) {
	setup();
}

void BIRD_GAME::set_score(int score) {
	this->score = score;
}

void BIRD_GAME::set_birdPos(int birdPos) {
	this->birdPos = birdPos;
}

void BIRD_GAME::set_pipePos(int index, int val) {
	this->pipePos[index] = val;
}

void BIRD_GAME::set_gapPos(int index, int val) {
	this->gapPos[index] = val;
}

void BIRD_GAME::set_pipeFlag(int index, int val) {
	this->pipeFlag[index] = val;
}

int BIRD_GAME::get_score() const {
	return this->score;
}

int BIRD_GAME::get_birdPos() const {
	return this->birdPos;
}

const int* BIRD_GAME::get_pipePos() const {
	return pipePos;
}

const int* BIRD_GAME::get_gapPos() const {
	return this->gapPos;
}

const bool* BIRD_GAME::get_pipeFlag() const {
	return this->pipeFlag;
}

void BIRD_GAME::setup() {
	srand((unsigned)time(NULL));
	setcursor(0, 0);
	Reset();
}

void BIRD_GAME::gotoxy(int x, int y) {
	COORD CursorPosition;
	CursorPosition.X = x;
	CursorPosition.Y = y;
	SetConsoleCursorPosition(console, CursorPosition);
}

void BIRD_GAME::setcursor(bool visible, DWORD size) {
	if (size == 0)
		size = 50;
	
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = size;
	SetConsoleCursorInfo(console, &lpCursor);
}

void BIRD_GAME::drawBorder() {
	for (int i = 0; i < screen_width; i++) {
		gotoxy(i, 0);
		cout << "±";
		gotoxy(i, screen_height);
		cout << "±";
	}

	for (int i = 0; i < screen_height; i++) {
		gotoxy(0, i);
		cout << "±";
		gotoxy(screen_width, i);
		cout << "±";
	}

	for (int i = 0; i < screen_height; i++) {
		gotoxy(window_width, i);
		cout << "±";
	}
}

void BIRD_GAME::genPipe(int index) {
	gapPos[index] = 3 + rand() % 14;
}

void BIRD_GAME::drawPipe(int index) {
	if (pipeFlag[index] == true) {
		for (int i = 0; i < gapPos[index]; i++) {
			gotoxy(window_width - pipePos[index], i + 1);
			cout << "\xB2\xB2\xB2";
		}
		for (int i = gapPos[index] + gap_size; i < screen_height - 1; i++) {
			gotoxy(window_width - pipePos[index], i + 1);
			cout << "\xB2\xB2\xB2";
		}
	}
}

void BIRD_GAME::erasePipe(int index) {
	if (pipeFlag[index] == true) {
		for (int i = 0; i < gapPos[index]; i++) {
			gotoxy(window_width - pipePos[index], i + 1);
			cout << "   ";
		}
		for (int i = gapPos[index] + gap_size; i < screen_height - 1; i++) {
			gotoxy(window_width - pipePos[index], i + 1);
			cout << "   ";
		}
	}
}

void BIRD_GAME::drawBird() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + birdPos);
			cout << bird[i][j];
		}
	}
}

void BIRD_GAME::eraseBird() {
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 6; j++) {
			gotoxy(j + 2, i + birdPos);
			cout << " ";
		}
	}
}

void BIRD_GAME::debug() {
	//gotoxy(screen_height + 3, 4); cout << "Pipe Pos: " << pipePos[0];
}

void BIRD_GAME::Reset() {
	set_birdPos(6);
	set_score(0);
	set_pipeFlag(0, 1);
	set_pipeFlag(1, 0);
	set_pipePos(0, 4);
	set_pipePos(1, 4);
}

void BIRD_GAME::Logic() {
	Reset();
	system("cls");
	drawBorder();
	genPipe(0);
	updateScore();
	info();

	while (true) {
		if (_kbhit()) {
			char ch = _getch();
			if (ch == 32) {
				if (birdPos > 3)
					birdPos -= 3;
			}
			if (ch == 27) {
				break;
			}
		}

		drawBird();
		drawPipe(0);
		drawPipe(1);
		//debug();
		if (collision()) {
			gameover();
			return;
		}
		Sleep(100);
		eraseBird();
		erasePipe(0);
		erasePipe(1);
		birdPos += 1;

		if (birdPos > screen_height - 2) {
			gameover();
			return;
		}

		if (pipeFlag[0] == 1)
			pipePos[0] += 2;

		if (pipeFlag[1] == 1)
			pipePos[1] += 2;

		if (pipePos[0] >= 40 && pipePos[0] < 42) {
			pipeFlag[1] = 1;
			pipePos[1] = 4;
			genPipe(1);
		}
		if (pipePos[0] > 68) {
			score++;
			updateScore();
			pipeFlag[1] = 0;
			pipePos[0] = pipePos[1];
			gapPos[0] = gapPos[1];
		}
	}
}

void BIRD_GAME::gameover() {
	system("cls");
	cout << endl;
	cout << "\t\t--------------------------" << endl;
	cout << "\t\t-------- Game Over -------" << endl;
	cout << "\t\t--------------------------" << endl
		<< endl;
	cout << "\t\tPress any key to go back to menu.";
	int ch = _getch();
}

void BIRD_GAME::updateScore() {
	gotoxy(window_width + 30, 5);
	cout << "Score: " << score << endl;
}

void BIRD_GAME::info() {
	
	gotoxy(window_width + 30, 2);
	cout << "Game";

	gotoxy(window_width + 30, 8);
	cout << "press_space";
	
	
	gotoxy( 2, 7);
	cout << "Press any key to start";
	int ch = _getch();
	
	system("cls");
	updateScore();
}

void BIRD_GAME::instructions() {
	system("cls");
	cout << "Instructions";
	cout << "\n----------------";
	cout << "\n Press spacebar to make bird fly";
	cout << "\n\nPress any key to go back to menu";
	int ch = _getch();
}

void BIRD_GAME::run() {
	do {
		system("cls");
		gotoxy(10, 5);
		cout << " -------------------------- ";
		gotoxy(10, 6);
		cout << " |      Flappy Bird       | ";
		gotoxy(10, 7);
		cout << " --------------------------";
		gotoxy(10, 9);
		cout << "1. Start Game";
		gotoxy(10, 10);
		cout << "2. Instructions";
		gotoxy(10, 11);
		cout << "3. Quit";
		gotoxy(10, 13);
		cout << "Select option: ";
		int ip = _getche();
		char op = (char)ip;

		if (op == '1')
			Logic();
		else if (op == '2')
			instructions();
		else if (op == '3')
			exit(0);

	} while (true);
}

bool BIRD_GAME::collision() {
	if (pipePos[0] >= 61) {
		if (birdPos < gapPos[0] || birdPos > gapPos[0] + gap_size) {
			return true;
		}
	}
	return false;
}