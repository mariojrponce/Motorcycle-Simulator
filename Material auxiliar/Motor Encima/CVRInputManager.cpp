/***********************************************************************
*Nome: CVRInputManager.cpp
*Descrição: Classe que implementa os métodos para o gerenciamento de dispositivos
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
*Description: método que libera recursos
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
*Description: método que inicia os dispositivos
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
*Description: método que atualiza os dispositivos
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