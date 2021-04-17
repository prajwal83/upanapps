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
# include <MTerm.h>
# include <malloc.h>
# include <stdio.h>
# include <ctype.h>
# include <string.h>

static unsigned MAX_ROWS;
static unsigned MAX_COLS;
static unsigned MAX_WIN_BUFFER;

/**************************** static functions **************************************/
static int MTerm_GetActualCursorPosGeneric(byte bCols, int iPilot, int iCurPos)
{
	int x = iCurPos % bCols ;
	int y = iCurPos / bCols ;

	return (iPilot + y * MAX_COLS + x) ;
}

static int MTerm_GetActualCursorPos(const MWindow* pMWindow)
{
	return MTerm_GetActualCursorPosGeneric(pMWindow->Cols, pMWindow->PilotPoint, pMWindow->CursorPos) ;
}

static void MTerm_InitWindow(MWindow* pMWindow, byte nRows, byte nCols)
{
	pMWindow->Rows = pMWindow->ERows = nRows ;
	pMWindow->Cols = pMWindow->ECols = nCols ;

 	pMWindow->WinCharAttr = DEF_ATTR ;
	pMWindow->CursorPos = 0 ;

	pMWindow->PilotPoint = 0 ;
	pMWindow->Focus = false ;
	pMWindow->InstantUpdate = false ;
	pMWindow->ScrollLock = true ;

	MTerm_WinClear(pMWindow) ;
}

static int MTerm_RowColToCursor(MWindow* pMWindow, int row, int col)
{
	return row * pMWindow->Cols + col ;
}
/***********************************************************************************/

MWindow* MTerm_CreateWindow(byte nRows, byte nCols)
{
	// Change this to malloc once moved out as a seperate library	
	MWindow* pMWindow = (MWindow*)malloc(sizeof(MWindow)) ;
  pMWindow->CharContent = (MChar*)malloc(sizeof(MChar) * MAX_WIN_BUFFER);

	MTerm_InitWindow(pMWindow, nRows, nCols) ;

	return pMWindow ;
}

void MTerm_DestroyWindow(MWindow* pMWindow)
{
	// Change this to free once moved out as a seperate library
	if(pMWindow)
	{
    free(pMWindow->CharContent);
		free(pMWindow) ;
	}	
}

void MTerm_InitScr()
{
  console_size(&MAX_ROWS, &MAX_COLS);
  MAX_WIN_BUFFER = MAX_ROWS * MAX_COLS;
	clrscr() ;
}

unsigned MTerm_MaxRows()
{
  return MAX_ROWS;
}

unsigned MTerm_MaxColumns()
{
  return MAX_COLS;
}

/******* Win Attrs Start ******/
void MTerm_WinDimension(MWindow* pMWindow, byte nRows, byte nCols)
{
	pMWindow->Rows = nRows ;
	pMWindow->Cols = nCols ;
}

void MTerm_SetWinAttr(MWindow* pMWindow, byte Attr)
{
	pMWindow->WinCharAttr = Attr ;
	
	int i ;
	for(i = 0; i < WIN_SIZE(pMWindow); i++)
		pMWindow->CharContent[i]._attr = Attr ;
}

void MTerm_WinSetCursor(MWindow* pMWindow, int iCurPos)
{
	if(iCurPos >= 0 && iCurPos < WIN_SIZE(pMWindow)) 
		pMWindow->CursorPos = iCurPos ;	
}

void MTerm_SetWinPilotPoint(MWindow* pMWindow, int iPilotPoint)
{
	pMWindow->PilotPoint = iPilotPoint ;
}

