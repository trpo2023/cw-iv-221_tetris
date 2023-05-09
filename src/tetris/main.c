#include <ncurses.h>
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
            int symbol = 1;

            if (tf->blocks[i * tf->width + j].b
                != 0) { // Если текущий блок не пуст, то выводим его на экран
                symbol = 2;
            } else {
                int x = j - t->x;
                int y = i - t->y;

                if (x >= 0 && x < t->size && y >= 0 && y < t->size) {
                    if (t->blocks[y * t->size + x].b != 0) {
                        symbol = 2;
                    }
                }
            }
            attron(COLOR_PAIR(symbol));
            mvaddch(i, j, ' ');
            attroff(COLOR_PAIR(symbol));
        }
    }
}

int main()
{
    struct timespec start, end, ts1, ts2 = {0, 0};

    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    cbreak();
    noecho();
    nodelay(stdscr, TRUE);
    scrollok(stdscr, TRUE);

    Game* tetGame = createGame(34, 30, 5, 6, templates);

    Player player;
    player.action = PLAYER_NON;
    tetGame->player = &player;
    dropNewFigure(tetGame);
    while (tetGame->playing != TET_GAMEOVER) {
        clock_gettime(
                CLOCK_MONOTONIC, &start); // фикируем начальный момент времени

        int ch = getch();
        switch (ch) {
        case 'w':
            player.action = PLAYER_UP;
            break;

        case 's':
            player.action = PLAYER_DOWN;
            break;

        case 'a':
            player.action = PLAYER_LEFT;
            break;

        case 'd':
            player.action = PLAYER_RIGHT;
            break;

        case 'q':
            tetGame->playing = TET_GAMEOVER;
            break;

        case 'p':
            getchar();
            break;

        default:
            player.action = PLAYER_NON;
            break;
        }

        calculateTetris(tetGame);
        printGame(tetGame);

        attron(COLOR_PAIR(1));
        mvprintw(0, 0, "Score: %d", tetGame->score);
        move(tetGame->field->height + 1, tetGame->field->width + 1);
        attroff(COLOR_PAIR(1));

        refresh();
        clock_gettime(CLOCK_MONOTONIC, &end);
        if (end.tv_sec - start.tv_sec <= 0
            && (ts2.tv_nsec = 33000000 - (end.tv_nsec - start.tv_nsec)) > 0) {
            nanosleep(&ts2, &ts1);
        }
    }
    freeGameTet(tetGame);
    endwin();
    return 0;
}