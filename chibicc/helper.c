#include "chibicc.h"
#include <sys/stat.h>

char *helper_strndup( const char *src, size_t size )
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

char *helper_strdup( const char *src)
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

char *helper_rebase(const char* newBase, const char* filename)
{
    char *slash = strrchr(newBase, '/');
    if( slash == 0 )
        slash = strrchr(newBase, '\\');
    const int len2 = strlen(filename);
    int len1;
    if (slash)
      len1 = slash - newBase;
    else
      len1 = strlen(newBase);
    const int len3 = len1 + len2 + 2;
    char* res = (char*)malloc(len3);
    memcpy(res, filename, len1);
    res[len1] = '/';
    memcpy(res + len1 + 1, filename, len2 );
    res[len3] = 0;
    return res;
}
