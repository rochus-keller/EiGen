#include "chibicc.h"
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
