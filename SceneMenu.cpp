/***********************************************************************
*Nome: SceneMenu.cpp
*Descrição: Classe criada para apresentar o menu do jogo
*Data: 04/04/12
*Local: UNITINS
************************************************************************/

#include "SceneMenu.h"
#include "CVRManager.h"
#include "SceneConfig.h"

/***********************************************************
*Name: SceneMenu()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneMenu::SceneMenu()
{
	spr_mouse[0] = NULL;
	spr_mouse[1] = NULL;

	snd_clicks[0] = NULL;
	snd_clicks[1] = NULL;
}

/***********************************************************
*Name: ~SceneMenu()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneMenu::~SceneMenu()
{
	
}

/***********************************************************
*Name: Init()
*Description: inicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool SceneMenu::Init()
{
	//Configura o OpenGL
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	//Configura a cor do fundo
	pManager->cMainWindow.SetBackground(0,0,0);
	glClearColor(pManager->cMainWindow.r,pManager->cMainWindow.g, pManager->cMainWindow.b,0.0); 

	//Configura o colorkey
	pManager->cGraphicsManager.SetColorKey(255,0,255);

	//Criação do Sprite (MENU PRINCIPAL)
	spr_backgroundPrincipal = CreateSprite("Images\\menuPrincipal.bmp",1024,768,true);
	spr_backgroundPrincipal->SetPosX((float)(pManager->cMainWindow.lWindowWidth/2));
	spr_backgroundPrincipal->SetPosY((float)(384));
	spr_backgroundPrincipal->AddAnimation(1,true,1,0);
	spr_backgroundPrincipal->SetCurrentAnimation(0);
	spr_backgroundPrincipal->SetVisible(true);

	//Criação dos Sprites de Menus
	//Menu (Sair)
	spr_menuSair = CreateSprite("Images\\menuSair.bmp",256,64,true);
	spr_menuSair->SetPosX((float)(295));
	spr_menuSair->SetPosY((float)(695));
	spr_menuSair->AddAnimation(1,true,1,0);
	spr_menuSair->AddAnimation(1,true,1,1);
	spr_menuSair->SetCurrentAnimation(0);
	spr_menuSair->SetVisible(true);

	//Menu (Sobre)
	spr_menuSobre = CreateSprite("Images\\menuSobre.bmp",256,64,true);
	spr_menuSobre->SetPosX((float)(295));
	spr_menuSobre->SetPosY((float)(620));
	spr_menuSobre->AddAnimation(1,true,1,0);
	spr_menuSobre->AddAnimation(1,true,1,1);
	spr_menuSobre->SetCurrentAnimation(0);
	spr_menuSobre->SetVisible(true);

	//Menu (Ajuda)
	spr_menuAjuda = CreateSprite("Images\\menuAjuda.bmp",256,64,true);
	spr_menuAjuda->SetPosX((float)(295));
	spr_menuAjuda->SetPosY((float)(545));
	spr_menuAjuda->AddAnimation(1,true,1,0);
	spr_menuAjuda->AddAnimation(1,true,1,1);
	spr_menuAjuda->SetCurrentAnimation(0);
	spr_menuAjuda->SetVisible(true);

	//Menu (Configuração)
	spr_menuConfig = CreateSprite("Images\\menuConfig.bmp",256,64,true);
	spr_menuConfig->SetPosX((float)(295));
	spr_menuConfig->SetPosY((float)(470));
	spr_menuConfig->AddAnimation(1,true,1,0);
	spr_menuConfig->AddAnimation(1,true,1,1);
	spr_menuConfig->SetCurrentAnimation(0);
	spr_menuConfig->SetVisible(true);

	//Menu (Play)
	//CriaSprite(spr_menuPlay, );
	spr_menuPlay = CreateSprite("Images\\menuPlay.bmp",256,64,true);
	spr_menuPlay->SetPosX((float)(295));
	spr_menuPlay->SetPosY((float)(395));
	spr_menuPlay->AddAnimation(1,true,1,0);
	spr_menuPlay->AddAnimation(1,true,1,1);
	spr_menuPlay->SetCurrentAnimation(0);
	spr_menuPlay->SetVisible(true);



	//Cria o ponteiro do mouse
	spr_mouse[0] = CreateSprite("Images\\MouseUp.bmp",32,16,true);
	spr_mouse[0]->AddAnimation(1,true,1,0);
	spr_mouse[1] = CreateSprite("Images\\MouseDown.bmp",32,16,true);
	spr_mouse[1]->AddAnimation(1,true,1,0);
	spr_mouse[0]->SetPosXY(0,0);

	//Carrega a musica do menu
	/*pManager->cSoundManager.LoadMusic("Sounds\\soundmenu.wav");
	pManager->cSoundManager.GetMusic().SetRepeat(-1);
	pManager->cSoundManager.GetMusic().SetVolume(-600);
	pManager->cSoundManager.GetMusic().PlayMusic();*/

	//Cria os efeitos de clique
	snd_clicks[0] = pManager->cSoundManager.LoadSound("\\Sounds\\btnClick.wav");
	snd_clicks[0]->SetVolume(0);
	snd_clicks[0]->SetMaxMin(800,300);
	snd_clicks[1] = pManager->cSoundManager.LoadSound("\\Sounds\\btnOn.wav");
	snd_clicks[1]->SetVolume(0);
	snd_clicks[1]->SetMaxMin(800,300);

	//Configura a posicao da camera
	pManager->cView.SetPosition(0.0f,0.0f,0.0f);
	pManager->cView.RotY(0);

	return true;
}

