#include <pdclib/_PDCLIB_glue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pdclib/_PDCLIB_tzcode.h"
#include <signal.h>
#include <limits.h>
#include <errno.h>

struct timeval
{
    long tv_sec;		/* Seconds.  */
};

struct tms
{
    clock_t tms_utime;		/* User CPU time.  */
    clock_t tms_stime;		/* System CPU time.  */

    clock_t tms_cutime;		/* User CPU time of dead children.  */
    clock_t tms_cstime;		/* System CPU time of dead children.  */
};

// defined in ECS runtime
extern int sys_close(int fd);
extern int sys_open(const char *pathname, int flags, ... /* mode_t mode */ );
extern int sys_renameat(int olddirfd, const char *oldpath,
                    int newdirfd, const char *newpath);
extern int sys_gettimeofday(struct timeval *restrict tv, void * restrict tz);
extern int sys_unlink(const char *pathname);
extern char *sys_getcwd(char* buf, size_t size);
extern size_t sys_read(int fd, void* buf, size_t count);
extern size_t sys_write(int fd, const void* buf, size_t count);
extern clock_t sys_times(struct tms *buf);
extern long sys_lseek(int fd, long offset, int whence);
extern void sys_exit(int status);

_PDCLIB_LOCAL _PDCLIB_Noreturn void _PDCLIB_Exit( int status ) _PDCLIB_NORETURN
{
    sys_exit( status );
}

#define O_RDONLY	     00
#define O_WRONLY	     01
#define O_RDWR		     02
# define O_CREAT	   0100	/* Not fcntl.  */
# define O_TRUNC	  01000	/* Not fcntl.  */
# define O_APPEND	  02000
# define S_IRUSR	0400       /* Read by owner.  */
# define S_IWUSR	0200      /* Write by owner.  */
# define S_IRGRP	(S_IRUSR >> 3)  /* Read by group.  */
# define S_IWGRP	(S_IWUSR >> 3)  /* Write by group.  */
# define S_IROTH	(S_IRGRP >> 3)  /* Read by others.  */
# define S_IWOTH	(S_IWGRP >> 3)  /* Write by others.  */

_PDCLIB_LOCAL _PDCLIB_fd_t _PDCLIB_open( const char * const filename, unsigned int mode )
{
    int osmode;
    _PDCLIB_fd_t rc;

    switch ( mode & ( _PDCLIB_FREAD | _PDCLIB_FWRITE | _PDCLIB_FAPPEND | _PDCLIB_FRW ) )
    {
        case _PDCLIB_FREAD: /* "r" */
            osmode = O_RDONLY;
            break;

        case _PDCLIB_FWRITE: /* "w" */
            osmode = O_WRONLY | O_CREAT | O_TRUNC;
            break;

        case _PDCLIB_FAPPEND: /* "a" */
            osmode = O_WRONLY | O_APPEND | O_CREAT;
            break;

        case _PDCLIB_FREAD | _PDCLIB_FRW: /* "r+" */
            osmode = O_RDWR;
            break;

        case _PDCLIB_FWRITE | _PDCLIB_FRW: /* "w+" */
            osmode = O_RDWR | O_CREAT | O_TRUNC;
            break;

        case _PDCLIB_FAPPEND | _PDCLIB_FRW: /* "a+" */
            osmode = O_RDWR | O_APPEND | O_CREAT;
            break;

        default: /* Invalid mode */
            return _PDCLIB_NOHANDLE;
    }

    if ( osmode & O_CREAT )
    {
        rc = sys_open( filename, osmode, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH );
    }
    else
    {
        rc = sys_open( filename, osmode );
    }

    if ( rc == _PDCLIB_NOHANDLE )
    {
        /* The 1:1 mapping in _PDCLIB_config.h ensures this works. */
        *_PDCLIB_errno_func() = _PDCLIB_ENOTSUP; // TODO errno;
    }

    return rc;
}

#define _PDCLIB_IO_RETRIES 1

