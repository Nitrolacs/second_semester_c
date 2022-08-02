#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED


/// PrintMenu - Вывод меню программы.
void PrintMenu(void);


/// CheckingInput - Получение числа из пользовательского ввода.
/// \param message - Сообщение, приглашающее ко вводу.
/// \param lowerBound - Нижняя допустимая граница вводимых чисел.
/// \param count - Верхняя допустимая граница вводимых чисел
/// \return userInput - Число, введённое пользователем.
int CheckingInput(const char message[], int lowerBound, int count);


/// Функция ввода строки
/// \return userStr - Введённая пользователем строка.
char* StringInput(void);


// Функции для человека.


/// CreateHuman - Создание нового экземпляра структуры Human.
/// \param n - Номер человека.
/// \param fullName - ФИО человека.
/// \param birthYear - Год рождения человека.
/// \param gender - Пол человека.
/// \return human - Экземпляр структуры Human.
Human* CreateHuman(int n, const char* fullName, int birthYear,
                   const char* gender);


/// InsertAfterHuman - Вставка экземпляра в произвольную позицию списка.
/// \param leftHuman - Левый элемент.
/// \param newHuman - Правый элемент.
/// \return newHuman - Новый элемент, вставленный в конец.
Human* InsertAfterHuman(Human* leftHuman, Human* newHuman);


/// GetTailHuman - Поиск конца списка.
/// \param humans - Список людей.
/// \return humans - Последний элемент в списке.
Human* GetTailHuman(Human* humans);


/// PushBackHuman - Добавление человека в конец списка.
/// \param humans - Список людей.
/// \param newHuman - Новый элемент, который нужно вставить после последнего.
/// \return newHuman - Последний элемент.
Human* PushBackHuman(Human* humans, Human* newHuman);


/// AddingHuman - Добавление человека.
/// \param humans - Список людей.
/// \param countHumans - Количество людей.
/// \return humans - Список людей с добавленным человеком.
Human* AddingHuman(Human* humans, int* countHumans);


/// PrintHumans - Вывод информации о людях.
/// \param human - Список людей.
void PrintHumans(Human* human);


/// DeleteListHuman - Очищение списка людей
/// \param list - Список людей.
void DeleteListHuman(Human* list);


/// RemoveHuman - Удаление человека из списка.
/// \param first - Первый элемент списка людей.
/// \param del - Удаляемый элемент.
/// \return first - Список людей без удалённого человека.
Human* RemoveHuman(Human* first, Human* del);


/// DeletingHuman - Получение информации о том, какого человека нужно удалить.
/// \param humans - Список людей.
/// \param countHumans - Количество людей
/// \param numberHuman - Номер удаляемого человека
/// \return humans - Список людей без удалённого человека.
Human* DeletingHuman(Human* humans, int* countHumans, int* numberHuman);


/// SwapItemsHuman - Перестановка соседних элементов местами.
/// \param list - Список людей.
/// \param first - Первый элемент.
/// \param second - Второй элемент.
/// \return list - Список людей с перестановленными элементами.
Human* SwapItemsHuman(Human* list, Human* first, Human* second);


/// SortingHumans - Сортировка списка людей.
/// \param humans - Список людей.
/// \return head - Отсортированный список.
Human* SortingHumans(Human* humans);


// Функции для болезни.


/// CreateDisease - Создание нового экземпляра структуры Disease.
/// \param n - Номер болезни.
/// \param name - Название болезни.
/// \param averageDuration - Средняя продолжительность болезни.
/// \param heaviness - Тяжесть болезни (по 10 бальной шкале).
/// \return disease - Экземпляр структуры Disease.
Disease* CreateDisease(int n, const char* name,
                       const char* averageDuration, int heaviness);


/// InsertAfterDisease - Вставка экземпляра в произвольную позицию списка.
/// \param leftDisease - Левый элемент.
/// \param newDisease - Правый элемент.
/// \return newDisease - Новый элемент, вставленный в конец.
Disease* InsertAfterDisease(Disease* leftDisease, Disease* newDisease);


/// GetTailDisease - Поиск конца списка.
/// \param diseases - Список болезней.
/// \return diseases - Последний элемент в списке.
Disease* GetTailDisease(Disease* diseases);


/// PushBackDisease - Добавление болезни в конец списка.
/// \param diseases - Список болезней.
/// \param newDisease - Новый элемент, который нужно вставить после последнего.
/// \return newDisease - Последний элемент.
Disease* PushBackDisease(Disease* diseases, Disease* newDisease);


/// AddingDisease - Добавление болезни.
/// \param diseases - Список болезней.
/// \param countDiseases - Количество болезней.
/// \return diseases - Список болезней с добавленной болезней.
Disease* AddingDisease(Disease* diseases, int* countDiseases);


/// PrintDiseases - Вывод информации о болезнях.
/// \param disease - Список болезней.
void PrintDiseases(Disease* disease);


/// DeleteListDisease - Очищение списка болезней.
/// \param list - Список болезней.
void DeleteListDisease(Disease* list);


/// RemoveDisease - Удаление болезни из списка.
/// \param first - Первый элемент списка болезней.
/// \param del - Удаляемый элемент.
/// \return first - Список болезней без удалённой болезни.
Disease* RemoveDisease(Disease* first, Disease* del);


/// Получение информации о том, какую болезнь нужно удалить.
/// \param diseases - Список болезней.
/// \param countDiseases - Количество болезней.
/// \param numberDisease - Номер удаляемой болезни.
/// \return diseases - Список болезней без удалённой болезни.
Disease* DeletingDisease(Disease* diseases, int* countDiseases,
                         int* numberDisease);


