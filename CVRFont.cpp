/***********************************************************************
*Nome: CVRFont.cpp
*Descrição: Implementação da classe responsável pela renderização de fontes
*Data: 09/05/07
*Local: LNCC
************************************************************************/

#include "CVRFont.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <cstdio>

/***********************************************************
*Name: CVRFont()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRFont::CVRFont()
{
	fPosX = 0;
	fPosY = 0;
	iSize = 20;

	g_HDC = NULL;

	fRed = 1.0f;
	fGreen = 0.0f;
	fBlue = 0.0f;

	sprintf(text,"%s","NONENONENONENONE");
}

/***********************************************************
*Name: CVRFont()
*Description: construtor da classe
*Params: char*, int
*Return: Nenhum
************************************************************/
CVRFont::CVRFont(char* fType, int size)
{
	fPosX = 0.0;
	fPosY = 0.0;
	iSize = size;

	g_HDC = NULL;

	fRed = 1.0f;
	fGreen = 0.0f;
	fBlue = 0.0f;
	sprintf(text,"%s",fType);
}

/***********************************************************
*Name: CVRFont()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRFont::~CVRFont()
{
	
}

/***********************************************************
*Name: GetSize()
*Description: retorna o tamanho da fonte
*Params: Nenhum
*Return: Nenhum
************************************************************/
int CVRFont::GetSize()
{
	return iSize;
}

/***********************************************************
*Name: SetHDC()
*Description: configura o HDC da fonte
*Params: HDC
*Return: Nenhum
************************************************************/
void CVRFont::SetHDC(HDC *pHdc)
{
	g_HDC = pHdc;
}

/***********************************************************
*Name: SetPosY()
*Description: altera a posicao X
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRFont::SetColor(float r, float g, float b)
{
	fRed = r;
	fGreen =g;
	fBlue = b;
}

/***********************************************************
*Name: SetText()
*Description: configura o texto a ser exibido
*Params: char*
*Return: Nenhum
************************************************************/
void CVRFont::SetText(char* pText)
{
	sprintf(text,"%s",pText);
}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRFont::Release()
{
	if (iCodeBase!=0)
	{
		glDeleteLists(iCodeBase, 256);
		iCodeBase=0;
	}

	if (g_HDC)
	{
		g_HDC = NULL;
	}
}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRFont::Init()
{
	hFont = CreateFont(iSize,0,0,0,FW_BOLD,FALSE,FALSE,FALSE,ANSI_CHARSET,
					   OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS,ANTIALIASED_QUALITY,
					   FF_DONTCARE | DEFAULT_PITCH,LPCWSTR("arial"));

	iCodeBase = glGenLists(256);

	if (!iCodeBase)
	{
		return false;
	}

	SelectObject(*g_HDC, hFont);

	wglUseFontBitmaps(*g_HDC,0,256,iCodeBase);

	return true;
}

/***********************************************************
*Name: Render()
*Description: renderiza o texto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRFont::Render()
{
	//Verifica se está visível
	if(!bVisible)
	{
		return;
	}

	if (iCodeBase ==0)
	{
		return;
	}

	glDisable(GL_TEXTURE_2D);
	glPushAttrib(GL_CURRENT_BIT);
		glColor3f(fRed, fGreen, fBlue);
		glRasterPos2f(fPosX,fPosY);
		glPushAttrib(GL_LIST_BIT);
			glListBase(iCodeBase);
			glCallLists((GLsizei)strlen(text),GL_UNSIGNED_BYTE,text);
		glPopAttrib();
	glPopAttrib();
}

/***********************************************************
*Name: Update()
*Description: atualiza a fonte
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRFont::Update()
{

}