_PDCLIB_LOCAL int _PDCLIB_flushbuffer( struct _PDCLIB_file_t * stream )
{
    /* No need to handle buffers > INT_MAX, as PDCLib doesn't allow them */
    _PDCLIB_size_t written = 0;
    int rc;
    unsigned int retries;

    if ( !( stream->status & _PDCLIB_FBIN ) )
    {
        /* TODO: Text stream conversion here */
    }

    /* Keep trying to write data until everything is written, an error
       occurs, or the configured number of retries is exceeded.
    */
    for ( retries = _PDCLIB_IO_RETRIES; retries > 0; --retries )
    {
        rc = ( int )sys_write( stream->handle, stream->buffer + written, stream->bufidx - written );

        if ( rc < 0 )
        {
            /* The 1:1 mapping done in _PDCLIB_config.h ensures
               this works.
            */
            *_PDCLIB_errno_func() = -1; // TODO errno;
            /* Flag the stream */
            stream->status |= _PDCLIB_ERRORFLAG;
            /* Move unwritten remains to begin of buffer. */
            stream->bufidx -= written;
            memmove( stream->buffer, stream->buffer + written, stream->bufidx );
            return EOF;
        }

        written += ( _PDCLIB_size_t )rc;
        stream->pos.offset += rc;

        if ( written == stream->bufidx )
        {
            /* Buffer written completely. */
            stream->bufidx = 0;
            return 0;
        }
    }

    /* Number of retries exceeded. */
    *_PDCLIB_errno_func() = _PDCLIB_EAGAIN;
    stream->status |= _PDCLIB_ERRORFLAG;
    /* Move unwritten remains to begin of buffer. */
    stream->bufidx -= written;
    memmove( stream->buffer, stream->buffer + written, stream->bufidx );
    return EOF;
}

_PDCLIB_LOCAL int _PDCLIB_fillbuffer( struct _PDCLIB_file_t * stream )
{
    /* No need to handle buffers > INT_MAX, as PDCLib doesn't allow them */
    size_t rc = sys_read( stream->handle, stream->buffer, stream->bufsize );

    if ( rc > 0 )
    {
        /* Reading successful. */
        if ( !( stream->status & _PDCLIB_FBIN ) )
        {
            /* TODO: Text stream conversion here */
        }

        stream->pos.offset += rc;
        stream->bufend = rc;
        stream->bufidx = 0;
        return 0;
    }

    if ( rc < 0 )
    {
        /* The 1:1 mapping done in _PDCLIB_config.h ensures
           this works.
        */
        *_PDCLIB_errno_func() = errno;
        /* Flag the stream */
        stream->status |= _PDCLIB_ERRORFLAG;
        return EOF;
    }

    /* End-of-File */
    stream->status |= _PDCLIB_EOFFLAG;
    return EOF;
}

_PDCLIB_LOCAL _PDCLIB_int_least64_t _PDCLIB_seek( struct _PDCLIB_file_t * stream, _PDCLIB_int_least64_t offset, int whence )
{
    _PDCLIB_int_least64_t rc;

    switch ( whence )
    {
        case SEEK_SET:
        case SEEK_CUR:
        case SEEK_END:
            /* EMPTY - OK */
            break;

        default:
            *_PDCLIB_errno_func() = _PDCLIB_EINVAL;
            return EOF;
            break;
    }

    rc = sys_lseek( stream->handle, offset, whence );

    if ( rc != EOF )
    {
        stream->ungetidx = 0;
        stream->bufidx = 0;
        stream->bufend = 0;
        stream->pos.offset = rc;
        return rc;
    }

    /* The 1:1 mapping in _PDCLIB_config.h ensures that this works. */
    *_PDCLIB_errno_func() = -1; // TODO errno;
    return EOF;
}

_PDCLIB_LOCAL int _PDCLIB_close( _PDCLIB_fd_t fd )
{
    return sys_close( fd );
}

_PDCLIB_LOCAL int _PDCLIB_changemode( struct _PDCLIB_file_t * stream, unsigned int mode )
{
    if ( mode == 0 )
    {
        return INT_MIN;
    }

    /* Attempt mode change without closing the stream */

    if ( stream->filename == NULL )
    {
        /* Standard stream, no filename for reopen */
        return INT_MIN;
    }
    else
    {
        /* Stream with file associated, attempt reopen */
        return 0;
    }
}

