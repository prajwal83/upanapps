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
# include <MshCommands.h>
# include <CommandLineParser.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <mosstd.h>
# include <fs.h>
# include <malloc.h>
# include <drive.h>
# include <error.h>
# include <dtime.h>
# include <cdisplay.h>

/**** Command Fucntion Declarations  *****/

void MshCommands_Echo(const MshCommand* pCommand) ;
void MshCommands_ClearScreen(const MshCommand* pCommand) ;
void MshCommands_Exit(const MshCommand* pCommand) ;
void MshCommands_CreateDirectory(const MshCommand* pCommand) ;
void MshCommands_Delete(const MshCommand* pCommand) ;
void MshCommands_GetDirContent(const MshCommand* pCommand) ;
void MshCommands_ChangeDirectory(const MshCommand* pCommand) ;
void MshCommands_ChangeDrive(const MshCommand* pCommand) ;
void MshCommands_ShowDrives(const MshCommand* pCommand) ;
void MshCommands_MountDrive(const MshCommand* pCommand) ;
void MshCommands_UnMountDrive(const MshCommand* pCommand) ;
void MshCommands_FormatDrive(const MshCommand* pCommand) ;
void MshCommands_ShowCurrentDrive(const MshCommand* pCommand) ;
void MshCommands_PresentWorkingDir(const MshCommand* pCommand) ;
void MshCommands_CopyFile(const MshCommand* pCommand) ;
void MshCommands_ShowFileContent(const MshCommand* pCommand) ;
void MshCommands_GetDateTime(const MshCommand* pCommand) ;
void MshCommands_Reboot(const MshCommand* pCommand) ;
void MshCommands_Help(const MshCommand* pCommand) ;
void MshCommands_GetProcessDetails(const MshCommand* pCommand) ;
void MshCommands_Export(const MshCommand* pCommand) ;
void MshCommands_Test(const MshCommand* pCommand) ;

/*****************************************/

int MshCommands_NoOfInterCommands ;

static const MshCommand MshCommands_CommandList[] = {
	{	
		"echo",
		&MshCommands_Echo, 
		1, 
		1,
		"[\"]<string to be displayed>[\"] - Use \" if msg conatains whitespace"
	},
		
	{
		"clear",
		&MshCommands_ClearScreen,
		0,
		0,
		"\0"
	},
	
	{
		"exit",
		&MshCommands_Exit,
		0,
		0,
		"\0"
	},
	
	{
		"mkdir",
		&MshCommands_CreateDirectory,
		1,
		10,
		"<new_dir_name> [<new_dir_name> ...]"
	}
	,
	{
		"rm",
		&MshCommands_Delete,
		1,
		10,
		"<file_name> [<file_name> ...]"
	},
	
	{
		"ls",
		&MshCommands_GetDirContent,
		0,
		20,
		"<file_name> [<file_name> ...]"
	},
	
	{
		"cd",
		&MshCommands_ChangeDirectory,
		1,
		1,
		"<dir_name>"
	},

	{
		"pwd",
		&MshCommands_PresentWorkingDir,
		0,
		0,
		"\0"
	},

	{
		"cp",
		&MshCommands_CopyFile,
		2,
		2,
		"<src_file_name> <dest_file_name>"
	},

	{
		"see",
		&MshCommands_ShowFileContent,
		1,
		1,
		"<text_file_name>"
	},

	{
		"date",
		&MshCommands_GetDateTime,
		0,
		0,
		"\0"
	},
	
	{
		"chd",
		&MshCommands_ChangeDrive,
		1,
		1,
		"<Drive name> - Use the one listed by \"chd\" command"
	},
	
	{
		"shd",
		&MshCommands_ShowDrives,
		0,
		0,
		"\0"
	},

	{
		"mount",
		&MshCommands_MountDrive,
		1,
		1,
		"<Drive name> - Use the one listed by \"shd\" command"
	},
	{
		"umount",
		&MshCommands_UnMountDrive,
		1,
		1,
		"<Drive name> - Use the one listed by \"shd\" command"
	},

	{
		"format",
		&MshCommands_FormatDrive,
		1,
		1,
		"<Drive name> - Use the one listed by \"shd\" command"
	},

	{
		"cud",
		&MshCommands_ShowCurrentDrive,
		0,
		0,
		"\0"
	},

	{
		"reboot",
		&MshCommands_Reboot,
		0,
		0,
		"\0"
	},

	{
		"help",
		&MshCommands_Help,
		0,
		0,
		"\0"
	},

	{
		"ps",
		&MshCommands_GetProcessDetails,
		0,
		0,
		"\0"
	},

	{
		"export",
		&MshCommands_Export,
		1,
		1,
		"<var>=<val>"
	},

	{
		"test",
		&MshCommands_Test,
		0,
		0,
		"\0"
	},

	{
		"\0",
		NULL,
		0,
		0,
		"\0"
	}
} ;

