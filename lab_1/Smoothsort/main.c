#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define CORRECT_INPUT 2
#define END_STRING '\n'
#define INPUT_ARRAY_ELEMENTS 1
#define ARRAY_SORTING 2
#define PRINTING_ARRAY 3
#define EXIT 4

void PrintArray(int array[], int length)
{
    for (int i = 0;
         i < length;
         ++i)
    {
        printf(" %d ", array[i]);
    }
    printf("\n");
}

void GetLeonardoNumbers(int numbers[], int arrayLength)
{
    // Генерация чисел Леонардо, не превышающих
    // количество элементов массива
    int firstNumber = 1, secondNumber = 1, index = 0;

    while (firstNumber <= arrayLength)
    {
        numbers[index] = firstNumber;
        int i = firstNumber;
        firstNumber = secondNumber;
        secondNumber = firstNumber + i + 1;
        ++index;
    }
}

void GetChildTrees(int tmpArray[], int index, int lastHeap, int leoNums[])
{
    // При удалении корня куча делится на две меньшие кучи,
    // соответствующие двум предыдущим числами Леонардо

    // Получаем порядки куч, из которых состоит целвя куча
    int firstRoot = index - 1;
    int secondRoot = lastHeap - 2;
    int thirdRoot = firstRoot - leoNums[secondRoot];
    int fourthRoot = lastHeap - 1;

    // Чтобы вернуть четыре значения, помещаем их в массив
    tmpArray[0] = firstRoot;
    tmpArray[1] = secondRoot;
    tmpArray[2] = thirdRoot;
    tmpArray[3] = fourthRoot;
}

// Восстановление кучи после слияния куч или удаления корня
void RestoreHeap(int array[], int index, int heap[],
                 int heapLen, int leoNums[])
{
    // Модифицированная сортировка вставками для корней куч

    // Значение переменной current определяет, сколько
    // проходов цикла сортировки вставками будет.
    // Если heap состоит из 1 элемента
    // (heapLen = 1), то не придётся
    // сортировать значения корней куч
    int current = heapLen - 1;

    int lastHeap = heap[current]; // Получаем порядок последней кучи
    int secondHeap; // Порядок предыдущей кучи
    int tmp; // Временная переменная для обмена значениями

    int* tmpArray = (int*) calloc(4, sizeof(int));

    while (current > 0)
    {
        secondHeap = index - leoNums[lastHeap];

        // Проверяем, что порядок последней кучи меньше
        // порядка предыдущей кучи
        if (array[secondHeap] > array[index] && (lastHeap < 2 ||
            array[secondHeap] > array[index - 1] &&
            array[secondHeap] > array[index - 2]))
        {
            // Меняем местами элементы в массиве элементов,
            // так как самая последняя куча должна иметь наибольший корень
            tmp = array[index];
            array[index] = array[secondHeap];
            array[secondHeap] = tmp;
            index = secondHeap;
            --current;
            lastHeap = heap[current];
        }
        else
        {
            break;
        }
    }

    // Просейка
    // Если порядок последней кучи меньше 2, то просейку
    // осуществлять не нужно
    while (lastHeap >= 2)
    {
        // Узнаём, из куч какого порядка состояла целая куча
        GetChildTrees(tmpArray, index, lastHeap, leoNums);
        int firstRoot = tmpArray[0];
        int secondRoot = tmpArray[1];
        int thirdRoot = tmpArray[2];
        int fourthRoot = tmpArray[3];

        if (array[index] < array[firstRoot] || array[index] < array[thirdRoot])
        {
            // Если элемент меньше по размеру, чем потомки, то
            // этот элемент нужно перенести как можно ниже,
            // а больший потомок поднять наверх.
            // В корне дерева должен быть максимальный элемент.
            if (array[firstRoot] > array[thirdRoot])
            {
                tmp = array[index];
                array[index] = array[firstRoot];
                array[firstRoot] = tmp;
                index = firstRoot;
                lastHeap = secondRoot;
            }
            else
            {
                tmp = array[index];
                array[index] = array[thirdRoot];
                array[thirdRoot] = tmp;
                index = thirdRoot;
                lastHeap = fourthRoot;
            }
        }
        else
        {
            break;
        }
    }
    free(tmpArray);
}