_PDCLIB_LOCAL int _PDCLIB_remove( const char * pathname )
{
    return sys_unlink( pathname );
}

# define AT_FDCWD		-100

_PDCLIB_LOCAL int _PDCLIB_rename( const char * oldpath, const char * newpath )
{
    /* Whether existing newpath is overwritten is implementation-
       defined. This system call *does* overwrite.
    */
    if ( sys_renameat( AT_FDCWD, oldpath, AT_FDCWD, newpath ) != 0 )
    {
        /* The 1:1 mapping in _PDCLIB_config.h ensures this works. */
        *_PDCLIB_errno_func() = errno;
        return -1;
    }
    else
    {
        return 0;
    }
}

#define PATH_MAX 1024

_PDCLIB_LOCAL char * _PDCLIB_realpath( const char * path )
{
    // this is adopted from uClibc-ng 1.0.49
    char copy_path[PATH_MAX];
    char *max_path, *new_path, *allocated_path, *got_path;
    size_t path_len;

    if (path == NULL) {
        *_PDCLIB_errno_func() = EINVAL;
        return NULL;
    }
    if (*path == '\0') {
        *_PDCLIB_errno_func() = ENOENT;
        return NULL;
    }
    /* Make a copy of the source path since we may need to modify it. */
    path_len = strlen(path);
    if (path_len >= PATH_MAX - 2) {
        *_PDCLIB_errno_func() = ENAMETOOLONG;
        return NULL;
    }
    /* Copy so that path is at the end of copy_path[] */
    strcpy(copy_path + (PATH_MAX-1) - path_len, path);
    path = copy_path + (PATH_MAX-1) - path_len;
    allocated_path = got_path = malloc(PATH_MAX);
    max_path = got_path + PATH_MAX - 2; /* points to last non-NUL char */
    new_path = got_path;
    if (*path != '/') {
        /* If it's a relative pathname use getcwd for starters. */
        if (!sys_getcwd(new_path, PATH_MAX - 1))
            goto err;
        new_path += strlen(new_path);
        if (new_path[-1] != '/')
            *new_path++ = '/';
    } else {
        *new_path++ = '/';
        path++;
    }
    /* Expand each slash-separated pathname component. */
    while (*path != '\0') {
        /* Ignore stray "/". */
        if (*path == '/') {
            path++;
            continue;
        }
        if (*path == '.') {
            /* Ignore ".". */
            if (path[1] == '\0' || path[1] == '/') {
                path++;
                continue;
            }
            if (path[1] == '.') {
                if (path[2] == '\0' || path[2] == '/') {
                    path += 2;
                    /* Ignore ".." at root. */
                    if (new_path == got_path + 1)
                        continue;
                    /* Handle ".." by backing up. */
                    while ((--new_path)[-1] != '/');
                    continue;
                }
            }
        }
        /* Safely copy the next pathname component. */
        while (*path != '\0' && *path != '/') {
            if (new_path > max_path) {
                *_PDCLIB_errno_func() = ENAMETOOLONG;
 err:
                free(allocated_path);
                return NULL;
            }
            *new_path++ = *path++;
        }
        *new_path++ = '/';
    }
    /* Delete trailing slash but don't whomp a lone slash. */
    if (new_path != got_path + 1 && new_path[-1] == '/')
        new_path--;
    /* Make sure it's null terminated. */
    *new_path = '\0';
    return got_path;
}

extern struct _PDCLIB_file_t * _PDCLIB_filelist;

