#include <stdio.h>
#include "myMath.h"

#define CALCULATING_PERRIN_NUMBER 1
#define EXIT 2

int main()
{
    printf("-----------------------------------------------\n");
    printf("| Программа для вычисления n-го числа Перрена |\n");
    printf("-----------------------------------------------\n");

    const char firstMessage[] = "Введите номер числа Перрена, "
                                "которое вы хотите вычислить: ";
    const char secondMessage[] = "Введите номер пункта: ";
    int tmp = 0;
    int userChoice = 0;

    do
    {
        PrintMenu(); // выводим меню на экран
        const int menuItemsCount = 2; // кол-во пунктов меню
        // нижняя граница допустимых значений
        int lowerBound = 1;
        // получаем номер выбранного пункта меню
        userChoice = CheckingInput(secondMessage, lowerBound, menuItemsCount);
        if (userChoice == CALCULATING_PERRIN_NUMBER)
        {
            lowerBound = 2;
            int number = CheckingInput(firstMessage, lowerBound, tmp);
            int result = PerrinNumber(number);
            printf("%d-ое число Перрена: %d\n", number, result);
        }
        else
        {
            printf("Выход...");
        }

    } while (userChoice != EXIT);

    return 0;
}
