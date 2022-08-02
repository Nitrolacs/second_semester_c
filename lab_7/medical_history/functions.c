#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structure.h"

#define CORRECT_INPUT 2
#define END_STRING '\n'
#define BACKSPACE_KEY 8

// Вывод меню
void PrintMenu(void)
{
    printf("-------------------\n");
    printf("| Меню программы: |\n");
    printf("-------------------\n");
    printf("1 - Добавление элементов\n");
    printf("2 - Создание связи между элементами\n");
    printf("3 - Вывод элементов на экран\n");
    printf("4 - Вывод всех связей\n");
    printf("5 - Вывод всех элементов, связанных с другим\n");
    printf("6 - Удаление элемента\n");
    printf("7 - Запись и чтение данных из файла\n");
    printf("8 - Сортировка по одному из полей\n");
    printf("9 - Выход\n");
}

// Проверка вводимого числа
int CheckingInput(const char message[], int lowerBound, int count)
{
    int userInput = 1;
    char inputChar = '\0';

    printf("%s", message);
    int input = scanf("%d%c", &userInput, &inputChar);
    // Если числа ограничены сверху
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
    // Функция, отвечающая за ввод строки
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

        else
        {
            if (curChar != '\n')
            {
                deltaVal = 1; // Увеличиваем длину на 1
                lengthDif = 2; // Не заполняем последние 2 символа -
                               // оставляем место для введённого символа и \0
            }
            else
            {
                continue;
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

// ФУНКЦИИ ДЛЯ ЧЕЛОВЕКА

Human* CreateHuman(int n, const char* fullName, int birthYear,
                       const char* gender)
{
    // Создать новый экземпляр структуры
    // (выделить память):
    Human* human = (Human*) malloc(sizeof(Human));
    // Присвоить все характеристики батарейки
    human->number = n;
    strcpy(human->fullName, fullName);
    human->birthYear = birthYear;
    strcpy(human->gender, gender);
    // Обнулить указатель на след. и пред. элемент:
    human->next = NULL;
    return human;
}

Human* InsertAfterHuman(Human* leftHuman, Human* newHuman)
{
    // Вставка нового элемента после последнего
    if (leftHuman != NULL)
    {
        newHuman->next = leftHuman->next;
        leftHuman->next = newHuman;
    }
    return newHuman;
}

Human* GetTailHuman(Human* humans)
{
    // Получение последнего элемента в массиве человек
    if (humans == NULL)
    {
        return NULL;
    }

    while (humans->next != NULL) // Пока не конец списка
    {
        humans = humans->next; // перейти к след. элементу
    }

    // Теперь humans указывает на последний элемент.
    return humans; // Вернуть указатель из функции.
}

Human* PushBackHuman(Human* humans, Human* newHuman)
{
    // Найти последний элемент списка:
    Human* last = GetTailHuman(humans);
    // Вставить новый элемент после последнего:
    return InsertAfterHuman(last, newHuman);
}

Human* AddingHuman(Human* humans, int* countHumans)
{
    // Добавление человека

    int humanNumber =
            CheckingInput("Сколько людей вы хотите добавить: ",
                          0, 0);
    for (int i = *countHumans;
         i < *countHumans + humanNumber;
         ++i)
    {

        printf("--------------\n");
        printf("| Человек №%d|\n", i + 1);
        printf("--------------\n");
        printf("Введите ФИО человека: ");
        char* fullName = StringInput();
        int birthYear = CheckingInput("Введите год рождения человека: ",
                                  0, 0);
        printf("Введите пол человека: ");
        char* gender = StringInput();

        Human* newHuman = CreateHuman(i + 1, fullName,
                                            birthYear,
                                            gender);
        PushBackHuman(humans, newHuman);

        if (humans == NULL)
        {
            humans = newHuman;
        }
    }
    *countHumans += humanNumber;
    return humans;
}

void PrintHumans(Human* human)
{
    // Вывод информации о людях

    printf("---------------\n");
    printf("| Вывод людей |\n");
    printf("---------------\n");
    printf("---------------\n");
    while (human != NULL)
    {
        printf("Человек №%d:\n", human->number);
        printf("ФИО: %s\n", human->fullName);
        printf("Год рождения: %d\n", human->birthYear);
        printf("Пол: %s\n", human->gender);
        printf("------------------\n");
        human = human->next;
    }
}

void DeleteListHuman(Human* list)
{
    // Удаление списка людей
    while (list)
    {
        Human* tmp = list;
        list = list->next;
        free(tmp);
    }
}

Human* RemoveHuman(Human* first, Human* del)
{
    // Если УЭ - это начало списка, то
    if (del == first)
    {
        // НС = следующий за НС
        first = first->next;
        // Обнулить связь УЭ со след. и пред. элементом.
        del->next = NULL;
        // Выйти из функции, вернув НС.
        return first;
    }

    // Установить ПЭ равным НС.
    Human* p = first;
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

Human* DeletingHuman(Human* humans, int* countHumans, int* numberHuman)
{
    // Удаление элемента типа "человек"
    PrintHumans(humans);
    *numberHuman = CheckingInput("Введите номер человека, которого "
                                   "вы хотите удалить: ", 1,
                                   *countHumans);
    Human* cur = humans;
    while (cur != NULL)
    {
        Human* tmp = cur;
        cur = cur->next;
        if (tmp->number == *numberHuman)
        {
            humans = RemoveHuman(humans, tmp);
        }
    }
    *countHumans -= 1;
    return humans;
}

Human* SwapItemsHuman(Human* list, Human* first, Human* second)
{
    // Перестановка соседних элементов местами
    if (list == first)
    {
        first->next = second->next;
        second->next = first;
        return second;
    }

    Human* p = list;
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

Human* SortingHumans(Human* humans)
{
    // Сортировка людей
    printf("------------------\n");
    printf("1 - ФИО\n");
    printf("2 - Год рождения\n");
    printf("3 - Пол\n");
    printf("------------------\n");
    printf("По какому полю будем сортировать?\n");
    const char firstMessage[] = "Введите номер пункта: ";
    int userChoice = 0;
    int menuItemsCount = 3; // кол-во пунктов меню
    int lowerBound = 1; // нижняя граница допустимых значений
    userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);

    int bWasModified = 0;
    Human* head = humans;
    do
    {
        bWasModified = 0;
        Human* cur = head;

        while (cur != NULL && cur->next != NULL)
        {
            if (userChoice == 1 && strcmp(cur->fullName,
                                          cur->next->fullName) < 0)
            {
                head = SwapItemsHuman(head, cur, cur->next);
                bWasModified = 1;
            }
            else if (userChoice == 2 && cur->birthYear < cur->next->birthYear)
            {
                head = SwapItemsHuman(head, cur, cur->next);
                bWasModified = 1;
            }
            else if (userChoice == 3 && strcmp(cur->gender,
                                               cur->next->gender) < 0)
            {
                head = SwapItemsHuman(head, cur, cur->next);
                bWasModified = 1;
            }
            else
            {
                cur = cur->next;
            }
        }
    } while (bWasModified);

    printf("Сортировка прошла успешно.\n");
    return head;
}

// ФУНКЦИИ ДЛЯ БОЛЕЗНИ

Disease* CreateDisease(int n, const char* name,
                   const char* averageDuration, int heaviness)
{
    // Создать новый экземпляр структуры
    // (выделить память):
    Disease* disease = (Disease*) malloc(sizeof(Disease));
    // Присвоить все характеристики батарейки
    disease->number = n;
    strcpy(disease->name, name);
    strcpy(disease->averageDuration, averageDuration);
    disease->heaviness = heaviness;
    // Обнулить указатель на след. элемент:
    disease->next = NULL;
    return disease;
}

Disease* InsertAfterDisease(Disease* leftDisease, Disease* newDisease)
{
    // Вставка новой болезнм в конец массива
    if (leftDisease != NULL)
    {
        newDisease->next = leftDisease->next;
        leftDisease->next = newDisease;
    }
    return newDisease;
}

Disease* GetTailDisease(Disease* diseases)
{
    // Получение последнего элемента в массиве
    if (diseases == NULL)
    {
        return NULL;
    }

    while (diseases->next != NULL) // Пока не конец списка
    {
        diseases = diseases->next; // перейти к след. элементу
    }

    // Теперь diseases указывает на последний элемент.
    return diseases; // Вернуть указатель из функции.
}

Disease* PushBackDisease(Disease* diseases, Disease* newDisease)
{
    // Найти последний элемент списка:
    Disease* last = GetTailDisease(diseases);
    // Вставить новый элемент после последнего:
    return InsertAfterDisease(last, newDisease);
}

Disease* AddingDisease(Disease* diseases, int* countDiseases)
{
    // Добавление новой болезни
    int diseaseNumber =
            CheckingInput("Сколько болезней вы хотите добавить: ",
                          0, 0);
    for (int i = *countDiseases;
         i < *countDiseases + diseaseNumber;
         ++i)
    {

        printf("--------------\n");
        printf("| Болезнь №%d|\n", i + 1);
        printf("--------------\n");
        printf("Введите название болезни: ");
        char* name = StringInput();
        printf("Введите среднюю продолжительность: ");
        char* averageDuration = StringInput();
        int heaviness = CheckingInput("Введите тяжесть по 10 бальной шкале: ",
                                      1, 10);
        Disease* newDisease = CreateDisease(i + 1, name,
                                      averageDuration,
                                      heaviness);
        PushBackDisease(diseases, newDisease);

        if (diseases == NULL)
        {
            diseases = newDisease;
        }
    }
    *countDiseases += diseaseNumber;
    return diseases;
}


void PrintDiseases(Disease* disease)
{
    // Вывод информации о болезнях
    printf("------------------\n");
    printf("| Вывод болезней |\n");
    printf("------------------\n");
    printf("------------------\n");
    while (disease != NULL)
    {
        printf("Болезнь №%d:\n", disease->number);
        printf("Название: %s\n", disease->name);
        printf("Средняя продолжительность: %s\n", disease->averageDuration);
        printf("Тяжесть по 10 бальной шкале: %d\n", disease->heaviness);
        printf("------------------\n");
        disease = disease->next;
    }
}

void DeleteListDisease(Disease* list)
{
    // Удаление списка болезней
    while (list)
    {
        Disease* tmp = list;
        list = list->next;
        free(tmp);
    }
}

Disease* RemoveDisease(Disease* first, Disease* del)
{
    // Если УЭ - это начало списка, то
    if (del == first)
    {
        // НС = следующий за НС
        first = first->next;
        // Обнулить связь УЭ со след. и пред. элементом.
        del->next = NULL;
        // Выйти из функции, вернув НС.
        return first;
    }

    // Установить ПЭ равным НС.
    Disease* p = first;
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

Disease* DeletingDisease(Disease* diseases, int* countDiseases,
                         int* numberDisease)
{
    // Удаление болезни
    PrintDiseases(diseases);
    *numberDisease = CheckingInput("Введите номер болезни, которую "
                                    "вы хотите удалить: ", 1,
                                    *countDiseases);
    Disease* cur = diseases;
    while (cur != NULL)
    {
        Disease* tmp = cur;
        cur = cur->next;
        if (tmp->number == *numberDisease)
        {
            diseases = RemoveDisease(diseases, tmp);
        }
    }
    *countDiseases -= 1;
    return diseases;
}

Disease* SwapItemsDisease(Disease* list, Disease* first, Disease * second)
{
    // Перестановка двух соседних элементов
    if (list == first)
    {
        first->next = second->next;
        second->next = first;
        return second;
    }

    Disease* p = list;
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

Disease* SortingDiseases(Disease* diseases)
{
    // Сортировка болезней
    printf("-------------------------------\n");
    printf("1 - Наименование\n");
    printf("2 - Средняя продолжительность\n");
    printf("3 - Тяжесть по 10 бальной шкале\n");
    printf("-------------------------------\n");
    printf("По какому полю будем сортировать?\n");
    const char firstMessage[] = "Введите номер пункта: ";
    int userChoice = 0;
    int menuItemsCount = 3; // кол-во пунктов меню
    int lowerBound = 1; // нижняя граница допустимых значений
    userChoice = CheckingInput(firstMessage, lowerBound, menuItemsCount);

    int bWasModified = 0;
    Disease* head = diseases;
    do
    {
        bWasModified = 0;
        Disease* cur = head;

        while (cur != NULL && cur->next != NULL)
        {
            if (userChoice == 1 && strcmp(cur->name,
                                          cur->next->name) < 0)
            {
                head = SwapItemsDisease(head, cur, cur->next);
                bWasModified = 1;
            }
            else if (userChoice == 2 && strcmp(cur->averageDuration,
                                               cur->next->
                                               averageDuration) < 0)
            {
                head = SwapItemsDisease(head, cur, cur->next);
                bWasModified = 1;
            }
            else if (userChoice == 3 && cur->heaviness < cur->
            next->heaviness)
            {
                head = SwapItemsDisease(head, cur, cur->next);
                bWasModified = 1;
            }
            else
            {
                cur = cur->next;
            }
        }
    } while (bWasModified);

    printf("Сортировка прошла успешно.\n");
    return head;
}

// ФУНКЦИИ ДЛЯ СОЗДАНИЯ СВЯЗИ

void PrintingAllConnections(HumanDisease* humanDisease)
{
    // Вывод всех связей
    printf("----------------\n");
    printf("| Вывод связей |\n");
    printf("----------------\n");
    printf("----------------\n");
    while (humanDisease != NULL)
    {
        printf("Связь №%d:\n", humanDisease->linkNumber);
        printf("%s - %s\n", humanDisease->human->fullName,
               humanDisease->disease->name);
        printf("------------------\n");
        humanDisease = humanDisease->next;
    }
}

HumanDisease* CreateHumanDisease(int n, Human* human, Disease* disease)
{
    // Создать новый экземпляр структуры
    // (выделить память)
    HumanDisease* humDis = (HumanDisease*) malloc(sizeof(HumanDisease));
    // Присвоить все характеристики батарейки
    humDis->linkNumber = n;
    humDis->human = human;
    humDis->disease = disease;
    // Обнулить указатель на след. элемент:
    humDis->next = NULL;
    return humDis;
}

HumanDisease* InsertAfterHumDis(HumanDisease* leftHumDis,
                                HumanDisease* newHumDis)
{
    // Вставка в конец массива
    if (leftHumDis != NULL)
    {
        newHumDis->next = leftHumDis->next;
        leftHumDis->next = newHumDis;
    }
    return newHumDis;
}

HumanDisease* GetTailHumDis(HumanDisease* humanDiseases)
{
    // Нахождение последнего элемента массива
    if (humanDiseases == NULL)
    {
        return NULL;
    }

    while (humanDiseases->next != NULL) // Пока не конец списка
    {
        humanDiseases = humanDiseases->next; // перейти к след. элементу
    }

    // Теперь humanDiseases указывает на последний элемент.
    return humanDiseases; // Вернуть указатель из функции.
}

HumanDisease* PushBackHumDis(HumanDisease* humanDiseases,
                             HumanDisease* newHumDis)
{
    // Найти последний элемент списка:
    HumanDisease* last = GetTailHumDis(humanDiseases);
    // Вставить новый элемент после последнего:
    return InsertAfterHumDis(last, newHumDis);
}

HumanDisease* CreatingConnection(Human* humans, Disease* diseases,
                                 HumanDisease* humanDiseases,
                                 int countHumans, int countDiseases,
                                 int* countHumDis)
{
    // Создание связи
    printf("-------------------\n");
    printf("| Создание связей |\n");
    printf("-------------------\n");

    PrintHumans(humans);
    int userChoice = CheckingInput("Введите номер человека, "
                                   "которого вы хотите выбрать: ",
                                   1, countHumans);
    Human* curHum = humans;
    while (curHum != NULL)
    {
        if (curHum->number != userChoice)
        {
            curHum = curHum->next;
        }
        else
        {
            break;
        }
    }

    PrintDiseases(diseases);
    userChoice = CheckingInput("Введите номер болезни, "
                               "которую вы хотите выбрать: ",
                               1, countDiseases);
    Disease* curDis = diseases;
    while (curDis != NULL)
    {
        if (curDis->number != userChoice)
        {
            curDis = curDis->next;
        }
        else
        {
            break;
        }
    }

    HumanDisease* newHumDis = CreateHumanDisease(*countHumDis + 1,
                                                 curHum, curDis);
    PushBackHumDis(humanDiseases, newHumDis);

    if (humanDiseases == NULL)
    {
        humanDiseases = newHumDis;
    }

    *countHumDis += 1;
    return humanDiseases;
}

void DeleteListHumDis(HumanDisease* list)
{
    // Удаление списка связей
    while (list)
    {
        HumanDisease* tmp = list;
        list = list->next;
        free(tmp);
    }
}

HumanDisease* RemoveHumDis(HumanDisease* first, HumanDisease* del)
{
    // Если УЭ - это начало списка, то
    if (del == first)
    {
        // НС = следующий за НС
        first = first->next;
        // Обнулить связь УЭ со след. и пред. элементом.
        del->next = NULL;
        // Выйти из функции, вернув НС.
        return first;
    }

    // Установить ПЭ равным НС.
    HumanDisease* p = first;
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

HumanDisease* DeletingHumDis(HumanDisease* humanDisease, int numberHuman,
                             int numberDisease, int* countHumDis)
{
    HumanDisease* cur = humanDisease;
    if (numberHuman > 0)
    {
        while (cur != NULL)
        {
            HumanDisease* tmp = cur;
            cur = cur->next;
            if (tmp->human->number == numberHuman)
            {
                humanDisease = RemoveHumDis(humanDisease, tmp);
            }
        }
    }
    else if (numberDisease > 0)
    {
        while (cur != NULL)
        {
            HumanDisease* tmp = cur;
            cur = cur->next;
            if (tmp->disease->number == numberDisease)
            {
                humanDisease = RemoveHumDis(humanDisease, tmp);
            }
        }
    }

    *countHumDis -= 1;
    return humanDisease;
}

// Другие функции

void HumanRelated(HumanDisease* humanDisease, Human* humans,
                  int countHumans)
{
    // Нахождение элементов, связанных с человеком
    PrintHumans(humans);
    int userChoice = CheckingInput("Введите номер человека, "
                                   "которого вы хотите выбрать: ",
                                   1, countHumans);

    printf("Все связанные с ним элементы:\n");
    printf("-----------------------------\n");
    while (humanDisease != NULL)
    {
        if (humanDisease->human->number == userChoice)
        {
            printf("%s - %s\n", humanDisease->human->fullName,
                   humanDisease->disease->name);
        }
        humanDisease = humanDisease->next;
    }
}

void DiseaseRelated(HumanDisease* humanDisease, Disease* diseases,
                    int countDiseases)
{
    // Нахождение элементов, связанных с болезнью
    PrintDiseases(diseases);
    int userChoice = CheckingInput("Введите номер болезни, "
                                   "которую вы хотите выбрать: ",
                                   1, countDiseases);

    printf("Все связанные с ней элементы:\n");
    printf("-----------------------------\n");
    while (humanDisease != NULL)
    {
        if (humanDisease->disease->number == userChoice)
        {
            printf("%s - %s\n", humanDisease->disease->name,
                   humanDisease->human->fullName);
        }
        humanDisease = humanDisease->next;
    }
}

void SaveInformation(Human* humans, int countHumans, Disease* diseases,
                     int countDiseases, HumanDisease* humanDiseases,
                     int countHumDis)
{
    // Сохранение болезней
    FILE* myFile = fopen("/home/nitrolacs/c programming/lab_7/"
                     "medical_history/files/data.txt", "wt");
    fprintf(myFile, "%d\n", countHumans);
    if (countHumans > 0)
    {
        for (int i = 0; i < countHumans; ++i)
        {
            fprintf(myFile, "%d\n", humans->number);
            fprintf(myFile, "%s\n", humans->fullName);
            fprintf(myFile, "%d\n", humans->birthYear);
            fprintf(myFile, "%s\n", humans->gender);
            humans = humans->next;
        }
    }
    fprintf(myFile, "%d\n", countDiseases);
    if (countDiseases > 0)
    {
        for (int i = 0; i < countDiseases; ++i)
        {
            fprintf(myFile, "%d\n", diseases->number);
            fprintf(myFile, "%s\n", diseases->name);
            fprintf(myFile, "%s\n", diseases->averageDuration);
            fprintf(myFile, "%d\n", diseases->heaviness);
            diseases = diseases->next;
        }
    }
    fprintf(myFile, "%d\n", countHumDis);
    if (countHumDis > 0)
    {
        for (int i = 0; i < countHumDis; ++i)
        {
            fprintf(myFile, "%d\n", humanDiseases->human->number);
            fprintf(myFile, "%d\n", humanDiseases->disease->number);
            humanDiseases = humanDiseases->next;
        }
    }

    printf("Данные записаны.\n");
    fclose(myFile);
}

Human* LoadInformationHuman(Human* humans, int* countHumans, int* position)
{
    // Загрузка информации о людях
    FILE* myFile = fopen("/home/nitrolacs/c programming/lab_7/"
                         "medical_history/files/data.txt", "rt");
    fscanf(myFile, "%d", &*countHumans);

    int number = 0;
    char fullName[150];
    int birthYear = 0;
    char gender[80];

    if (*countHumans > 0)
    {
        for (int i = 0; i < *countHumans; ++i)
        {
            fscanf(myFile, "%d", &number);
            fgetc(myFile);
            int index = 0, flag = 0;
            while (flag != 1)
            {
                fullName[index] = fgetc(myFile);
                if (fullName[index] == '\n') {
                    fullName[index] = '\0';
                    flag = 1;
                }
                else index++;
            }
            index = 0;
            flag = 0;
            fscanf(myFile, "%d", &birthYear);
            fscanf(myFile, "%s", &gender);

            Human* newHuman = CreateHuman(number,
                                          fullName,
                                          birthYear,
                                          gender);
            if (i == 0)
            {
                humans = newHuman;
            }
            else
            {
                PushBackHuman(humans, newHuman);
            }
        }
    }

    *position = ftell(myFile);
    fclose(myFile);
    return humans;
}

Disease* LoadInformationDisease(Disease* diseases, int* countDiseases,
                                int* position)
{
    // Загрузка информации о болезнях
    FILE* myFile = fopen("/home/nitrolacs/c programming/lab_7/"
                         "medical_history/files/data.txt", "rt");
    fseek(myFile, *position, SEEK_SET);
    fscanf(myFile, "%d", &*countDiseases);

    int number = 0;
    char name[80];
    char averageDuration[80];
    int heaviness;

    if (*countDiseases > 0)
    {
        for (int i = 0; i < *countDiseases; ++i)
        {
            fscanf(myFile, "%d", &number);
            fgetc(myFile);
            int index = 0, flag = 0;
            while (flag != 1)
            {
                name[index] = fgetc(myFile);
                if (name[index] == '\n') {
                    name[index] = '\0';
                    flag = 1;
                }
                else index++;
            }
            index = 0;
            flag = 0;

            while (flag != 1)
            {
                averageDuration[index] = fgetc(myFile);
                if (averageDuration[index] == '\n') {
                    averageDuration[index] = '\0';
                    flag = 1;
                }
                else index++;
            }

            fscanf(myFile, "%d", &heaviness);

            Disease* newDisease = CreateDisease(number,
                                                name,
                                                averageDuration,
                                                heaviness);
            if (i == 0)
            {
                diseases = newDisease;
            }
            else
            {
                PushBackDisease(diseases, newDisease);
            }
        }
    }

    *position = ftell(myFile);
    fclose(myFile);
    return diseases;
}



Human* SearchHuman(Human* humans, int numberHuman)
{
    Human* curHum = humans;
    while (curHum != NULL)
    {
        if (curHum->number != numberHuman)
        {
            curHum = curHum->next;
        }
        else
        {
            break;
        }
    }
    return curHum;
}

Disease* SearchDisease(Disease* diseases, int numberDisease)
{
    Disease* curDis = diseases;
    while (curDis != NULL)
    {
        if (curDis->number != numberDisease)
        {
            curDis = curDis->next;
        }
        else
        {
            break;
        }
    }
    return curDis;
}

HumanDisease* LoadInformationHumDis(HumanDisease* humanDisease, int* position,
                                    int* countHumDis, Human* humans,
                                    Disease* diseases)
{
    int numberHuman = 0;
    int numberDisease = 0;
    Human* human;
    Disease* disease;

    // Загрузка информации о связях
    FILE* myFile = fopen("/home/nitrolacs/c programming/lab_7/"
                         "medical_history/files/data.txt", "rt");
    fseek(myFile, *position, SEEK_SET);
    fscanf(myFile, "%d", &*countHumDis);

    if (*countHumDis > 0)
    {
        int end = *countHumDis;
        for (int i = 0; i < end; ++i)
        {
            fscanf(myFile, "%d", &numberHuman);
            human = SearchHuman(humans, numberHuman);
            fscanf(myFile, "%d", &numberDisease);
            disease = SearchDisease(diseases, numberDisease);

            HumanDisease* newHumDis = CreateHumanDisease(i + 1,
                                                         human, disease);
            PushBackHumDis(humanDisease, newHumDis);

            if (humanDisease == NULL)
            {
                humanDisease = newHumDis;
            }

        }
    }


    return humanDisease;
}