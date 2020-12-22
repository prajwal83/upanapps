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
# include <Action.h>
# include <Edit.h>
# include <kb.h>
# include <fs.h>
# include <string.h>

MWindow *pOkWin, *pCancelWin ;

int Action_FileOpen()
{
	int fd ;

	if((fd = open(Edit_szFilename, O_RDONLY)) < 0)
		return -1 ;

	Edit_ClearData(Edit_headNode) ;
	Edit_headNode = Edit_CreateNode() ;
	Edit_curNode = Edit_headNode ;

	MTerm_WinClear(Edit_pEditWin) ;
	MTerm_WinRefresh(Edit_pEditWin) ;

	int n, i ;
	char buffer[512] ;

	for(;;)
	{
		if((n = read(fd, buffer, 512)) < 0)
			return -1 ;

		for(i = 0; i < n; i++)
			Edit_InsertCh(buffer[i]);

		if(n < 512)
			break ;
	}

	Edit_curNode = Edit_headNode ;
	
	MTerm_WinMove(Edit_pEditWin, Edit_yMin, Edit_xMin) ;
	
	Edit_row = wy = Edit_yMin ;
	Edit_col = wx = Edit_xMin ;

	Edit_DisplayLine() ;

	Edit_bSave = 1 ;

	close(fd) ;
	return 1 ;
}

void Action_FileSave()
{
	ENode* temp ;
	int fd ;

	if((fd = open(Edit_szFilename, O_RDWR | O_TRUNC )) < 0)
		return ;

	char buffer[512] ;
	int n ;

	temp = Edit_headNode->flink;
	n = 0 ;

	while(temp != NULL)
	{
		if(n < 512)
			buffer[n] = temp->c ;
		else
		{
			if(write(fd, buffer, n) < 0)
			{
				close(fd) ;
				return ;
			}
			n = 0 ;
			continue ;
		}

		temp = temp->flink;
		n++ ;
	}

	if(n != 0)
		write(fd, buffer, n) ;

	Edit_bSave = TRUE ;
	close(fd);
} 

void Action_DrawOkCancel(int pos)
{
	pOkWin = MTerm_CreateWindow(1, 8) ;
	MTerm_SetWinPilotPoint(pOkWin, pos * MTerm_MaxColumns() + 27) ;
	MTerm_SetWinAttr(pOkWin, ATTR_NOBLINK | FG_BLACK | BG_RED) ;

	pCancelWin = MTerm_CreateWindow(1, 8) ;
	MTerm_SetWinPilotPoint(pCancelWin, pos * MTerm_MaxColumns() + 43) ;
	MTerm_SetWinAttr(pCancelWin, ATTR_NOBLINK | FG_BLACK | BG_RED) ;

	MTerm_WinMovePutString(pOkWin, 0, 3, "OK") ;
	MTerm_WinMovePutString(pCancelWin, 0, 1, "CANCEL") ;

	Action_RefershOkCancel() ;
}

void Action_OkCancel()
{
	int ch ;
	ok = 1 ;

	MTerm_WinMove(pOkWin, 0, 0) ;
	MTerm_SetWinAttr(pOkWin, ATTR_NOBLINK | FG_RED | BG_BLACK) ;
	MTerm_WinRefresh(pOkWin) ;

	kb_get_ch_wait(&ch) ;

	while(ch != Keyboard_ENTER)
	{
		if(ch == '\t' && ok == 1)
		{
			MTerm_WinMove(pOkWin, 0, 0) ;
			MTerm_SetWinAttr(pOkWin, ATTR_NOBLINK | FG_BLACK | BG_RED) ;
			ok = 0 ;

			MTerm_WinMove(pCancelWin, 0, 0) ;
			MTerm_SetWinAttr(pCancelWin, ATTR_NOBLINK | FG_RED | BG_BLACK) ;
		}
		else if(ch == '\t' && ok == 0)
		{
			MTerm_WinMove(pCancelWin, 0, 0) ;
			MTerm_SetWinAttr(pCancelWin, ATTR_NOBLINK | FG_BLACK | BG_RED) ;
			ok = 1 ;

			MTerm_WinMove(pOkWin, 0, 0) ;
			MTerm_SetWinAttr(pOkWin, ATTR_NOBLINK | FG_RED | BG_BLACK) ;
		} 

		Action_RefershOkCancel() ;

		kb_get_ch_wait(&ch) ;
	}

	MTerm_DestroyWindow(pOkWin) ;
	MTerm_DestroyWindow(pCancelWin) ;
}

void Action_FilenameDis()
{
	int i, n_file_len = 0 ; 

	for(i=0; Edit_szFilename[i] != '\0' && i <= 6; i++)
		Edit_szFname[i] = Edit_szFilename[i] ;

	n_file_len = strlen(Edit_szFilename) ;
	if(n_file_len > 7)
	{
		Edit_szFname[i] = '.' ;
		Edit_szFname[i+1] = '.' ;
		Edit_szFname[i+2] = '\0' ;
	}
	else
		Edit_szFname[i] = '\0' ;
}

void Action_RefershOkCancel()
{
	MTerm_WinRefresh(pOkWin) ;
	MTerm_WinRefresh(pCancelWin) ;
}
