/***********************************************************************
*Nome: CVRQuad.cpp
*Descrição: Implementação da classe responsável pela representação de um frame
*Data: 11/01/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRQuad.h"
#include "CVRLog.h"


/***********************************************************
*Name: CVRQuad()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRQuad::CVRQuad()
{
	fTop = 0;
	fBottom = 0;
	fRight = 0;
	fLeft = 0;
}

/***********************************************************
*Name: ~CVRQuad()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRQuad::~CVRQuad()
{

}

/***********************************************************
*Name: CVRQuad()
*Description: construtor da classe
*Params: float, float, float, float
*Return: Nenhum
************************************************************/
CVRQuad::CVRQuad(float top, float bottom, float left, float right)
{
	fTop = 0;
	fBottom = 0;
	fRight = 0;
	fLeft = 0;
}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRQuad::Release()
{
	fTop = 0;
	fBottom = 0;
	fRight = 0;
	fLeft = 0;
}

/***********************************************************
*Name: IsValid()
*Description: verifica se é um frame válido
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRQuad::IsValid()
{
	return (fBottom >= fTop && fRight >= fLeft);
}

/***********************************************************
*Name: GetHeight()
*Description: retorna a altura do frame
*Params: Nenhum
*Return: float
************************************************************/
float CVRQuad::GetHeight()
{
	return (fBottom - fTop);
}

/***********************************************************
*Name: GetWidth()
*Description: retorna a largura do frame
*Params: Nenhum
*Return: float
************************************************************/
float CVRQuad::GetWidth()
{
	return (fRight - fLeft);
}


/***********************************************************
*Name: Collide()
*Description: verifica se os quadros colidem
*Params: CVRQuad
*Return: bool
************************************************************/
bool CVRQuad::Collide(CVRQuad& Quad)
{
	return((fLeft < Quad.fRight)  && (fRight  > Quad.fLeft) && 
				 (fTop  < Quad.fBottom) && (fBottom > Quad.fTop));
}