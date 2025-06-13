#include <unistd.h>

#include "parse.h"
#define HEIGHT 25
#define WIDTH 80

int main() {
    char* ptr = read_arr();
    if (ptr != NULL) {
        int len_arr = strlen(ptr);
        char* output_str = polish_convert(ptr, len_arr);
        len_arr = strlen(output_str);
        double step_y = 2.0 / 25.0;
        double step_x = 4.0 * M_PI / 79.0;
        for (double y = -1.0; y <= 1.0; y += step_y) {
            for (double x = 0.0; x <= 4.0 * M_PI; x += step_x) {
                double result = ariphmetics(output_str, x, len_arr);
                if (result <= y + step_y / 2.0 && result >= y - step_y / 2.0)
                    printf("*");
                else
                    printf(".");
            }
            printf("\n");
        }
        free(output_str);
    } else
        printf("NULL");
    free(ptr);
    return 0;
}