/************************** Static Functions *******************************/

static void MshCommands_DisplayDetailDirContent(const FS_Node* pDirList, int iListSize)
{
	char rwx[12] ;
	int i ;

	// Attr, User, Size, Create Time, Modify Time, Access Time, Name
	for(i = 0; i < iListSize; i++)
	{
		format_dir_attr(pDirList[i]._attribute, rwx) ;
		printf("\n%-15s%-15d%s", rwx, pDirList[i]._size, pDirList[i]._name) ;
	}
}

static void MshCommands_DisplayDirectoryContent(const FS_Node* pDirList, int iListSize)
{
	if(CommandLineParser_IsOptPresent("-l"))
	{
		MshCommands_DisplayDetailDirContent(pDirList, iListSize) ;
	}
	else
	{
		int i ;
		for(i = 0; i < iListSize; i++)
		{
			if(!(i % 3) && i != 0)
				putc('\n', stdout) ;	
			printf("%-20s", pDirList[i]._name) ;
		}
	}
}

static void MshCommands_DisplayCommandUsage(const MshCommand* pCommand)
{
	printf("Usage: %s %s\n", pCommand->szCommand, pCommand->szUsage) ;
}

static bool MshCommands_GenericValidation(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfCommandLineEntries() - 1 >= pCommand->iMinParCount
		&& CommandLineParser_GetNoOfCommandLineEntries() - 1 <= pCommand->iMaxParCount)
	{
		return true ;
	}

	MshCommands_DisplayCommandUsage(pCommand) ;
	return false ;
}

/*********************************************************************************/

void MshCommands_Init()
{
	for(MshCommands_NoOfInterCommands = 0; 
		MshCommands_CommandList[MshCommands_NoOfInterCommands].szCommand[0] != '\0';
		MshCommands_NoOfInterCommands++) ;
}

bool MshCommands_ExecuteInternalCommand()
{
	int i ;
	for(i = 0; i < MshCommands_NoOfInterCommands; i++)
	{
		if(strcmp(CommandLineParser_GetCommand(), MshCommands_CommandList[i].szCommand) == 0)
		{
			if(!MshCommands_GenericValidation(&MshCommands_CommandList[i]))
				return true ;
				
			MshCommands_CommandList[i].cmdFunc(&MshCommands_CommandList[i]) ;

			return true ;
		}
	}

	return false ;
}

bool MshCommands_ExecuteProcess()
{
	int pid ;
	pid = execv(CommandLineParser_GetCommand(), 
				CommandLineParser_GetNoOfCommandLineEntries(),
				CommandLineParser_GetArgV()) ;

	/* --> way to work using execvp */
	/*
	char** argv = CommandLineParser_GetArgV();
	argv[CommandLineParser_GetNoOfCommandLineEntries()] = (char*)NULL ;
	pid = execvp(CommandLineParser_GetCommand(), argv );
	*/
	
	if(pid < 0)
	{
		return false ;
	}
	else
	{
		waitpid(pid) ;
	}

	return true ;
}

/****************************** Command Implementation *********************************/

void MshCommands_Echo(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters())
		puts(CommandLineParser_GetParameterAt(0)) ;
}

void MshCommands_ClearScreen(const MshCommand* pCommand)
{
	clrscr() ;
}

void MshCommands_Exit(const MshCommand* pCommand)
{
	exit(0) ;
}

void MshCommands_CreateDirectory(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters())
	{
		int i ;
		for(i = 0; i < CommandLineParser_GetNoOfParameters(); i++)
		{
			if(mkdir(CommandLineParser_GetParameterAt(i), ATTR_DIR_DEFAULT | ATTR_TYPE_DIRECTORY) < 0)
			{
				printerr("%s : Directory Creation Failed", CommandLineParser_GetParameterAt(i)) ;
			}
		}
		return ;
	}
}

