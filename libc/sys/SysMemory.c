/*
 *  Mother Operating System - An x86 based Operating System
 *  Copyright (C) 2011 'Prajwala Prabhakar' 'srinivasa_prajwal@yahoo.co.in'
 *                                                                          
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *                                                                          
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *                                                                          
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/
 */
# include <SysCall.h>

int SysMemory_Alloc(void** addr, unsigned uiSizeInBytes)
{
	__volatile__ int iRetStatus ;

	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	__asm__ __volatile__("pushl %0" : : "rm"(uiSizeInBytes)) ;
	__asm__ __volatile__("pushl %0" : : "rm"(addr)) ;
	DO_SYS_CALL(SYS_CALL_ALLOC) ;

	__asm__ __volatile__("movl %%eax, %0" : "=m"(iRetStatus) : ) ;
	__asm__ __volatile__("pop %eax") ;
	return iRetStatus;
}

int SysMemory_Free(void* uiAddress)
{
	__volatile__ int iRetStatus ;

	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	__asm__ __volatile__("pushl %0" : : "rm"((unsigned)uiAddress)) ;
	DO_SYS_CALL(SYS_CALL_FREE) ;

	__asm__ __volatile__("movl %%eax, %0" : "=m"(iRetStatus) : ) ;
	__asm__ __volatile__("pop %eax") ;
	return iRetStatus ;
}

int SysMemory_GetAllocSize(void* uiAddress, int* size)
{
	__volatile__ int iRetStatus ;

	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	__asm__ __volatile__("pushl %0" : : "rm"((unsigned)size)) ;
	__asm__ __volatile__("pushl %0" : : "rm"((unsigned)uiAddress)) ;
	DO_SYS_CALL(SYS_CALL_GET_ALLOC_SIZE) ;

	__asm__ __volatile__("movl %%eax, %0" : "=m"(iRetStatus) : ) ;
	__asm__ __volatile__("pop %eax") ;
	return iRetStatus ;
}
