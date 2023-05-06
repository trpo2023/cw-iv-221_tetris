#include "tetris.h"
#include <stdlib.h>

Field* createField(int widthT, int heightT)
{
    Field* tetrisField = (Field*)malloc(sizeof(Field));
    tetrisField->width = widthT;
    tetrisField->height = heightT;
    tetrisField->blocks = (Block*)malloc(sizeof(Block) * widthT * heightT);
    for (int i = 0; i < widthT * heightT; i++) {
        tetrisField->blocks[i].b = 0;
    }
    return tetrisField;
}

Figures* createFigures(int countF, int sizeF, Block* templateF)
{
    Figures* tetrisFigures = (Figures*)malloc(sizeof(Figures));
    tetrisFigures->blocks = templateF;
    tetrisFigures->count = countF;
    tetrisFigures->size = sizeF;

    return tetrisFigures;
}
Game* createGame(int width, int height, int size, int count, Block* template)
{
    Game* tetrisGame = (Game*)malloc(sizeof(Game));
    tetrisGame->field = createField(width, height);
    tetrisGame->figures = createFigures(count, size, template);
    return tetrisGame;
}
Figure* createNewFigure(Game* tetGame)
{
    Figure* t = (Figure*)malloc(sizeof(Figure));
    t->x = 0;
    t->y = 0;
    t->size = tetGame->figures->size;
    t->blocks = (Block*)malloc(sizeof(Block) * t->size * t->size);
    return t;
}

void dropNewFigure(Game* tetGame)
{
    Figure* t = createNewFigure(tetGame);

    t->x = tetGame->field->width / 2
            - t->size / 2; // Поставить фигуру по середине
    t->y = 0;

    // Выбрать рандомную фигуру из списка templates()
    int fnum = rand() % tetGame->figures->count;
    for (int i = 0; i < t->size; i++) {
        for (int j = 0; j < t->size; j++) {
            // Присваиваем значени текущей фигуры из списка всех
            // фигур(templates), т.е. t - это текущая фигура

            t->blocks[i * t->size + j].b
                    = tetGame->figures
                              ->blocks
                                      [fnum * t->size * t->size + i * t->size
                                       + j]
                              .b;
        }
    }

    // Меняем на новую фигуру
    freeFigureTet(tetGame->figure);
    tetGame->figure = t;
}

void freeFigureTet(Figure* f)
{
    if (f != NULL) {
        free(f->blocks);
    }
    free(f);
}
void freeFiguresTet(Figures* f)
{
    free(f);
}
void freeFieldTet(Field* f)
{
    if (f != NULL)
        free(f->blocks);
    free(f);
}
void freeGameTet(Game* g)
{
    if (g != NULL) {
        freeFieldTet(g->field);
        freeFiguresTet(g->figures);
        free(g);
    }
}