#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

typedef struct Battery
{
    int number;
    char model[80];
    char batterySize[80];
    int price;
    float voltage;
    char type[80];
    struct Battery* next;
    struct Battery* prev;
} Battery;

#endif // STRUCTURE_H_INCLUDED

