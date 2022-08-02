#include <stdio.h>
#include <stdlib.h>

#include "structure.h"
#include "functions.h"

#define ADDING_BATTERY 1
#define DELETING_BATTERY 2
#define PRINTING_BATTERIES 3
#define BATTERY_SORTING 4
#define SEARCH 5
#define EXIT 6

int main()
{
    printf("--------------------------------------------------\n");
    printf("| Программа для хранения информации о батарейках |\n");
    printf("--------------------------------------------------\n");

    const char firstMessage[] = "Введите номер пункта: ";
    int userChoice = 0;

    int countBatteries = 0;
    BatteryList_t batteries = {0, NULL};

    do
    {
        PrintMenu(); // выводим меню на экран
        int menuItemsCount = 6; // кол-во пунктов меню
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
                    battery_t tmpBattery = {NULL, NULL, 0, 0, NULL};
                    printf("---------------\n");
                    printf("| Батарейка №%d|\n", i + 1);
                    printf("---------------\n");
                    printf("Введите модель батарейки: ");
                    tmpBattery.model = StringInput();
                    printf("Введите типоразмер (ААА, АА) батарейки: ");
                    tmpBattery.batterySize = StringInput();
                    tmpBattery.price = CheckingInput("Введите цену батарейки: ",
                                                     0, 0);
                    tmpBattery.voltage = FloatInput();
                    printf("Введите вид батарейки (alkaline, "
                           "salt water и т.д.): ");
                    getchar();
                    tmpBattery.type = StringInput();

                    addBattery2Batteries(&batteries, tmpBattery);
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
                    WriteToFile(batteries);
                    printf("Информация о батарейках записана в файл "
                           "batteries.txt\n");
                }

                countBatteries += batteryNumber;
                break;

            case DELETING_BATTERY:
                if (batteries.batteryNumber == 0)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                DeletingBattery(&batteries, &countBatteries, mode);
                break;

            case PRINTING_BATTERIES:
                if (batteries.batteryNumber == 0)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                PrintingBatteries(batteries);
                break;

            case BATTERY_SORTING:
                if (batteries.batteryNumber == 0)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                SortingBatteries(&batteries, mode);
                break;

            case SEARCH:
                if (batteries.batteryNumber == 0)
                {
                    printf("Батарейки ещё не добавлены.\n");
                    break;
                }
                SearchByFeature(batteries);
                break;

            default:
                for (int i = 0; i < countBatteries; ++i)
                {
                    free(batteries.b_array[i].type);
                    free(batteries.b_array[i].batterySize);
                    free(batteries.b_array[i].model);
                }
                free(batteries.b_array);
                printf("Выход...");
        }
    } while (userChoice != EXIT);

    return 0;
}
