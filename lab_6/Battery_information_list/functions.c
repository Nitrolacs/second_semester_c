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
    printf("6 - Определение длины списка\n");
    printf("7 - Инвертирование связного списка\n");
    printf("8 - Выход\n");
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

Battery* CreateBattery(int n, const char* model, const char* batterySize,
                       int price, float voltage, const char* type)
{
    // Создать новый экземпляр структуры
    // (выделить память):
    Battery* bt = (Battery*) malloc(sizeof(Battery));
    // Присвоить все характеристики батарейки
    bt->number = n;
    strcpy(bt->model, model);
    strcpy(bt->batterySize, batterySize);
    bt->price = price;
    bt->voltage = voltage;
    strcpy(bt->type, type);
    // Обнулить указатель на след. и пред. элемент:
    bt->next = NULL;
    bt->prev = NULL;
    return bt;
}

Battery* InsertAfter(Battery* leftBattery, Battery* newBattery)
{
    if (leftBattery != NULL)
    {
        newBattery->next = leftBattery->next;
        leftBattery->next = newBattery;
        newBattery->prev = leftBattery;
    }
    return newBattery;
}

Battery* GetTail(Battery* list)
{

    if (list == NULL)
    {
        return NULL;
    }

    while (list->next != NULL) // Пока не конец списка
    {
        list = list->next; // перейти к след. элементу
    }

    // Теперь list указывает на последний элемент.
    return list; // Вернуть указатель из функции.
}

Battery* PushBack(Battery* list, Battery* newBattery)
{
    // Найти последний элемент списка:
    Battery* last = GetTail(list);
    // Вставить новый элемент после последнего:
    return InsertAfter(last, newBattery);
}

void WriteToFile(Battery* battery)
{
    FILE* myFile = NULL;
    myFile = fopen("/home/nitrolacs/c programming/lab_6/"
                   "Battery_information_list/batteries.txt", "wt");
    fprintf(myFile, "-------------------\n");
    fprintf(myFile, "| Список батареек |\n");
    fprintf(myFile, "-------------------\n");
    while (battery != NULL)
    {
        fprintf(myFile, "Батарейка №%d:\n", battery->number);
        fprintf(myFile, "Модель: %s\n", battery->model);
        fprintf(myFile, "Типоразмер: %s\n", battery->batterySize);
        fprintf(myFile, "Цена: %d\n", battery->price);
        fprintf(myFile, "Вольтаж: %.3f\n", battery->voltage);
        fprintf(myFile, "Вид: %s\n", battery->type);
        fprintf(myFile, "Цена за 1 вольт: %.3f\n", (float) battery->price /
                                                   battery->voltage);
        fprintf(myFile, "------------------\n");
        battery = battery->next;
    }
    fclose(myFile);
}

void PrintList(Battery* battery)
{
    printf("------------------\n");
    printf("| Вывод батареек |\n");
    printf("------------------\n");
    printf("------------------\n");
    while (battery != NULL)
    {
        printf("Батарейка №%d:\n", battery->number);
        printf("Модель: %s\n", battery->model);
        printf("Типоразмер: %s\n", battery->batterySize);
        printf("Цена: %d\n", battery->price);
        printf("Вольтаж: %.3f\n", battery->voltage);
        printf("Вид: %s\n", battery->type);
        printf("Цена за 1 вольт: %.3f\n", (float) battery->price /
                                          battery->voltage);
        printf("------------------\n");
        battery = battery->next;
    }
}

Battery* RemoveBattery(Battery* first, Battery* del)
{
    // Если УЭ - это начало списка, то
    if (del == first)
    {
        // НС = следующий за НС
        first = first->next;
        // Обнулить связь УЭ со след. и пред. элементом.
        del->next = NULL;
        del->prev = NULL;
        // Выйти из функции, вернув НС.
        return first;
    }

    // Установить ПЭ равным НС.
    Battery* p = first;
    // Цикл пока у ПЭ есть след. элемент
    while (p->next != NULL)
    {
        // Если след. для ПЭ – это УЭ, то
        if (p->next == del)
        {
            // Остановить цикл
            break;
        }
        // Установить ПЭ равным следующему за ПЭ элементу
        p = p->next;
    }

    // Связать ПЭ с элементом, следующим за УЭ
    p->next = del->next;
    // Обнулить связь УЭ со след. элементом
    del->next = NULL;

    // Выйти из функции, вернув НС
    return first;
}

