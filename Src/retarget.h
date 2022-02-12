#ifndef _RETARGET_H__
#define _RETARGET_H__

#include "stm32f10x.h"
#include <sys/stat.h>

void RetargetInit(USART_TypeDef *huart);
int _isatty(int fd);
int _write(int fd, char* ptr, int len);
int _close(int fd);
int _lseek(int fd, int ptr, int dir);
int _read(int fd, char* ptr, int len);
int _fstat(int fd, struct stat* st);

#endif //#ifndef _RETARGET_H__
