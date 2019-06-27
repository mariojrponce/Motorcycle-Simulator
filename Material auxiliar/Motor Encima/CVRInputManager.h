/***********************************************************************
*Nome: CVRInputManager
*Descrição: Cabeçalho da classe responsável pelo gerenciamento ds dispositivos
*Data: 21/08/07
*Local: LNCC
************************************************************************/
#ifndef _CVRINPUTMANAGER_
#define _CVRINPUTMANAGER_

//Bibliotecas
#include "CVRObject.h"
#include "CVRJoystick.h"
#include "CVRSTDInput.h"
#include "CVRForceFeedbackManager.h"

class CVRManager;

class CVRInputManager: public CVRObject
{
public:
	CVRInputManager();
	~CVRInputManager();
	void Release();
	bool Init();
	void Update();
public:
	CVRManager* pManager;
	CVRSTDInput cStdInput;
	CVRJoystick cJoystick;
	//CVRForceFeedbackManager cForceFeedbackManager;
};

#endif