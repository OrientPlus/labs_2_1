#include <windows.h>
#include <cwchar>
#include "ConsoleGraphic.hpp"


using namespace std;

void setconsoletextsize(int size)
{
	HANDLE hCons;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_FONT_INFOEX fontInfo;
	GetCurrentConsoleFontEx(hCons, TRUE, &fontInfo);
	fontInfo.cbSize = sizeof(fontInfo);
	fontInfo.nFont = 0;
	fontInfo.dwFontSize.X = 0;
	fontInfo.dwFontSize.Y = size;
	fontInfo.FontFamily = FF_DONTCARE;
	fontInfo.FontWeight = FW_NORMAL;
	wcscpy_s(fontInfo.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(hCons, FALSE, &fontInfo);
}

void setconsolesize(int x, int y)
{
	HWND hWinCons = GetConsoleWindow();
	RECT rc;
	GetWindowRect(hWinCons, &rc);
	MoveWindow(hWinCons, rc.left, rc.top, x, y, TRUE);
}
void hidecursor()
{
	HANDLE hCons;
	CONSOLE_CURSOR_INFO cci;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	cci.dwSize = 1;
	cci.bVisible = false;
	SetConsoleCursorInfo(hCons, &cci);
}
void clrscr()
{
	HANDLE hCons;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD crd;
	int len;
	DWORD bRet;
	short x, y;
	char space = 0x20;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hCons, &csbi);
	x = csbi.dwSize.X;
	y = csbi.dwSize.Y;
	len = (int)x*y;
	crd.X = 0;
	crd.Y = 0;
	FillConsoleOutputCharacter(hCons, space, len, crd, &bRet);
}
void gotoxy(int column, int row)
{
	HANDLE hCons;
	COORD crd;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	//#ifdef MY_DEBUG
	//  if (hCons == INVALID_HANDLE_VALUE || hCons == 0) printf("\nERROR!!!\n");
	//#endif  	  
	crd.X = (short)column;
	crd.Y = (short)row;
	//#ifedf MY_DEBUG
	// if (SetConsoleCursorPosition(hCons,crd) == 0) printf("\nERROR2\n");
	//#else 
	SetConsoleCursorPosition(hCons, crd);
	//#endif
}
void setcolor(short int color)
{
	HANDLE hCons;
	hCons = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hCons, color);
}