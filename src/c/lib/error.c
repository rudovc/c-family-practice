#include <stdint.h>
#include <stdio.h>

int32_t print_error(const char* message)
{
        int32_t err = fprintf(stderr, "%s", message);

        if (err < 0) {
                perror("Error");
        }

        return err;
}
