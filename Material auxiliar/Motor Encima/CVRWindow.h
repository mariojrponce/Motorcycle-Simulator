/***********************************************************************
*Nome: CVRWindow.h
*Descrição: Classe responsavel pela criação e configuração da Janela
*Data: 17/07/07
*Local: LNCC
************************************************************************/

#ifndef _CVRWINDOW_
#define _CVRWINDOW_

//Bibliotecas
#include "CVRObject.h"

/****Definitions**************/
#define WIN32_LEAN_AND_MEAN

class CVRWindow: public CVRObject
{
public:
	static long lWindowWidth;
	static long lWindowHeight;
	static HDC hdc;
	static HGLRC hrc;
	static unsigned int uiWindowDepth;
	static float mouseX, mouseY;

private:   
	bool bFullScreen;
	char cTitle[100];
	static LRESULT CALLBACK MainWindowProc(HWND, UINT, WPARAM, LPARAM);
	int xPos, yPos;
	
public:
	CVRWindow();
	~CVRWindow();
	void SetFullScreen(bool);
	void SetResolution(long, long, unsigned int);
	void Show();
	void Release();
	void SetTitle(char *);
	void SetBackground(float, float, float);
	void SetBackground(int, int, int);
	void SetPosition(int, int);
	HINSTANCE hInstance;
	HWND		hwnd;
	float r, g, b;
	HDC GetHdc();
	
private:
	static void SetupPixelFormat(HDC);
};
#endif