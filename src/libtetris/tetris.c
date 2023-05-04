#include <stdlib.h>
#include "tetris.h"

Field *createField(int widthT, int heightT)
{
    Field *tetrisField = (Field *)malloc(sizeof(Field));
    tetrisField->width = widthT;
    tetrisField->height = heightT;
    tetrisField->blocks = (Block *)malloc(sizeof(Block) * widthT * heightT);
    for (int i = 0; i < widthT * heightT; i++)
    {
        tetrisField->blocks[i].b = 0;
    }
    return tetrisField;
}

Figures *createFigures(int countF, int sizeF, Block *templateF)
{
    Figures *tetrisFigures = (Figures *)malloc(sizeof(Figures));
    tetrisFigures->blocks = templateF;
    tetrisFigures->count = countF;
    tetrisFigures->size = sizeF;

    return tetrisFigures;
}

Game *createGame(int width, int height, int size, int count, Block *template)
{
    Game *tetrisGame = (Game *)malloc(sizeof(Game));
    tetrisGame->field = createField(width, height);
    tetrisGame->figures = createFigures(count, size, template);
    return tetrisGame;
}

Figure *createNewFigure(Game *tetGame)
{
    Figure *t = (Figure *)malloc(sizeof(Figure));
    t->x = 0;
    t->y = 0;
    t->size = tetGame->figures->size;
    t->blocks = (Block *)malloc(sizeof(Block) * t->size * t->size);
    return t;
}