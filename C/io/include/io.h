#ifndef __IO_H__
#define __IO_H__

extern void copy(int fdin, int fdout);

extern void set_fl(int fd, int flag);

extern void clr_fl(int fd, int flag);

#endif //__IO_H__