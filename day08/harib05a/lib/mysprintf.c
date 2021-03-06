
#include "mysprintf.h"

int sprintk_dec(char *str, int num, int zero_padding, int width);
int sprintk_hex(char *str, unsigned int num, int capital, int zero_padding, int width);
int sprintk_str(char *str, char *src);
int sprintk_char(char *str, int c);

int sprintk(char *str, char *fmt, ...)
{
  int *arg = (int *)(&str + 2);
  int str_len = 0;
  int convert_len = 0;
  int zero_padding, width = 0;

  int int_val;
  int uint_val;
  
  str_len = 0;
  while (*fmt) {
    if (*fmt != '%') {
      *str++ = *fmt++;
      str_len++;
    } else {
      fmt++;

      zero_padding = 0;
      if (*fmt == '0') {
      	zero_padding = 1;
      	fmt++;
      }
      
      width = 0;
      while ('0' <= *fmt && *fmt <= '9') {
      	width = width * 10 + (*fmt - '0');
	fmt++;
      }
      
      convert_len = 0;
      switch (*fmt) {
      case 'd':
      	convert_len = sprintk_dec(str, *arg++, zero_padding, width);
      	break;
      case 'x':
      	convert_len = sprintk_hex(str, (unsigned int)*arg++, 0, zero_padding, width);
      	break;
      case 'X':
      	convert_len = sprintk_hex(str, (unsigned int)*arg++, 1, zero_padding, width);
      	break;
      case 's':
      	convert_len = sprintk_str(str, (char *)*arg++);
      	break;
      case 'c':
      	convert_len = sprintk_char(str, *arg++);
      	break;
      default:
      	str_len++;
      	*str++ = *fmt;
      	break;
      }

      fmt++;
      str += convert_len;
      str_len += convert_len;
    }
  }

  *str = '\0';

  return str_len;
}

int sprintk_dec(char *str, int num, int zero_padding, int width)
{
  char *dst;
  
  int i = 0;
  char tmp_buf[16 + 1];
  int minus_sign = 0;
  int one_digit;

  dst = str;
  if (num == 0) {
    tmp_buf[i++] = '0';
  } else {
    if (num < 0) {
      minus_sign = 1;
      num = -1 * num;
    }

    while (num > 0) {
      one_digit = num % 10;
      tmp_buf[i++] = '0' + one_digit;

      num /= 10;
    }
  }
    
  while (width - i > 0) {
    tmp_buf[i++] = '0';
  }
  
  if (minus_sign == 1) {
    tmp_buf[i++] = '-';
  }
  
  while (i-- > 0 ) {
    *dst++ = tmp_buf[i];
  }
    
  return dst - str;
}

int sprintk_hex(char *str, unsigned int num, int capital, int zero_padding, int width)
{
  char *dst;
  
  int i = 0;
  char tmp_buf[8];
  int sign = 1;
  int one_digit;
  
  dst = str;

  if (num == 0) {
    tmp_buf[i++] = '0';
  } else {
    while (num > 0) {
      one_digit = num % 16;
      if (one_digit <= 9) {
  	tmp_buf[i++] = '0' + one_digit;
      } else {
  	tmp_buf[i++] = (capital != 0 ? 'A' : 'a') + (one_digit - 10);
      }

      num /= 16;
    }
  }
  
  while (width - i > 0) {
    tmp_buf[i++] = '0';
  }
  
  while (i-- > 0) {
    *dst++ = tmp_buf[i];
  }
  
  return dst - str;
}

int sprintk_str(char *str, char *src)
{
  char *dst;

  dst = str;
  while (*src) {
    *dst++ = *src++;
  }
  
  return dst - str;
}

int sprintk_char(char *str, int c)
{
  *str = c;
  
  return 1;
}