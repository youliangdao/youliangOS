#include "strncmp.h"

int strncmp(char *s1, char *s2, unsigned int n){
    unsigned int i = 0;
    while(*s1 != '\0' && *s2 != '\0' && ++i < n){
        if(*s1 != *s2) break;
        s1++;
        s2++;
    }
    
    return(*s1 - *s2);
}