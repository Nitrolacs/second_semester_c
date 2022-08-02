#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CORRECT_INPUT 2
#define END_STRING '\n'
#define MATRIX_CREATION 1
#define KRONECKER_PRODUCT 2
#define PRINTING_MATRIX 3
#define EXIT 4

void PrintMatrix(int** array, int rowsNumber, int columnsNumber,
                 int maxLenNumber)
{
    for (int i = 0;
         i < rowsNumber;
         ++i)
    {
        for (int j = 0;
             j < columnsNumber;
             j++)
        {
            // maxLenNumber нужен для того, чтобы определить, сколько
            // знаков нужно выделить под каждый элемент матрицы
            printf("%*d  ", maxLenNumber, array[i][j]);
        }
        printf("\n");
    }

}

int CheckingInput(const char message[], int lowerBound, int count)
{
    int userInput = 1;
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
            userInput = 1;
            printf("Неверный ввод. Попробуйте снова.\n%s", message);
            input = scanf("%d%c", &userInput, &inputChar);
        }
    }
    return userInput;
}

int** CreationMatrix(char symbol, int* rowsNumber, int* columnsNumber)
{
    // Границы для функции CheckingInput
    int bottomLine = 0, tmp = 0;

    const char firstMessage[] = "Создание матрицы %c\n";
    const char secondMessage[] = "Введите количество строк: ";
    const char thirdMessage[] = "Введите количество столбцов: ";

    printf(firstMessage, symbol);
    *rowsNumber = CheckingInput(secondMessage, bottomLine, tmp);
    *columnsNumber = CheckingInput(thirdMessage, bottomLine, tmp);

    int** array = (int**)malloc(*rowsNumber * sizeof(int*));
    for (int i = 0;
         i < *rowsNumber;
         i++)
    {
        array[i] = (int*) malloc(*columnsNumber * sizeof(int));
    }
    if (NULL == array)
    {
        printf("Превышено значение для "
               "выделения памяти. Матрица %c не создана.\n", symbol);
    }
    return array;
}

// Функция считает то, сколько символов занимает число.
int NumberLength(int number)
{
    // Если число отрицательное - добавляем длину одного символа (знак минус)
    int lenNumber = (number >= 0) ? 0 : 1;
    while (number != 0)
    {
        number /= 10;
        lenNumber++;
    }
    return lenNumber;
}

int** FillingMatrix(int** array, char symbol, int rowsNumber, int columnsNumber,
                    int* maxLenNumber)
{
    const char firstMessage[] = "Введите номер пункта: ";
    const char message[] = "Введите %d элемент %d строки: ";
    int bottomLine = 0, number = 0, lowerBound = 1;
    char inputChar = '\0';

    printf("Заполнение матрицы %c\n", symbol);

    printf("Выберите способ заполнения матрицы числами:\n");
    printf("1 - Заполнение вручную\n");
    printf("2 - Заполнение случайным образом\n");

    // Нужны для того, чтобы ограничить диапазон случайных чисел
    const int TOP_NUMBER_LIMIT = 201;
    const int BOTTOM_NUMBER_LIMIT = 100;

    const int MANUAL_INPUT = 1;
    int pointsCount = 2;

    int curLenNumber = 0;

    int userChoice = CheckingInput(firstMessage, lowerBound, pointsCount);

    for (int i = 0;
        i < rowsNumber;
        i++)
    {
        for (int j = 0;
             j < columnsNumber;
             j++)
        {
            if (userChoice == MANUAL_INPUT)
            {
                printf(message, j + 1, i + 1);

                int input = scanf("%d%c", &number, &inputChar);
                while (input != CORRECT_INPUT || inputChar != END_STRING)
                {
                    while ((inputChar = getchar()) != '\n');
                    printf("Неверный ввод. Попробуйте снова.\n");
                    printf(message, i + 1, j + 1);
                    input = scanf("%d%c", &number, &inputChar);
                }
            }

            else
            {
                number = rand() % TOP_NUMBER_LIMIT - BOTTOM_NUMBER_LIMIT;
            }

            curLenNumber = NumberLength(number);
            if (curLenNumber > *maxLenNumber)
            {
                *maxLenNumber = curLenNumber;
            }

            array[i][j] = number;
        }
    }
    return array;
}

void KroneckerProduct(int** firstMatrix, int rowsNumberFirst,
                      int columnsNumberFirst, int** secondMatrix,
                      int rowsNumberSecond, int columnsNumberSecond,
                      int maxLenNumber)

