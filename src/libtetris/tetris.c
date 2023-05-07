#include <stdlib.h>
#include "tetris.h"

Field * createField(int widthT, int heightT) {
    Field *tetrisField = (Field *)malloc(sizeof(Field));

    tetrisField->width = widthT;
    tetrisField->height = heightT;
    tetrisField->blocks = (Block *)malloc(sizeof(Block) * widthT * heightT);

    for (int i = 0; i < widthT * heightT; i++) {
        tetrisField->blocks[i].b = 0;
    }

    return tetrisField;
}

Figures * createFigures(int countF, int sizeF, Block *templateF) {
    Figures *tetrisFigures = (Figures *)malloc(sizeof(Figures));

    tetrisFigures->blocks = templateF;
    tetrisFigures->count = countF;
    tetrisFigures->size = sizeF;

    return tetrisFigures;
}

Game * createGame(int width, int height, int size, int count, Block *template) {
    Game *tetrisGame = (Game *)malloc(sizeof(Game));

    tetrisGame->field = createField(width, height);
    tetrisGame->figures = createFigures(count, size, template);

    tetrisGame->ticks = TICKS_START;
    tetrisGame->ticksLeft = TICKS_START;

    return tetrisGame;
}

void moveFigureDown(Game *tetGame) {
    tetGame->figure->y++;
}

void moveFigureUp(Game *tetGame) {
    tetGame->figure->y--;
}

void moveFigureRight(Game *tetGame) {
    tetGame->figure->x++;
}

void moveFigureLeft(Game *tetGame) {
    tetGame->figure->x--;
}

Figure * rotateFigure(Game *tetGame) {
    Figure *t = createNewFigure(tetGame);
    Figure *old = tetGame->figure;

    t->x = old->x;
    t->y = old->y;

    for (int i = 0; i < t->size; i++) {
        for (int j = 0; j < t->size; j++) {
            t->blocks[i * t->size + j].b = old->blocks[j * t->size + t->size - 1 - i].b;
        }
    }

    return t;
}

Figure * createNewFigure(Game *tetGame) {
    Figure *t = (Figure *)malloc(sizeof(Figure));

    t->x = 0;
    t->y = 0;
    t->size = tetGame->figures->size;
    t->blocks = (Block *)malloc(sizeof(Block) * t->size * t->size);
    return t;
}

void dropNewFigure(Game *tetGame) {
    Figure *t = createNewFigure(tetGame);

    t->x = tetGame->field->width / 2
        - t->size / 2;     // Поставить фигуру по середине
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

int collisionEnter(Game *tetGame) {
    Figure *t = tetGame->figure;
    Field *tf = tetGame->field;

    for (int i = 0; i < t->size; i++) { // i - y, j - x
        for (int j = 0; j < t->size; j++) {
            if (t->blocks[i * t->size + j].b != 0) {
                int fx = t->x + j;
                int fy = t->y + i;

                if (tf->blocks[fy * tf->width + fx].b
                    != 0) { // Если столкнулся с другим блоком
                    return 1;
                }

                if (fx < 0 || fx >= tf->width || fy < 0
                    || fy >= tf->height) { // Елси столкнулся с границей
                    return 1;
                }
            }
        }
    }

    return 0;
}

void plantFigure(Game *tetGame) {
    Figure *t = tetGame->figure;

    for (int i = 0; i < t->size; i++) {
        // j - строка, i - столбец
        for (int j = 0; j < t->size; j++) {
            if (t->blocks[i * t->size + j].b != 0) {
                // Размещение текущей фигуры на поле(выполняется при Collision)
                int fx = t->x + j;
                int fy = t->y + i;
                tetGame->field->blocks[fy * tetGame->field->width + fx].b
                    = t->blocks[i * t->size + j].b;
            }
        }
    }
}

void dropLine(int i, Field *tfl)
{
    if (i == 0) // Елси строка нулевая, то очищаем
    {
        for (int j = 0; j < tfl->width; j++)
        {
            tfl->blocks[j].b = 0;
        }
    }
    else // перенос строк ниже
    {
        for (int k = i; k > 0; k--)
        {
            for (int j = 0; j < tfl->width; j++)
            {
                tfl->blocks[k * tfl->width + j].b = tfl->blocks[(k - 1) * tfl->width + j].b;
            }
        }
    }
}

void calculateTetris(Game *tetGame) { // Прочсет одного такта
    if (tetGame->ticksLeft <= 0) { // Этот if замедляет игру
        tetGame->ticksLeft = tetGame->ticks; // Возобновляем "таймер"
        tetGame->figure->y++;

        if (collisionEnter(tetGame)) {
            tetGame->figure->y--;
            plantFigure(tetGame);
            dropNewFigure(tetGame);

            if (collisionEnter(
                    tetGame)) {   // если коллизия произошла вновь, то нет
                                  // места, а следовательно игра окончена
                // game over
                return;
            }
        }
    }

    tetGame->ticksLeft--;
}

void freeFigureTet(Figure *f) {
    if (f != NULL) {
        free(f->blocks);
    }

    free(f);
}

void freeFiguresTet(Figures *f) {
    free(f);
}

void freeFieldTet(Field *f) {
    if (f != NULL) {
        free(f->blocks);
    }

    free(f);
}

void freeGameTet(Game *g) {
    if (g != NULL) {
        freeFieldTet(g->field);
        freeFiguresTet(g->figures);
        free(g);
    }
}
