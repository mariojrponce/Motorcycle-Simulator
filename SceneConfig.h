/***********************************************************************
*Nome: SceneConfig
*Descrição: Classe criada para implementar as configuracoes do simulador
*Data: 04/04/12
*Local: UNITINS
************************************************************************/
#ifndef _SCENECONFIG_
#define _SCENECONFIG_


#include "CVRScene.h"
#include "CVRObjLoader.h"
#include "CVRFont.h"



class SceneConfig: public CVRScene
{
public:
	SceneConfig();
	~SceneConfig();
	void Release();
	void Execute();
	bool Init();
	void UpdateMouse();
	void TrataConfig();
	void MovimentaSprite(CVRSprite*);

	//Ponteiros sao o inferno, mas resolvem
	int* vrMotoSelecao;

	
private:
	CVRSprite* spr_backgroundConfig;
	CVRSprite* spr_selectMoto1;
	CVRSprite* spr_selectMoto2;
	CVRSprite* spr_selectMoto3;
	CVRObjLoader* spr_Scooter;
	CVRObjLoader* spr_Custom;
	CVRObjLoader* spr_Cbr;
	float fAngle;
	CVRFont* posicao;
	CVRSprite* spr_mouse[2];
	
};
#endif