/***********************************************************************
*Nome: SceneAjuda.cpp
*Descrição: Classe criada para apresentar a Cena Ajuda
*Data: 06/03/19
*Local: PALMAS-TO
************************************************************************/

#include "SceneAjuda.h"
#include "CVRManager.h"

/***********************************************************
*Name: SceneAjuda()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneAjuda::SceneAjuda()
{
	
}

/***********************************************************
*Name: ~SceneAjuda()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneAjuda::~SceneAjuda()
{
	
}

/***********************************************************
*Name: Init()
*Description: inicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool SceneAjuda::Init()
{

	//Criação do Sprite (AJUDA BG)
	spr_backgroundAjuda = CreateSprite("Images\\backgroundAjuda8.bmp",1024,768,true);
	spr_backgroundAjuda->SetPosX((float)(pManager->cMainWindow.lWindowWidth/2));
	spr_backgroundAjuda->SetPosY((float)(384));
	spr_backgroundAjuda->AddAnimation(1,true,1,0);
	spr_backgroundAjuda->SetCurrentAnimation(0);
	spr_backgroundAjuda->SetVisible(true);


	//Criação do botão voltar
	spr_menuVoltar = CreateSprite("Images\\menuVoltarOk.bmp",256,64,true);
	spr_menuVoltar->SetPosX((float)(500));
	spr_menuVoltar->SetPosY((float)(630));
	spr_menuVoltar->AddAnimation(1,true,1,0);
	spr_menuVoltar->AddAnimation(1,true,1,1);
	spr_menuVoltar->SetCurrentAnimation(0);
	spr_menuVoltar->SetVisible(true);

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
void SceneAjuda::Release()
{
	CVRScene::Release();
}

/***********************************************************
*Name: Execute()
*Description: executa a cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneAjuda::Execute()
{
	UpdateMouse();//Chama o update do mouse na cena Ajuda.

	//Ao precionar a tecla ESC a cena é alterada para o Menu
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
void SceneAjuda::UpdateMouse()
{
	spr_mouse[0]->SetPosXY(pManager->cInputManager.cStdInput.GetMousePosition().x,pManager->cInputManager.cStdInput.GetMousePosition().y);
	spr_mouse[1]->SetPosXY(pManager->cInputManager.cStdInput.GetMousePosition().x,pManager->cInputManager.cStdInput.GetMousePosition().y+16.0f);
}