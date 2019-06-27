/***********************************************************************
*Nome: CVRManager.h
*Descrição: Classe responsavel pelo controle dos recursos da Engine
*Data: 18/07/07
*Local: LNCC
************************************************************************/
#ifndef _CVRMANAGER_
#define _CVRMANAGER_

//Bibliotecas
#include "CVRWindow.h"
#include "CVRObject.h"
#include "CVRTimeManager.h"
#include "CVRGraphicsManager.h"
#include "CVRInputManager.h"
#include "CVRSoundManager.h"
#include "CVRCollisionManager.h"
#include "CVRLog.h"
#include "CVRView.h"
#include "CVRScene.h"

class CVRManager: public CVRObject
{
public:
	CVRWindow cMainWindow;
	CVRTimeManager cTimeManager;
	CVRGraphicsManager cGraphicsManager;
	CVRSoundManager cSoundManager;
	CVRCollisionManager cCollisionManager;
	CVRInputManager cInputManager;
	CVRView cView;
	bool bRunning;
	CVRScene* pScene;
	vector<CVRScene *> vScenes;

public:
	CVRManager();
	~CVRManager();
	void Loop();
	void Exit();
	void SetCurrentScene(int);
	void AddNewScene(CVRScene *);
	CVRScene* GetCurrentScene();
	void Release();
	void SwpBuffers();
	void ClearBuffer();
	
private:
	void Update();
	void Init();
};
#endif