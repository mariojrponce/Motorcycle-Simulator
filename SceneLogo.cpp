/***********************************************************************
*Nome: SceneLogo.cpp
*Descrição: Classe criada para exibir o LOGO da Catolica
*Data: 04/04/12
*Local: UNITINS
************************************************************************/

#include "SceneLogo.h"
#include "CVRManager.h"
#include "CVRTimer.h"

//Variável global do tipo CTimer
CVRTimer timerLogo;

/***********************************************************
*Name: SceneLogo()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneLogo::SceneLogo()
{
	iFadeState = 0;
	sprCatolicaLogo = NULL;
}

/***********************************************************
*Name: ~SceneLogo()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneLogo::~SceneLogo()
{
	
}

/***********************************************************
*Name: Init()
*Description: inicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool SceneLogo::Init()
{
	//Inicialização do timer
	timerLogo.Init(&pManager->cTimeManager);
	timerLogo.ResetTime(3000);

	//Configura a cor do fundo
	pManager->cMainWindow.SetBackground(255,255,255);
	glClearColor(255,255,255,0.0);
	
	//Colorkey preto
	pManager->cGraphicsManager.SetColorKey(0,0,0);

	//Criação do Sprite
	sprCatolicaLogo = CreateSprite("Images\\LogoCatolica.bmp",512,128,true);
	sprCatolicaLogo->SetPosX((float)(pManager->cMainWindow.lWindowWidth/2));
	sprCatolicaLogo->SetPosY((float)(pManager->cMainWindow.lWindowHeight/2));
	sprCatolicaLogo->AddAnimation(1,true,1,0);
	sprCatolicaLogo->SetCurrentAnimation(0);
	sprCatolicaLogo->SetVisible(false);

	return true;
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneLogo::Release()
{
	CVRScene::Release();
}

/***********************************************************
*Name: Execute()
*Description: executa a cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneLogo::Execute()
{
	//Aguarda um tempo até o modo fullscreen ser configurado
	if (!timerLogo.TimerEnded())
	{
		timerLogo.Update();
		return;
	}

	//Fade in do LOGO
	if (iFadeState == 0)
	{
		sprCatolicaLogo->SetVisible(true);
		sprCatolicaLogo->FadeIn(2000);
		iFadeState++;

	}
	else if (iFadeState == 1)
	{
		if (sprCatolicaLogo->FadeEnded())
		{
			sprCatolicaLogo->FadeOut(2000);
			iFadeState++;
		}
	}
	else if (iFadeState == 2)
	{
		if (sprCatolicaLogo->FadeEnded())
		{
			pManager->SetCurrentScene(1);
			return;
		}
	}
}