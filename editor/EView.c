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
# include <stdio.h>
# include <fs.h>
# include <kb.h>
# include <string.h>
# include <malloc.h>
# include <mosstd.h>

# include <MTerm.h>
# include <Action.h>
# include <Edit.h>
# include <EView.h>

static byte EView_backWinRows, EView_backWinCols, EView_editWinRows, EView_editWinCols ;
static const int filem = 1, warn = 0, chance = 1;
const int editw = 3 ;
char bakfile[110] = "\0" ;

#define MENU_COLS 15

/**************** static functions *********************/

static void EView_DrawBorderInBack(MWindow* pWin)
{
	MTerm_WinPutCharInRange(pWin, '-', 0, 0, pWin->Cols) ;
	MTerm_WinPutCharInRange(pWin, '-', pWin->Rows - 1, 0, pWin->Cols) ;
}

static int EView_DrawMenu(char *text[], int no_rows, int start_y, int start_x)
{
	int i, j, ch, res = -1, over = 0 ;

	MWindow* pMenuWin = MTerm_CreateWindow(no_rows, MENU_COLS) ;
	MTerm_SetWinPilotPoint(pMenuWin, start_y * MTerm_MaxColumns() + start_x) ;
	MTerm_SetWinAttr(pMenuWin, ATTR_NOBLINK | FG_BLACK | BG_WHITE) ;
	MTerm_WinFocus(pMenuWin, true) ;

	EView_DrawBorderInBack(pMenuWin) ;

	for(i = 0; i < no_rows - 2; i++)
		MTerm_WinMovePutString(pMenuWin, i + 1, 1, text[i]) ;

	i = 1;

	MTerm_WinRefresh(pMenuWin) ;

	while(true)
	{
		MTerm_SetAttr(pMenuWin, i, 1, MENU_COLS - 2, ATTR_NOBLINK | FG_BLACK | BG_RED) ;

		MTerm_WinRefresh(pMenuWin) ;
		
		j = i;

		kb_get_ch_wait(&ch) ;

		switch(ch)
		{
		case Keyboard_KEY_UP:
				i = (i == 1) ? no_rows - 2 : i - 1 ;
				break ;
		case Keyboard_KEY_DOWN:
				i = (i == no_rows - 2) ? 1 : i + 1 ;
				break ;
		case Keyboard_ESC:
				over = 1 ;
				res = -1 ;
				break ;
		case Keyboard_ENTER:
				over = 1 ;
				res = i ;
				break ;
		default:
				break ;
		}

		if(over)
		{
			EView_Refresh() ;
 			MTerm_DestroyWindow(pMenuWin) ;
			return res ;
		}

		MTerm_SetAttr(pMenuWin, j, 1, MENU_COLS - 2, ATTR_NOBLINK | FG_BLACK | BG_WHITE) ;
	}

	return 0 ;
}

static void EView_WarningBox(char text[], int interact)
{
	int ch ;
	MWindow* pWarnWin = MTerm_CreateWindow(7, 40) ;
	MTerm_SetWinPilotPoint(pWarnWin, 5 * MTerm_MaxColumns() + 20) ;
	MTerm_SetWinAttr(pWarnWin, ATTR_BLINK | FG_BLACK | BG_WHITE) ;

	EView_DrawBorderInBack(pWarnWin) ;

	MTerm_WinMovePutString(pWarnWin, 2, 1, text) ;

	MTerm_Refresh(pWarnWin) ;

	if(interact)
	{
		Action_DrawOkCancel(10) ;
		Action_OkCancel() ;
	}
	else
	{
		kb_get_ch_wait(&ch) ;
	}

	MTerm_DestroyWindow(pWarnWin) ;
	MTerm_WinRefresh(Edit_pBackWin) ;
	MTerm_WinRefresh(Edit_pEditWin) ;
}

