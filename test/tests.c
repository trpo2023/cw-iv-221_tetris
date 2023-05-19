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
// MAIN_LOGIC
CTEST(TETRIS_MAIN_LOGIC, COLLISION_ENTER)
{
    /*
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    tetGame->field->blocks[0].b = 1;
    tetGame->figure->blocks[0].b = 1;
    tetGame->figure->x = 0;
    tetGame->figure->y = 0;
    ASSERT_EQUAL(0, collisionEnter(tetGame));

    tetGame->field->blocks[0].b = 1;
    tetGame->figure->blocks[0].b = 1;
    tetGame->figure->x = 0;
    tetGame->figure->y = 1;
    ASSERT_EQUAL(1, collisionEnter(tetGame));
    freeGameTet(tetGame);
    */
}
CTEST(TETRIS_MAIN_LOGIC, DROP_NEW_FIGURE)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    freeGameTet(tetGame);
}
CTEST(TETRIS_MAIN_LOGIC, PLANT_FIGURE)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    freeGameTet(tetGame);
}
// SCORE
CTEST(TETRIS_SCORE, LINE_TETRIS)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    freeGameTet(tetGame);
}
// MOVEMENT
CTEST(TETRIS_MOVEMENT, ROTATE_FIGURE)
{
    Game* tetGame = createGame(10, 10, 5, 6, templates, 50);
    freeGameTet(tetGame);
}
