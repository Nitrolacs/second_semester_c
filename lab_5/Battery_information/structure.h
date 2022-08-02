typedef struct battery
{
    char* model;
    char* batterySize;
    int price;
    float voltage;
    char* type;
} battery_t;

typedef struct BatteryList
{
    int batteryNumber;
    battery_t* b_array;
} BatteryList_t;
