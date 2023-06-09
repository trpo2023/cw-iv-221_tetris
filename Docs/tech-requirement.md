# Техническое задание - Тетрис
Создано для репозитория cw-iv-221_tetris

## Функциональность проекта:
Цель проекта - создать классический тетрис с основными функциями:
- Движение фигур по игровому полю.
- Поворот фигур. 
- Счет очков за заполнение горизонтальной линии.
- Ускорение падения фигур.
(Возможно - обсуждается командой)
- Возможность приостановить игру.
- Возможность начать новую игру.

## Формат входных данных:
- Пользовательский ввод: нажатия клавиш на клавиатуре (для движения, поворота и ускорения фигур).
- Аргументы командной строки: при запуске приложения пользователь должен указать размер игрового поля и скорость игры.

## Интерфейс приложения: 
- Игровое поле: прямоугольный экран, на котором отображаются движущиеся фигуры, заполняющиеся блоками.
- Очки: счетчик очков игрока.

## Аргументы командной строки: 
При запуске приложения пользователь должен указать размер игрового поля и скорость игры следующим образом:

```
./tetris <ширина поля> <высота поля> <скорость игры>
```
Например:
```
./tetris 10 20 5
```
где 10 - ширина поля, 20 - высота поля, 5 - скорость игры.
