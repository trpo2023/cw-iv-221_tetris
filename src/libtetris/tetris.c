
#include <stdlib.h>

#include "tetris.h"
// Создание
Game* createGame(
        int width, int height, int size, int count, Block* template, int speed)
{
    Game* tetrisGame = (Game*)malloc(sizeof(Game));

    if (tetrisGame == NULL)
        return NULL;

    tetrisGame->field = createField(width, height);
    tetrisGame->figures = createFigures(count, size, template);

    tetrisGame->ticks = speed;
    tetrisGame->ticksLeft = speed;

    tetrisGame->score = 0;
    tetrisGame->playing = TET_PLAYING;
    return tetrisGame;
}
Field* createField(int widthT, int heightT)
{
    Field* tetrisField = (Field*)malloc(sizeof(Field));

    if (tetrisField == NULL)
        return NULL;

    tetrisField->width = widthT;
    tetrisField->height = heightT;
    tetrisField->blocks = (Block*)malloc(sizeof(Block) * widthT * heightT);

    if (tetrisField->blocks == NULL)
        return NULL;

    for (int i = 0; i < widthT * heightT; i++) {
        tetrisField->blocks[i].b = 0;
    }

    return tetrisField;
}
Figures* createFigures(int countF, int sizeF, Block* templateF)
{
    Figures* tetrisFigures = (Figures*)malloc(sizeof(Figures));

    if (tetrisFigures == NULL)
        return NULL;

    tetrisFigures->blocks = templateF;
    tetrisFigures->count = countF;
    tetrisFigures->size = sizeF;

    return tetrisFigures;
}
Figure* createNewFigure(Game* tetGame)
{
    Figure* t = (Figure*)malloc(sizeof(Figure));

    if (t == NULL)
        return NULL;

    t->x = 0;
    t->y = 0;
    t->size = tetGame->figures->size;
    t->blocks = (Block*)malloc(sizeof(Block) * t->size * t->size);

    if (t->blocks == NULL)
        return NULL;

    return t;
}
// Движение
void moveFigureDown(Game* tetGame)
{
    tetGame->figure->y++;
}
void moveFigureUp(Game* tetGame)
{
    tetGame->figure->y--;
}
void moveFigureRight(Game* tetGame)
{
    tetGame->figure->x++;
}
void moveFigureLeft(Game* tetGame)
{
    tetGame->figure->x--;
}
Figure* rotateFigure(Game* tetGame)
{
    Figure* t = createNewFigure(tetGame);
    Figure* old = tetGame->figure;

    t->x = old->x;
    t->y = old->y;

    for (int i = 0; i < t->size; i++) {
        for (int j = 0; j < t->size; j++) {
            t->blocks[i * t->size + j].b
                    = old->blocks[j * t->size + t->size - 1 - i].b;
        }
    }

    return t;
}
// Логика
void calculateTetris(Game* tetGame)
{                                  // Прочсет одного такта
    if (tetGame->ticksLeft <= 0) { // Этот if замедляет игру
        tetGame->ticksLeft = tetGame->ticks; // Возобновляем "таймер"
        moveFigureDown(tetGame);

        if (collisionEnter(tetGame)) {
            moveFigureUp(tetGame);
            plantFigure(tetGame);
            tetGame->score += lineTetris(tetGame);
            dropNewFigure(tetGame);

            if (collisionEnter(
                        tetGame)) { // если коллизия произошла вновь, то нет
                                    // места, а следовательно игра окончена
                tetGame->playing = TET_GAMEOVER;
                return;
            }
        }
    }
    switch (tetGame->player->action) {
        case PLAYER_DOWN: {
            moveFigureDown(tetGame);
            if (collisionEnter(tetGame))
                moveFigureUp(tetGame);
            break; }
        case PLAYER_UP: {
            Figure* t = rotateFigure(tetGame);
            Figure* old = tetGame->figure;
            tetGame->figure = t;
            if (collisionEnter(tetGame)) {
                tetGame->figure = old;
                freeFigureTet(t);
            } else {
                freeFigureTet(old);
            }
            break;}
        case PLAYER_LEFT: {
            moveFigureLeft(tetGame);
            if (collisionEnter(tetGame))
                moveFigureRight(tetGame);
            break; }
        case PLAYER_RIGHT: {
            moveFigureRight(tetGame);
            if (collisionEnter(tetGame))
                moveFigureLeft(tetGame);
            break; }
        case PLAYER_NON: {
        default:
            break; }
        }
        tetGame->ticksLeft--;
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
    int collisionEnter(Game* tetGame)
    {
        Figure* t = tetGame->figure;
        Field* tf = tetGame->field;

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
    void plantFigure(Game* tetGame)
    {
        Figure* t = tetGame->figure;

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
    // Подсчет очков
    void dropLine(int i, Field* tfl)
    {
        if (i == 0) { // Елси строка нулевая, то очищаем
            for (int j = 0; j < tfl->width; j++) {
                tfl->blocks[j].b = 0;
            }
        } else { // перенос строк ниже
            for (int k = i; k > 0; k--) {
                for (int j = 0; j < tfl->width; j++) {
                    tfl->blocks[k * tfl->width + j].b
                            = tfl->blocks[(k - 1) * tfl->width + j].b;
                }
            }
        }
    }
    int lineFilled(int i, Field* tfl) // Проверяет заполнена ли строка
    {
        for (int j = 0; j < tfl->width; j++) {
            if (tfl->blocks[i * tfl->width + j].b == 0) {
                return 0;
            }
        }

        return 1;
    }
    int lineTetris(Game* tetGame) // удаляет заполнненые строки
    {
        Field* tfl = tetGame->field;
        int count = 0; // Подсчитывай количество полных строк

        for (int i = tfl->height - 1; i >= 0; i--) {
            while (lineFilled(i, tfl)) {
                dropLine(i, tfl);
                count++;
            }
        }

        return count;
    }
    // Освобождение памяти
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
        if (f != NULL) {
            free(f->blocks);
        }

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