/// SwapItemsDisease - Перестановка соседних элементов местами.
/// \param list - Список болезней.
/// \param first - Первый элемент.
/// \param second - Второй элемент.
/// \return list - Список болезней с перестановленными элементами.
Disease* SwapItemsDisease(Disease* list, Disease* first, Disease * second);


/// SortingDiseases - Сортировка списка болезней.
/// \param diseases - Список болезней.
/// \return head - Отсортированный список.
Disease* SortingDiseases(Disease* diseases);


// Функции для создания связи.


/// PrintingAllConnections - Вывод всех связей.
/// \param humanDisease - Список всех связей.
void PrintingAllConnections(HumanDisease* humanDisease);


/// CreateHumanDisease - Создание нового экземпляра структуры HumanDisease.
/// \param n - Номер связи.
/// \param human - Экземпляр структуры Human.
/// \param disease - Экземпляр структуры Disease.
/// \return humDis - Список связей.
HumanDisease* CreateHumanDisease(int n, Human* human, Disease* disease);


/// InsertAfterHumDis - Вставка в конец массива.
/// \param leftHumDis - Левый элемент.
/// \param newHumDis - Новый элемент.
/// \return newHumDis - Последний элемент.
HumanDisease* InsertAfterHumDis(HumanDisease* leftHumDis,
                                HumanDisease* newHumDis);


/// GetTailHumDis - Нахождение последнего элемента списка.
/// \param humanDiseases - Список связей.
/// \return humanDiseases - Последний элемент.
HumanDisease* GetTailHumDis(HumanDisease* humanDiseases);


/// PushBackHumDis - Добавление в конец списка нового элемента.
/// \param humanDiseases - Список связей.
/// \param newHumDis - Новый элемент.
/// \return humanDiseases - Список связей с новым элементом.
HumanDisease* PushBackHumDis(HumanDisease* humanDiseases,
                             HumanDisease* newHumDis);


/// CreatingConnection - Создание связи.
/// \param humans - Список людей.
/// \param diseases - Список болезней.
/// \param humanDiseases - Список связей.
/// \param countHumans - Количество людей.
/// \param countDiseases - Количество болезней.
/// \param countHumDis - Количество связей.
/// \return humanDiseases - Созданная связь.
HumanDisease* CreatingConnection(Human* humans, Disease* diseases,
                                 HumanDisease* humanDiseases,
                                 int countHumans, int countDiseases,
                                 int* countHumDis);


/// DeleteListHumDis - Очищение списка связей.
/// \param list - Список связей.
void DeleteListHumDis(HumanDisease* list);


/// RemoveHumDis - Удаление элемента из списка.
/// \param first - Первый элемент.
/// \param del - Удаляемый элемент.
/// \return first - Список без удалённого элемента.
HumanDisease* RemoveHumDis(HumanDisease* first, HumanDisease* del);


/// DeletingHumDis - Получение информации о том, какой элемент нужно удалить.
/// \param humanDisease - Список связей.
/// \param numberHuman - Номер человека.
/// \param numberDisease - Номер болезни.
/// \return humanDisease - Список связей.
HumanDisease* DeletingHumDis(HumanDisease* humanDisease, int numberHuman,
                             int numberDisease, int* countHumDis);


// Другие функции


/// HumanRelated - Получение элементов, связанных с человеком.
/// \param humanDisease - Список связей.
/// \param humans - Список людей.
/// \param countHumans - Количество людей.
void HumanRelated(HumanDisease* humanDisease, Human* humans,
                  int countHumans);


/// DiseaseRelated - Получение элементов, связанных с болезнью.
/// \param humanDisease - Список связей.
/// \param diseases - Список болезней.
/// \param countDiseases - Количество болезней.
void DiseaseRelated(HumanDisease* humanDisease, Disease* diseases,
                    int countDiseases);


// Работа с файлом


/// SaveInformation - Сохранение информации в файл.
/// \param humans - Список людей.
/// \param countHumans - Количество людей.
/// \param diseases - Список болезней.
/// \param countDiseases - Количество болезней.
/// \param humanDiseases - Список связей.
/// \param countHumDis - Количество связей.
void SaveInformation(Human* humans, int countHumans, Disease* diseases,
                     int countDiseases, HumanDisease* humanDiseases,
                     int countHumDis);


/// LoadInformationHuman - Загрузка информации о людях из файла.
/// \param humans - Список людей.
/// \param countHumans - Количество людей.
/// \param position - Позиция каретки в файле.
/// \return humans - Считанный список людей.
Human* LoadInformationHuman(Human* humans, int* countHumans, int* position);


/// LoadInformationDisease - Загрузка информации о болезнях из файла.
/// \param diseases - Список болезней.
/// \param countDiseases - Количество болезней.
/// \param position - Позиция каретки в файле.
/// \return diseases - Считанный список болезней.
Disease* LoadInformationDisease(Disease* diseases, int* countDiseases,
                                int* position);


/// SearchHuman - Поиск человека.
/// \param humans - Список людей.
/// \param numberHuman - Номер человека.
/// \return curHum - Текущий человек.
Human* SearchHuman(Human* humans, int numberHuman);


/// SearchDisease - Поиск болезней.
/// \param diseases - Список болезней.
/// \param numberDisease - Номер болезни.
/// \return curDis - Текущая болезнь.
Disease* SearchDisease(Disease* diseases, int numberDisease);


/// LoadInformationHumDis - Загрузка информации о связях.
/// \param humanDisease - Список связей.
/// \param position - Позиция каретки в файле.
/// \param countHumDis - Количество связей.
/// \param humans - Список людей.
/// \param diseases - Список болезней.
/// \return humanDisease - Загруженный список связей.
HumanDisease* LoadInformationHumDis(HumanDisease* humanDisease, int* position,
                                    int* countHumDis, Human* humans,
                                    Disease* diseases);

#endif // FUNCTIONS_H_INCLUDED
