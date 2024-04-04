#include "chibicc.h"

void strarray_push(StringArray *arr, char *s) {
  if (!arr->data) {
    arr->data = calloc(8, sizeof(char *));
    arr->capacity = 8;
  }

  if (arr->capacity == arr->len) {
    arr->data = realloc(arr->data, sizeof(char *) * arr->capacity * 2);
    arr->capacity *= 2;
    for (int i = arr->len; i < arr->capacity; i++)
      arr->data[i] = NULL;
  }

  arr->data[arr->len++] = s;
}

// Takes a printf-style format string and returns a formatted string.
char *format(char *fmt, ...) {
  static const int buflen = 2048;
  char buf[buflen];

  va_list ap;
  va_start(ap, fmt);
  int len = vsnprintf(buf, buflen, fmt, ap);

  if( len < 0 )
      len = 0;

  char* out = (char*)malloc(len+1);
  if( len > buflen )
      vsnprintf(out, len, fmt, ap);
  memcpy(out,buf,len);
  out[len] = 0;

  va_end(ap);

  return out;
}
