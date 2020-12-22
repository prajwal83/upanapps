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
#include <MTerm.h>
#include <Action.h>
#include <Edit.h>
#include <EView.h>
#include <kb.h>
#include <stdio.h>
# include <dtime.h>

int main(int argc, char** argv)
{
	MTerm_InitScr() ;

	Edit_Init() ;

 	EView_DrawInitBack() ;
	EView_DrawMenuBar() ;
	EView_DrawStatusBar() ;

	MTerm_WinMove(Edit_pEditWin, Edit_yMin, Edit_xMin) ;

	EView_Refresh() ;

	int ch, y ;

	while(TRUE)
	{
		MTerm_GetWinYX(Edit_pEditWin, &y, &Edit_col) ;
		EView_DisplayStatus() ;
		MTerm_WinRefresh(Edit_pEditWin) ;

		kb_get_ch_wait(&ch) ;

		if(CTRL(ch, 'f') || CTRL(ch, 'F'))
		{
			EView_FileMenu(0) ; // Ctrl+F - FILE MENU
		}
		else if(CTRL(ch, 'n') || CTRL(ch, 'N'))
		{
			EView_FileMenu(1) ; // Ctrl+N - New
		}
		else if(CTRL(ch, 'o') || CTRL(ch, 'O'))
		{
			EView_FileMenu(2) ; // Ctrl+O - Open
		}
		else if(CTRL(ch, 's') || CTRL(ch, 'S'))
		{
			EView_FileMenu(3) ; // Ctrl+S - Save
		}
		else if(CTRL(ch, 'a') || CTRL(ch, 'A'))
		{
			EView_FileMenu(4) ; // Ctrl+A - Save as
		}
		else if(CTRL(ch, 'x') || CTRL(ch, 'X'))
		{
			EView_FileMenu(5) ; // ctrl+X - Exit
		}
		else if(CTRL(ch, 'e') || CTRL(ch, 'E'))
		{
			EView_EditMenu(0) ; // Ctrl+E - EDIT MENU
		}
		else if(CTRL(ch, 'd') || CTRL(ch, 'D'))
		{
			EView_EditMenu(1) ; // Ctrl+D - Delete line
		}
		else if(CTRL(ch, 'r') || CTRL(ch, 'R'))
		{
			EView_EditMenu(2) ; // Ctrl+R - Delete word
		}
		else if(CTRL(ch, 'k') || CTRL(ch, 'K'))
		{
			EView_EditMenu(3) ; // Ctrl+K - Insert line
		}
		else if(CTRL(ch, 'w') || CTRL(ch, 'W'))
		{
			EView_EditMenu(4) ; // Ctrl+W - Insert word
		}
		else if(CTRL(ch, 'p') || CTRL(ch, 'P'))
		{
		//	options_menu();//Ctrl+P - Options Men
		}
		else if(CTRL(ch, 'h') || CTRL(ch, 'H'))
		{
			EView_HelpMenu() ;
		}
		else if(ch == Keyboard_KEY_HOME)
		{
			Edit_Home() ;
		}
		else if(ch == Keyboard_KEY_END)
		{
			Edit_End() ;
		}
		else if(ch == Keyboard_KEY_UP)
		{
			Edit_MoveUp() ;
		}
		else if(ch == Keyboard_KEY_DOWN)
		{
			Edit_MoveDown() ;
		}
		else if(ch == Keyboard_KEY_LEFT)
		{
			Edit_MoveLeft() ;
		}
		else if(ch == Keyboard_KEY_RIGHT)
		{
			Edit_MoveRight() ;
		}
		else if(ch == Keyboard_KEY_DEL)
		{
			Edit_DeleteCh() ;
			Edit_bSave = FALSE ;
			Edit_DisplayLine() ;
		}
		else if(ch == Keyboard_BACKSPACE)
		{
			Edit_BakSpace() ;
			Edit_bSave = FALSE ;
			Edit_DisplayLine() ;
		}
		else if(ch == Keyboard_KEY_PG_UP)
		{
			Edit_PageUp() ;
		}
		else if(ch == Keyboard_KEY_PG_DOWN)
		{
			Edit_PageDown() ;
		}
		else
		{
			if(toascii(ch) > 30 || ch == Keyboard_ENTER || ch == '\t')
			{
				if(ch == Keyboard_ENTER)
					ch = '\n' ;

				Edit_InsertCh(ch) ;
				Edit_bSave = FALSE ;
				Edit_DisplayLine() ;
			}
		}
	}

	EView_Release() ;

	return 0;
}

