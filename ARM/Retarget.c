/*----------------------------------------------------------------------------
 * Name:    Retarget.c
 * Purpose: 'Retarget' layer for target-dependent low level functions
 * Note(s):
 *----------------------------------------------------------------------------
 * This file is part of the uVision/ARM development tools.
 * This software may only be used under the terms of a valid, current,
 * end user licence from KEIL for a compatible version of KEIL software
 * development tools. Nothing else gives you the right to use this software.
 *
 * This software is supplied "AS IS" without warranties of any kind.
 *
 * Copyright (c) 2011-2013 Keil - An ARM Company. All rights reserved.
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <rt_sys.h>
#include <rt_misc.h>
#include "Serial.h"

#pragma import(__use_no_semihosting)


// ARM Semihosting Commands
#define SYS_OPEN   (0x1)
#define SYS_CLOSE  (0x2)
#define SYS_WRITE  (0x5)
#define SYS_READ   (0x6)
#define SYS_ISTTY  (0x9)
#define SYS_SEEK   (0xa)
#define SYS_ENSURE (0xb)
#define SYS_FLEN   (0xc)
#define SYS_REMOVE (0xe)
#define SYS_RENAME (0xf)
#define SYS_EXIT   (0x18)

typedef  unsigned int uint32_t;
typedef short int int16_t;

#define MIN(a,b)  (a >= b ? b : a);

struct __FILE { char *pData; int size;};

struct __FILE indata;
struct __FILE outdata;



_ARMABI FILE *fopen(const char * filename,
                           const char * mode)
{
	FILE *pFile;
	
	if (strcmp(mode, "rb") == 0)
	{
		pFile = &indata;
		pFile->pData = (char *)0x60000000;
		pFile->size = 360960;
	}else if (strcmp(mode, "wb") == 0)
	{
		pFile = &outdata;
		pFile->pData = (char *)0x70000000;
		pFile->size = 360960;		
	}else
	{
		pFile = NULL;
	}
		
	return pFile;
}
_ARMABI size_t fread(void *buff, size_t elem_size, size_t num_elems, FILE *pFile)
{
	size_t n_elems, n_bytes;
	n_elems = MIN(pFile->size/elem_size, num_elems);
  n_bytes = 	n_elems * elem_size;
	memcpy(buff, pFile->pData, n_bytes );	
	pFile->pData += n_bytes;
	pFile->size -= n_bytes;
	return n_elems;
}

_ARMABI size_t fwrite(const void *buff, size_t elem_size, size_t num_elems, FILE *pFile)
{
	size_t n_elems, n_bytes;
	n_elems = MIN(pFile->size/elem_size, num_elems);
  n_bytes = 	n_elems * elem_size;
	memcpy(pFile->pData, buff, n_bytes );	
	pFile->pData += n_bytes;
	pFile->size -= n_bytes;
	return n_elems;
}

FILEHANDLE _sys_open(const char* name, int openmode) {
    uint32_t args[3];
    args[0] = (uint32_t)name;
    args[1] = (uint32_t)openmode;
    args[2] = (uint32_t)strlen(name);
    return __semihost(SYS_OPEN, args);
}
 
int _sys_close(FILEHANDLE fh) {
    return __semihost(SYS_CLOSE, &fh);
}
 
int _sys_write(FILEHANDLE fh, const unsigned char* buffer, unsigned int length, int mode) {
    uint32_t args[3];   
	
  	if (length == 0) return 0;
    args[0] = (uint32_t)fh;
    args[1] = (uint32_t)buffer;
    args[2] = (uint32_t)length;
    return __semihost(SYS_WRITE, args);
}
 
int _sys_read(FILEHANDLE fh, unsigned char* buffer, unsigned int length, int mode) {
    uint32_t args[3];
    args[0] = (uint32_t)fh;
    args[1] = (uint32_t)buffer;
    args[2] = (uint32_t)length;
    return __semihost(SYS_READ, args);
}
 
int semihost_istty(FILEHANDLE fh) {
    return __semihost(SYS_ISTTY, &fh);
}
 
int semihost_seek(FILEHANDLE fh, long position) {
    uint32_t args[2];
    args[0] = (uint32_t)fh;
    args[1] = (uint32_t)position;
    return __semihost(SYS_SEEK, args);
}
 
int semihost_ensure(FILEHANDLE fh) {
    return __semihost(SYS_ENSURE, &fh);
}
 
long semihost_flen(FILEHANDLE fh) {
    return __semihost(SYS_FLEN, &fh);
}
 
int semihost_remove(const char *name) {
    uint32_t args[2];
    args[0] = (uint32_t)name;
    args[1] = (uint32_t)strlen(name);
    return __semihost(SYS_REMOVE, args);
}
 
int semihost_rename(const char *old_name, const char *new_name) {
    uint32_t args[4];
    args[0] = (uint32_t)old_name;
    args[1] = (uint32_t)strlen(old_name);
    args[0] = (uint32_t)new_name;
    args[1] = (uint32_t)strlen(new_name);
    return __semihost(SYS_RENAME, args);
}


int fputc(int c, FILE *f) {
  return (SER_PutChar(c));
}


int fgetc(FILE *f) {
  return (SER_GetChar());
}


int ferror(FILE *f) {
  /* Your implementation of ferror */
  return EOF;
}


void _ttywrch(int c) {
  SER_PutChar(c);
}

void _sys_exit(int return_code) {
label:  goto label;  /* endless loop */
}

void exit(int return_code)
{
label:  goto label;  /* endless loop */
}

void __aeabi_assert(const char *expr, const char *file, int line)
{
//	printf("Assert at file %s, expr %s, line %d", file, expr, line);
	exit(1);
}
