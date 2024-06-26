#include <pdclib/_PDCLIB_glue.h>
#include <stdio.h>
#include "pdclib/_PDCLIB_tzcode.h"

// defined in ECS runtime
extern void _rt_exit(int);

_PDCLIB_LOCAL _PDCLIB_Noreturn void _PDCLIB_Exit( int status ) _PDCLIB_NORETURN
{
    // TODO _rt_exit(status);
}

_PDCLIB_LOCAL _PDCLIB_fd_t _PDCLIB_open( const char * const filename, unsigned int mode )
{
	return NULL; // TODO
}

_PDCLIB_LOCAL int _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream )
{
	return EOF; // TODO
}

_PDCLIB_LOCAL int _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream )
{
	return EOF; // TODO
}

_PDCLIB_LOCAL _PDCLIB_int_least64_t _PDCLIB_seek( struct _PDCLIB_file_t * stream, _PDCLIB_int_least64_t offset, int whence )
{
	return -1; // TODO
}

_PDCLIB_LOCAL int _PDCLIB_close( _PDCLIB_fd_t fd )
{
	return -1; // TODO
}

_PDCLIB_LOCAL int _PDCLIB_changemode( struct _PDCLIB_file_t * stream, unsigned int mode )
{
	return 0; // TODO
}

_PDCLIB_LOCAL char * _PDCLIB_realpath( const char * path )
{
	return NULL; // TODO
}

_PDCLIB_LOCAL int _PDCLIB_remove( const char * pathname )
{
	return -1; // TODO
}

_PDCLIB_LOCAL int _PDCLIB_rename( const char * oldpath, const char * newpath )
{
	return -1; // TODO
}

void __set_errno(int e)
{

}

static char _PDCLIB_sin_buffer[BUFSIZ];
static char _PDCLIB_sout_buffer[BUFSIZ];
static char _PDCLIB_serr_buffer[BUFSIZ];

static struct _PDCLIB_file_t _PDCLIB_serr = { 2, _PDCLIB_serr_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, { 0 }, _IONBF | _PDCLIB_FWRITE,
    NULL, NULL
};
static struct _PDCLIB_file_t _PDCLIB_sout = { 1, _PDCLIB_sout_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, { 0 }, _IOLBF | _PDCLIB_FWRITE,
    NULL, &_PDCLIB_serr
};
static struct _PDCLIB_file_t _PDCLIB_sin  = { 0, _PDCLIB_sin_buffer, BUFSIZ, 0, 0, { 0, 0 }, 0, { 0 }, _IOLBF | _PDCLIB_FREAD,
    NULL, &_PDCLIB_sout
};

struct _PDCLIB_file_t * stdin  = &_PDCLIB_sin;
struct _PDCLIB_file_t * stdout = &_PDCLIB_sout;
struct _PDCLIB_file_t * stderr = &_PDCLIB_serr;

/* FIXME: This approach is a possible attack vector. */
struct _PDCLIB_file_t * _PDCLIB_filelist = &_PDCLIB_sin;

struct state _PDCLIB_lclmem;
struct state _PDCLIB_gmtmem;
struct tm _PDCLIB_tm;
