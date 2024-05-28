#include "temp_api.h"
#include "temp_sys.h"

int main(int argc, char *argv[])
{
    uint8_t err = 0;
    err = menu(parse_args(argc, argv));   
    return err;
}