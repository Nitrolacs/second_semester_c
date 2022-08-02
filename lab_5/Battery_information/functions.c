#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"

#define CORRECT_INPUT 2
#define END_STRING '\n'
#define BACKSPACE_KEY 8
#define START_CHAR_RANGE 32
#define END_CHAR_RANGE 126

void PrintMenu(void)
{
    printf("-------------------\n");
    printf("| Меню программы: |\n");
    printf("-------------------\n");
    printf("1 - Добавление батареек\n");
    printf("2 - Удаление батарейки\n");
    printf("3 - Вывод батареек\n");
    printf("4 - Сортировка\n");
    printf("5 - Поиск\n");
    printf("6 - Выход\n");
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

char* StringInput(void)
{
    char* userStr = (char*)malloc(1 * sizeof(char));
    userStr[0] = '\0';
    char curChar = 0;
    int curSize = 1;

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
                               // оставляем место для введённого символа и \0
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

    return userStr;
}

void addBattery2Batteries(BatteryList_t* batteries, battery_t battery)
{
    int newArrSize = batteries->batteryNumber + 1;
    battery_t* tmpArr = (battery_t*)malloc(newArrSize * sizeof(battery_t));

    for (int i = 0; i < batteries->batteryNumber; ++i)
    {
        tmpArr[i] = batteries->b_array[i];
    }

    tmpArr[newArrSize - 1] = battery;
    free(batteries->b_array);
    batteries->b_array = tmpArr;
    batteries->batteryNumber = newArrSize;
}

void WriteToFile(BatteryList_t batteries)
{
    FILE* myFile = NULL;
    myFile = fopen("/home/nitrolacs/c programming/lab_5/"
                   "Battery_information/batteries.txt", "wt");

    fprintf(myFile, "-------------------\n");
    fprintf(myFile, "| Список батареек |\n");
    fprintf(myFile, "-------------------\n");

    for (int i = 0; i < batteries.batteryNumber; ++i)
    {
        battery_t battery = batteries.b_array[i];
        fprintf(myFile, "Батарейка №%d:\n", i + 1);
        fprintf(myFile, "Модель: %s\n", battery.model);
        fprintf(myFile, "Типоразмер: %s\n", battery.batterySize);
        fprintf(myFile, "Цена: %d\n", battery.price);
        fprintf(myFile, "Вольтаж: %.3f\n", battery.voltage);
        fprintf(myFile, "Вид: %s\n", battery.type);
        fprintf(myFile, "Цена за 1 вольт: %.3f\n", (float) battery.price /
                                                   battery.voltage);
        fprintf(myFile, "------------------\n");
    }
    fclose(myFile);
}

void PrintingBatteries(BatteryList_t batteries)
{
    printf("------------------\n");
    printf("| Вывод батареек |\n");
    printf("------------------\n");
    printf("------------------\n");
    for (int i = 0; i < batteries.batteryNumber; ++i)
    {
        battery_t battery = batteries.b_array[i];
        printf("Батарейка №%d:\n", i + 1);
        printf("Модель: %s\n", battery.model);
        printf("Типоразмер: %s\n", battery.batterySize);
        printf("Цена: %d\n", battery.price);
        printf("Вольтаж: %.3f\n", battery.voltage);
        printf("Вид: %s\n", battery.type);
        printf("Цена за 1 вольт: %.3f\n", (float) battery.price /
                                          battery.voltage);
        printf("------------------\n");
    }
}

void DeletingBattery(BatteryList_t* batteries, int* countBatteries, int mode)
{
    PrintingBatteries(*batteries);
    printf("Введите номер батарейки, которую вы хотите удалить: ");
    int numberBattery = 0;
    const int FILE_STORAGE = 1;
    scanf("%d", &numberBattery);

    int newArrSize = batteries->batteryNumber - 1;
    *countBatteries -= 1;

    battery_t* tmpArr = (battery_t*)malloc(newArrSize * sizeof(battery_t));
    int index = 0;

    for (int i = 0; i < batteries->batteryNumber; ++i)
    {
        if (i != numberBattery - 1)
        {
            tmpArr[index] = batteries->b_array[i];
        }
        else
        {
            tmpArr[index] = batteries->b_array[i + 1];
            i++;
        }
        index++;
    }

    free(batteries->b_array);
    batteries->b_array = tmpArr;
    batteries->batteryNumber = newArrSize;

    if (mode == FILE_STORAGE)
    {
        WriteToFile(*batteries);
        printf("Файл batteries.txt перезаписан\n");
    }
}

float FloatInput()
{
    const char* message = "Введите вольтаж батарейки: ";
    float number = 0;
    printf("%s", message);
    while (number == 0)
    {
        char* InputValue = StringInput();
        number = strtof(InputValue, NULL);
        if (number == 0)
        {
            printf("Неверный ввод. Попробуйте снова.\n%s", message);

        }
    }
    return number;
}

int ModelComparator(const void* _a, const void* _b)
{
    return strcmp(((battery_t*)_a)->model, ((battery_t*)_b)->model);
}

int BatterySizeComparator(const void* _a, const void* _b)
{
    return strcmp(((battery_t*)_a)->batterySize,
                  ((battery_t*)_b)->batterySize);
}

int PriceComparator(const void* _a, const void* _b)
{
    const battery_t* a = _a;
    const battery_t* b = _b;
    return b->price - a->price;
}

int VoltageComparator(const void* _a, const void* _b)
{
    const battery_t* a = _a;
    const battery_t* b = _b;
    return b->voltage - a->voltage;
}

int TypeComparator(const void* _a, const void* _b)
{
    return strcmp(((battery_t*)_a)->type,
                  ((battery_t*)_b)->type);
}

void PrintingCharacteristics()
{
    printf("---------------------------\n");
    printf("| Характеристики батареек |\n");
    printf("---------------------------\n");
    printf("1 - Модель\n");
    printf("2 - Типоразмер\n");
    printf("3 - Цена\n");
    printf("4 - Вольтаж\n");
    printf("5 - Вид\n");
}

void SortingBatteries(BatteryList_t* batteries, int mode)
{
    PrintingCharacteristics();
    printf("По какой характеристике отсортировать?\n");
    const char firstMessage[] = "Введите номер пункта: ";
    const int FILE_STORAGE = 1;
    int userChoice = 0;
    int menuItemsCount = 5; // кол-во пунктов меню
    int lowerBound = 1; // нижняя граница допустимых значений
    userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);

    if (userChoice == 1)
    {
        qsort(batteries->b_array, batteries->batteryNumber, sizeof(battery_t),
              ModelComparator);
        printf("Сортировка по модели прошла успешно.\n");
    }

    if (userChoice == 2)
    {
        qsort(batteries->b_array, batteries->batteryNumber, sizeof(battery_t),
              BatterySizeComparator);
        printf("Сортировка по типоразмеру прошла успешно.\n");
    }

    if (userChoice == 3)
    {
        qsort(batteries->b_array, batteries->batteryNumber, sizeof(battery_t),
              PriceComparator);
        printf("Сортировка по цене прошла успешно.\n");
    }

    if (userChoice == 4)
    {
        qsort(batteries->b_array, batteries->batteryNumber, sizeof(battery_t),
              VoltageComparator);
        printf("Сортировка по вольтажу прошла успешно.\n");
    }

    if (userChoice == 5)
    {
        qsort(batteries->b_array, batteries->batteryNumber, sizeof(battery_t),
              TypeComparator);
        printf("Сортировка по виду прошла успешно.\n");
    }

    if (mode == FILE_STORAGE)
    {
        WriteToFile(*batteries);
        printf("Файл batteries.txt перезаписан\n");
    }
}

