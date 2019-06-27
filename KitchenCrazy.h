/***********************************************************************
*Nome: KitchenCrazy
*Descrição: Classe criada para testar uma cena
*Data: 31/07/07
*Local: LNCC
************************************************************************/
#ifndef _KCRAZY_
#define _KCRAZY_

#include "CVRScene.h"
#include <wiiuse.h>

class KitchenCrazy: public CVRScene
{
public:
	KitchenCrazy();
	~KitchenCrazy();
	void Release();
	void Execute();
	bool Init();
	void HandleKeyboard();
	void HandleWiiMote();
	void SetWiiMotes(wiimote**);
private:
	CVRSprite* prCursor;
	wiimote** prWiiMotes;
	CVRSkyBox* skyBox;
	CVRTerrain* terrain;
	unsigned int uX;
	unsigned int uY;
};
#endif