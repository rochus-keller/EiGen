/* make sure we have some posix functions available. Include this file first! */

#if defined(_WIN32) && !defined(__CYGWIN__)
#include <fcntl.h>
#include <io.h>

/* no eXecute on Win32 */
#define X_OK 0
#define W_OK 2
#define R_OK 4

#define O_RDWR          _O_RDWR
#define O_CREAT         _O_CREAT
#define O_EXCL          _O_EXCL
#define O_BINARY        _O_BINARY

/* remap some names, we are not in the POSIX world */
#define access(fname, mode)      _access(fname, mode)
#define fdopen(fd, mode)         _fdopen(fd, mode)
#define isatty(fd)               _isatty(fd)
#define mktemp(tmpl)             _mktemp(tmpl)
#define mkdir(name, mode)        _mkdir(name)
#define open(fname, oflag, mode) _open(fname, oflag, mode)
#define pclose(file)             _pclose(file)
#define popen(cmd, mode)         _popen(cmd, mode)
#define unlink(filename)         _unlink(filename)

#ifndef STDOUT_FILENO
#define STDOUT_FILENO _fileno(stdout)
#endif
#ifndef STDERR_FILENO
#define STDERR_FILENO _fileno(stderr)
#endif

#else
#	ifdef __APPLE__
#		define _DARWIN_C_SOURCE /* Required for mkdtemp(). */
#	endif
#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/stat.h>
#define HAVE_MKDTEMP
#define HAVE_FILENO
#define HAVE_ASCTIME_R
#define HAVE_FSTAT
#endif
