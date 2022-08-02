#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

// Функция вывода меню
void PrintMenu(void);

// Функция проверки ввода
int CheckingInput(const char[], int, int);

// Функция ввода строки
char* StringInput(void);

// Функция добавления батарейки в общий массив
void addBattery2Batteries(BatteryList_t*, battery_t);

// Вывод всех батареек
void PrintingBatteries(BatteryList_t);

// Удаление батарейки
void DeletingBattery(BatteryList_t*, int*, int);

// Запись информации о батарейках в файл
void WriteToFile(BatteryList_t);

void PrintingCharacteristics();

// Сортировка батареек
void SortingBatteries(BatteryList_t*, int);

// Ввод числа с плавающей точкой
float FloatInput();

// Компараторы
int ModelComparator(const void*, const void*);

int BatterySizeComparator(const void*, const void*);

int PriceComparator(const void*, const void*);

int VoltageComparator(const void*, const void*);

int TypeComparator(const void*, const void*);

void PrintingBattery(BatteryList_t, int);

// Поиск по полю

void SearchByFeature(BatteryList_t);

#endif // FUNCTIONS_H_INCLUDED
