/***********************************************************************
*Nome: CVRObjGeneric.cpp
*Descri��o: Implementa��o da classe respons�vel pela cria��o de um 
*			objeto gen�rico
*Data: 18/06/08
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRObjGeneric.h"

/***********************************************************
*Name: CVRObjGeneric()
*Description: construtor da classe default
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRObjGeneric::CVRObjGeneric()
{

}

/***********************************************************
*Name: ~CVRObjGeneric()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRObjGeneric::~CVRObjGeneric()
{	

}

/***********************************************************
*Name: Init()
*Description: realiza as inicializa��es
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRObjGeneric::Init()
{
	CVRObject3D::Init();
	return true;
}

/***********************************************************
*Name: Render()
*Description: renderiza o objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObjGeneric::Render()
{
}

/***********************************************************
*Name: Update()
*Description: realiza as atualiza��es no objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObjGeneric::Update()
{
	CVRObject3D::Update();
}

