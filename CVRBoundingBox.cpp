/***********************************************************************
*Nome: CVRBoundingSphere.cpp
*Descrição: Implementação da classe responsável pela criação de um 
*			envoltório em formato de caixa
*Data: 18/06/08
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRBoundingBox.h"

/***********************************************************
*Name: CVRBoundingBox()
*Description: construtor da classe default - cria um CVRBoundingBox
*			  com largura, altura e profundidade igual a 1 na posição (0,0,0), não visível
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRBoundingBox::CVRBoundingBox()
{
	fDimension = 1.0f;
	vPos = CVRVector(0.0f,0.0f,0.0f);
	vScale  = CVRVector(1.0f,1.0f,1.0f);
	bVisible = false;
}

/***********************************************************
*Name: ~CVRBoundingBox()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRBoundingBox::~CVRBoundingBox()
{
	
}

/***********************************************************
*Name: SetDimension()
*Description: configura a dimensão do BoundingBox
*Params: int
*Return: Nenhum
************************************************************/
void CVRBoundingBox::SetDimension(float dimension)
{
	fDimension = dimension;
}

/***********************************************************
*Name: GetDimension()
*Description: retorna a dimensão do BoundingBox
*Params: Nenhum
*Return: float
************************************************************/
float CVRBoundingBox::GetDimension()
{
	return fDimension;	
}

/***********************************************************
*Name: SetPosition()
*Description: Configura a posicao do BoundingSphere
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBoundingBox::SetPosition(float fX, float fY, float fZ)
{
	vPos.SetX(fX);
	vPos.SetY(fY);
	vPos.SetZ(fZ);
}

/***********************************************************
*Name: GetPosition()
*Description: Retorna a posicao do BoundingSphere
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRVector CVRBoundingBox::GetPosition()
{
	return vPos;
}

/***********************************************************
*Name: SetScale()
*Description: Configura a escala do BoundingSphere
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBoundingBox::SetScale(float fX, float fY, float fZ)
{
	vScale.SetX(fX);
	vScale.SetY(fY);
	vScale.SetZ(fZ);
}

/***********************************************************
*Name: GetScale()
*Description: Retorna a escala do BoundingSphere
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRVector CVRBoundingBox::GetScale()
{
	return vScale;
}

/***********************************************************
*Name: SetVisible()
*Description: configura se o bounds será visto ou nao
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBoundingBox::SetVisible(bool visible)
{
	bVisible = visible;
}

/***********************************************************
*Name: GetVisible()
*Description: retorna se o bounds será visto ou nao
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRBoundingBox::GetVisible()
{
	return bVisible;
}
