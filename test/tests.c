#include "ctest.h"

#include <libtetris/tetris.h>
Block templates[] = {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
                     0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1,
                     0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1,
                     0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1,
                     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,

                     0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1,
                     1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/*
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
*/
static void createNewFigureTest(Game* tetGame)
{
    Figure* t = createNewFigure(tetGame);

    t->x = 0;
    t->y = 0;

    // Выбрать рандомную фигуру из списка templates()
    int fnum = 0;

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
// MAIN_LOGIC
CTEST(TETRIS_MAIN_LOGIC, COLLISION_ENTER)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    createNewFigureTest(tetGame);
    tetGame->field->blocks[2].b = 1;
    ASSERT_EQUAL(1, collisionEnter(tetGame));

    tetGame->field->blocks[2].b = 0;
    ASSERT_EQUAL(0, collisionEnter(tetGame));
    freeGameTet(tetGame);
}
CTEST(TETRIS_MAIN_LOGIC, DROP_NEW_FIGURE)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    createNewFigureTest(tetGame);
    ASSERT_EQUAL(1, tetGame->figure->blocks[2].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[7].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[12].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[17].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[22].b);
    ASSERT_EQUAL(0, tetGame->figure->blocks[24].b);
    freeGameTet(tetGame);
}
CTEST(TETRIS_MAIN_LOGIC, PLANT_FIGURE)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    createNewFigureTest(tetGame);
    plantFigure(tetGame);
    ASSERT_EQUAL(1, tetGame->field->blocks[2].b);
    ASSERT_EQUAL(1, tetGame->field->blocks[12].b);
    ASSERT_EQUAL(1, tetGame->field->blocks[22].b);
    ASSERT_EQUAL(1, tetGame->field->blocks[32].b);
    ASSERT_EQUAL(1, tetGame->field->blocks[42].b);
    ASSERT_EQUAL(0, tetGame->field->blocks[52].b);
    freeGameTet(tetGame);
}
// SCORE
CTEST(TETRIS_SCORE, LINE_TETRIS)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    createNewFigureTest(tetGame);
    ASSERT_EQUAL(0, lineTetris(tetGame));
    for (int i = 0; i < 11; i++) {
        tetGame->field->blocks[i].b = 1;
    }
    ASSERT_EQUAL(1, lineTetris(tetGame));
    freeGameTet(tetGame);
}
// MOVEMENT
CTEST(TETRIS_MOVEMENT, ROTATE_FIGURE)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    createNewFigureTest(tetGame);
    ASSERT_EQUAL(1, tetGame->figure->blocks[2].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[7].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[12].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[17].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[22].b);
    tetGame->figure = rotateFigure(tetGame);
    ASSERT_EQUAL(1, tetGame->figure->blocks[10].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[11].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[12].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[13].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[14].b);
    freeGameTet(tetGame);
}
