#include <stdio.h>

#define CORRECT_INPUT 2
#define END_STRING '\n'

int CheckingInput(const char message[], int lowerBound, int count)
{
    int userInput = 3; // Минимальное натуральное число, большее lowerBound
    char inputChar = '\0';

    printf("%s", message);
    int input = scanf("%d%c", &userInput, &inputChar);

    if (count)
    {
        while (input != CORRECT_INPUT || inputChar != END_STRING
               || userInput < lowerBound || userInput > count)
        {
            if (userInput >= lowerBound && userInput <= count)
            {
                while ((inputChar = getchar()) != '\n');
            }
            userInput = 1;
            printf("Неверный ввод. Попробуйте снова.\n%s", message);
            input = scanf("%d%c", &userInput, &inputChar);
        }
    }
    else
    {
        while (input != CORRECT_INPUT || inputChar != END_STRING
               || userInput <= lowerBound)
        {
            if (userInput > lowerBound)
            {
                while ((inputChar = getchar()) != '\n');
            }
            userInput = 3;
            printf("Неверный ввод. Попробуйте снова.\n%s", message);
            input = scanf("%d%c", &userInput, &inputChar);
        }
    }
    return userInput;
}

int PerrinNumber(int number)
{
   if (number == 0) return 3;
   else if (number == 1) return 0;
   else if (number == 2) return 2;
   else return PerrinNumber(number - 2) + PerrinNumber(number - 3);
}

void PrintMenu(void)
{
    printf("------------------\n");
    printf("| Меню программы |\n");
    printf("------------------\n");
    printf("1 - Вычисление n-го числа Перрена\n");
    printf("2 - Выход\n");
}