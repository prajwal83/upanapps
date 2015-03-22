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
# include <malloc.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>

int SysProcess_Exec(const char* szFileName, int iNoOfArgs, char *const szArgList[])
{
	__volatile__ int iProcessID ;

	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	__asm__ __volatile__("pushl %0" : : "rm"(szArgList)) ;
	__asm__ __volatile__("pushl %0" : : "rm"(iNoOfArgs)) ;
	__asm__ __volatile__("pushl %0" : : "rm"(szFileName)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_EXEC) ;
	__asm__ __volatile__("movl %%eax, %0" : "=m"(iProcessID) : ) ;
	__asm__ __volatile__("pop %eax") ;

	return iProcessID ;
}

void SysProcess_WaitPID(int iProcessID)
{
	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	__asm__ __volatile__("pushl %0" : : "rm"(iProcessID)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_WAIT_PID) ;
	__asm__ __volatile__("pop %eax") ;
}

int SysProcess_IsChildAlive(int iProcessID)
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

	__asm__ __volatile__("pushl %0" : : "rm"(iProcessID)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_CHILD_ALIVE) ;
	__asm__ __volatile__("movl %%eax, %0" : "=m"(iRetStatus) : ) ;
	__asm__ __volatile__("pop %eax") ;

	return iRetStatus ;
}

void SysProcess_Exit(int iExitStatus)
{
	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	__asm__ __volatile__("pushl %0" : : "rm"(iExitStatus)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_EXIT) ;
	__asm__ __volatile__("pop %eax") ;
}

void SysProcess_Sleep(unsigned milisec)
{
	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	__asm__ __volatile__("pushl %0" : : "rm"(milisec)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_SLEEP) ;
	__asm__ __volatile__("pop %eax") ;
}

int SysProcess_GetPID()
{
	__volatile__ int iProcessID ;

	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	DO_SYS_CALL(SYS_CALL_PROCESS_PID) ;
	__asm__ __volatile__("movl %%eax, %0" : "=m"(iProcessID) : ) ;
	__asm__ __volatile__("pop %eax") ;

	return iProcessID ;
}

char* SysProcess_GetEnv(const char* szVar, char* szVal)
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

	__asm__ __volatile__("pushl %0" : : "rm"(szVar)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_GET_ENV) ;

	__asm__ __volatile__("movl %%eax, %0" : "=m"(iRetStatus) : ) ;
	__asm__ __volatile__("pop %eax") ;
	return (char*)iRetStatus ;
}

int SysProcess_SetEnv(const char* szVar, const char* szVal)
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

	__asm__ __volatile__("pushl %0" : : "rm"(szVal)) ;
	__asm__ __volatile__("pushl %0" : : "rm"(szVar)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_SET_ENV) ;

	__asm__ __volatile__("movl %%eax, %0" : "=m"(iRetStatus) : ) ;
	__asm__ __volatile__("pop %eax") ;
	return iRetStatus ;
}

int SysProcess_GetProcList(PS** pProcList, unsigned* uiListSize)
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

	__asm__ __volatile__("pushl %0" : : "rm"(uiListSize)) ;
	__asm__ __volatile__("pushl %0" : : "rm"(pProcList)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_GET_PS_LIST) ;

	__asm__ __volatile__("movl %%eax, %0" : "=m"(iRetStatus) : ) ;
	__asm__ __volatile__("pop %eax") ;
	return iRetStatus ;
}

void SysProcess_FreeProcListMem(PS* pProcList, unsigned uiListSize)
{
	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	__asm__ __volatile__("pushl %0" : : "rm"(uiListSize)) ;
	__asm__ __volatile__("pushl %0" : : "rm"(pProcList)) ;
	DO_SYS_CALL(SYS_CALL_PROCESS_FREE_PS_LIST) ;
	__asm__ __volatile__("pop %eax") ;
}

void SysProcess_DisableTaskSwitch()
{
	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	DO_SYS_CALL(SYS_CALL_DISABLE_TASK_SWITCH) ;
	__asm__ __volatile__("pop %eax") ;
}

void SysProcess_EnableTaskSwitch()
{
	__asm__ __volatile__("push %eax") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;
	__asm__ __volatile__("pushl $0x20") ;

	DO_SYS_CALL(SYS_CALL_ENABLE_TASK_SWITCH) ;
	__asm__ __volatile__("pop %eax") ;
}


int exec(const char* szFileName, ...)
{
	__volatile__ int iProcessID ;
	__volatile__ int argc ;
	__volatile__ int* argv = NULL ;

	__volatile__ int i ;
	__volatile__ int* ref = (int*)&szFileName + 1 ;
	for(argc = 0; *(ref + argc); argc++) ;

	if(argc)
	{
		argv = (int*)malloc(sizeof(int) * argc) ;
		if(!argv)
			return -1 ;

		for(i = 0; i < argc; i++)
		{
			argv[i] = malloc(strlen((char*)(*(ref + i))) + 1) ;
			strcpy((char*)argv[i], (char*)(*(ref + i))) ;
		}
	}

	iProcessID = SysProcess_Exec(szFileName, argc, argv) ;

	for(i = 0; i < argc; i++)
		free((void*)argv[i]) ;
	free((void*)argv) ;

	return iProcessID ;
}

int execv(const char* szFileName, int iNoOfArgs, char *const szArgList[])
{
	return SysProcess_Exec(szFileName, iNoOfArgs, szArgList) ;
}

int execvp(const char* szFileName, char *const szArgList[])
{
	__volatile__ int argc ;
	__volatile__ const int max_args = 256 ;


	for(argc = 0; szArgList[ argc ] != NULL; argc++)
	{
		if(argc > max_args)
		{
			printf("\n Number of arguments to execvp exceeded max args of %d", max_args) ;
			return -1 ;
		}
	}

	return SysProcess_Exec(szFileName, argc, szArgList) ;
}

int childalive(int pid)
{
	return SysProcess_IsChildAlive(pid) ;
}
