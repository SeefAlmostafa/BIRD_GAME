#pragma once
#include <conio.h>
#include <dos.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#include <cstring>
#include <iostream>
using namespace std;

class BIRD_GAME {
   private:
    const int screen_width;
    const int screen_height;
    const int window_width;
    const int menu_width;
    const int gap_size;
    const int pipe_dif;

    int pipePos[3];
    int gapPos[3];
    bool pipeFlag[3];
    char bird[2][6] = {'/', '-', '-', 'o', '\\', ' ',
                       '|', '_', '_', '_', ' ', '>'};
    int birdPos;
    int score;

   public:
    BIRD_GAME();

    void set_score(int score);
    void set_birdPos(int birdPos);
    void set_pipePos(int index, int val);
    void set_gapPos(int index, int val);
    void set_pipeFlag(int index, int val);
    int get_score() const;
    int get_birdPos() const;
    const int* get_pipePos() const;
    const int* get_gapPos() const;
    const bool* get_pipeFlag() const;

    void setup();
    void gotoxy(int x, int y);
    void setcursor(bool visible, DWORD size);
    void drawBorder();
    void genPipe(int index);
    void drawPipe(int index);
    void erasePipe(int index);
    void drawBird();
    void eraseBird();
    void debug();
    void Reset();
    void Logic();
    void gameover();
    void updateScore();
    void info();
    void instructions();
    void run();
    bool collision();
};