static void EView_MessageBox(char text[], int margin, int *value, int option)
{
	char tempfl[105] = "\0" ;

	MWindow* pMsgWin = MTerm_CreateWindow(10, 40) ;
	MTerm_SetWinPilotPoint(pMsgWin, 5 * MTerm_MaxColumns() + 20) ;
	MTerm_SetWinAttr(pMsgWin, ATTR_NOBLINK | FG_BLACK | BG_WHITE) ;

	MTerm_WinMovePutString(pMsgWin, 1, 1, text) ;

	if(margin)
	{
		char b[20] ;
		sprintf(b, ": %d", *value) ;
		MTerm_WinMovePutString(pMsgWin, 1, 30, b) ;
	}

	EView_DrawBorderInBack(pMsgWin) ;

	MTerm_WinMove(pMsgWin, 2, 1) ;
	MTerm_WinRefresh(pMsgWin) ;

	Action_DrawOkCancel(12) ;

	void win_echo(char ch)
	{
		if(ch == Keyboard_BACKSPACE)
		{
			int y, x ;
			
			MTerm_GetWinYX(pMsgWin, &y, &x) ;
			MTerm_WinMove(pMsgWin, y, x - 1) ;
			MTerm_WinClearLineFromCursor(pMsgWin) ;
		}
		else
		{
			MTerm_WinPutChar(pMsgWin, ch) ;
		}

		MTerm_WinRefresh(pMsgWin) ;
		Action_RefershOkCancel() ;
	}

	switch(option)
	{
	case 1://Read filename
		scanf_cecho(&win_echo, "%s", tempfl) ;
		Action_OkCancel() ;

		if(tempfl[0] == '\0')
			ok = 0 ;

		if(ok)
		{
			strcpy(Edit_szFilename, tempfl) ;
			Action_FilenameDis() ;
		}	
		break ;

	case 2://Read Pagesetup
		scanf_cecho(&win_echo, "%d",value) ;
		Action_OkCancel() ;
		break ;
		
	case 3://Read word to insert
		if(word != NULL)
			free(word) ;
		word = (char*)malloc(sizeof(char) * 105) ;
		word[0] = '\0';
		scanf_cecho(&win_echo, "%s", word) ;
		Action_OkCancel() ;
		
		if(word[0] == '\0')
			ok = 0 ;
		break ;
	}

	MTerm_DestroyWindow(pMsgWin) ;
	MTerm_WinRefresh(Edit_pBackWin) ;
	MTerm_WinRefresh(Edit_pEditWin) ;
}

static void EView_ConfirmSave()
{
	int fd = open(Edit_szFilename, O_RDONLY) ;

	if(fd >= 0)
	{
		EView_WarningBox("**File Already Exist : Overwrite File?**", chance) ;

		if(ok)
			Action_FileSave() ;
		else
		{
			strcpy(Edit_szFilename, bakfile) ;
			Action_FilenameDis() ;
		}
	}
	else
	{
		if(create(Edit_szFilename, ATTR_FILE_DEFAULT) < 0)
		{
			EView_WarningBox("** Failed to Create file **", warn) ;
		}
		else
			Action_FileSave() ;
	}

	close(fd) ;
}

static void EView_CheckSave()
{
	if(!Edit_bSave)
	{
		EView_WarningBox("**** File not saved : Save File? ****", chance);

		if(ok)
		{
			if(strcmp(Edit_szFilename, "\0") == 0)
			{
				EView_MessageBox("Enter Filename(or Path) To Save : ", 0, 0, filem) ;
				if(ok)
					EView_ConfirmSave() ;
				sleep(1) ;
			}
			else
				Action_FileSave() ;
		}
	}
}

