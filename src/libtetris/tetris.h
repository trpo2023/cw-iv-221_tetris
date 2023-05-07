#pragma once
#define TICKS_START 60
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

//преречисления движений-7


typedef struct Game {
    Field* field;
    Figure* figure;
    Figures* figures;
    int ticks;
    int ticksLeft;
} Game;

// Создание игровых объектов
Field* createField(int widthT, int heightT);
Figures* createFigures(int countT, int sizeT, Block* templateT);
Game* createGame(int width, int height, int count, int size, Block* template);
Figure *createNewFigure(Game *tetGame);

//движения фигур-7



// Основная логика игры
void dropNewFigure(Game* tetGame);
int collisionEnter(Game* tetGame);
void plantFigure(Game* tetGame);
void calculateTetris(Game* tetGame);
// Освобождение памяти
void freeFigureTet(Figure* f);
void freeFiguresTet(Figures* f);
void freeFieldTet(Field* f);
void freeGameTet(Game* g);
