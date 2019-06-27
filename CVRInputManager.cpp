/***********************************************************************
*Nome: CVRInputManager.cpp
*Descri��o: Classe que implementa os m�todos para o gerenciamento de dispositivos
*Data: 21/08/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRInputManager.h"
#include "CVRManager.h"

/***********************************************************
*Name: CVRInputManager()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRInputManager::CVRInputManager()
{
}

/***********************************************************
*Name: ~CVRInputManager()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRInputManager::~CVRInputManager()
{
	
}

/***********************************************************
*Name: Release()
*Description: m�todo que libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRInputManager::Release()
{
	cJoystick.Release();
	cStdInput.Release();
}

/***********************************************************
*Name: Init()
*Description: m�todo que inicia os dispositivos
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRInputManager::Init()
{
	cStdInput.pManager = pManager;
	cStdInput.Init();
	cJoystick.Init();
	//cForceFeedbackManager.initFFManager( pManager->cMainWindow.hwnd );

	return true;
}

/***********************************************************
*Name: Update()
*Description: m�todo que atualiza os dispositivos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRInputManager::Update()
{
	cStdInput.Update();
	
	if(cJoystick.HasJoystick())
	{
		cJoystick.Update();
	}
}