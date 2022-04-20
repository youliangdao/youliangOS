#include "bootpack.h"

int strncmp(char *s1, char *s2, unsigned int n){
    unsigned int i = 0;
    while(*s1 != '\0' && *s2 != '\0' && ++i < n){
        if(*s1 != *s2) break;
        s1++;
        s2++;
    }
    
    return(*s1 - *s2);
}

int isdigit(char c){
    return((c >= '0' && c <= '9'));
}

int strtol(char *s, char **endp, int base){
    int _base;
    int ret = 0;
    int sign = 0;
    
    //空白のスキップ
    while(*s == ' ') s++;
    
    if(*s == '-') sign = 1;
    
    //base = 0なら基数は渡された文字列の表記に従う
    if(base == 0){
        //渡された文字列の表記方法の検出
        //16進数
        if(strncmp(s, "0x", 2) == 0 || strncmp(s, "0X", 2) == 0){
            _base = 16;
        }
        //8進数
        if(strncmp(s, "0", 1) == 0){
            _base = 8;
        }
        //それ以外は10進数
        else{
            _base = 10;
        }
    }
    else{
        _base = base;
    }
    
    //16進数
    if(_base == 16){
       while(isdigit(*s) || (*s >= 'a' && *s <= 'f') || (*s >= 'A' && *s <= 'F') ){
            if(isdigit(*s)){
                ret = (ret * 16) + (*s - '0');
            }
            else if(*s >= 'a' && *s <= 'f'){
                ret = (ret * 16) + (*s - 'a' + 10);
            }
            else if(*s >= 'A' && *s <= 'F'){
                ret = (ret * 16) + (*s - 'A' + 10);
            }
            s++;
        }
    }
    
    //8進数（多分使わないので省略）
    
    //10進数
    if(_base == 10){
        while(isdigit(*s)){
            ret = (ret * 10) + (*s - '0');
            s++;
        }
    }
    
    if(sign != 0) ret *= -1;
    *endp = s;
    return ret;
}
