#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include <ncurses.h>

#include <libtetris/tetris.h>
void printGame(Game* tetGame)
{
    Field* tf = tetGame->field;
    Figure* t = tetGame->figure;

    for (int i = 0; i < tf->height; i++) {
        for (int j = 0; j < tf->width; j++) {
            int symbol = 1;

            // Если текущий блок не пуст, то выводим его на экран
            if (tf->blocks[i * tf->width + j].b != 0) {
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

int main(int argc, char* argv[])
{
    srand(time(NULL));
    // clang-format off
    Block templates[] = {0, 0, 1, 0, 0, 
                        0, 0, 1, 0, 0, 
                        0, 0, 1, 0, 0, 
                        0, 0, 1, 0, 0, 
                        0, 0, 1, 0, 0,

                        0, 0, 0, 0, 0, 
                        0, 0, 1, 0, 0, 
                        0, 1, 1, 1, 0, 
                        0, 0, 0, 0, 0, 
                        0, 0, 0, 0, 0,

                        0, 0, 0, 0, 0, 
                        0, 0, 1, 1, 0, 
                        0, 0, 1, 0, 0, 
                        0, 0, 1, 0, 0, 
                        0, 0, 0, 0, 0,

                        0, 0, 0, 0, 0, 
                        0, 1, 1, 0, 0, 
                        0, 0, 1, 0, 0, 
                        0, 0, 1, 0, 0, 
                        0, 0, 0, 0, 0,

                        0, 0, 0, 0, 0, 
                        0, 0, 1, 1, 0, 
                        0, 1, 1, 0, 0, 
                        0, 0, 0, 0, 0, 
                        0, 0, 0, 0, 0,

                        0, 0, 0, 0, 0, 
                        0, 1, 1, 0, 0, 
                        0, 0, 1, 1, 0, 
                        0, 0, 0, 0, 0, 
                        0, 0, 0, 0, 0};
    // clang-format on
    FILE* fr = fopen("max/score.txt", "r");
    if (!fr) {
        printf("Не удалось открыть файл\n");
        exit(1);
    }
    char str[10];
    fgets(str, 10, fr);
    int max = atoi(str);
    if (menu() == 1)
        exit(0);
    int width = 25;
    int height = 25;
    int speed = 45;
    if (argc == 4) {
        if (atoi(argv[1]) != 0)
            width = atoi(argv[1]);
        if (atoi(argv[2]) != 0)
            height = atoi(argv[2]);
        if (atoi(argv[3]) != 0)
            speed = atoi(argv[3]);
    }

    struct timespec start, end, ts1,
            ts2 = {0, 0}; // снижает частоту срабатывания игрового цикла до 30
                          // кадров в секунду

    initscr(); // Инициализирует библиотеку curses, выделяет память для структур
    start_color(); // инициализировать цвета
    // второй аргумет - цвет, третий аргумет - фон
    init_pair(1, COLOR_WHITE, COLOR_MAGENTA);
    init_pair(2, COLOR_GREEN, COLOR_GREEN);
    cbreak(); // Позволяет сочетаниями клавиш ctrl+c или ctrl+z прерывать
              // выполнение программы, елси заменить на raw(), то эти сочетания
              // клавиш не будут оказывать на приложение никакого эффекта
    noecho(); // отключает вывод нажатых клавиш
    nodelay(stdscr, TRUE); // отключает задержку при вызове функции getch
    scrollok(stdscr, TRUE); // отключает скроллинг

    Game* tetGame = createGame(width, height, 5, 6, templates, speed);

    Player player;
    player.action = PLAYER_NON;
    tetGame->player = &player;
    dropNewFigure(tetGame);
    while (tetGame->playing != TET_GAMEOVER) {
        clock_gettime(
                CLOCK_MONOTONIC, &start); // фикируем начальный момент времени
        // CLOCK_MONOTONIC - часы, которые  показывают монотонный ход времени
        // отсчитываемой с некой неопределённой начальной точки

        int ch = getch(); // Как getchar(), но не надо жать Enter после ввода
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

        case 'q': {
            fclose(fr);
            if (tetGame->score > max) {
                FILE* fw = fopen("max/score.txt", "w");
                if (!fw) {
                    printf("Не удалось открыть файл\n");
                    exit(1);
                }
                fprintf(fw, "%d", tetGame->score);
                fclose(fw);
            }

            freeGameTet(tetGame);
            endwin();
            exit(0);
        } break;

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
        mvprintw(0, 0, "Score: %d   MAX SCORE: %d", tetGame->score, max);
        move(tetGame->field->height + 1, tetGame->field->width + 1);
        attroff(COLOR_PAIR(1));

        refresh();

        clock_gettime(
                CLOCK_MONOTONIC, &end); // фикируем конечный момент времени

        // 1 условие - если расчет игры
        // произошел меньше, чем за секунду
        // Во втором условие расчитывается задержка
        if (end.tv_sec - start.tv_sec <= 0
            && (ts2.tv_nsec = 33000000 - (end.tv_nsec - start.tv_nsec)) > 0) {
            nanosleep(&ts2, &ts1); // Выполняем задержку
        }
    }
    fclose(fr);
    if (tetGame->score > max) {
        FILE* fw = fopen("max/score.txt", "w");
        if (!fw) {
            printf("Не удалось открыть файл\n");
            exit(1);
        }
        fprintf(fw, "%d", tetGame->score);
        fclose(fw);
    }
    freeGameTet(tetGame);
    endwin(); // освобождает память
    return 0;
}