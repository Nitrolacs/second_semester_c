#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define CORRECT_INPUT 2
#define END_STRING '\n'
#define STRING_INPUT 1
#define PARENTHESIS_CHECK  2
#define PRINTING_STRING 3
#define EXIT 4

#define BACKSPACE_KEY 8
#define START_CHAR_RANGE 32
#define END_CHAR_RANGE 126

void ParenthesisCheck(char* userStr, int* stringSize, int mode)
{
    char tmpStr[*stringSize];
    for (int i = 0;
         i < *stringSize;
         ++i)
    {
        tmpStr[i] = userStr[i];
    }

    FILE* myFile = NULL;
    const int FILE_HANDLING  = 2;
    bool errors = false;

    if (mode == FILE_HANDLING)
    {
        myFile = fopen("/home/nitrolacs/c programming/lab_3/"
                             "round_brackets/result.txt", "wt");
        if (myFile == NULL)
        {
            printf("Ошибка открытия файла result.txt\n");
            exit(0);
        }
        printf("Запись результата в файл...\n");
    }

    for (int i = 0;
         i < *stringSize;
         ++i)
    {
        if (tmpStr[i] == ')')
        {
            if (mode == FILE_HANDLING)
            {
                fprintf(myFile, "Лишняя правая скобка ')' %d-ым символом\n",
                        i + 1);
            }
            else
            {
                printf("Лишняя правая скобка ')' %d-ым символом\n", i + 1);
            }
            errors = true;
        }
        else if (tmpStr[i] == '(')
        {
            for (int index = i;
                 index < *stringSize;
                 ++index)
            {
                if (tmpStr[index] == ')')
                {
                    // Если нашли закрывающую правую скобку, то заменяем её
                    // на другой символ, чтобы она не мешала в дальнейшем.
                    tmpStr[index] = ' ';
                    break;
                }
                else if (index + 1 < *stringSize)
                {
                    continue;
                }
                else
                {
                    if (mode == FILE_HANDLING)
                    {
                        fprintf(myFile, "Лишняя левая скобка '(' %d-ым "
                                        "символом\n", i + 1);
                    }
                    else
                    {
                        printf("Лишняя левая скобка '(' %d-ым символом\n",
                               i + 1);
                    }
                    errors = true;
                }
            }
        }
        else
        {
            continue;
        }
    }

    if (errors == false)
    {
        if (mode == FILE_HANDLING)
        {
            fprintf(myFile, "Все скобки расставлены верно.\n");
        }
        else
        {
            printf("Все скобки расставлены верно.\n");
        }
    }
    if (myFile != NULL)
    {
        fclose(myFile);
    }
}

char* StringInput(int* stringSize)
{
    char* userStr = (char*)malloc(1 * sizeof(char));
    userStr[0] = '\0';
    char curChar = 0;
    int curSize = 1;

    printf("Введите строку: ");
    while(curChar != '\n')
    {
        curChar = getchar();

        int deltaVal = 0; // Определяет, на сколько изменится длина массива
        int lengthDif = 0;

        // Если мы стираем символы, а не пишем их,
        if (curChar == BACKSPACE_KEY)
        {
            deltaVal = -1; // то будем уменьшать длину массива
            lengthDif = 1; // и копировать строку до предпоследнего символа
        }

        // Иначе проверяем, входит ли введённый символ в диапазон печатных
        else
        {
            if (curChar >= START_CHAR_RANGE && curChar <= END_CHAR_RANGE)
            {
                deltaVal = 1; // Если да, то будем увеличивать длину на 1
                lengthDif = 2; // Не заполняем последние 2 символа -
                               // оставляем место для введённого символа и '\0'
            }
            else
            {
                continue; // Если это не печатный символ, то пропускаем его
            }
        }

        // Если стирать больше нечего, но пользователь
        // всё равно жмёт Backspace.
        int newSize = curSize + deltaVal;
        if (newSize == 0)
        {
            continue; // то мы переходим на следующую итерацию - ждём '\n'
        }

        char* tmpStr = (char*)malloc(newSize * sizeof(char));
        if (tmpStr) // Проверяем, выделилась ли память
        {
            // Идём до предпоследнего символа, т.к. надо в конец записать '\0'
            for (int i = 0;
                 i < newSize - lengthDif;
                 ++i)
            {
                tmpStr[i] = userStr[i];
            }

            if (curChar != BACKSPACE_KEY) // Если введён печатный символ,
            {
                tmpStr[newSize - 2] = curChar; // Добавляем его в строку
                tmpStr[newSize - 1] = '\0';
            }
            free(userStr);
            userStr = tmpStr;
            curSize = newSize;
        }
        else
        {
            printf("Не могу выделить память под обновлённую строку!");
            break;
        }
    }

    *stringSize = curSize - 1;
    return userStr;
}

