#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

// Функция вывода меню
void PrintMenu(void);

// Функция проверки ввода
int CheckingInput(const char[], int, int);

// Функция ввода строки
char* StringInput(void);

// Вывод всех батареек
void PrintList(Battery*);

// Удаление элемента
Battery* RemoveBattery(Battery*, Battery*);

// Удаление батарейки
Battery* DeletingBattery(Battery*, int);

// Создание батарейки
Battery* CreateBattery(int, const char*, const char*,
                       int, float, const char*);

// Вставка батарейки в произвольную позицию списка
Battery* InsertAfter(Battery*, Battery*);

// Поиск конца списка
Battery* GetTail(Battery*);

// Добавление батарейки в конец списка
Battery* PushBack(Battery*, Battery*);

// Запись информации о батарейках в файл
void WriteToFile(Battery*);

void PrintingCharacteristics();

// Перестановка соседних элементов списка
Battery* SwapItems(Battery*, Battery*, Battery*);

// Сортировка батареек
Battery* SortingBatteries(Battery*, int);

// Ввод числа с плавающей точкой
float FloatInput();

void PrintingBattery(Battery*);

// Поиск по полю
void SearchByFeature(Battery*);

// Удаление списка
void DeleteList(Battery*);

// Определение длины списка
int GetLength(Battery*);

// Инвертирование связного списка
Battery* ReverseList(Battery*, int);

#endif // FUNCTIONS_H_INCLUDED
