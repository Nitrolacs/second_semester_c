#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "functions.h"

#define ADDING_BATTERY 1
#define DELETING_BATTERY 2
#define PRINTING_BATTERIES 3
#define BATTERY_SORTING 4
#define SEARCH 5
#define GET_LENGTH 6
#define REVERSE 7
#define EXIT 8

int main()
{
    printf("--------------------------------------------------\n");
    printf("| Программа для хранения информации о батарейках |\n");
    printf("--------------------------------------------------\n");

    const char firstMessage[] = "Введите номер пункта: ";
    int userChoice = 0;

    int countBatteries = 0;

    Battery* list = NULL;

    do
    {
        PrintMenu(); // выводим меню на экран
        int menuItemsCount = 8; // кол-во пунктов меню
        // нижняя граница допустимых значений
        int lowerBound = 1;
        // получаем номер выбранного пункта меню
        userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);
        // суммарное количество батареек

        switch (userChoice)
        {
            case ADDING_BATTERY:

                printf("-----------------------\n");
                printf("| Добавление батареек |\n");
                printf("-----------------------\n");

                int batteryNumber =
                        CheckingInput("Сколько батареек вы хотите добавить: ",
                                  0, 0);
                for (int i = countBatteries;
                     i < countBatteries + batteryNumber;
                     ++i)
                {

                    printf("---------------\n");
                    printf("| Батарейка №%d|\n", i + 1);
                    printf("---------------\n");
                    printf("Введите модель батарейки: ");
                    char* model = StringInput();
                    printf("Введите типоразмер (ААА, АА) батарейки: ");
                    char* batterySize = StringInput();
                    int price = CheckingInput("Введите цену батарейки: ",
                                                     0, 0);
                    float voltage = FloatInput();
                    printf("Введите вид батарейки (alkaline, "
                           "salt water и т.д.): ");
                    getchar();
                    char* type = StringInput();

                    Battery* newBattery = CreateBattery(i + 1, model,
                                                        batterySize,
                                                        price, voltage, type);
                    PushBack(list, newBattery);

                    if (list == NULL)
                    {
                        list = newBattery;
                    }
                }

                printf("Сохранить информацию о батарейках в файл?\n");
                printf("(введите цифру)\n");
                printf("1 - Да\n");
                printf("2 - Нет\n");

                menuItemsCount = 2;
                int mode = CheckingInput(firstMessage, lowerBound,
                                         menuItemsCount);
                const int FILE_STORAGE = 1;

                if (mode == FILE_STORAGE)
                {
                    WriteToFile(list);
                    printf("Информация о батарейках записана в файл "
                           "batteries.txt\n");
                }

                countBatteries += batteryNumber;
                break;

            case DELETING_BATTERY:
                if (list == NULL)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                list = DeletingBattery(list, mode);
                break;

            case PRINTING_BATTERIES:
                if (list == NULL)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    countBatteries = 0;
                    break;
                }
                PrintList(list);
                break;

            case BATTERY_SORTING:
                if (list == NULL)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                list = SortingBatteries(list, mode);
                break;

            case SEARCH:
                if (list == NULL)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                SearchByFeature(list);
                break;

            case GET_LENGTH:
                if (list == NULL)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                int length = GetLength(list);
                printf("----------------\n");
                printf("Длина списка: %d\n", length);
                printf("----------------\n");
                break;

            case REVERSE:
                if (list == NULL)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                list = ReverseList(list, mode);
                break;

            default:
                DeleteList(list);
                printf("Выход...");
        }
    } while (userChoice != EXIT);

    return 0;
}
