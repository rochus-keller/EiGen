#include "widcc.h"
#include <sys/stat.h>

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
  char *buf;
  size_t buflen;
  FILE *out = open_memstream(&buf, &buflen);

  va_list ap;
  va_start(ap, fmt);
  vfprintf(out, fmt, ap);
  va_end(ap);
  fclose(out);
  return buf;
}

char *mystrndup( const char *src, size_t size )
{
    int null = -1;
    for(int i = 0; i < size; i++ )
    {
        if( src[i] == 0 )
        {
            null = i;
            break;
        }
    }
    if( null == -1 )
        null = size;
    size = null + 1;
    char* res = (char*)malloc(size);
    memcpy(res, src, null);
    res[null] = 0;
    return res;
}

char *mystrdup( const char *src)
{
    const int len = strlen(src);
    char* res = (char*)malloc(len+1);
    memcpy(res, src, len+1);
    return res;
}

// Returns true if a given file exists.
bool file_exists(char *path) {
  struct stat st;
  return !stat(path, &st);
}

char *rebase_file(const char* newBase, const char* filename)
{
    char *slash = strrchr(newBase, '/');
    if( slash == 0 )
        slash = strrchr(newBase, '\\');
    const int filenameLen = strlen(filename);
    int pathLen;
    if (slash)
      pathLen = slash - newBase;
    else
      pathLen = strlen(newBase);
    const int newPathLen = pathLen + filenameLen + 2;
    char* res = (char*)malloc(newPathLen);
    memcpy(res, newBase, pathLen);
    res[pathLen] = '/';
    memcpy(res + pathLen + 1, filename, filenameLen );
    res[newPathLen-1] = 0;
    return res;
}