FILE * tmpfile( void )
{
    FILE * rc;

    char * filename = ( char * )malloc( L_tmpnam );
    _PDCLIB_fd_t fd;

    for ( ;; )
    {
        /* Get a filename candidate. What constitutes a valid filename and
           where temporary files are usually located is platform-dependent,
           which is one reason why this function is located in the platform
           overlay. The other reason is that a *good* implementation should
           use high-quality randomness instead of a pseudo-random sequence to
           generate the filename candidate, which is *also* platform-dependent.
        */
        unsigned int random = rand();
        sprintf( filename, "/tmp/%u.tmp", random );
        /* Check if file of this name exists. Note that fopen() is a very weak
           check, which does not take e.g. access permissions into account
           (file might exist but not readable). Replace with something more
           appropriate.
        */
        fd = sys_open( filename, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR );

        if ( fd != -1 )
        {
            /* Found a file that does not exist yet */
            break;
        }

        sys_close( fd );
    }

    /* See fopen(), which does much of the same. */

    if ( ( rc = _PDCLIB_init_file_t( NULL ) ) == NULL )
    {
        /* initializing FILE structure failed */
        sys_close( fd );
        return NULL;
    }

    rc->status |= _PDCLIB_filemode( "wb+" ) | _IOLBF | _PDCLIB_DELONCLOSE;
    rc->handle = fd;

    /* Filename (for potential freopen()) */
    rc->filename = filename;

    /* Adding to list of open files */
    _PDCLIB_LOCK( _PDCLIB_filelist_mtx );
    rc->next = _PDCLIB_filelist;
    _PDCLIB_filelist = rc;
    _PDCLIB_UNLOCK( _PDCLIB_filelist_mtx );
    return rc;
}

void ( *_PDCLIB_sigabrt )( int ) = SIG_DFL;
void ( *_PDCLIB_sigfpe )( int )  = SIG_DFL;
void ( *_PDCLIB_sigill )( int )  = SIG_DFL;
void ( *_PDCLIB_sigint )( int )  = SIG_DFL;
void ( *_PDCLIB_sigsegv )( int ) = SIG_DFL;
void ( *_PDCLIB_sigterm )( int ) = SIG_DFL;

void ( *signal( int sig, void ( *func )( int ) ) )( int )
{
    void ( *oldhandler )( int );

    if ( sig <= 0 || func == SIG_ERR )
    {
        return SIG_ERR;
    }

    switch ( sig )
    {
        case SIGABRT:
            oldhandler = _PDCLIB_sigabrt;
            _PDCLIB_sigabrt = func;
            break;

        case SIGFPE:
            oldhandler = _PDCLIB_sigfpe;
            _PDCLIB_sigfpe = func;
            break;

        case SIGILL:
            oldhandler = _PDCLIB_sigill;
            _PDCLIB_sigill = func;
            break;

        case SIGINT:
            oldhandler = _PDCLIB_sigint;
            _PDCLIB_sigint = func;
            break;

        case SIGSEGV:
            oldhandler = _PDCLIB_sigsegv;
            _PDCLIB_sigsegv = func;
            break;

        case SIGTERM:
            oldhandler = _PDCLIB_sigterm;
            _PDCLIB_sigterm = func;
            break;

        default:
            /* The standard calls for an unspecified "positive value".
               Copying Linux' behaviour of setting EINVAL.
            */
            *_PDCLIB_errno_func() = _PDCLIB_EINVAL;
            return SIG_ERR;
    }

    return oldhandler;
}

int system( const char * string )
{
    return -1; // TODO
}

double strtod( const char * _PDCLIB_restrict nptr, char ** _PDCLIB_restrict endptr )
{
    return 0.0; // TODO
}

//extern char ** environ; // TODO

char * getenv( const char * name )
{
    size_t len = strlen( name );
    size_t index = 0;

#if 0 // TODO
    while ( environ[ index ] != NULL )
    {
        if ( strncmp( environ[ index ], name, len ) == 0 )
        {
            return environ[ index ] + len + 1;
        }

        index++;
    }
#endif

    return NULL;
}

clock_t clock( void )
{
    struct tms buf;

    if ( sys_times( &buf ) != ( clock_t )-1 )
    {
        return buf.tms_utime + buf.tms_stime;
    }

    return -1;
}

time_t time( time_t * timer )
{
    struct timeval tv;

    if ( sys_gettimeofday( &tv, NULL ) == 0 )
    {
        if ( timer != NULL )
        {
            *timer = tv.tv_sec;
        }

        return tv.tv_sec;
    }

    return -1;
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