void Smoothsort(int array[], int arrayLength)
{

    // Вычислим необходимое количество чисел Леонардо
    int* leoNums = (int*) calloc(arrayLength, sizeof(int));
    GetLeonardoNumbers(leoNums, arrayLength);

    // Куча будет храниться в виде списка деревьев Леонардо
    int* heap = (int*) calloc(arrayLength, sizeof(int));
    int heapLen = 0;

    // Создание первоначальной кучи
    // Очередной элемент или объединяет две предыдущие кучи
    // или добавляет новую кучу из одного узла (дерево первого порядка)
    for (int index = 0;
         index < arrayLength;
         ++index)
    {
        // Если у прошлых деревьев смежный порядок (например, 1 и 2,
        // 4 и 5, 8 и 9), то объединяем их в одно большое дерево;
        // Новая вершина - корень дерева.
        if (heapLen >= 2 && heap[heapLen - 2] == heap[heapLen - 1] + 1)
        {
            --heapLen;
            // Объединяем две крайние слева кучи в одну
            ++heap[heapLen - 1];
        }

        // Если первое условие не выполняется и порядок последнего
        // дерева равен 1, то добавляем дерево 0-го порядка.
        else if (heapLen >= 1 && heap[heapLen - 1] == 1)
        {
            ++heapLen;
            heap[heapLen - 1] = 0;
        }

        // Иначе - добавляем дерево 1-го порядка.
        else
        {
            ++heapLen;
            heap[heapLen - 1] = 1;
        }
        RestoreHeap(array, index, heap, heapLen, leoNums);
    }
    // В итоге в heap хранятся порядки получившихся куч, а в
    // array в соответствие расставлены элементы.

    // Разбираем кучу куч

    int secondIndex = arrayLength - 1;
    for (secondIndex;
         secondIndex > 0;
         --secondIndex)
    {

        if (heap[heapLen - 1] < 2)
        {
            // Если порядок последней кучи равен 0 или 1, то
            // убираем его из heap, так как его не нужно расскладывать
            // на меньше кучи

            --heapLen;
        }
        else
        {
            // Раскладываем кучу на две кучи смежного порядка (например
            --heapLen;
            int lastOrder = heap[heapLen]; // Порядок взятой последней кучи

            int* secondTmpArray = (int*) calloc(4, sizeof(int));

            GetChildTrees(secondTmpArray, secondIndex, lastOrder, leoNums);
            int firstRoot = secondTmpArray[0];
            int secondRoot = secondTmpArray[1];
            int thirdRoot = secondTmpArray[2];
            int fourthRoot = secondTmpArray[3];
            free(secondTmpArray);

            ++heapLen;
            heap[heapLen - 1] = fourthRoot;
            // После того как извлекаем элементы из кучи,
            // необходимо поменять корни местами так, чтобы
            // последовательность снова стала возрастающей
            // т.е. 1, 0  ->  0, 1
            RestoreHeap(array, thirdRoot, heap, heapLen, leoNums);
            ++heapLen;
            heap[heapLen - 1] = secondRoot;
            // Снова сортировка
            RestoreHeap(array, firstRoot, heap, heapLen, leoNums);
        }
    }
    free(leoNums);
    free(heap);
}


void ArrayGeneration(int array[], int maxSize)
{
    // Нужны для того, чтобы ограничить диапазон случайных чисел
    const int TOP_NUMBER_LIMIT = 2001;
    const int BOTTOM_NUMBER_LIMIT = 1000;

    for (int index = 0;
         index < maxSize;
         index++)
    {
        int number = rand() % TOP_NUMBER_LIMIT - BOTTOM_NUMBER_LIMIT;
        array[index] = number;
    }
}

