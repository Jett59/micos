#include <strings.h>

int strlen(const char* str) {
    int i = 0;
    while (str[i++]);
    return i - 1;
}
int strcpy(char* dest, const char* src) {
    int i = 0;
    do {
        dest[i] = src[i];
    }while (src[i++]);
    return i - 1;
}
int strlen32(const u32_t* str) {
    int i = 0;
    while (str[i++]);
    return i - 1;
}
int strcpy32(u32_t* dest, const u32_t* src) {
    int i = 0;
    do {
        dest[i] = src[i];
    }while (src[i++]);
    return i - 1;
}
