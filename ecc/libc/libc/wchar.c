#include "wchar.h"

int wcscmp(const wchar_t * s1, const wchar_t * s2)
{
    // TODO: dummy implementation, check
    while ( ( *s1 ) && ( *s1 == *s2 ) )
    {
        ++s1;
        ++s2;
    }

    return ( *( unsigned * )s1 - * ( unsigned * )s2 );
}

size_t wcslen(const wchar_t * s)
{
    size_t rc = 0;

    while ( s[rc] )
    {
        ++rc;
    }

    return rc;
}
