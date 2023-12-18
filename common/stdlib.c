#include "types.h"

char *itoa(int num, char *str, int base) {
  int i = 0;
  unsigned int unum = (unsigned int)num;

  if (unum == 0) {
    str[i++] = '0';
    str[i] = '\0';
    return str;
  }

  while (unum != 0) {
    int rem = unum % base;
    str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    unum = unum / base;
  }

  str[i] = '\0';

  int start = 0;
  int end = i - 1;
  while (start < end) {
    char temp = str[start];
    str[start] = str[end];
    str[end] = temp;
    start++;
    end--;
  }
  return str;
}