void PrintingBattery(BatteryList_t batteries, int i)
{
    printf("------------------\n");
    printf("Батарейка №%d:\n", i + 1);
    printf("Модель: %s\n", batteries.b_array[i].model);
    printf("Типоразмер: %s\n",
           batteries.b_array[i].batterySize);
    printf("Цена: %d\n", batteries.b_array[i].price);
    printf("Вольтаж: %.3f\n", batteries.b_array[i].voltage);
    printf("Вид: %s\n", batteries.b_array[i].type);
    printf("Цена за 1 вольт: %.3f\n",
           (float) batteries.b_array[i].price /
           batteries.b_array[i].voltage);
    printf("------------------\n");
}

void SearchByFeature(BatteryList_t batteries)
{
    PrintingCharacteristics();
    printf("По какой характеристике будет происходить поиск?\n");
    const char firstMessage[] = "Введите номер пункта: ";
    int userChoice = 0;
    int menuItemsCount = 5; // кол-во пунктов меню
    int lowerBound = 1; // нижняя граница допустимых значений
    userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);
    if (userChoice == 1 || userChoice == 2 || userChoice == 5)
    {
        printf("Введите значение, которое будет искаться: ");
        char* value = StringInput();
        printf("Найденные батарейки:\n");
        for (int i = 0; i < batteries.batteryNumber; ++i)
        {
            if (userChoice == 1)
            {
                if (!strcmp(batteries.b_array[i].model, value))
                {
                    PrintingBattery(batteries, i);
                }
            }
            if (userChoice == 2)
            {
                if (!strcmp(batteries.b_array[i].batterySize, value))
                {
                    PrintingBattery(batteries, i);
                }
            }
            if (userChoice == 5)
            {
                if (!strcmp(batteries.b_array[i].type, value))
                {
                    PrintingBattery(batteries, i);
                }
            }
        }
    }
    if (userChoice == 3)
    {
        const char secondMessage[] = "Введите значение, которое будет "
                                     "искаться: ";
        int lowerBound = 0; // нижняя граница допустимых значений
        int value = CheckingInput(secondMessage, lowerBound, 0);
        printf("Найденные батарейки:\n");
        for (int i = 0; i < batteries.batteryNumber; ++i)
        {
            if (batteries.b_array[i].price == value)
            {
                PrintingBattery(batteries, i);
            }
        }
    }
    if (userChoice == 4)
    {
        float value = FloatInput();
        printf("Найденные батарейки:\n");
        for (int i = 0; i < batteries.batteryNumber; ++i)
        {
            if (batteries.b_array[i].voltage == value)
            {
                PrintingBattery(batteries, i);
            }
        }
    }
}