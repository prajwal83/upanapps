/*
 *  Upanix - An x86 based Operating System
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
#ifndef _EDIT_H_
#define _EDIT_H_

# include <MTerm.h>

MWindow* Edit_pBackWin ;
MWindow* Edit_pEditWin ;
MWindow* Edit_pMenuWin ;
MWindow* Edit_pStatusWin ;

int Edit_row, Edit_col ;
int Edit_yMin, Edit_yMax, Edit_xMin, Edit_xMax ;

byte Edit_bSave ;
char Edit_szFilename[110], Edit_szFname[10], Edit_szCheck[110] ;

int wy, wx ;
int ok ;

char *word ;

/*
int aymin = 0, aymax = 19, axmin = 0, axmax = 77 ;
int ok = 1, cpair = 1;
char *word = NULL; 
*/

typedef struct eachar
{
	char c ;
	struct eachar *flink ;
	struct eachar *blink ;
} ENode ;

ENode *Edit_headNode, *Edit_curNode ;

void Edit_Init() ;
ENode* Edit_CreateNode() ;
void Edit_Home() ;
void Edit_End() ;
void Edit_DisplayLine() ;
void Edit_InsertCh(char ch) ;
void Edit_DeleteCh() ;
void Edit_BakSpace() ;
void Edit_MoveUp() ;
void Edit_MoveDown() ;
void Edit_MoveLeft() ;
void Edit_MoveDown() ;
void Edit_MoveRight() ;
void Edit_PageUp() ;
void Edit_PageDown() ;
void Edit_ClearData(ENode* temp) ;
void Edit_InsertLine() ;
void Edit_InsertWord() ;
void Edit_DeleteLine() ;
void Edit_DeleteWord() ;

#endif