static void help(int abus)
{
	int key ;
	MWindow* pHelpWin = MTerm_CreateWindow(21, 75) ;
	MTerm_SetWinPilotPoint(pHelpWin, 2 * MTerm_MaxColumns() + 2) ;
	MTerm_SetWinAttr(pHelpWin, ATTR_NOBLINK | FG_WHITE | BG_BLACK) ;

	if(abus)
	{
		MTerm_WinMovePutString(pHelpWin, 1, 1, "*************************************************************************") ;

		MTerm_WinMovePutString(pHelpWin, 4, 10, "This is...  ******* \"edit\" ******* ...a simple text editor") ;

		MTerm_SetAttr(pHelpWin, 4, 31, 4, ATTR_NOBLINK | FG_BRIGHT_WHITE | BG_BLACK) ;

		MTerm_WinMovePutString(pHelpWin, 8, 15, "Release Version - 1.0") ;
		MTerm_WinMovePutString(pHelpWin, 10, 15, "Done By - MosMan") ;

		MTerm_WinMovePutString(pHelpWin, 18, 1, "*************************************************************************") ;
	}
	else
	{
		MTerm_WinMovePutString(pHelpWin, 1, 1, "*************************************************************************") ;

		MTerm_WinMovePutString(pHelpWin, 2, 1, "FILE MENU:Ctrl+F/f") ;
		MTerm_WinMovePutString(pHelpWin, 3, 1, "Ctrl+N/n:Newfile | Ctrl+O/o:Open Specified file | Ctrl+S/s:Save") ;
		MTerm_WinMovePutString(pHelpWin, 4, 1, "Ctrl+A/a:Save as | Ctrl+X/x:Exit") ;

		MTerm_WinMovePutString(pHelpWin, 5, 1, "*************************************************************************") ;
		MTerm_WinMovePutString(pHelpWin, 6, 1, "EDIT MENU:Ctrl+E/e") ;
		MTerm_WinMovePutString(pHelpWin, 7, 1, "Ctrl+D/d:Delete Line | Ctrl+R/r:Delete word | Ctrl+K/k:Insert Line") ;
		MTerm_WinMovePutString(pHelpWin, 8, 1, "Ctrl+W/w:Insert Word") ;

		MTerm_WinMovePutString(pHelpWin, 9, 1, "*************************************************************************") ;
		MTerm_WinMovePutString(pHelpWin, 13, 1, "*************************************************************************") ;

		MTerm_WinMovePutString(pHelpWin, 14, 1, "OPTIONS MENU: <to be done> ") ; //Ctrl+P-\n Ctrl+G:Set Fore/background Color | Page Setup");

		MTerm_WinMovePutString(pHelpWin, 16, 1, "*************************************************************************") ;

		MTerm_WinMovePutString(pHelpWin, 17, 1, "HELP MENU:Ctrl+H/h") ;
		MTerm_WinMovePutString(pHelpWin, 18, 1, "ABOUT US  |  COMMANDS") ;

		MTerm_WinMovePutString(pHelpWin, 19, 1, "*************************************************************************") ;
	}

	EView_DrawBorderInBack(pHelpWin) ;

	MTerm_WinMove(pHelpWin, 1, 1) ;

	MTerm_WinRefresh(pHelpWin) ;

	do
	{
		kb_get_ch_wait(&key) ;
	}
	while(key != Keyboard_ENTER) ;

	MTerm_DestroyWindow(pHelpWin) ;

	MTerm_WinRefresh(Edit_pBackWin) ;
	MTerm_WinRefresh(Edit_pEditWin) ;
}

/******************************************************/

