/***********************************************************************
*Nome: KinectGame
*Descrição: Classe criada para implementar o o Jogo com Kinect
*Data: 04/04/12
*Local: UNITINS
************************************************************************/
#ifndef _KINECTGAME_
#define _KINECTGAME_

//Bibliotecas utilizadas
#include "CVRScene.h"
#include "CVRTimer.h"
//#include <NuiApi.h>

//Definições da classe
#define NUM_SKELETONS 1
#define NUM_COINS 20

class KinectGame: public CVRScene
{
public:
	KinectGame();
	~KinectGame();
	bool Init();
	void Execute();
	void Release();
	void InitKinect();
	void UpdateKinect();
	void Load2DAssets();
	void HandleCollision();
	void UpdateSprites();
private:
	CVRSound* snd_clicks[3];
	CVRTimer* vrGameTime;
	CVRFont* timeFont;
	CVRFont* pointsFont;
	CVRSprite* sprBord;
	CVRSprite* vetSprite[NUM_COINS];
	CVRSprite* vetJoins[1][20];
	INuiSensor * pNuiSensor;
	HANDLE m_hNextSkeletonEvent;
	int iSensorCount;
	int iTotalPoints;
	int iIncPoints;
	int iCountSeconds;
};
#endif