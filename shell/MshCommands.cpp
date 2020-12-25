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
# include <MshCommandExecutor.h>
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

void MshCommandEcho::execute() {
  if(CommandLineParser_GetNoOfParameters())
    puts(CommandLineParser_GetParameterAt(0));
}

void MshCommandClearScreen::execute() {
  clrscr();
}

void MshCommandExit::execute() {
  exit(0);
}

void MshCommandCreateDir::execute() {
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
  }
}

void MshCommandDeleteFile::execute() {
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
  }
}

void MshCommandListDir::execute() {
  FS_Node *pDirList;
  int iListSize;

  if (CommandLineParser_GetNoOfParameters()) {
    int i;
    bool bDisplayParentDirName = CommandLineParser_GetNoOfParameters() > 1;

    for (i = 0; i < CommandLineParser_GetNoOfParameters(); i++) {
      if (get_dir_content(CommandLineParser_GetParameterAt(i), &pDirList, &iListSize) < 0) {
        printerr("%s : No Such Directory/File", CommandLineParser_GetParameterAt(i));
      } else {
        if (bDisplayParentDirName)
          printf("\n\n %s :", CommandLineParser_GetParameterAt(i));

        showDirContent(pDirList, iListSize);

        free(pDirList);
      }
    }
  } else {
    if (get_dir_content("", &pDirList, &iListSize) < 0) {
      puts("\nFailed to Get Directory Content");
    } else {
      showDirContent(pDirList, iListSize);
      free(pDirList);
    }
  }
}

void MshCommandListDir::showDirContent(const FS_Node* pDirList, int iListSize) {
  if(CommandLineParser_IsOptPresent("-l")) {
    char rwx[12] ;
    int i ;

    // Attr, User, Size, Create Time, Modify Time, Access Time, Name
    for(i = 0; i < iListSize; i++)
    {
      format_dir_attr(pDirList[i]._attribute, rwx) ;
      printf("\n%-15s%-15d%s", rwx, pDirList[i]._size, pDirList[i]._name) ;
    }
  } else {
    int i ;
    for(i = 0; i < iListSize; i++)
    {
      if(!(i % 3) && i != 0)
        putc('\n', stdout) ;
      printf("%-20s", pDirList[i]._name) ;
    }
  }
}

void MshCommandChangeDir::execute() {
  if(CommandLineParser_GetNoOfParameters())
  {
    if(chdir(CommandLineParser_GetParameterAt(0)) < 0)
      printerr("%s : No Such Directory", CommandLineParser_GetParameterAt(1)) ;
  }
}

void MshCommandPresentWorkingDir::execute() {
  char* szPWD ;
  getpwd(&szPWD) ;
  printf("%s", szPWD) ;
  free(szPWD) ;
}

void MshCommandCopyFile::execute() {
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

void MshCommandShowFile::execute() {
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

void MshCommandDate::execute() {
  RTCTime rtcTime ;
  dtime(&rtcTime) ;

  printf("%d/%d/%d %d:%d:%d", rtcTime.bDayOfMonth, rtcTime.bMonth,
         rtcTime.bCentury * 100 + rtcTime.bYear, rtcTime.bHour, rtcTime.bMinute,
         rtcTime.bSecond) ;
}

void MshCommandChangeDrive::execute() {
  if(CommandLineParser_GetNoOfParameters())
  {
    if(chdrive(CommandLineParser_GetParameterAt(0)) < 0)
      printerr("Failed to switch drive to %s", CommandLineParser_GetParameterAt(1)) ;
  }
}

void MshCommandShowDrives::execute() {
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

void MshCommandMountDrive::execute() {
  if(CommandLineParser_GetNoOfParameters() < 1)
    return ;

  const char* szDriveName = CommandLineParser_GetParameterAt(0) ;

  if(mount(szDriveName) < 0)
    printerr("Failed to mount drive %s", szDriveName) ;
}

void MshCommandUnMountDrive::execute() {
  if(CommandLineParser_GetNoOfParameters() < 1)
    return ;

  const char* szDriveName = CommandLineParser_GetParameterAt(0) ;

  if(umount(szDriveName) < 0)
    printerr("Failed to unmount drive %s", szDriveName) ;
}

void MshCommandFormatDrive::execute() {
  if(CommandLineParser_GetNoOfParameters() < 1)
    return ;

  const char* szDriveName = CommandLineParser_GetParameterAt(0) ;

  if(format(szDriveName) < 0)
    printerr("Failed to format drive %s", szDriveName) ;
}

void MshCommandShowCurrentDrive::execute() {
  DriveStat driveStat;

  if(getcurdrive(&driveStat) < 0)
    printerr("Failed to get current drive") ;

  printf("%s (%d B) %s", driveStat.driveName, driveStat.uiSizeInSectors * 512,
         (driveStat.bMounted) ? "-- mounted" : "not mounted") ;
}

void MshCommandReboot::execute() {
  reboot();
}

void MshCommandHelp::execute() {
  int i = 0;
  for(auto cmd : MshCommandExecutor::Instance().getCommands()) {
    if(!(i % 3) && i != 0)
      putc('\n', stdout) ;
    printf("%-20s", cmd.second->name().c_str()) ;
    ++i;
  }
}

void MshCommandGetProcessDetails::execute() {
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

void MshCommandExportEvnVar::execute() {
  if(CommandLineParser_GetNoOfParameters() < 1)
    return ;

  char* szExp = CommandLineParser_GetParameterAt(0) ;
  char* var = szExp ;
  char* val = strchr(szExp, '=') ;

  if(val == NULL) {
    printUsage();
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
