#include <stdio.h>

#include "structure.h"
#include "functions.h"

enum Points
{
    ADDING_ELEMENTS = 1,
    CREATING_CONNECTION,
    PRINTING_ELEMENTS,
    PRINTING_CONNECTIONS,
    RELATED_ELEMENTS,
    DELETING_ELEMENT,
    FILE_HANDLING,
    SORTING_ELEMENTS,
    EXIT,
};

int main()
{
    printf("-------------------------------------------\n");
    printf("| Программа для хранения историй болезней |\n");
    printf("-------------------------------------------\n");

    const char firstMessage[] = "Введите номер пункта: ";
    int userChoice = 0;

    Human* humans = NULL;
    int countHumans = 0;
    Disease* diseases = NULL;
    int countDiseases = 0;
    HumanDisease* humanDiseases = NULL;
    int countHumDis = 0;

    do
    {
        PrintMenu(); // выводим меню на экран
        int menuItemsCount = 9; // кол-во пунктов меню
        // нижняя граница допустимых значений
        int lowerBound = 1;
        // получаем номер выбранного пункта меню
        userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);
        // суммарное количество батареек

        switch (userChoice)
        {
            case ADDING_ELEMENTS:

                printf("------------------------------\n");
                printf("| Добавление нового элемента |\n");
                printf("------------------------------\n");

                printf("Элементы какого типа вы хотите добавить?\n");
                printf("1 - Человек\n");
                printf("2 - Болезнь\n");

                menuItemsCount = 2;
                userChoice = CheckingInput(firstMessage, lowerBound,
                                           menuItemsCount);

                if (userChoice == 1)
                {
                    humans = AddingHuman(humans, &countHumans);
                }
                else if (userChoice == 2)
                {
                    diseases = AddingDisease(diseases, &countDiseases);
                }

                break;

            case CREATING_CONNECTION:
                if (humans == NULL)
                {
                    printf("Люди ещё не добавлены.\n");
                    break;
                }
                if (diseases == NULL)
                {
                    printf("Болезни ещё не добавлены.\n");
                    break;
                }

                humanDiseases = CreatingConnection(humans, diseases,
                                                   humanDiseases,
                                                   countHumans,
                                                   countDiseases,
                                                   &countHumDis);
                break;

            case PRINTING_ELEMENTS:
                printf("-------------------\n");
                printf("| Вывод элементов |\n");
                printf("-------------------\n");

                printf("Элементы какого типа вы хотите вывести?\n");
                printf("1 - Человек\n");
                printf("2 - Болезнь\n");

                menuItemsCount = 2;
                userChoice = CheckingInput(firstMessage, lowerBound,
                                           menuItemsCount);
                if (userChoice == 1)
                {
                    if (humans == NULL)
                    {
                        printf("Люди ещё не добавлены.\n");
                        break;
                    }
                    PrintHumans(humans);
                }

                else if (userChoice == 2)
                {
                    if (diseases == NULL)
                    {
                        printf("Болезни ещё не добавлены.\n");
                        break;
                    }
                    PrintDiseases(diseases);
                }
                break;

            case PRINTING_CONNECTIONS:
                if (humanDiseases == NULL)
                {
                    printf("Связи ещё не созданы\n");
                    break;
                }
                PrintingAllConnections(humanDiseases);
                break;

            case RELATED_ELEMENTS:
                if (humanDiseases == NULL)
                {
                    printf("Связи ещё не созданы\n");
                    break;
                }

                printf("По элементу какого типа будем искать связанные?\n");
                printf("1 - Человек\n");
                printf("2 - Болезнь\n");
                menuItemsCount = 2;
                userChoice = CheckingInput(firstMessage, lowerBound,
                                           menuItemsCount);
                if (userChoice == 1)
                {
                    HumanRelated(humanDiseases, humans, countHumans);
                }
                else if (userChoice == 2)
                {
                    DiseaseRelated(humanDiseases, diseases, countDiseases);
                }

                break;

            case DELETING_ELEMENT:
                printf("Элемент какого типа будем удалять?\n");
                printf("1 - Человек\n");
                printf("2 - Болезнь\n");
                menuItemsCount = 2;
                int numberHuman = 0, numberDisease = 0;
                userChoice = CheckingInput(firstMessage, lowerBound,
                                           menuItemsCount);
                if (userChoice == 1)
                {
                    if (humans == NULL)
                    {
                        printf("Люди ещё не добавлены.\n");
                        break;
                    }

                    humans = DeletingHuman(humans, &countHumans, &numberHuman);
                }

                else if (userChoice == 2)
                {
                    if (diseases == NULL)
                    {
                        printf("Болезни ещё не добавлены.\n");
                        break;
                    }
                    diseases = DeletingDisease(diseases, &countDiseases,
                                               &numberDisease);
                }

                humanDiseases = DeletingHumDis(humanDiseases, numberHuman,
                                               numberDisease, &countHumDis);

                break;

            case FILE_HANDLING:
                printf("Что нужно сделать?\n");
                printf("1 - Сохранить данные в файл\n");
                printf("2 - Считать данные из файла\n");
                menuItemsCount = 2;
                userChoice = CheckingInput(firstMessage, lowerBound,
                                           menuItemsCount);
                if (userChoice == 1)
                {
                    SaveInformation(humans, countHumans, diseases,
                                    countDiseases, humanDiseases,
                                    countHumDis);
                }
                else if (userChoice == 2)
                {
                    int position = 0;
                    humans = LoadInformationHuman(humans, &countHumans,
                                                  &position);
                    diseases = LoadInformationDisease(diseases,
                                                      &countDiseases,
                                                      &position);


                    humanDiseases = LoadInformationHumDis(humanDiseases,
                                                          &position,
                                                    &countHumDis, humans,
                                                    diseases);

                    printf("Данные считаны.\n");
                }
                break;

            case SORTING_ELEMENTS:
                printf("Элемент какого типа будем сортировать?\n");
                printf("1 - Человек\n");
                printf("2 - Болезнь\n");
                menuItemsCount = 2;
                userChoice = CheckingInput(firstMessage, lowerBound,
                                           menuItemsCount);
                if (userChoice == 1)
                {
                    if (humans == NULL)
                    {
                        printf("Люди ещё не добавлены.\n");
                        break;
                    }
                    humans = SortingHumans(humans);
                }

                else if (userChoice == 2)
                {
                    if (diseases == NULL)
                    {
                        printf("Болезни ещё не добавлены.\n");
                        break;
                    }
                    diseases = SortingDiseases(diseases);
                }

                break;

            default:
                DeleteListHuman(humans);
                DeleteListDisease(diseases);
                DeleteListHumDis(humanDiseases);
                printf("Выход...");
        }
    } while (userChoice != EXIT);

    return 0;
}
