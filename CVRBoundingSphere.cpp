/***********************************************************************
*Nome: CVRBoundingSphere.cpp
*Descrição: Implementação da classe responsável pela criação de um 
*			envoltório em formato de esfera
*Data: 03/03/08
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRBoundingSphere.h"

/***********************************************************
*Name: CVRBoundingSphere()
*Description: construtor da classe default - cria um BoundingSphere
*			  com raio 1 na posição (0,0,0), não visível
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRBoundingSphere::CVRBoundingSphere()
{
	fRadius = 1.0f;
	vPos = CVRVector(0.0f,0.0f,0.0f);
	vScale  = CVRVector(1.0f,1.0f,1.0f);
	bVisible = false;
}

/***********************************************************
*Name: ~CVRBoundingSphere()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRBoundingSphere::~CVRBoundingSphere()
{
	
}

/***********************************************************
*Name: SetRadius()
*Description: configura o raio do BoundingSphere
*Params: int
*Return: Nenhum
************************************************************/
void CVRBoundingSphere::SetRadius(float radius)
{
	fRadius = radius;
}

/***********************************************************
*Name: GetRadius()
*Description: retorna o raio do BoundingSphere
*Params: Nenhum
*Return: float
************************************************************/
float CVRBoundingSphere::GetRadius()
{
	return fRadius;	
}

/***********************************************************
*Name: SetPosition()
*Description: Configura a posicao do BoundingSphere
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBoundingSphere::SetPosition(float fX, float fY, float fZ)
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
CVRVector CVRBoundingSphere::GetPosition()
{
	return vPos;
}

/***********************************************************
*Name: SetScale()
*Description: Configura a escala do BoundingSphere
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBoundingSphere::SetScale(float fX, float fY, float fZ)
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
CVRVector CVRBoundingSphere::GetScale()
{
	return vScale;
}

/***********************************************************
*Name: SetVisible()
*Description: configura se o bounds será visto ou nao
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBoundingSphere::SetVisible(bool visible)
{
	bVisible = visible;
}

/***********************************************************
*Name: GetVisible()
*Description: retorna se o bounds será visto ou nao
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRBoundingSphere::GetVisible()
{
	return bVisible;
}