void EView_DrawInitBack()
{
	EView_backWinRows = MTerm_MaxRows() - 2 ;
	EView_backWinCols = MTerm_MaxColumns() ;

	EView_editWinRows = MTerm_MaxRows() - 4 ;
	EView_editWinCols = MTerm_MaxColumns() - 2 ;

	Edit_pBackWin = MTerm_CreateWindow(EView_backWinRows, EView_backWinCols) ;
	MTerm_SetWinAttr(Edit_pBackWin, ATTR_NOBLINK | FG_WHITE | BG_BLUE) ;
	MTerm_SetWinPilotPoint(Edit_pBackWin, EView_backWinCols) ;

	Edit_pEditWin = MTerm_CreateWindow(EView_editWinRows, EView_editWinCols) ;
	MTerm_SetWinAttr(Edit_pEditWin, ATTR_NOBLINK | FG_WHITE | BG_BLUE) ;
	MTerm_SetWinPilotPoint(Edit_pEditWin, Edit_pBackWin->PilotPoint + MTerm_MaxColumns() + 1) ;
	MTerm_WinFocus(Edit_pEditWin, true) ;
//	MTerm_WinInstantUpdate(Edit_pEditWin, true) ;
	MTerm_WinScrollLock(Edit_pEditWin, false) ;

	EView_DrawBorderInBack(Edit_pBackWin) ;

	MTerm_WinRefresh(Edit_pBackWin) ;
	MTerm_WinRefresh(Edit_pEditWin) ;
}

void EView_DrawMenuBar()
{
	char text[] = { "File            Edit                           Options          Help" } ;
	int i ;

	Edit_pMenuWin = MTerm_CreateWindow(1, MTerm_MaxColumns()) ;
	MTerm_SetWinAttr(Edit_pMenuWin, ATTR_NOBLINK | FG_BLACK | BG_WHITE) ;
	MTerm_SetWinPilotPoint(Edit_pMenuWin, 0) ;

	MTerm_WinMovePutString(Edit_pMenuWin, 0, 1, text) ;

	for(i = 1; i < 66; i += 16)
	{
		MTerm_SetAttr(Edit_pMenuWin, 0, i, 1, ATTR_NOBLINK | FG_RED | BG_WHITE) ;
	}

	MTerm_WinRefresh(Edit_pMenuWin) ;
}

void EView_DrawStatusBar()
{
	Edit_pStatusWin = MTerm_CreateWindow(1, MTerm_MaxColumns()) ;
	MTerm_SetWinAttr(Edit_pStatusWin, ATTR_NOBLINK | FG_BLACK | BG_WHITE) ;
	MTerm_SetWinPilotPoint(Edit_pStatusWin, MTerm_MaxRows() * MTerm_MaxColumns() - MTerm_MaxColumns()) ;

	MTerm_WinRefresh(Edit_pStatusWin) ;

	EView_DisplayStatus() ;
}

void EView_Refresh()
{
	MTerm_WinRefresh(Edit_pBackWin) ;
	MTerm_WinRefresh(Edit_pEditWin) ;
	MTerm_WinRefresh(Edit_pMenuWin) ;
	MTerm_WinRefresh(Edit_pStatusWin) ;
}

void EView_Release()
{
	MTerm_DestroyWindow(Edit_pBackWin) ;
	MTerm_DestroyWindow(Edit_pEditWin) ;
	MTerm_DestroyWindow(Edit_pMenuWin) ;
	MTerm_DestroyWindow(Edit_pStatusWin) ;

	free(Edit_headNode) ;
	free(Edit_curNode) ;
}

void EView_DisplayStatus()
{
	MTerm_WinMove(Edit_pStatusWin, 0, 0) ;
	MTerm_WinClearLineFromCursor(Edit_pStatusWin) ;

	char szBuf[100] = "\0" ;
	
	if(Edit_bSave)
		sprintf(szBuf, "FileName-%s | Status-Saved", (Edit_szFilename[0] == '\0') ? "Newfile" : Edit_szFname) ;
	else
		sprintf(szBuf, "FileName-%s | Status-Unsaved", (Edit_szFilename[0] == '\0') ? "Newfile" : Edit_szFname) ;

	MTerm_WinMovePutString(Edit_pStatusWin, 0, 20, szBuf) ;

	sprintf(szBuf, "Row:%3d|Col:%2d", Edit_row + 1, Edit_col - Edit_xMin + 1) ;
	MTerm_WinMovePutString(Edit_pStatusWin, 0, 1, szBuf) ;
	MTerm_WinRefresh(Edit_pStatusWin) ;
}

