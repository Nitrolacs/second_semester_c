#ifndef STRUCTURE_H_INCLUDED
#define STRUCTURE_H_INCLUDED

typedef struct human
{
    int number;
    char fullName[150];
    int birthYear;
    char gender[80];
    struct human* next;
} Human;

typedef struct disease
{
    int number;
    char name[80];
    char averageDuration[80];
    int heaviness;
    struct disease* next;
} Disease;

typedef struct humanDisease
{
    int linkNumber;
    Human* human;
    Disease* disease;
    struct humanDisease* next;
} HumanDisease;

#endif // STRUCTURE_H_INCLUDED

