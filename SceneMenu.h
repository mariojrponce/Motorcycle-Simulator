/***********************************************************************
*Nome: SceneMenu
*Descrição: Classe criada para apresentar o menu do jogo
*Data: 04/04/12
*Local: UNITINS
************************************************************************/
#ifndef _SCENEMENU_
#define _SCENEMENU_

#include "CVRScene.h"

#define QTDBUTTONS 4

class SceneMenu: public CVRScene
{
public:
	SceneMenu();
	~SceneMenu();
	void Release();
	void Execute();
	bool Init();
	void UpdateMouse();
	void TrataMenu();
	void CriaSprite(string nomeSprite, string ulr_HUD, int valorX, int valorY, int posX, int posY, bool visibilidade);
private:
	CVRSprite* spr_mouse[2];
	CVRSprite* spr_backgroundPrincipal;
	CVRSprite* spr_menuSair;
	CVRSprite* spr_menuSobre;
	CVRSprite* spr_menuAjuda;
	CVRSprite* spr_menuConfig;
	CVRSprite* spr_menuPlay;
	CVRSound* snd_clicks[2];

};
#endif