void MshCommands_Delete(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters())
	{
		int i ;
		for(i = 0; i < CommandLineParser_GetNoOfParameters(); i++)
		{
			if(unlink(CommandLineParser_GetParameterAt(i)) < 0)
			{
				printerr("%s : Directory Deletion Failed", CommandLineParser_GetParameterAt(i)) ;
			}
		}
		return ;
	}
}

void MshCommands_GetDirContent(const MshCommand* pCommand)
{
	FS_Node* pDirList ;
	int iListSize ;

	if(CommandLineParser_GetNoOfParameters())
	{
		int i ;
		bool bDisplayParentDirName = CommandLineParser_GetNoOfParameters() > 1 ;

		for(i = 0; i < CommandLineParser_GetNoOfParameters(); i++)
		{
			if(get_dir_content(CommandLineParser_GetParameterAt(i), &pDirList, &iListSize) < 0)
			{
				printerr("%s : No Such Directory/File", CommandLineParser_GetParameterAt(i)) ;
			}
			else
			{
				if(bDisplayParentDirName)
					printf("\n\n %s :", CommandLineParser_GetParameterAt(i)) ;

				MshCommands_DisplayDirectoryContent(pDirList, iListSize) ;
	
				free(pDirList) ;
			}
		}
	}
	else
	{
		if(get_dir_content("", &pDirList, &iListSize) < 0)
		{
			puts("\nFailed to Get Directory Content") ;
		}
		else
		{
			MshCommands_DisplayDirectoryContent(pDirList, iListSize) ;
			free(pDirList) ;
		}
	}
}

void MshCommands_ChangeDirectory(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters())
	{
		if(chdir(CommandLineParser_GetParameterAt(0)) < 0)
			printerr("%s : No Such Directory", CommandLineParser_GetParameterAt(1)) ;
	}
}

void MshCommands_ChangeDrive(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters())
	{
		if(chdrive(CommandLineParser_GetParameterAt(0)) < 0)
			printerr("Failed to switch drive to %s", CommandLineParser_GetParameterAt(1)) ;
	}
}

void MshCommands_ShowDrives(const MshCommand* pCommand)
{
	DriveStat* pDriveList ;
	int iListSize ;

	if(get_drive_list(&pDriveList, &iListSize) < 0)
	{
		printerr("Failed to get drive list") ;
		return ;
	}

	int i ;
	
	printf("%-4s | %-10s| %-10s| %-10s| %-10s| %-10s| %-8s\n", 
	"SlNo", "DriveName", "Size(Phy)", "Total(fs)", "Used(fs)", "Free(fs)", "Mounted") ;
	for(i = 0; i < 4*1 + 10*6 + 3*5; i++)
		putc('-', stdout) ;

	for(i = 0; i < iListSize; i++)
	{
		//TODO: use float after coprocessor support
		//float fSize = (pDriveList[i].uiSizeInSectors * 512) / (1024 * 1024) ;
		//printf("\n[Drive %d] %s (%f MB)", i + 1, pDriveList[i].driveName, fSize) ;

		printf("\n%-4d   %-10s  %-10d  %-10d  %-10d  %-10d  %-8s", i + 1, 
		pDriveList[i].driveName, (pDriveList[i].uiSizeInSectors * 512), 
		pDriveList[i].ulTotalSize, pDriveList[i].ulUsedSize,
		(pDriveList[i].ulTotalSize - pDriveList[i].ulUsedSize),
		(pDriveList[i].bMounted) ? "Yes" : "No") ;
	}

	free(pDriveList) ;
}

void MshCommands_PresentWorkingDir(const MshCommand* pCommand)
{
	char* szPWD ;
	getpwd(&szPWD) ;
	printf("%s", szPWD) ;
	free(szPWD) ;
}