void MTerm_SetAttr(MWindow* pMWindow, int row, int col, int iLen, byte Attr)
{
	int iStartPos = MTerm_RowColToCursor(pMWindow, row, col) ;

	int iEndPos = 0 ;
	
	if(!(iStartPos >= 0 && iStartPos < WIN_SIZE(pMWindow)))
		return ;

	if(iLen == MTERM_LINE_END)
		iEndPos = iStartPos + pMWindow->Cols - (iStartPos % pMWindow->Cols) ;
	else if(iLen == MTERM_WIN_END)
		iEndPos = WIN_SIZE(pMWindow) ;
	else
	{
		iEndPos = iStartPos + iLen - 1 ;
		if(iEndPos >= WIN_SIZE(pMWindow))
			iEndPos = WIN_SIZE(pMWindow) ;
		else if(iEndPos < iStartPos)
			iEndPos = iStartPos ;
	}

	int i ;
	for(i = iStartPos; i <= iEndPos; i++)
		pMWindow->CharContent[i]._attr = Attr ;
}

void MTerm_WinFocus(MWindow* pMWindow, byte bFocus)
{
	pMWindow->Focus = bFocus ;
}

void MTerm_WinInstantUpdate(MWindow* pMWindow, byte bUpdate)
{
	pMWindow->InstantUpdate = bUpdate ;
}

void MTerm_WinScrollLock(MWindow* pMWindow, byte bLock)
{
	pMWindow->ScrollLock = bLock ;
}

/****** Win Attrs End  ******/

void MTerm_WinMoveCursor(MWindow* pMWindow, int iCurOffset)
{
	int iPos = pMWindow->CursorPos + iCurOffset ;

	if(iPos >= 0 && iPos < WIN_SIZE(pMWindow))
		pMWindow->CursorPos = iPos ;	
}

void MTerm_WinPutCharSpec(MWindow* pMWindow, char Ch, byte Attr)
{
	if(pMWindow->InstantUpdate)
	{
		int iCurPos = MTerm_GetActualCursorPos(pMWindow) ;
		int iOldPos = get_cursor() ;
		set_cursor(iCurPos) ;

		uiwritec(Ch, Attr, true) ;

		if(pMWindow->Focus)
			set_cursor(iCurPos + 1) ;
		else
			set_cursor(iOldPos) ;
	}

	MChar* pMChar =	(MChar*)&(pMWindow->CharContent[pMWindow->CursorPos]) ;

	pMChar->_ch = Ch ;
	pMChar->_attr = Attr ;

	pMWindow->CursorPos++ ;

	if(pMWindow->CursorPos >= WIN_SIZE(pMWindow))
	{
		if(pMWindow->ScrollLock)
			pMWindow->CursorPos = 0 ;
		else
			MTerm_ScrollDown(pMWindow) ;
	}
}

void MTerm_WinNextLine(MWindow* pMWindow)
{
	int row = pMWindow->CursorPos / pMWindow->Cols + 1 ;
	pMWindow->CursorPos = row * pMWindow->Cols ;

	if(pMWindow->CursorPos >= WIN_SIZE(pMWindow))
	{
		if(pMWindow->ScrollLock)
			pMWindow->CursorPos = 0 ;
		else
			MTerm_ScrollDown(pMWindow) ;
	}
}

void MTerm_WinPutChar(MWindow* pMWindow, char Ch)
{
	MTerm_WinPutCharSpec(pMWindow, Ch, pMWindow->WinCharAttr) ;
}

void MTerm_WinPutStringSpec(MWindow* pMWindow, const char* szStr, int len, byte Attr)
{
	unsigned i ;
	for(i = 0; i < len; i++)
		MTerm_WinPutCharSpec(pMWindow, szStr[i], Attr) ;
}

void MTerm_WinPutString(MWindow* pMWindow, const char* szStr, int len)
{
	unsigned i ;
	for(i = 0; i < len; i++)
		MTerm_WinPutChar(pMWindow, szStr[i]) ;
}

void MTerm_WinRefresh(const MWindow* pMWindow)
{
	int iCurPos = MTerm_GetActualCursorPosGeneric(pMWindow->Cols, pMWindow->PilotPoint, 0) ;
	int iOldPos = get_cursor() ;
  uiwritea(pMWindow->CharContent, pMWindow->Rows, pMWindow->Cols, iCurPos);

	if(pMWindow->Focus)
		set_cursor(MTerm_GetActualCursorPos(pMWindow)) ;
	else
		set_cursor(iOldPos) ;
}

