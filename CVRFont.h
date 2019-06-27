/***********************************************************************
*Nome: CVRFont.h
*Descrição: Cabeçalho da classe responsável pela renderização de fontes
*Data: 09/05/07
*Local: LNCC
************************************************************************/
#ifndef _CVRFONT_
#define _CVRFONT_

#include "CVRObject2D.h"

class CVRFont: public CVRObject2D
{
private:
	float fRed, fGreen, fBlue;
	int iCodeBase;
	int iSize;
	HFONT hFont;
	char text[100];
public:
	CVRFont();
	CVRFont(char*, int);
	~CVRFont();
	void SetHDC(HDC *);
	void SetColor(float, float, float);
	int GetSize();
	void Render();
	void SetText(char *);
	void Release();
	bool Init();
	void Update();

public:
	HDC* g_HDC;
};
#endif