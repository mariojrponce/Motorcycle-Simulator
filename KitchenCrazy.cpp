/***********************************************************************
*Nome: KitchenCrazy.cpp
*Descrição: Classe criada para testar uma cena
*Data: 31/07/07
*Local: LNCC
************************************************************************/
#include "KitchenCrazy.h"
#include "CVRManager.h"

//Definiçao que cria uma referencia para o teclado
#define KEYBOARD pManager->cInputManager.cStdInput
#define QTDCONTROLES 2

//Variável temporária global para armazenar as coordenadas do IR
char coords[100];
char coords2[100];
int iX1 = 0, iX2 = 0;
/***********************************************************
*Name: KitchenCrazy()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
KitchenCrazy::KitchenCrazy()
{
	prWiiMotes = NULL;
	prCursor = NULL;
}

/***********************************************************
*Name: ~KitchenCrazy()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
KitchenCrazy::~KitchenCrazy()
{
	
}

/***********************************************************
*Name: Init()
*Description: inicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool KitchenCrazy::Init()
{
	//Configura o OpenGL
	glClearColor(0.0f,0.0f,0.0f,0.5f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	//Configura a cor do colorkey
	pManager->cGraphicsManager.SetColorKey(255,0,255);

	//Habilita o sensoriamento se controle 1 habilitado
	if (prWiiMotes[0])
	{
		//Habilita o rastremento do infravermelho
		wiiuse_set_ir(prWiiMotes[0],1);
	}
	//Habilita o sensoriamento se controle 2 abilitado
	if (prWiiMotes[1])
	{
		//Habilita o rastremento do infravermelho
		wiiuse_set_ir(prWiiMotes[1],1);
	}
	
	//Cria o sprite do cursor
	prCursor = this->CreateSprite("Images\\cursor.bmp",128,128,true);
	prCursor->SetPosX(336.0f);
	prCursor->SetPosY(236.0f);
	prCursor->AddAnimation(1,true,1,0);
	prCursor->SetCurrentAnimation(0);

	//Cria a caixa que representa o céu
	skyBox = CreateSkyBox(true);
	skyBox->SetCenterBox(3200,0.0f,-3200);
	skyBox->SetBoxSize(6400,5000,6400);
	skyBox->SetLeftTexture("Images\\left2.bmp");
	skyBox->SetRightTexture("Images\\right2.bmp");
	skyBox->SetUpTexture("Images\\up2.bmp");
	skyBox->SetFrontTexture("Images\\front2.bmp");
	skyBox->SetBackTexture("Images\\back2.bmp");
	skyBox->bDrawGround = false;

	//Habilita o acelerometro
	wiiuse_motion_sensing(prWiiMotes[0], 1);
	//wiiuse_set_aspect_ratio(prWiiMotes[0], WIIUSE_ASPECT_16_9 );

	wiiuse_motion_sensing(prWiiMotes[1], 1);
	//wiiuse_set_aspect_ratio(prWiiMotes[1], WIIUSE_ASPECT_16_9 );

	//Configura a posição da câmera
	pManager->cView.SetPositionX(200);
	pManager->cView.SetPositionZ(-200);
	pManager->cView.SetPositionY(300);

	//Cria o objeto do terreno
	terrain = CreateBmpTerrain("Images\\terrain.bmp","Images\\ground2.bmp",100.0f,true);

	//Inicializa a posicao do cursor
	uX = 730;
	uY = 430;

	//Init finalizado com sucesso
	return true;
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KitchenCrazy::Release()
{
	CVRScene::Release();
}

/***********************************************************
*Name: Execute()
*Description: executa a cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KitchenCrazy::Execute()
{
	HandleWiiMote();
	HandleKeyboard();
}

/***********************************************************
*Name: SetWiimotes()
*Description: configura o ponteiro para o WiiMote
*Params: wiimote**
*Return: Nenhum
************************************************************/
void KitchenCrazy::SetWiiMotes(wiimote** pWiiMotes)
{
	prWiiMotes = pWiiMotes;
}

/***********************************************************
*Name: HandleWiiMotes()
*Description: realiza a verificação do dispositivo e trata eventos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KitchenCrazy::HandleWiiMote()
{	
	//Executa o pooling na pilha de eventos e retorna caso nada tenha sido feito
	if (!wiiuse_poll(prWiiMotes, QTDCONTROLES))
		return;

	//GAMBIRA
	for (int iIndex=0; iIndex<QTDCONTROLES; iIndex++)
	{
		//Se controle não existe ou não tem eventos continua
		if (!prWiiMotes[iIndex] || prWiiMotes[iIndex]->event == WIIUSE_NONE)
			continue;

		//Caso exista evento, testa para ver qual é
		switch (prWiiMotes[iIndex]->event)  
		{
			//Caso seja do tipo evento varre os eventos
			case WIIUSE_EVENT:
			{
				//Se botao home pressionado volta
				if (IS_RELEASED(prWiiMotes[iIndex], WIIMOTE_BUTTON_HOME))	
				{	
					pManager->SetCurrentScene(1); 
					return;
				}

				//Confere as coords do IR
				if (prWiiMotes[iIndex]->ir.dot[0].visible) 
				{
					prCursor->SetPosXY((((int)prWiiMotes[iIndex]->ir.dot[0].x - 64)) , (((int)prWiiMotes[iIndex]->ir.dot[0].y - 64)));
				}
			}
		}
	}
}

/***********************************************************
*Name: HandleKeyboard()
*Description: trata eventos do teclado
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KitchenCrazy::HandleKeyboard()
{
	if (KEYBOARD.KeyPressed(DIK_ESCAPE))
	{
		pManager->SetCurrentScene(1);
		return;
	}
	if (KEYBOARD.KeyDown(DIK_UP))
	{
		pManager->cView.MoveForward();
	}
	if (KEYBOARD.KeyDown(DIK_DOWN))
	{
		pManager->cView.MoveBackward();
	}
	if (KEYBOARD.KeyDown(DIK_RIGHT))
	{
		pManager->cView.RotY(pManager->cView.GetAngleY()+0.3f);
	}
	if (KEYBOARD.KeyDown(DIK_LEFT))
	{
		pManager->cView.RotY(pManager->cView.GetAngleY()-0.5f);
	}
	if (KEYBOARD.KeyDown(DIK_Z))
	{
		pManager->cView.MoveLeft();
	}
	if (KEYBOARD.KeyDown(DIK_X))
	{
		pManager->cView.MoveRight();
	}
	if (KEYBOARD.KeyDown(DIK_HOME))
	{
		pManager->cView.SetPositionY(pManager->cView.GetPositionY()+0.3f);
	}
	if (KEYBOARD.KeyDown(DIK_END))
	{
		pManager->cView.SetPositionY(pManager->cView.GetPositionY()-0.3f);
	}
}