void EView_FileMenu(int scut)
{
	char *text[] = { 
		"New      Ct+N", 
		"Open     Ct+O",
		"Save     Ct+S",
		"Save as  Ct+A",
		"Exit     Ct+X"
	} ;

	int key, res ;

	if(!scut)
	{
		key = EView_DrawMenu(text, 7, 1, 0) ; //6 Items -> 8 rows : 2 for border
	}
	else
	{
		key = scut ;
	}
 
	switch(key)
	{
	case 1: // New
		EView_CheckSave() ;
		Edit_ClearData(Edit_headNode) ;
		Edit_headNode = Edit_CreateNode() ;
		Edit_curNode = Edit_headNode ;
		Edit_row = Edit_yMin ;
		Edit_col = Edit_xMin ;

		MTerm_WinMove(Edit_pEditWin, Edit_row, Edit_col) ;

		Edit_szFilename[0] = bakfile[0] = '\0' ;

		MTerm_WinClear(Edit_pEditWin) ;
		MTerm_WinRefresh(Edit_pEditWin) ;
		Edit_bSave = true ;
		break ;

	case 2: // Open
		EView_CheckSave() ;
		strcpy(bakfile, Edit_szFilename) ;

		EView_MessageBox("  Enter Filename To Open :", 0, 0, filem) ;

		if(ok)
		{
			res = Action_FileOpen() ;
			if(res < 0)
			{
				EView_WarningBox("    ***** No  Such  File *****", warn) ;
				strcpy(Edit_szFilename, bakfile) ;
				Action_FilenameDis() ;
				return ;
			}
		}
		break ;

	case 3: // Save
		strcpy(bakfile, Edit_szFilename) ;
		if(strcmp(Edit_szFilename, "\0") == 0)
		{
			EView_MessageBox("  Enter Filename To Save :", 0, 0, filem) ;
			if(ok)
				EView_ConfirmSave() ;
		}
		else
			Action_FileSave() ;
		break ;

	case 4: // Save as
		strcpy(bakfile, Edit_szFilename) ;
		EView_MessageBox("  Enter Filename To Save as :", 0, 0, filem) ;
		if(ok)
			EView_ConfirmSave() ;
		break ;

	case 5: // Exit
		EView_CheckSave() ;
		Edit_ClearData(Edit_headNode) ;

		clrscr() ;
		exit(0) ;
		break ;

	default:
		break  ;
	}
}

void EView_EditMenu(int scut)
{
	char *text[] = { 
		"Del Line Ct+D",
		"Del Word Ct+R",
		"Ins Line Ct+K",
		"Ins Word Ct+W"
	} ;

	int key ;

	if(!scut)
		key = EView_DrawMenu(text, 6, 1, 17) ;
	else
		key = scut ;
 
	switch(key)
	{
	case 1://Delete line
		Edit_DeleteLine() ;
		Edit_bSave = false ;
		break ;
	case 2://Delete word
		Edit_DeleteWord() ;
		Edit_bSave = false ;
		break ;
	case 3://Insert line
		Edit_InsertLine() ;
		Edit_bSave = false ;
		break ;
	case 4://Insert word
		EView_MessageBox("Enter the word to be Inserted :", 0, 0, editw) ;
		if(ok)
		{
			Edit_InsertWord() ;
			Edit_bSave = false ;
		}
		else
			free(word) ;
		break ;
	default:
		break ;
	}         
}

void EView_HelpMenu()
{
	char *text[] = { "About Us     ","Hot Keys     " } ;
	int key ;

	key = EView_DrawMenu(text, 4, 1, 65) ;

	switch(key)
	{
	case 1://About us
		help(1);
		break;
	case 2://Commands
		help(0);
		break;
	default:
		break;
	}
}  

