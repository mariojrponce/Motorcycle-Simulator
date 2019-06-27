/***********************************************************************
*Nome: CVRObject32.cpp
*Descrição: Classe que implementa os métodos para os objetos 2D
*Data: 03/08/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRObject2D.h"


/***********************************************************
*Name: CVRObject2D()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRObject2D::CVRObject2D()
{
	bAutoRender = false;
	bVisible = true;
	fScaleX=1.0f;
	fScaleY=1.0f;
	fPosX = 0.0f; 
	fPosY = 0.0f;
	fAngle = 0.0f;
	imageId = 0;
}

/***********************************************************
*Name: ~CVRObject2D()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRObject2D::~CVRObject2D()
{
	
}

/***********************************************************
*Name: GetPosX()
*Description: retorna oa posicao X
*Params: Nenhum
*Return: Nenhum
************************************************************/
float CVRObject2D::GetPosX()
{
	return fPosX;
}

/***********************************************************
*Name: GetPosY()
*Description: retorna oa posicao Y
*Params: Nenhum
*Return: Nenhum
************************************************************/
float CVRObject2D::GetPosY()
{
	return fPosY;
}

/***********************************************************
*Name: SetPosX()
*Description: altera a posicao X
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject2D::SetPosX(float pos)
{
	fPosX = pos;
}

/***********************************************************
*Name: SetPosY()
*Description: altera a posicao X
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject2D::SetPosY(float pos)
{
	fPosY = pos;
}

/***********************************************************
*Name: SetPosXY()
*Description: altera a posicao X,Y do objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject2D::SetPosXY(float posX, float posY)
{
	fPosX = posX;
	fPosY = posY;
}

/***********************************************************
*Name: SetPosXY()
*Description: altera a posicao X,Y do objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject2D::SetScaleXY(float scaleX, float scaleY)
{
	fScaleX = scaleX;
	fScaleY = scaleY;
}

/***********************************************************
*Name: SetVisible()
*Description: configura se o objeto será visto ou nao
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject2D::SetVisible(bool visible)
{
	bVisible = visible;
}

/***********************************************************
*Name: GetVisible()
*Description: retorna se o objeto será visto ou nao
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRObject2D::GetVisible()
{
	return bVisible;
}