char* ReadingFile(int* stringSize)
{
    char* userStr = (char*)malloc(1 * sizeof(char));
    char symbol;
    int strLength = 1;

    FILE* myFile = fopen("/home/nitrolacs/c programming/lab_3/"
                         "round_brackets/expression.txt", "rt");
    if (myFile == NULL)
    {
        printf("Ошибка открытия файла expression.txt\n");
        exit(0);
    }
    else
    {
        printf("Считано: ");
        while ((symbol = fgetc(myFile)) != EOF)
        {
            userStr[strLength - 1] = symbol;
            ++strLength;
            userStr = (char*) realloc(userStr, strLength);
            printf("%c", symbol);
        }
        fclose(myFile);
        userStr[strLength - 1] = '\0';
    }
    *stringSize = strLength - 2;
    return userStr;
}

int CheckingInput(const char message[], int lowerBound, int count)
{
    int userInput = 1;
    char inputChar = '\0';

    printf("%s", message);
    int input = scanf("%d%c", &userInput, &inputChar);

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
    return userInput;
}


void PrintMenu(void)
{
    printf("-------------------\n");
    printf("| Меню программы: |\n");
    printf("-------------------\n");
    printf("1 - Ввод арифметического выражения\n");
    printf("2 - Проверка круглых скобок\n");
    printf("3 - Вывод арифметического выражения\n");
    printf("4 - Выход\n");
}

int main(void)
{
    printf("------------------------------------------------------\n");
    printf("| Программа проверки правильности расстановки скобок |\n");
    printf("------------------------------------------------------\n");


    const char firstMessage[] = "Введите номер пункта: ";

    int userChoice, lowerBound = 1;
    char* userStr = 0;


    do
    {
        PrintMenu(); // выводим меню на экран
        int menuItemsCount = 4;
        // получаем номер выбранного пункта меню
        userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);
        switch (userChoice)
        {
            case STRING_INPUT:
                printf("----------------\n");
                printf("| Ввод строки. |\n");
                printf("----------------\n");

                printf("Выберите способ создания строки:\n");
                printf("1 - Ввод вручную\n");
                printf("2 - Чтение из файла expression.txt\n");

                int mode = CheckingInput(firstMessage, lowerBound, menuItemsCount);
                const int MANUAL_INPUT = 1;
                int stringSize = 0;

                if (mode == MANUAL_INPUT)
                {
                    userStr = StringInput(&stringSize);
                    break;
                }
                else
                {
                    userStr = ReadingFile(&stringSize);
                    break;
                }

            case PARENTHESIS_CHECK:
                if (userStr == 0)
                {
                    printf("Выражение ещё не введено.\n");
                    break;
                }
                ParenthesisCheck(userStr, &stringSize, mode);
                break;

            case PRINTING_STRING:
                if (userStr == 0)
                {
                    printf("Выражение ещё не введено.\n");
                    break;
                }
                printf("Введённая строка: %s\n", userStr);
                break;

            default:
                free(userStr);
                printf("Выход...");
        }
    } while (userChoice != EXIT);

    return 0;
}
