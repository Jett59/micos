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
int strcmp(const char* a, const char* b) {
    int i = 0;
    while (a[i] == b[i] && a[i]) {
        i++;
    }
    return a[i] - b[i];
}
int strappend(char* str, char c) {
    int len = strlen(str);
    str[len] = c;
    len++;
    str[len] = 0;
    return len;
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
int strcmp32(const u32_t* a, const u32_t* b) {
    int i = 0;
    while (a[i] == b[i] && a[i]) {
        i++;
    }
    return a[i] - b[i];
}
int strappend32(u32_t* str, u32_t n) {
    int len = strlen32(str);
    str[len] = n;
    len++;
    str[len] = 0;
    return len;
}
