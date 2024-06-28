#define __wur

#include <syscall.h>
#include <unistd.h>
#include <sys/times.h>

#ifndef __ecs_chibicc__

void sys_exit(int status)
{
    syscall(60,status);
}

clock_t sys_times(struct tms *buf)
{
    return syscall(43,buf);
}

int sys_close(int fd)
{
    return syscall(6,fd);
}

int sys_open(const char *pathname, int flags, ... /* mode_t mode */ )
{
    return syscall(5,pathname,flags,0);
}

int sys_renameat(int olddirfd, const char *oldpath,
                    int newdirfd, const char *newpath)
{
    return syscall(264,olddirfd,oldpath,newdirfd,newpath);
}

int sys_gettimeofday(struct timeval *restrict tv, void * restrict tz)
{
    return syscall(96,tv,tz);
}

int sys_unlink(const char *pathname)
{
    return syscall(10,pathname);
}

char *sys_getcwd(char* buf, size_t size)
{
    return syscall(79,buf, size);
}

size_t sys_read(int fd, void* buf, size_t count)
{
    return syscall(3,fd, buf,count);
}

size_t sys_write(int fd, const void* buf, size_t count)
{
    return syscall(4,fd, buf,count);
}

long sys_lseek(int fd, long offset, int whence)
{
    return syscall(19,fd, offset,whence);
}

#endif
