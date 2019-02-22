/***********************************************************************
*Nome: SceneSobre.cpp
*Descrição: Classe criada para apresentar a Cena Sobre
*Data: 12/02/19
*Local: FACTO
************************************************************************/

#include "SceneSobre.h"
#include "CVRManager.h"
#include "CVRSprite.h"

/***********************************************************
*Name: SceneSobre()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneSobre::SceneSobre()
{
	
}

/***********************************************************
*Name: ~SceneSobre()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneSobre::~SceneSobre()
{
	
}

/***********************************************************
*Name: Init()
*Description: inicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool SceneSobre::Init()
{
	//Criação do Sprite (SOBRE)
	spr_backgroundSobre = CreateSprite("Images\\backgroundSobre.bmp",1024,768,true);
	spr_backgroundSobre->SetPosX((float)(pManager->cMainWindow.lWindowWidth/2));
	spr_backgroundSobre->SetPosY((float)(384));
	spr_backgroundSobre->AddAnimation(1,true,1,0);
	spr_backgroundSobre->SetCurrentAnimation(0);
	spr_backgroundSobre->SetVisible(true);
	
	//Cria o ponteiro do mouse
	spr_mouse[0] = CreateSprite("Images\\MouseUp.bmp",32,16,true);
	spr_mouse[0]->AddAnimation(1,true,1,0);
	spr_mouse[1] = CreateSprite("Images\\MouseDown.bmp",32,16,true);
	spr_mouse[1]->AddAnimation(1,true,1,0);
	spr_mouse[0]->SetPosXY(0,0);

	return true;
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneSobre::Release()
{
	CVRScene::Release();
}

/***********************************************************
*Name: Execute()
*Description: executa a cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneSobre::Execute()
{
	UpdateMouse();

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_ESCAPE))
	{
		pManager->SetCurrentScene(0);
		return;
	}


}

/***********************************************************
*Name: UpdateMouse()
*Description: atualiza a posicao do mouse
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneSobre::UpdateMouse()
{
	spr_mouse[0]->SetPosXY(pManager->cInputManager.cStdInput.GetMousePosition().x,pManager->cInputManager.cStdInput.GetMousePosition().y);
	spr_mouse[1]->SetPosXY(pManager->cInputManager.cStdInput.GetMousePosition().x,pManager->cInputManager.cStdInput.GetMousePosition().y+16.0f);
}