void MshCommands_CopyFile(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters() < 1)
		return ;

	const char* szSrcFileName = CommandLineParser_GetParameterAt(0) ;
	const char* szDestFileName = CommandLineParser_GetParameterAt(1) ;

	if(strcmp(szSrcFileName, szDestFileName) == 0)
	{
		printerr("Src and Dest files must be different") ;
		return ;
	}

	int fdSrc ;
	if((fdSrc = open(szSrcFileName, O_RDONLY)) < 0)
	{
		printerr("Failed to open file %s", szSrcFileName) ;
		return ;
	}

	if(create(szDestFileName, ATTR_FILE_DEFAULT) < 0)
	{
		printerr("Failed to create file %s", szDestFileName) ;
		close(fdSrc) ;
		return ;
	}

	int fdDest ;
	if((fdDest = open(szDestFileName, O_RDWR)) < 0)
	{
		printerr("Failed to open file %s", szDestFileName) ;
		close(fdSrc) ;
		return ;
	}

	printf("\n Progress = ") ;
	int cr = get_cursor() ;

	int progress = 0 ;

	struct stat fStat;
	if(fstat(fdSrc, &fStat) < 0)
	{
		printf("\n Failed to get stat on file: %s", szSrcFileName) ;
		close(fdSrc) ;
		close(fdDest) ;
		return ;
	}

	unsigned fsize = fStat.st_size ;
	if(fsize == 0) fsize = 1 ;

	int n = 0 ;
	const int BUF_SIZE = 8192 ;
	char *buffer = (char*)malloc( BUF_SIZE ) ;

	if(!buffer)
	{
		printerr(" buffer malloc failed") ;
		close(fdSrc) ;
		close(fdDest) ;
		return;
	}
	
	while(true)
	{
		if((n = read(fdSrc, buffer, BUF_SIZE)) < 0)
		{
			printerr(" error reading file %s", szSrcFileName) ;
			break ;
		}

		if(n < BUF_SIZE)
		{
			if(n == 0)
				break ;

			if(write(fdDest, buffer, n) < 0)
			{
				printerr(" error writing file %s", szDestFileName) ;
				break ;
			}

			showprogress(cr, "", 100) ;
			break ;
		}
		
		if(write(fdDest, buffer, n) < 0)
		{
			printerr(" error writing file %s", szDestFileName) ;
			break ;
		}

		progress++ ;
		showprogress(cr, "", (progress * BUF_SIZE * 100) / fsize) ;
	}

	free(buffer) ;
	close(fdSrc) ;
	close(fdDest) ;
}

void MshCommands_ShowFileContent(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters() < 1)
		return ;

	const char* szFileName = CommandLineParser_GetParameterAt(0) ;

	int fd ;
	if((fd = open(szFileName, O_RDONLY)) < 0)
	{
		printerr("Failed to open file %s", szFileName) ;
		return ;
	}

	int n = 0 ;
	char buffer[513] ;

	while(true)
	{
		if((n = read(fd, buffer, 512)) < 0)
		{
			printerr(" error reading file %s", szFileName) ;
			break ;
		}

		if(n == 0)
			break ;

		buffer[n] = '\0' ;
		puts(buffer) ;

		if(n < 512)
			break ;
	}

	close(fd) ;
}

void MshCommands_GetDateTime(const MshCommand* pCommand)
{
	RTCTime rtcTime ;
	dtime(&rtcTime) ;

	printf("%d/%d/%d %d:%d:%d", rtcTime.bDayOfMonth, rtcTime.bMonth,
        rtcTime.bCentury * 100 + rtcTime.bYear, rtcTime.bHour, rtcTime.bMinute,
        rtcTime.bSecond) ;
}

void MshCommands_Reboot(const MshCommand* pCommand)
{
	reboot() ;
}

void MshCommands_MountDrive(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters() < 1)
		return ;

	const char* szDriveName = CommandLineParser_GetParameterAt(0) ;

	if(mount(szDriveName) < 0)
		printerr("Failed to mount drive %s", szDriveName) ;
}

void MshCommands_UnMountDrive(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters() < 1)
		return ;

	const char* szDriveName = CommandLineParser_GetParameterAt(0) ;

	if(umount(szDriveName) < 0)
		printerr("Failed to unmount drive %s", szDriveName) ;
}

void MshCommands_FormatDrive(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters() < 1)
		return ;

	const char* szDriveName = CommandLineParser_GetParameterAt(0) ;

	if(format(szDriveName) < 0)
		printerr("Failed to format drive %s", szDriveName) ;
}

void MshCommands_ShowCurrentDrive(const MshCommand* pCommand)
{
	DriveStat driveStat;
	
	if(getcurdrive(&driveStat) < 0)
		printerr("Failed to get current drive") ;

	printf("%s (%d B) %s", driveStat.driveName, driveStat.uiSizeInSectors * 512,
		(driveStat.bMounted) ? "-- mounted" : "not mounted") ;
}

void MshCommands_Help(const MshCommand* pCommand)
{
	int i ;
	
	for(i = 0; i < MshCommands_NoOfInterCommands; i++)
	{
		if(!(i % 3) && i != 0)
			putc('\n', stdout) ;
		printf("%-20s", MshCommands_CommandList[i].szCommand) ;
	}
}

