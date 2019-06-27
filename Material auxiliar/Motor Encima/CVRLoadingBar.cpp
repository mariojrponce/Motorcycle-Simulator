/***********************************************************************
*Nome: CVRLoadingBar.h
*Descrição: Implementação da classe responsável pela criação da barra de 
			loading
*Data: 29/02/08
*Local: LNCC
************************************************************************/

#include "CVRLoadingBar.h"


/***********************************************************
*Name: CVRLoadingBar()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRLoadingBar::CVRLoadingBar(int width, int height)
{
	fPosX = 0.0f;
	fPosY = 0.0f;

	iWidth = width;
	iHeight = height;
	iRight = width;
	iPercentage = 100;

	for (int iIndex=0; iIndex< 3; iIndex++)
	{
		emptyColor[iIndex] = 0.0f;
		fullColor[iIndex] = 1.0f;
	}
	emptyColor[0] = 1.0f;
}


/***********************************************************
*Name: ~CVRLoadingBar()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRLoadingBar::~CVRLoadingBar()
{

}

/***********************************************************
*Name: Init()
*Description: Inicializa os recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRLoadingBar::Init()
{
	return true;
}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRLoadingBar::Release()
{
	
}

/***********************************************************
*Name: Render()
*Description: Renderiza o objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRLoadingBar::Render()
{
	if (!bVisible)
	{
		return;
	}

	glDisable(GL_TEXTURE_2D);
	glPushAttrib(GL_CURRENT_BIT);
		
		glColor3f(emptyColor[0],emptyColor[1], emptyColor[2]);
		glPolygonMode(GL_FRONT,GL_LINE);
		glBegin(GL_QUADS);
			glVertex2f(fPosX, fPosY);
			glVertex2f(fPosX, fPosY+iHeight);
			glVertex2f(fPosX+iWidth, fPosY+iHeight);
			glVertex2f(fPosX+iWidth, fPosY);
		glEnd();

		glColor3f(fullColor[0],fullColor[1], fullColor[2]);
		glPolygonMode(GL_FRONT,GL_FILL);
		glBegin(GL_QUADS);
			glVertex2f(fPosX, fPosY);
			glVertex2f(fPosX, fPosY+iHeight);
			glVertex2f((float)iRight, fPosY+iHeight);
			glVertex2f((float)iRight, fPosY);
		glEnd();

	glPopAttrib();
}

/***********************************************************
*Name: SetPercentage()
*Description: atualiza a percentagem da barra
*Params: int
*Return: Nenhum
************************************************************/
void CVRLoadingBar::SetPercentage(int percent)
{
	iPercentage = percent;
}

/***********************************************************
*Name: GetPercentage()
*Description: retorna o valor da percentagem atual
*Params: Nenhum
*Return: CVRLoadingBar
************************************************************/
int CVRLoadingBar::GetPercentage()
{
	return iPercentage;
}


/***********************************************************
*Name: Update()
*Description: Atualiza o objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRLoadingBar::Update()
{
	iRight = (int)(fPosX + (iWidth*iPercentage)/100);
}

/***********************************************************
*Name: SetBorderColor()
*Description: Atualiza a cor da borda
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRLoadingBar::SetBorderColor(float red, float green, float blue)
{
	emptyColor[0] = red;
	emptyColor[1] = green;
	emptyColor[2] = blue;
}

/***********************************************************
*Name: SetBarColor()
*Description: Atualiza a cor da barra
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRLoadingBar::SetBarColor(float red, float green, float blue)
{
	fullColor[0] = red;
	fullColor[1] = green;
	fullColor[2] = blue;
}

