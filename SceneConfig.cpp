/***********************************************************************
*Nome: SceneConfig.cpp
*Descrição: Classe criada para exibir a tela de configuracoes
*Data: 04/04/12
*Local: CATOLICA
************************************************************************/

#include "SceneConfig.h"
#include "CVRManager.h"
#include "CVRTimer.h"
#include "CVRSprite.h"




char texto[100];
CVRSprite* spr_selecao1;
CVRSprite* spr_selecao2;
CVRSprite* spr_selecao3;



/***********************************************************
*Name: SceneConfig()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneConfig::SceneConfig()
{
	
}

/***********************************************************
*Name: ~SceneConfig()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneConfig::~SceneConfig()
{
	
}

/***********************************************************
*Name: Init()
*Description: inicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool SceneConfig::Init()
{
	//BG padrão da cena Configuração
	spr_backgroundConfig = CreateSprite("Images\\backgroundConfig.bmp",1024,768,true);
	spr_backgroundConfig->SetPosX((float)(pManager->cMainWindow.lWindowWidth/2));
	spr_backgroundConfig->SetPosY((float)(384));
	spr_backgroundConfig->AddAnimation(1,true,1,0);
	spr_backgroundConfig->SetCurrentAnimation(0);
	spr_backgroundConfig->SetVisible(true);

	//Sprite do que chama o BG para mostrar a seleção da moto.
	spr_selectMoto1 = CreateSprite("Images\\selectMoto1.bmp", 1024,768, true);
	spr_selectMoto1->SetPosX((float)(pManager->cMainWindow.lWindowWidth/2));
	spr_selectMoto1->SetPosY((float)(384));
	spr_selectMoto1->AddAnimation(1,true,1,0);
	spr_selectMoto1->SetCurrentAnimation(0);
	spr_selectMoto1->SetVisible(false);

	//Sprite do que chama o BG para mostrar a seleção da moto.
	spr_selectMoto2 = CreateSprite("Images\\selectMoto2.bmp", 1024,768, true);
	spr_selectMoto2->SetPosX((float)(pManager->cMainWindow.lWindowWidth/2));
	spr_selectMoto2->SetPosY((float)(384));
	spr_selectMoto2->AddAnimation(1,true,1,0);
	spr_selectMoto2->SetCurrentAnimation(0);
	spr_selectMoto2->SetVisible(false);

	//Sprite do que chama o BG para mostrar a seleção da moto.
	spr_selectMoto3 = CreateSprite("Images\\selectMoto3.bmp", 1024,768, true);
	spr_selectMoto3->SetPosX((float)(pManager->cMainWindow.lWindowWidth/2));
	spr_selectMoto3->SetPosY((float)(384));
	spr_selectMoto3->AddAnimation(1,true,1,0);
	spr_selectMoto3->SetCurrentAnimation(0);
	spr_selectMoto3->SetVisible(false);

	//Create OBJ da moto 0
	spr_Scooter = CreateObj("Scooter.obj","Models\\Scooter\\",true);
	spr_Scooter->SetPosition(-180, 120, -740);

	//Create OBJ da moto 1
	spr_Custom = CreateObj("Custom.obj","Models\\Custom\\",true);
	spr_Custom->SetPosition(-9110, -2680, -38260);

	//Create OBJ da moto 2
	spr_Cbr = CreateObj("Cbr.obj","Models\\Cbr\\",true);
	spr_Cbr->SetPosition(-1759, -2215, -7157);

	//Velocidade de rotação da moto
	pManager->cView.SetSpeed(500);

	//Posição da fonte que informa as cordenadas do Sprite selecionado
	posicao = CreateFont2D("POSICAO X Y Z", 30, true);
	posicao->SetPosXY(500, 200);
	posicao->bVisible = false;
	
	//Importação de sprites Transparentes para o reconhecimento da seleção.
	spr_selecao1 = CreateSprite("Images\\SelecaoMoto.bmp", 256,128, true);
	spr_selecao1->AddAnimation(15, true, 1, 7);
	spr_selecao1->SetPosXY(212,237);
	spr_selecao1->SetCurrentAnimation(0);
	spr_selecao1->SetVisible(false);

	//Importação de sprites Transparentes para o reconhecimento da seleção.
	spr_selecao2 = CreateSprite("Images\\SelecaoMoto.bmp", 256,128, true);
	spr_selecao2->AddAnimation(15, true, 1, 7);
	spr_selecao2->SetPosXY(212,448);
	spr_selecao2->SetCurrentAnimation(0);
	spr_selecao2->SetVisible(false);

	//Importação de sprites Transparentes para o reconhecimento da seleção.
	spr_selecao3 = CreateSprite("Images\\SelecaoMoto.bmp", 256,128, true);
	spr_selecao3->AddAnimation(15, true, 1,7);
	spr_selecao3->SetPosXY(212,661);
	spr_selecao3->SetCurrentAnimation(0);
	spr_selecao3->SetVisible(false);

	fAngle = 0;

	//Sprite do mouse que é criado na cena Config
	spr_mouse[0] = CreateSprite("Images\\MouseUp.bmp",32,16,true);
	spr_mouse[0]->AddAnimation(1,true,1,0);
	spr_mouse[1] = CreateSprite("Images\\MouseDown.bmp",32,16,true);
	spr_mouse[1]->AddAnimation(1,true,1,0);
	spr_mouse[0]->SetPosXY(0,0);

	return true;
}

/***********************************************************
*Name: UpdateMouse()
*Description: atualiza a posicao do mouse
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneConfig::UpdateMouse()
{
	spr_mouse[0]->SetPosXY(pManager->cInputManager.cStdInput.GetMousePosition().x,pManager->cInputManager.cStdInput.GetMousePosition().y);
	spr_mouse[1]->SetPosXY(pManager->cInputManager.cStdInput.GetMousePosition().x,pManager->cInputManager.cStdInput.GetMousePosition().y+16.0f);
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneConfig::Release()
{
	CVRScene::Release();
}


/***********************************************************
*Name: Execute()
*Description: executa a cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneConfig::Execute()
{
	//Pra movimentar o Sprite
	MovimentaSprite(spr_selecao1);

	if (pManager->cInputManager.cStdInput.KeyReleased(DIK_ESCAPE))
	{
		pManager->SetCurrentScene(1);
		return;
	}

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_UP))
	{
		spr_Cbr->vPos.z-= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_DOWN))
	{
		spr_Cbr->vPos.z+= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_LEFT))
	{
		spr_Cbr->vPos.x-= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_RIGHT))
	{
		spr_Cbr->vPos.x+= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_HOME))
	{
		spr_Cbr->vPos.y+= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_END))
	{
		spr_Cbr->vPos.y-= 1;
	}	

	//sprintf(texto,"%.2f %0.2f %2f", spr_Cbr->vPos.x, spr_Cbr->vPos.y, spr_Cbr->vPos.z);

	spr_Scooter->RotY(spr_Scooter->GetAngle().GetY() + 1);
	spr_Custom->RotY(spr_Custom->GetAngle().GetY() + 1);
	spr_Cbr->RotY(spr_Cbr->GetAngle().GetY() + 1);
	
	pManager->cView.RotY(fAngle);

	TrataConfig();

	UpdateMouse();
}

int selecaoMoto = 1, selecaoMotoAnterior = 1;//Declaração da variável selecao e selecao anterior

/***********************************************************
*Name: TrataConfig()
*Description: Gerencia eventos de mouse da cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneConfig::TrataConfig()
{
	//para corrigir o problema do seletor sumir
	if(selecaoMoto == 0)selecaoMoto = 1;
	if(selecaoMoto == 4)selecaoMoto = 3;

	if (pManager->cInputManager.cStdInput.KeyReleased(DIK_UP))
	{
		if (selecaoMoto >= 1 && selecaoMoto <= 3) selecaoMoto--;

	}
	else if (pManager->cInputManager.cStdInput.KeyReleased(DIK_DOWN))
	{
		if (selecaoMoto >= 0 && selecaoMoto <= 3) selecaoMoto++;
	}

	if(selecaoMoto != selecaoMotoAnterior)
	{
		selecaoMotoAnterior = selecaoMoto;
		spr_selecao1->SetVisible(false);
		spr_selecao2->SetVisible(false);
		spr_selecao3->SetVisible(false);
		spr_selectMoto1->SetVisible(false);
		spr_selectMoto2->SetVisible(false);
		spr_selectMoto3->SetVisible(false);
	}

	//Tratamento da seleção 01
	if(spr_selecao1->GetQuad().Collide(spr_mouse[0]->GetQuad()))
	{
		selecaoMoto = 1;
	}
	//Tratamento da seleção 02
	else if(spr_selecao2->GetQuad().Collide(spr_mouse[0]->GetQuad()))
	{
		selecaoMoto = 2;
	}
	//Tratamento da seleção 03
	else if(spr_selecao3->GetQuad().Collide(spr_mouse[0]->GetQuad()))
	{
		selecaoMoto = 3;
	}

	//Switch que ativa a animação da seleção 
	switch(selecaoMoto){
	case 1:
		spr_selecao1->SetVisible(false);
		spr_selectMoto1->SetVisible(true);
		break;
	case 2:
		spr_selecao2->SetVisible(false);
		spr_selectMoto2->SetVisible(true);
		break;
	case 3:
		spr_selecao3->SetVisible(false);
		spr_selectMoto3->SetVisible(true);
		break;
	}

	//Ações (Caso selecionado, irá modificar a moto padrão)
	if (pManager->cInputManager.cStdInput.MouBtnPressed(0) || pManager->cInputManager.cStdInput.KeyReleased(DIK_RETURN))
	{
		switch(selecaoMoto){
		case 1:
			spr_selecao1->SetVisible(false);
			spr_selectMoto1->SetVisible(true);
			//ação da seleção moto 1
			*vrMotoSelecao = 0;
			this->pManager->SetCurrentScene(2);
			break;
		case 2:
			spr_selecao2->SetVisible(false);
			spr_selectMoto2->SetVisible(true);
			//ação da seleçao moto 2	
			*vrMotoSelecao = 1;
			this->pManager->SetCurrentScene(2);
			break;
		case 3:
			spr_selecao3->SetVisible(false);
			spr_selectMoto3->SetVisible(true);
			//ação da seleção moto 3
			*vrMotoSelecao = 2;
			this->pManager->SetCurrentScene(2);
			break;
		}
	}
	sprintf(texto,"%d",*vrMotoSelecao);
	posicao->SetText(texto);

}


/***********************************************************
*Name: MovimentaSprite() 
*Description: utilizado para o posicionamento de Sprites
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneConfig::MovimentaSprite(CVRSprite* sprite)
{
	posicao->bVisible = true;

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_W))
	{
		sprite->fPosY-=1.0;
	}

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_A))
	{
		sprite->fPosX-=1.0;
	}

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_D))
	{
		sprite->fPosX+=1.0;
	}

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_X))
	{
		sprite->fPosY+=1.0;
	}

	sprintf(texto,"%.2f %0.2f %2f %.2f", sprite->fPosX, sprite->fPosY);
	posicao->SetText(texto);
}