void MshCommands_GetProcessDetails(const MshCommand* pCommand)
{
	PS* pPS ;
	unsigned uiSize ;
	
	if(getpslist(&pPS, &uiSize) < 0)
	{
		printf("\n Error\n", ' ') ;
		return ;
	}
	
	printf("\n %-7s%-7s%-7s%-18s%-7s%-15s", "Pid", "PPid", "PGid", "Status", "Uid", "Proc Name") ;
	printf("\n ------------------------------------------------------------\n") ;
	unsigned i ;
	for(i = 0; i < uiSize; i++)
	{
		printf("\n %-7d%-7d%-7d%-18s%-7d%-15s", pPS[i].pid, pPS[i].iParentProcessID, pPS[i].iProcessGroupID, getProcStatusDesc(pPS[i].status), 
					pPS[i].iUserID,	pPS[i].pname) ;
	}
	putc('\n', stdout) ;

	freepslist(pPS, uiSize) ;
}

void MshCommands_Export(const MshCommand* pCommand)
{
	if(CommandLineParser_GetNoOfParameters() < 1)
		return ;

	char* szExp = CommandLineParser_GetParameterAt(0) ;
	char* var = szExp ;
	char* val = strchr(szExp, '=') ;

	if(val == NULL)
	{
		MshCommands_DisplayCommandUsage(pCommand) ;
		return ;
	}
	
	val[0] = '\0' ;
	val = val + 1 ;
	
	if(setenv(var, val) < 0)
	{
		printf("\n Failed to set env variable\n") ;
		return ;
	}
}

void MshCommands_Test(const MshCommand* pCommand)
{
	putenv("PATH=/usr/lib:/lib") ;	
}
	/*
	printf("\n Test ScanF \n") ;

	int n = 100 ;
	float f = 2.0 ;
	char name[20] ;
	printf("\n Enter Name, Age, Float: ") ;
	scanf("%s %d %f", name, &n, &f) ;

	printf("\n Name: %s, Age: %d, Float: %f", name, n, f) ;
}
*/
	/*
	float f1 = 10.2;
	float f2 = 20.1;
	float r = f1 * f2;
	printf("\n %f * %f = %f", f1, f2, r);
}
*/
/*
	int fdMain ;

	if((fdMain = open("./DupImpact.tt", O_APPEND)) < 0)
	{
		printf("\n Open Failed: %d", __LINE__);
		return;
	}

	char buf1[20] = "Write Before Dup\n" ;
	
	if(write(fdMain, buf1, strlen(buf1)) < 0)
	{
		printf("\n Write Failed: %d", __LINE__) ;
		return;
	}

	if(dup2(fdMain, 1) < 0)
	{
		printf("\n Dup2 Failed: %d", __LINE__) ;
		return;
	}

	printf("\nDup2: Normal Print to StdOut\n") ;
	fprintf(stdout, "\nDup2: file Print to StdOut\n") ;

	if(dup2(fdMain, 2) < 0)
	{
		printf("\n Dup2 Failed: %d", __LINE__) ;
		return;
	}

	fprintf(stderr, "\nDup2: file Print to StdErr\n") ;

	char buf2[20] = "Write After Dup\n" ;
	
	if(write(fdMain, buf2, strlen(buf2)) < 0)
	{
		printf("\n Write Failed: %d", __LINE__) ;
		return;
	}

	if(close(fdMain) < 0)
	{
		printf("\n fdMain close failed as expected") ;
	}
	else
	{
		printf("\n fdMain close succeeded - Test Failed");
		return;
	}

	if(resetstd(1) < 0)
	{
		printf("\n resetstd for stdout failed") ;
		return ;
	}

	if(close(fdMain) < 0)
	{
		printf("\n fdMain close failed as expected: %d", __LINE__) ;
	}
	else
	{
		printf("\n fdMain close succeeded - Test Failed: %d", __LINE__);
		return;
	}

	if(close(2) < 0)
	{
		printf("\n close on stderr failed") ;
		return ;
	}

	if(close(fdMain) < 0)
	{
		printf("\n close of fdMain failed") ;
		return ;
	}
	
	if(resetstd(2) < 0)
	{
		printf("\n resetstd for stderr failed") ;
		return ;
	}

	fprintf(stderr, "stderr print to console");

	printf("\n Dup2 Test Successful.... \n") ;
}
*/

/***************************************************************************************/
