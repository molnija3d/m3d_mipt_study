typedef struct 
{
    uint8_t item;
    char *file;
    uint8_t month;
} params; 

enum
{
    HELP,
    FULL,
    MONTH,
    WRONG
};

params parse_args(int argc, char *argv[]);
uint8_t menu(params);