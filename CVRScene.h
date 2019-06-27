/***********************************************************************
*Nome: CVRScene.h
*Descrição: Cabeçalho da classe responsável pelo gerenciamento de cena
*Data: 31/07/07
*Local: LNCC
************************************************************************/
#ifndef _CVRSCENE_
#define _CVRSCENE_

//Bibliotecas
#include "CVRObject.h"
#include "CVRObject3D.h"
#include "CVRFont.h"
#include "CVRBillboard.h"
#include "CVRSkyBox.h"
#include "CVRSkySphere.h"
#include "CVRTerrain.h"
#include "CVRMd2.h"
#include "CVRListener.h"
#include "CVRSprite.h"
#include "CVRSound.h"
#include "CVRMusic.h"
#include "CVRObjLoader.h"
#include "CVRLoadingBar.h"
#include "CVRObjGeneric.h"

class CVRManager;

class CVRScene: public CVRObject
{
public:
	CVRScene();
	~CVRScene();
	
	virtual void Release();
	virtual void Render(float, float);
	virtual void Render();
	virtual bool Init() = 0;
	virtual void Execute() = 0;
	void SetOrthoMode(int, int, int, int);
	void SetPerspectiveMode();
	void LoadMusic(char*);
	void Update();
	void ShowFps(bool);
	CVRFont* CreateFont2D(char *, int, bool);
	CVRBillboard* CreateBillboard(CVRSprite*, bool);
	CVRSkyBox* CreateSkyBox(char*,bool);
	CVRSkyBox* CreateSkyBox(bool);
	CVRSkySphere* CreateSkySphere(char*, bool);
	CVRTerrain* CreateRandomTerrain(char*, int, float, bool);
	CVRTerrain* CreateBmpTerrain(char*, char*,float, bool);
	CVRMd2* CreateMd2(char*, char*, bool);
	CVRListener* GetListener();
	CVRSound* LoadSound(char*);
	CVRMusic GetCurrentMusic();
	CVRObjLoader* CreateObj(char* fileName=NULL, char* workDirectory=NULL, bool autoRender=true, bool bGetGeometry=false);
	CVRSprite* CreateSprite(char*,int,int, bool);
	CVRSprite* CreateSprite(char*,char*, int,int, bool);
	CVRLoadingBar* CreateLoadingBar(int, int, bool);
	CVRObjGeneric* CreateObjGeneric(CVRObjGeneric*, bool);
	void RemoveObject2D(CVRObject2D*);
public:
	CVRManager* pManager;

private:
	vector<CVRObject3D *> vObject3D;
	vector<CVRObject2D *> vObject2D;
	CVRFont* fps;

private:
	void UpdateFps();
};
#endif