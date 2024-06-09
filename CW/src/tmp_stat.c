#include "temp_sys.h"
#include "temp_api.h"

int main(int argc, char *argv[])
{
    uint8_t err = 0;
    err = menu(parse_args(argc, argv));
    return err;
}
  