#include "ctest.h"

#include <libtetris/tetris.h>
// MAIN_LOGIC
CTEST(TETRIS_MAIN_LOGIC, NEW_FIGURE)
{
    // clang-format off
    Block templates[] = {0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0, 
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,};
    // clang-format on
    Game* tetGame = createGame(10, 10, 5, 1, templates, 50);
    Figure* t = createNewFigure(tetGame);
    newFigure(tetGame, 0, t);
    ASSERT_EQUAL(1, tetGame->figure->blocks[2].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[7].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[12].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[17].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[22].b);
    ASSERT_EQUAL(0, tetGame->figure->blocks[24].b);
    freeGameTet(tetGame);
}
CTEST(TETRIS_MAIN_LOGIC, COLLISION_ENTER)
{
    // clang-format off
    Block templates[] = {0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0, 
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,};
    // clang-format on
    Game* tetGame = createGame(10, 10, 5, 1, templates, 50);
    Figure* t = createNewFigure(tetGame);
    newFigure(tetGame, 0, t);
    tetGame->field->blocks[2].b = 1;
    ASSERT_EQUAL(1, collisionEnter(tetGame));

    tetGame->field->blocks[2].b = 0;
    ASSERT_EQUAL(0, collisionEnter(tetGame));
    freeGameTet(tetGame);
}
CTEST(TETRIS_MAIN_LOGIC, PLANT_FIGURE)
{
    // clang-format off
    Block templates[] = {0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0, 
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,};
    // clang-format on
    Game* tetGame = createGame(10, 10, 5, 1, templates, 50);
    Figure* t = createNewFigure(tetGame);
    newFigure(tetGame, 0, t);
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
    // clang-format off
    Block templates[] = {0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0, 
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,};
    // clang-format on
    Game* tetGame = createGame(10, 10, 5, 1, templates, 50);
    Figure* t = createNewFigure(tetGame);
    newFigure(tetGame, 0, t);
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
    // clang-format off
    Block templates[] = {0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0, 
                         0, 0, 1, 0, 0,
                         0, 0, 1, 0, 0,};
    // clang-format on
    Game* tetGame = createGame(10, 10, 5, 1, templates, 50);
    Figure* t = createNewFigure(tetGame);
    newFigure(tetGame, 0, t);
    ASSERT_EQUAL(0, tetGame->figure->blocks[1].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[2].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[7].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[12].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[17].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[22].b);
    tetGame->figure = rotateFigure(tetGame);
    ASSERT_EQUAL(0, tetGame->figure->blocks[1].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[10].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[11].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[12].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[13].b);
    ASSERT_EQUAL(1, tetGame->figure->blocks[14].b);
    freeGameTet(tetGame);
}