{
    int rowsNumberC = rowsNumberFirst * rowsNumberSecond;
    int columnsNumberC = columnsNumberFirst * columnsNumberSecond;

    int** resultMatrix = (int**)malloc(rowsNumberC *
                                       sizeof(int*));
    for (int i = 0;
         i < rowsNumberC;
         i++)
    {
        resultMatrix[i] = (int*) malloc(columnsNumberC * sizeof(int));
    }

    printf("Произведение Кронекера:\n");

    // Цикл проходит по всем строкам матрицы A
    for (int i = 0;
         i < rowsNumberFirst;
         i++)
    {
        // Цикл проходит по всем строкам матрицы B
        for (int k = 0;
             k < rowsNumberSecond;
             k++)
        {
            // Цикл проходит по всем столбцам матрицы A
            for (int j = 0;
                 j < columnsNumberFirst;
                 j++)
            {
                // Цикл проходит по всем столбцам матрицы B
                for (int l = 0;
                     l < columnsNumberSecond;
                     l++)
                {
                    // Каждый элемент матрицы A нужно умножить на всю
                    // матрицу B и поместить результат
                    // в итоговую матрицу.
                    int columnResult = j + k, rowResult = i + l;

                    resultMatrix[rowResult][columnResult] =
                            firstMatrix[i][j] * secondMatrix[k][l];
                    printf("%*d  ", maxLenNumber,
                           resultMatrix[rowResult][columnResult]);
                }
            }
            printf("\n");
        }
    }
}

void FreeArray(int** array, int rowsNumber)
{
    for (int i = 0;
         i < rowsNumber;
         i++)
    {
        free(array[i]);
    }
    free(array);
}

void PrintMenu(void)
{
    printf("-------------------\n");
    printf("| Меню программы: |\n");
    printf("-------------------\n");
    printf("1 - Создание матриц\n");
    printf("2 - Вычисление произведения Кронекера\n");
    printf("3 - Вывод матриц на экран\n");
    printf("4 - Выход\n");
}

int main(void)
{
    srand(time(NULL));

    printf("------------------------------------------------\n");
    printf("| Программа вычисления произведения Кронекера. |\n");
    printf("------------------------------------------------\n");


    const char firstMessage[] = "Введите номер пункта: ";

    int userChoice = 0;
    int lowerBound = 1;

    int maxLenNumber = 0;

    do
    {
        PrintMenu(); // выводим меню на экран
        const int menuItemsCount = 4;
        // получаем номер выбранного пункта меню
        userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);
        switch (userChoice)
        {
            case MATRIX_CREATION:
                printf("--------------------\n");
                printf("| Создание матриц. |\n");
                printf("--------------------\n");

                int rowsNumberFirst = 0, columnsNumberFirst = 0;
                char firstMatrixSymbol = 'A';
                int rowsNumberSecond = 0, columnsNumberSecond = 0;
                char secondMatrixSymbol = 'B';
                int** firstMatrix = CreationMatrix(firstMatrixSymbol,
                                                   &rowsNumberFirst,
                                                   &columnsNumberFirst);
                firstMatrix = FillingMatrix(firstMatrix, firstMatrixSymbol,
                                            rowsNumberFirst,
                                            columnsNumberFirst,
                                            &maxLenNumber);

                int** secondMatrix = CreationMatrix(secondMatrixSymbol,
                                                    &rowsNumberSecond,
                                                    &columnsNumberSecond);
                secondMatrix = FillingMatrix(secondMatrix, secondMatrixSymbol,
                                             rowsNumberSecond,
                                             columnsNumberSecond,
                                             &maxLenNumber);
                break;

            case KRONECKER_PRODUCT:
                if (rowsNumberFirst == 0 || rowsNumberSecond == 0)
                {
                    printf("Матрицы ещё не созданы.\n");
                    break;
                }

                KroneckerProduct(firstMatrix, rowsNumberFirst,
                                 columnsNumberFirst, secondMatrix,
                                 rowsNumberSecond, columnsNumberSecond,
                                 maxLenNumber);
                break;

            case PRINTING_MATRIX:
                if (rowsNumberFirst == 0 || rowsNumberSecond == 0)
                {
                    printf("Матрицы ещё не созданы.\n");
                    break;
                }

                printf("Матрица A:\n");
                PrintMatrix(firstMatrix, rowsNumberFirst, columnsNumberFirst,
                            maxLenNumber);
                printf("\n");
                printf("Матрица B:\n");
                PrintMatrix(secondMatrix, rowsNumberSecond, columnsNumberSecond,
                            maxLenNumber);
                break;

            default:
                // Перед тем как произвести очистку, необходимо проверить,
                // были ли созданы матрицы.
                if (rowsNumberFirst != 0 && rowsNumberSecond != 0)
                {
                    FreeArray(firstMatrix, rowsNumberFirst);
                    FreeArray(secondMatrix, rowsNumberSecond);
                }
                printf("Выход...");
        }
    } while (userChoice != EXIT);

    return 0;
}