void MTerm_ScrollDown(MWindow* pMWindow)
{
	int i ;
	for(i = pMWindow->Cols; i < WIN_SIZE(pMWindow); i++)
	{
		pMWindow->CharContent[i - pMWindow->Cols] = pMWindow->CharContent[i] ;
	}

	for(i = i - pMWindow->Cols; i < WIN_SIZE(pMWindow); i++)
	{
		pMWindow->CharContent[i]._ch = NO_CHAR ;
		pMWindow->CharContent[i]._attr = pMWindow->WinCharAttr ;
	}

	pMWindow->CursorPos = i - pMWindow->Cols ;
}

void MTerm_ScrollUp(MWindow* pMWindow)
{
	int i ;
	for(i = WIN_SIZE(pMWindow) - pMWindow->Cols - 1; i >= 0; i--)
	{
		pMWindow->CharContent[i + pMWindow->Cols] = pMWindow->CharContent[i] ;
	}

	for(i = 0; i < pMWindow->Cols; i++)
	{
		pMWindow->CharContent[i]._ch = NO_CHAR ;
		pMWindow->CharContent[i]._attr = pMWindow->WinCharAttr ;
	}

	pMWindow->CursorPos = 0 ;
}

void MTerm_WinClear(MWindow* pMWindow)
{
	unsigned i ;
	for(i = 0; i < MAX_WIN_BUFFER; i++)
	{
		pMWindow->CharContent[i]._ch = NO_CHAR ;
		pMWindow->CharContent[i]._attr = pMWindow->WinCharAttr ;
	}	

	pMWindow->CursorPos = 0 ;
}

void MTerm_WinClearFromCursor(MWindow* pMWindow)
{
	unsigned i ;
	for(i = pMWindow->CursorPos; i < MAX_WIN_BUFFER; i++)
	{
		pMWindow->CharContent[i]._ch = NO_CHAR ;
		pMWindow->CharContent[i]._attr = pMWindow->WinCharAttr ;
	}	
}

void MTerm_WinClearLineFromCursor(MWindow* pMWindow)
{
	unsigned i ;
	unsigned left = pMWindow->Cols - pMWindow->CursorPos % pMWindow->Cols ;
	for(i = pMWindow->CursorPos; i < pMWindow->CursorPos + left; i++)
	{
		pMWindow->CharContent[i]._ch = NO_CHAR ;
		pMWindow->CharContent[i]._attr = pMWindow->WinCharAttr ;
	}	
}

void MTerm_Refresh(const MWindow* pMWindow)
{
	MTerm_WinRefresh(pMWindow) ;
}

void MTerm_WinPutCharInRange(MWindow* pMWindow, char Ch, int row, int col, int iLen)
{
	MTerm_WinSetCursor(pMWindow, MTerm_RowColToCursor(pMWindow, row, col)) ;

	int i ;
	for(i = 0; i < iLen; i++)
		MTerm_WinPutChar(pMWindow, Ch) ;
}

void MTerm_WinMovePutString(MWindow* pMWindow, int row, int col, const char* szStr)
{
	MTerm_WinSetCursor(pMWindow, MTerm_RowColToCursor(pMWindow, row, col)) ;
	MTerm_WinPutString(pMWindow, szStr, strlen(szStr)) ;
}

void MTerm_WinMove(MWindow* pMWindow, int row, int col)
{
	MTerm_WinSetCursor(pMWindow, MTerm_RowColToCursor(pMWindow, row, col)) ;
}

void MTerm_GetWinYX(MWindow* pMWindow, int* y, int* x)
{
	*y = pMWindow->CursorPos / pMWindow->Cols ;
	*x = pMWindow->CursorPos % pMWindow->Cols ;
}

