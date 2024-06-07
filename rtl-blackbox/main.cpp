#include "add.hpp"
int main (void) {
    static uint32_t a[1024];
    static uint32_t b[1024];
    static uint32_t c[1024];
    static uint32_t c_stream[1024];
    for (uint32_t i = 0; i < 1024; ++i) {
        a[i] = i;
        b[i] = i;
        c[i] = 0;
        c_stream[i] = 0;
    }
    top_module(a, b, c, c_stream);
    for (uint32_t i = 0; i < 1024; ++i) {
        if (c[i] != a[i] + b[i]) {
            printf("Data does not match. %d vs %d\n", c[i], a[i] + b[i]);
            return -1;
        }
        if (c[i] != c_stream[i]) {
            printf("Data does not match. %d vs %d\n", c[i], c_stream[i]);
            printf("Add modules have different results.\n");
            return -2; 
        }
    }
    printf("Test succesfull.\n");
    return 0;
}