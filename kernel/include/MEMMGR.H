//***********************************************************************/
//    Author                    : Garry
//    Original Date             : Mar,09 2005
//    Module Name               : memmgr.h
//    Module Function           : 
//                                This module countains memory manager pro-type's
//                                definition.
//    Last modified Author      : Garry
//    Last modified Date        : Jun 11 of 2013
//    Last modified Content     :
//                                1. MemoryManager's definition and it's related declaration,
//                                   are deleted.MenoryManager is an old and obsoleted object,
//                                   it's function only worked a short period of time before
//                                   Hello China version 1.0.
//                                   MemoryManager related code can be found in version V1.75 or
//                                   even old versions,in this file.
//                                2.
//    Lines number              :
//***********************************************************************/

#ifndef __MEMMGR_H__
#define __MEMMGR_H__

/* For __CFG_SYS_SMP. */
#include "config.h"

//
//The definition of __PAGE_FRAME object.
//This object is used to manage a page frame.
//
BEGIN_DEFINE_OBJECT(__PAGE_FRAME)
    struct tag__PAGE_FRAME* lpNextFrame;
    struct tag__PAGE_FRAME* lpPrevFrame;
	DWORD dwKernelThreadNum;
	DWORD dwFrameFlag;
END_DEFINE_OBJECT(__PAGE_FRAME)

/* One page frame's size,in current version is 4K. */
#define PAGE_FRAME_SIZE     4096

#define PAGE_FRAME_FLAG_READONLY  0x00000001
#define PAGE_FRAME_FLAG_WRITE     0x00000002
#define PAGE_FRAME_READWRITE      0x00000003
#define PAGE_FRAME_EXECUTABLE     0x00000004

#define PAGE_FRAME_BLOCK_SIZE_4K    1024*4
#define PAGE_FRAME_BLOCK_SIZE_8K    1024*8
#define PAGE_FRAME_BLOCK_SIZE_16K   1024*16
#define PAGE_FRAME_BLOCK_SIZE_32K   1024*32
#define PAGE_FRAME_BLOCK_SIZE_64K   1024*64
#define PAGE_FRAME_BLOCK_SIZE_128K  1024*128
#define PAGE_FRAME_BLOCK_SIZE_256K  1024*256
#define PAGE_FRAME_BLOCK_SIZE_512K  1024*512
#define PAGE_FRAME_BLOCK_SIZE_1024K 1024*1024
#define PAGE_FRAME_BLOCK_SIZE_2048K 1024*2048
#define PAGE_FRAME_BLOCK_SIZE_4096K 1024*4096
#define PAGE_FRAME_BLOCK_SIZE_8192K 1024*8192

#define PAGE_FRAME_BLOCK_NUM  12

/* Aligment at 4k boundary. */
#define DEFAULT_PAGE_ALIGMENT 4096

//
//The definition of Page Frame Block object.
//This object is used to describe one page frame block.
//
BEGIN_DEFINE_OBJECT(__PAGE_FRAME_BLOCK)
    __PAGE_FRAME*         lpNextBlock;
    __PAGE_FRAME*         lpPrevBlock;
	DWORD*                lpdwBitmap;
END_DEFINE_OBJECT(__PAGE_FRAME_BLOCK)

//
//The definition of object Page Frame Manager.
//
BEGIN_DEFINE_OBJECT(__PAGE_FRAME_MANAGER)
    __PAGE_FRAME* lpPageFrameArray;
    __PAGE_FRAME_BLOCK FrameBlockArray[PAGE_FRAME_BLOCK_NUM];
	unsigned long dwTotalFrameNum;
	unsigned long dwFreeFrameNum;
	LPVOID lpStartAddress;
#if defined(__CFG_SYS_SMP)
	__SPIN_LOCK spin_lock;
#endif

	/* Initializer. */
	BOOL (*Initialize)(__COMMON_OBJECT* lpThis);
	LPVOID (*FrameAlloc)(__COMMON_OBJECT* lpThis,
		DWORD dwSize,
		DWORD dwFrameFlag);
	VOID (*FrameFree)(__COMMON_OBJECT* lpThis,
		LPVOID lpStartAddr,
		DWORD dwSize);
END_DEFINE_OBJECT(__PAGE_FRAME_MANAGER)

/* 
 * The maximal RAM length that Page Frame Manager can manage. 
 * Page frame manager allocates memory from kernel pool,to
 * manage each frame.Thus restricts the maximal size that
 * page frame manager can manage,since each page will use
 * about 16 bytes to describe.
 * This restrict will be omited in future that we will use
 * the page pool it self to offer management memory.
 */
#define MEM_MAX_PAGEPOOL_LEN (1024 * 1024 * 1024)

/*************************************************************************
**************************************************************************
**************************************************************************
*************************************************************************/

//
//Declare the global object PageFrameManager.
//
#ifdef __CFG_SYS_VMM
extern __PAGE_FRAME_MANAGER PageFrameManager;
#endif

#endif  //__MEMMGR_H__