Battery* DeletingBattery(Battery* list, int mode)
{
    PrintList(list);
    printf("Введите номер батарейки, которую вы хотите удалить: ");
    int numberBattery = 0;
    const int FILE_STORAGE = 1;
    scanf("%d", &numberBattery);

    Battery* cur = list;
    while (cur != NULL)
    {
        Battery* tmp = cur;
        cur = cur->next;
        if (tmp->number == numberBattery)
        {
           list = RemoveBattery(list, tmp);
        }
    }
    if (mode == FILE_STORAGE)
    {
        WriteToFile(list);
        printf("Файл batteries.txt перезаписан\n");
    }
    return list;
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

Battery* SwapItems(Battery* list, Battery* first, Battery* second)
{
    if (list == first)
    {
        first->next = second->next;
        second->next = first;
        return second;
    }

    Battery* p = list;
    while (p->next != NULL)
    {
        if (p->next == first)
        {
            break;
        }
        p = p->next;
    }

    p->next = second;
    first->next = second->next;
    second->next = first;

    return list;
}

Battery* SortingBatteries(Battery* list, int mode)
{
    PrintingCharacteristics();
    printf("По какой характеристике отсортировать?\n");
    const char firstMessage[] = "Введите номер пункта: ";
    const int FILE_STORAGE = 1;
    int userChoice = 0;
    int menuItemsCount = 5; // кол-во пунктов меню
    int lowerBound = 1; // нижняя граница допустимых значений
    userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);

    int bWasModified = 0;
    Battery* head = list;
    do
    {
        bWasModified = 0;
        Battery *cur = head;

        while (cur != NULL && cur->next != NULL)
        {
            if (userChoice == 1 && strcmp(cur->model,
                                          cur->next->model) < 0)
            {
                head = SwapItems(head, cur, cur->next);
                bWasModified = 1;
            }
            else if (userChoice == 2 && strcmp(cur->batterySize,
                                           cur->next->batterySize) < 0)
            {
                head = SwapItems(head, cur, cur->next);
                bWasModified = 1;
            }
            else if (userChoice == 3 && cur->price < cur->next->price)
            {
                head = SwapItems(head, cur, cur->next);
                bWasModified = 1;
            }
            else if (userChoice == 4 && cur->voltage < cur->next->voltage)
            {
                head = SwapItems(head, cur, cur->next);
                bWasModified = 1;
            }
            else if (userChoice == 5 && strcmp(cur->type,
                                               cur->next->type) < 0)
            {
                head = SwapItems(head, cur, cur->next);
                bWasModified = 1;
            }
            else
            {
                cur = cur->next;
            }
        }
    } while (bWasModified);

    printf("Сортировка прошла успешно.\n");

    if (mode == FILE_STORAGE)
    {
         WriteToFile(head);
         printf("Файл batteries.txt перезаписан\n");
    }

    return head;
}

void PrintingBattery(Battery* oneBattery)
{
    printf("------------------\n");
    printf("Батарейка №%d:\n", oneBattery->number);
    printf("Модель: %s\n", oneBattery->model);
    printf("Типоразмер: %s\n",
           oneBattery->batterySize);
    printf("Цена: %d\n", oneBattery->price);
    printf("Вольтаж: %.3f\n", oneBattery->voltage);
    printf("Вид: %s\n", oneBattery->type);
    printf("Цена за 1 вольт: %.3f\n",
           (float) oneBattery->price /
           oneBattery->voltage);
    printf("------------------\n");
}

void SearchByFeature(Battery* list)
{
    PrintingCharacteristics();
    printf("По какой характеристике будет происходить поиск?\n");
    const char firstMessage[] = "Введите номер пункта: ";
    int userChoice = 0;
    int menuItemsCount = 5; // кол-во пунктов меню
    int lowerBound = 1; // нижняя граница допустимых значений
    userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);

    Battery* cur = list;
    if (userChoice == 1 || userChoice == 2 || userChoice == 5)
    {
        printf("Введите значение, которое будет искаться: ");
        char* value = StringInput();
        printf("Найденные батарейки:\n");
        while (cur != NULL)
        {
            if (userChoice == 1)
            {
                if (!strcmp(cur->model, value))
                {
                    PrintingBattery(cur);
                }
            }
            if (userChoice == 2)
            {
                if (!strcmp(cur->batterySize, value))
                {
                    PrintingBattery(cur);
                }
            }
            if (userChoice == 5)
            {
                if (!strcmp(cur->type, value))
                {
                    PrintingBattery(cur);
                }
            }
            cur = cur->next;
        }
    }
    if (userChoice == 3)
    {
        const char secondMessage[] = "Введите значение, которое будет "
                                     "искаться: ";
        lowerBound = 0; // нижняя граница допустимых значений
        int value = CheckingInput(secondMessage, lowerBound, 0);
        printf("Найденные батарейки:\n");
        while (cur != NULL)
        {
            if (cur->price == value)
            {
                PrintingBattery(cur);
            }
            cur = cur->next;
        }
    }
    if (userChoice == 4)
    {
        float value = FloatInput();
        printf("Найденные батарейки:\n");
        while (cur != NULL)
        {
            if (cur->voltage == value)
            {
                PrintingBattery(cur);
            }
            cur = cur->next;
        }
    }
}

void DeleteList(Battery* list)
{
    while (list)
    {
        Battery* tmp = list;
        list = list->next;
        free(tmp);
    }
}

int GetLength(Battery* list)
{
    Battery* tmp = list;
    int count = 0;
    while (tmp != NULL)
    {
        count++;
        tmp = tmp->next;
    }
    return count;
}

Battery* ReverseList(Battery* list, int mode)
{
    const int FILE_STORAGE = 1;

    Battery* tmp = NULL;
    Battery* cur = list;

    while (cur != NULL)
    {
        tmp = cur->prev;
        cur->prev = cur->next;
        cur->next = tmp;
        cur = cur->prev;
    }

    if (tmp != NULL)
    {
        list = tmp->prev;
    }

    if (mode == FILE_STORAGE)
    {
        WriteToFile(list);
        printf("Файл batteries.txt перезаписан\n");
    }

    return list;
}
