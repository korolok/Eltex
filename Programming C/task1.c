#define _CRT_SECURE_NO_WARNINGS
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DBG 0

int input(int r1, int r2, int flag);

int main() {
    setlocale(LC_ALL, "Rus");
    int attempts = 0,  // количество попыток
        rand1 = 20,    // первое число координат
        rand2 = 40,    // второе uисло координат
        i = 0,         // счетчик в цикле
        j = 0,         // проверка scanf
        temp = 0,      // рандомное число после функции
        var = 0,       // временная переменная вычитания коэффицента
        var2 = 0,      // деньги с победы
        count = 0,     // счетчик начала игры
        money = 0,     // деньги
        points = 0,    // баллы
        ratio = 0,     // кэф
        bet = 0,       // ставка
        answer = 0;    // ответ
    char quit = 0;     // переменная выхода из игры
    //спрашиваем количество денег и перевдим в баллы
    while (1) {
        printf("Ведите количество монет которое вы хотите внести: ");
        j = scanf("%d", &money);
        getchar();
        if (j == 1 && money > 0) {
            points = (float)money / 1.4;
            printf("Ваши %d монет превратились в %d балл(ов)\n", money, points);
            break;
        } else
            printf("Ответ не верный, попробуй еще раз!\n");
    }

    while (1) {
        if (count != 0) {
            printf("Ваш баланс: %d\n", points);
            printf("Игра начилась!!!\n");
        }
        //ставки
        while (1) {
            printf("Ваши ставки: ");
            j = scanf("%d", &bet);
            getchar();
            if (j == 1 && bet > 0 && bet <= points) {
                points -= bet;
#if DBG == 1
                printf("%d\n", points);
#endif  // DBG
                break;
            } else
                printf("Ответ не верный, попробуй еще раз!\n");
        }
        i = 0;
        // случайное число
        while (i == 0) {
            printf("Введите параметры случайного числа: ");
            j = (scanf("%d%d", &rand1, &rand2));
            getchar();
            if (rand1 < rand2 && j == 2) {
                srand(time(NULL));
                temp = rand1 + rand() % (rand2 - rand1 + 1);
#if DBG == 1
                printf("%d\n", temp);
#endif  // DBG
                i++;
            } else {
                printf("Ответ не верный, попробуй еще раз!\n");
                // break;
            }
        }
        i = 0;
        rand2 -= rand1;
        //количество попыток
        while (i == 0) {
            printf("Введите количество попыток: ");
            j = scanf("%d", &attempts);
            getchar();
            if (j == 1 && attempts > 0 && rand2 > attempts) {
                i++;
                break;
            } else
                printf("Ответ не верный, попробуй еще раз!\n");
        }
        //функция вычисления коэффицента
        rand2 /= 20;
        if (rand2 == 0) rand2 = 1;
        var = (float)attempts * 0.7;
        if (var == 0 && var == 1 && var >= 3) var = 2;
        ratio = rand2 * var;
        if (ratio < 1) ratio = 1;
        if (ratio > 3) ratio = 2;
#if DBG == 1
        printf("Кэф %d\n", ratio);
#endif  // DBG
        // сами попытки
        for (i = 1; i <= attempts; i++) {
            printf("Введите свой вариант. Попытка немер: %d.\n", i);
            j = scanf("%d", &answer);
            getchar();
            if (j == 1 && answer > 0) {
                if (answer == temp) {
                    printf("Ура вы попедили!!!\n");
                    var2 = bet * ratio;
                    points += var2;
                    printf("Ваш банк составляет: %d балл(ов)\n", points);

                    break;
                } else if ((attempts - i) == 0)
                    printf("Вы проиграли. Правильный ответ %d\n", temp);
                else {
                    if (answer > temp)
                        printf("Заданное число меньше\n");
                    else
                        printf("Заданное число больше\n");
                }
            } else {
                printf("Ответ не верный, попробуй еще раз!\n");
            }
        }
        //меню выхода
        printf("Если хотите выйти нажмите q. Чтобы продолжить нажмите Enter\n");
        scanf("%c", &quit);
        if (quit == 'q')
            break;
        else
            count++;
        continue;
    }
    printf("Ваш баланс: %d\n", points);
    printf("Игра закончилась(\n");
    return 0;
}