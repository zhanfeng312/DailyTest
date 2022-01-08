#ifndef __IO_H__
#define __IO_H__

extern void Copy(int fdIn, int fdOut);

extern void SetFileStatusFlag(int fd, int flag);

extern void ClearFileStatusFlag(int fd, int flag);

#endif //__IO_H__