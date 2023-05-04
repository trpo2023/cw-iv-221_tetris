#pragma once

typedef struct Block {
    int b; // присутствует ли блок на поле
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

typedef struct Game {
    Field* field;
    Figure* figure;
    Figures* figures;
} Game;

Field* createField(int widthT, int heightT);
Figures* createFigures(int countT, int sizeT, Block* templateT);
Game* createGame(int width, int height, int count, int size, Block* template);
Figure* createNewFigure(Game* tetGame);
void freeFigureTet(Figure* f);
void freeFiguresTet(Figures* f);
void freeFieldTet(Field* f);
void freeGameTet(Game* g);