//valores da seleção do MENU
int selecao = 1, selecaoAnterior = 1;


/***********************************************************
*Name: TrataMenu()
*Description: Gerencia eventos de mouse do menu
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneMenu::TrataMenu()
{

	//Para corrigir o problema da seleção sumindo
	if(selecao == 0)selecao = 1;
	if(selecao == 6)selecao = 5;

	if (pManager->cInputManager.cStdInput.KeyReleased(DIK_UP))
	{
		if (selecao > 1 && selecao <= 5) snd_clicks[1]->StopSound(); selecao--;

	}
	else if (pManager->cInputManager.cStdInput.KeyReleased(DIK_DOWN))
	{
		if (selecao > 0 && selecao <= 4) snd_clicks[1]->StopSound(); selecao++;
	}

	if(selecao != selecaoAnterior)
	{
		selecaoAnterior = selecao;
		spr_menuPlay->SetCurrentAnimation(0);
		spr_menuConfig->SetCurrentAnimation(0);
		spr_menuAjuda->SetCurrentAnimation(0);
		spr_menuSobre->SetCurrentAnimation(0);
		spr_menuSair->SetCurrentAnimation(0);
	}

	
	//Tratamento menu Sair
	if(spr_menuSair->GetQuad().Collide(spr_mouse[0]->GetQuad()))
	{
		selecao = 5;
	}
	//Tratamento menu Sobre
	else if(spr_menuSobre->GetQuad().Collide(spr_mouse[0]->GetQuad()))
	{
		selecao = 4;
	}
	//Tratamento menu Ajuda
	else if(spr_menuAjuda->GetQuad().Collide(spr_mouse[0]->GetQuad()))
	{
		selecao = 3;
	}
	//Tratamento menu Configuração
	else if(spr_menuConfig->GetQuad().Collide(spr_mouse[0]->GetQuad()))
	{
		selecao = 2;
	}
	//Tratamento menu Play
	else if(spr_menuPlay->GetQuad().Collide(spr_mouse[0]->GetQuad()))
	{
		selecao = 1;
	}

	switch(selecao){
	case 1:
		spr_menuPlay->SetCurrentAnimation(1);
		break;
	case 2:
		spr_menuConfig->SetCurrentAnimation(1);
		break;
	case 3:
		spr_menuAjuda->SetCurrentAnimation(1);
		break;
	case 4:
		spr_menuSobre->SetCurrentAnimation(1);
		break;
	 case 5: 
		 spr_menuSair->SetCurrentAnimation(1);
		 break;
	}

	//Ações
	if (pManager->cInputManager.cStdInput.MouBtnPressed(0) || pManager->cInputManager.cStdInput.KeyReleased(DIK_RETURN))
	{
		switch(selecao){
		case 1:
			snd_clicks[0]->PlaySound(); 
			this->pManager->SetCurrentScene(2);

			break;
		case 2:
			snd_clicks[0]->PlaySound();
			this->pManager->SetCurrentScene(3);
			
			break;
		case 3:
			snd_clicks[0]->PlaySound();
			this->pManager->SetCurrentScene(4);
			break;
		case 4:
			snd_clicks[0]->PlaySound();
			this->pManager->SetCurrentScene(5);
			break;
		case 5:
			snd_clicks[0]->PlaySound();
			
			pManager->Exit();
			break;
		}
	}
}


/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneMenu::Release()
{
	CVRScene::Release();
}

/***********************************************************
*Name: Execute()
*Description: executa a cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneMenu::Execute()
{
	UpdateMouse();

	TrataMenu();

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_ESCAPE))
	{
		pManager->Exit();
	}

}

/***********************************************************
*Name: UpdateMouse()
*Description: atualiza a posicao do mouse
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneMenu::UpdateMouse()
{
	spr_mouse[0]->SetPosXY(pManager->cInputManager.cStdInput.GetMousePosition().x,pManager->cInputManager.cStdInput.GetMousePosition().y);
	spr_mouse[1]->SetPosXY(pManager->cInputManager.cStdInput.GetMousePosition().x,pManager->cInputManager.cStdInput.GetMousePosition().y+16.0f);
}

/***********************************************************
*Name: UpdateMouse()
*Description: atualiza a posicao do mouse
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneMenu::CriaSprite(string nomeSprite, string ulr_HUD, int valorX, int valorY, int posX, int posY, bool visibilidade)
{
	/*
	nomeSprite = CreateSprite(ulr_HUD,valorX,valorY,true);
	nomeSprite->SetPosX((float)(posX));
	nomeSprite->SetPosY((float)(posY));
	nomeSprite->AddAnimation(1,true,1,0);
	nomeSprite->AddAnimation(1,true,1,1);
	nomeSprite->SetCurrentAnimation(0);
	nomeSprite->SetVisible(visibilidade);*/
}

