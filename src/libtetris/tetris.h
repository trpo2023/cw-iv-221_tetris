#pragma once
typedef struct Block {
    int b; // присутствует ли блок (если 1, то да, елси 0, то нет)
} Block;

typedef struct Field {
    int width;
    int height;
    Block* blocks;
} Field;

typedef struct Figure {
    int x;
    int y;
    int size;
    Block* blocks;
} Figure;

typedef struct Figures {
    int count;
    int size;
    Block* blocks;
} Figures;

// преречисления движений-7
enum { PLAYER_NON = 0, PLAYER_UP, PLAYER_DOWN, PLAYER_LEFT, PLAYER_RIGHT };
typedef struct player {
    int action;
} Player;

typedef struct Game {
    Field* field;
    Figure* figure;
    Figures* figures;
    Player* player;
    int ticks;
    int ticksLeft;
    int score;
    int playing;
} Game;

// Создание игровых объектов
Field* createField(int widthT, int heightT);
Figures* createFigures(int countT, int sizeT, Block* templateT);
Game* createGame(
        int width, int height, int count, int size, Block* template, int speed);
Figure* createNewFigure(Game* tetGame);

// движения фигур-7
// движения фигур (прототипы)
void moveFigureDown(Game* tetGame);
void moveFigureUp(Game* tetGame);
void moveFigureRight(Game* tetGame);
void moveFigureLeft(Game* tetGame);
Figure* rotateFigure(Game* tetGame);

// Основная логика игры
void calculateTetris(Game* tetGame);
void dropNewFigure(Game* tetGame);
int collisionEnter(Game* tetGame);
void plantFigure(Game* tetGame);

// очки
void dropLine(int i, Field* tfl);
int lineFilled(int i, Field* tfl);
int lineTetris(Game* tetGame);
enum { TET_GAMEOVER = 0, TET_PLAYING };

// Освобождение памяти
void freeFigureTet(Figure* f);
void freeFiguresTet(Figures* f);
void freeFieldTet(Field* f);
void freeGameTet(Game* g);