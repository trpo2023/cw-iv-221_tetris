#include <stdio.h>
#include <time.h>

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
void printGame(Game* tetGame)
{
    Field* tf = tetGame->field;
    Figure* t = tetGame->figure;
    for (int i = 0; i < tf->height; i++) {
        for (int j = 0; j < tf->width; j++) {
            int symbol = 0;
            if (tf->blocks[i * tf->width + j].b
                != 0) // Если текущий блок не пуст, то выводим его на экран
            {
                symbol = 1;
            } else {
                int x = j - t->x;
                int y = i - t->y;
                if (x >= 0 && x < t->size && y >= 0 && y < t->size) {
                    if (t->blocks[y * t->size + x].b != 0) {
                        symbol = 1;
                    }
                }
            }
            printf("%d", symbol);
        }
    }
}
int main()
{
    Game* tetGame = createGame(34, 30, 5, 6, templates);
    dropNewFigure(tetGame);
    while (1) {
        calculateTetris(tetGame);
        printGame(tetGame);
    }
    freeGameTet(tetGame);
    return 0;
}