int CheckingInput(char message[], int lowerBound, int count)
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

void InputArray(int array[], int maxSize)
{
    char message[] = "Введите %d элемент массива: ";
    int number, input;
    char inputChar = '\0';
    for (int index = 0; index < maxSize; ++index)
    {
        printf(message, index + 1);
        input = scanf("%d%c", &number, &inputChar);
        while (input != CORRECT_INPUT || inputChar != END_STRING)
        {
            while ((inputChar = getchar()) != '\n');
            printf("Неверный ввод. Попробуйте снова.\n");
            printf(message, index + 1);
            input = scanf("%d%c", &number, &inputChar);
        }
        array[index] = number;
    }
}

void PrintMenu(void)
{
    printf("-------------------\n");
    printf("| Меню программы: |\n");
    printf("-------------------\n");
    printf("1 - Ввод элементов массива\n");
    printf("2 - Сортировка массива\n");
    printf("3 - Вывод массива на экран\n");
    printf("4 - Выход\n");
}

int main(void) {
    srand(time(NULL));

    printf("--------------------------------------------------------\n");
    printf("| Программа плавной сортировки массива чисел длиной n. |\n");
    printf("--------------------------------------------------------\n");


    const char firstMessage[] = "Введите номер пункта: ";
    const char secondMessage[] = "Введите длину массива: ";
    int arrayLength = 0, userChoice, lowerBound = 1, bottomLine = 0, tmp = 0;
    int* initialArray;

    do
    {
        PrintMenu(); // выводим меню на экран
        int count = 4;
        // получаем номер выбранного пункта меню
        userChoice = CheckingInput(firstMessage, lowerBound, count);
        switch (userChoice)
        {
            case INPUT_ARRAY_ELEMENTS:
                printf("Выберите способ заполнения массива числами:\n");
                printf("1 - Заполнение вручную\n");
                printf("2 - Заполнение случайным образом\n");

                const int MANUAL_INPUT = 1;
                count = 2;

                userChoice = CheckingInput(firstMessage, lowerBound, count);
                arrayLength = CheckingInput(secondMessage, bottomLine, tmp);
                initialArray = (int*) malloc(arrayLength * sizeof(int));

                if (NULL == initialArray)
                {
                    printf("Превышено значение для "
                           "выделения памяти. Выход...\n");
                    exit(1);
                }

                if (userChoice == MANUAL_INPUT)
                {
                    InputArray(initialArray, arrayLength);
                    break;
                }
                else
                {
                    ArrayGeneration(initialArray, arrayLength);
                    break;
                }

            case ARRAY_SORTING:

                if (arrayLength == 0)
                {
                    printf("Нет элементов в массиве.\n");
                    break;
                }

                printf("Выберите способ сортировки массива чисел:\n");
                printf("1 - По возрастанию.\n");
                printf("2 - По убыванию.\n");

                const int DESCENDING = 2;
                count = 2;

                int secondUserChoice = CheckingInput(firstMessage,
                                                     lowerBound,
                                                     count);
                Smoothsort(initialArray, arrayLength);
                int tmp;

                if (secondUserChoice == DESCENDING)
                {
                    for(int index = 0;
                        index < arrayLength / 2;
                        ++index)
                    {
                        tmp = initialArray[index];
                        initialArray[index] = initialArray[arrayLength -
                                                           1 - index];
                        initialArray[arrayLength - 1 - index] = tmp;
                    }
                }

                PrintArray(initialArray, arrayLength);
                break;

            case PRINTING_ARRAY:

                if (arrayLength == 0)
                {
                    printf("Нет элементов в массиве.\n");
                    break;
                }

                PrintArray(initialArray, arrayLength);
                break;

            default:
                free(initialArray);
                printf("Выход...");
        }
    } while (userChoice != EXIT);

    return 0;
}

