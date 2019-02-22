/***********************************************************************
*Nome: SceneGame.cpp
*Descrição: Classe criada para implementar o cenário virtual da simulação
*Data: 04/04/12
*Local: UNITINS
************************************************************************/
#include "SceneGame.h"
#include "CVRManager.h"
#include "CVRSprite.h"
#include "CVRLoadingBar.h"

#include "SceneConfig.h"




char textob[100];
float fScale = 1.0;
float velocidade = 0.0f;//Define a velocidade padrão da Moto recebe 0
float km = 0.0f;
float direcionamento = 0.0f;//Define o direcionamento padrão da moto. Recebe o valor de 0

/***********************************************************w
*Name: SceneGame()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneGame::SceneGame()
{
	
}

/***********************************************************
*Name: ~SceneGame()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
SceneGame::~SceneGame()
{
	
}

void SceneGame::Render()
{
	CVRScene::Render();
	glPushMatrix();
		glLoadIdentity();
		glRotatef(direcionamento,0,0,1);//Direcionamento em rotação Z da moto. Forçadamente. Feito pelo Silvano.
		spr_Motorcycle->Render();
	glPopMatrix();
}

/***********************************************************
*Name: SetMotoModel()
*Description: configura a visualizacao da moto escolhida
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneGame::SetMotoModel(int motoModel)
{
	switch(motoModel)
	{
		case 0:
			spr_Motorcycle =  CreateObj("Scooter.obj","Models\\Scooter\\",false);
			spr_Motorcycle->SetPosition(0, -37, -64);
			spr_Motorcycle->SetScale(0.62,0.62,0.62);
			spr_Motorcycle->RotY(-90);
		break;

		case 1:
			spr_Motorcycle =  CreateObj("Custom.obj","Models\\Custom\\",false);
			spr_Motorcycle->SetPosition(-6, -313, -658);
			spr_Motorcycle->SetScale(0.09,0.09,0.09);
			spr_Motorcycle->RotY(-90);
		break;

		case 2:
			spr_Motorcycle =  CreateObj("Cbr.obj","Models\\Cbr\\",false);
			spr_Motorcycle->SetPosition(-8, -253, -443);
			spr_Motorcycle->SetScale(0.41,0.41,0.41);
			spr_Motorcycle->RotY(-90);
		break;
	}
	
}


/***********************************************************
*Name: Init()
*Description: inicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool SceneGame::Init()
{

	//Configura o OpenGL
	glClearColor(10.0f,50.0f,50.0f,100.5f);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	//Configura a cor do colorkey
	pManager->cGraphicsManager.SetColorKey(255,0,255);

	CreateObj("city_tex_night.obj","Models\\cidade\\",true);

	pManager->cView.SetSpeed(3000);
	pManager->cView.SetPositionY(-2000);


	//Sprite do Painel digital - Serva de base para icones de seta, farol, bateria.
	spritePainelDigital = CreateSprite("Images\\painelDigital.bmp", 256, 256, true);
	spritePainelDigital->AddAnimation(1, true, 1,1);
	spritePainelDigital->SetPosXY(3438,3492);
	spritePainelDigital->SetScaleXY(0.25,0.2);


	//Sprite velocimetro - Base  
	spriteVelocimetro = CreateSprite("Images\\velocimetro.bmp", 128,128,true);
	spriteVelocimetro->AddAnimation(1, true, 1, 0);
	spriteVelocimetro->SetCurrentAnimation(0);
	spriteVelocimetro->SetPosXY(859,609);

	
	//Sprite AGULHA do velocimetro
	spriteAgulhaVelo = CreateSprite("Images\\agulha.bmp", 32,128,true);
	spriteAgulhaVelo->AddAnimation(1, true, 1, 0);
	spriteAgulhaVelo->SetPosXY(859,609); //Mesma posição da BASE. OK
	spriteAgulhaVelo->fAngle = -150;//A agulha move 1,25 a cada 1kmh
	

	//Sprite contaGiros - BASE
	spriteGiros = CreateSprite("Images\\contaGiros.bmp", 128,128,true);
	spriteGiros->AddAnimation(1, true, 1, 0);
	spriteGiros->SetPosXY(782, 687);
	

	//Sprite AGULHA do contaGiros
	spriteAgulhaGiros = CreateSprite("Images\\agulha.bmp", 32,128,true);
	spriteAgulhaGiros->AddAnimation(1, true, 1, 0);
	spriteAgulhaGiros->SetPosXY(1305, 1146); //Posições diferentes da base. 
	spriteAgulhaGiros->SetScaleXY(0.6,0.6);
	spriteAgulhaGiros->fAngle = -145;//Angulo da agulha do conta giros


	//Sprite das marchas - NUMEROS
	spriteMarchas = CreateSprite("Images\\numeroMarchas.bmp", 32,32, true);
	spriteMarchas->AddAnimation(0, true, 7, 0,1,2,3,4,5,6);
	spriteMarchas->SetCurrentAnimation(0);
	spriteMarchas->SetPosXY(863,644);

	
	//Sprite dos LEDs indicadores (Vermelho) - Quando o conta giros atigir a velocidade máxima, o led acende.
	spriteLedsVermelho = CreateSprite("Images\\luzesIndicadoras.bmp", 16,16, true);
	spriteLedsVermelho->AddAnimation(1, true, 2, 0,1);
	spriteLedsVermelho->SetPosXY(812, 682);


	//Sprite do combustível - BASE
	spriteCombustivel = CreateSprite("Images\\combustivel.bmp", 128,128, true);
	spriteCombustivel->AddAnimation(1, true, 1, 0);
	spriteCombustivel->SetPosXY(940, 687);


	//Sprite AGULHA do combustível
	spriteAgulhaCombu = CreateSprite("Images\\agulha.bmp", 32,128,true);
	spriteAgulhaCombu->AddAnimation(1, true, 1,0);
	spriteAgulhaCombu->SetPosXY(1563,1147); //Posição diferente da BASE.
	spriteAgulhaCombu->SetScaleXY(0.6,0.6);


	//Sprite do icone de combustível
	spriteIconeCombu = CreateSprite("Images\\iconeCombustivel.bmp", 32,32,true);
	spriteIconeCombu->AddAnimation(1, true, 2, 0,1);
	spriteIconeCombu->SetPosXY(912, 696);


	//Sprite seta Esquerda 
	spriteSetaEsq = CreateSprite("Images\\iconeSetaEsquerda.bmp", 16,16, true);
	spriteSetaEsq->AddAnimation(1, true, 2, 0,1);
	spriteSetaEsq->SetPosXY(843, 683);


	//Sprite seta Direita
	spriteSetaDir = CreateSprite("Images\\iconeSetaDireita.bmp", 16,16, true);
	spriteSetaDir->AddAnimation(1, true, 2, 0,1);
	spriteSetaDir->SetPosXY(875, 683);


	//Sprite de farol baixo
	spriteFarolBaixo = CreateSprite("Images\\farolBaixo.bmp", 16,16, true);
	spriteFarolBaixo->AddAnimation(1, true, 2, 0,1);
	spriteFarolBaixo->SetPosXY(844, 698);


	//Sprite de fatol alto 
	spriteFarolAlto = CreateSprite("Images\\farolAlto.bmp", 16,16, true);
	spriteFarolAlto->AddAnimation(1, true, 2, 0,1);
	spriteFarolAlto->SetPosXY(874, 698);


	//Sprite do ICONE BATERIA 
	spriteIconeBateria = CreateSprite("Images\\iconeBateria.bmp", 16,16, true);
	spriteIconeBateria->AddAnimation(1, true, 2, 0,1);
	spriteIconeBateria->SetPosXY(859, 713);

	//Angulo da camera
	fAngle = 0;

	//Seleciona o modelo da moto
	SetMotoModel(0);
	

	//Posicionamento do modelo Selecionado da moto.
	/*
	spr_Scooter =  CreateObj("Custom.obj","Models\\Custom\\",false);
	spr_Scooter->SetPosition(-70, -1245, -2325);
	spr_Scooter->SetScale(0.6, 0.6, 0.6);
	*/

	posicao = CreateFont2D("POSICAO X Y Z", 30, true);
	posicao->SetPosXY(500, 200);
	posicao->bVisible = false;

	//Carrega o som
	listener = GetListener();
	sound = LoadSound("\\Sounds\\motoLigadaEspera.wav");
	sound->SetRepeat(-1);
	sound->PlaySound(); 



	//Fim do método de carregamento
	return true;
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneGame::Release()
{
	CVRScene::Release();
}

/***********************************************************
*Name: MovimentaMoto()
*Description: Movimentos direcionais da moto.
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneGame::MovimentaMoto()
{
	//Define a velocidade da moto
	km = velocidade * 8.25f; 

	//spriteMarchas->SetCurrentAnimation(0);

	//Rotaciona a agulha conforme a velocidade da camera
	//spriteAgulhaVelo->fAngle = -150 + (velocidade*10.0f);
	spriteAgulhaVelo->fAngle = -150 + (km*1.2f);

	//Rotaciona a agulha do CONTA GIROS conforme a velocidade
	spriteAgulhaGiros->fAngle = -145 + (velocidade*20.0f);


	//Se a tecla Up for apertada, ele entre nesta função
	if (pManager->cInputManager.cStdInput.KeyDown(DIK_UP))
	{
		//Se a velocidade for menor que 20float, velocidade recebe 0.04f a cada frame
		if(velocidade < 20.0f) velocidade += 0.03f;//Valor de aceleração
		pManager->cView.Move(velocidade);

	}
	//Se a tecla for solta, e a velocidade maior que 0.0f, ele recebe a definição abaixo
	else if(velocidade > 0.0f) 
	{
		velocidade -= 0.02f;//Valor de desaceleração

		pManager->cView.Move(velocidade);//Recebe como parametro a variavel velocidade
	}

	//Se a tecla DOWN for precionada 
	if (pManager->cInputManager.cStdInput.KeyDown(DIK_DOWN))
	{
		if(velocidade > 0.0f)velocidade -= 0.1f;//A vocidade maior que 0 recebe velocidade - 0.1 a cada frame
		if(velocidade <= 0.0f) pManager->cView.Move(-0.2f);//Se a velocidade for menor que 0 ou igual, é passado como parametro -0.2f.
	}	
	else if(velocidade < 0.0f) velocidade = 0.0f;//Se a velocidade for menor que 0, velocidade recebe 0.0f

	//Se a tecla indicadora para esquerda for precionada, a moto virará para esquerda.
	if (pManager->cInputManager.cStdInput.KeyDown(DIK_LEFT))
	{
		fAngle-=0.8;//Movimenta a câmera

		direcionamento += 0.4f;//a cada frame adiociona 0.5 na rotação esquerda da moto

		if (direcionamento > 20.0f)
		{
			direcionamento = 20.0f;
		}

	}	
	//Se não se, a moto retornará a posição 0
	else if (direcionamento > 0.0f)
	{
		direcionamento -= 0.8f;
		
		if (direcionamento < 0.0f)
		{
			direcionamento = 0.0f;
		}
	}

	//Se a tecla indicaroa para direita for precionada, a moto virará para direita. 
	if (pManager->cInputManager.cStdInput.KeyDown(DIK_RIGHT))
	{
		fAngle+=0.8;//Movimenta a câmera

		direcionamento -= 0.4f;//a cada frame adiociona 0.5 na rotação direita da moto

		if (direcionamento < -20.0f)
		{
			direcionamento = -20.0f;
		}

	}

	//Se não se, ela retornará a posição 0
	else if (direcionamento < 0.0f)
	{
		direcionamento += 0.8f;

		if (direcionamento > 0.0f)
		{
			direcionamento = 0.0f;
		}
	}
	

	
	//SE A TECLA ESC FOR PRECIONADA, SAI DA CENA GAME. 
	if (pManager->cInputManager.cStdInput.KeyReleased(DIK_ESCAPE))
	{
		pManager->SetCurrentScene(1);
		sound->StopSound();//Pausa o som da moto
		return;
	}

	pManager->cView.RotY(fAngle);
}

/***********************************************************
*Name: Execute()
*Description: executa a cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneGame::Execute()
{
	MovimentaMoto();


	//****************************MARIO - USE ESTE COMANDO PARA TESTAR E POSICIONAR O SPRITE NA TELA ATRAVES DAS TECLAS (A, W, D, X) PARA MOVIMENTAR
	MovimentaSprite(spriteIconeBateria);

	//Movimentar o modelo da moto.
	/*
	if (pManager->cInputManager.cStdInput.KeyDown(DIK_UP))
	{
		spr_Scooter->vPos.z-= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_DOWN))
	{
		spr_Scooter->vPos.z+= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_LEFT))
	{
		spr_Scooter->vPos.x-= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_RIGHT))
	{
		spr_Scooter->vPos.x+= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_HOME))
	{
		spr_Scooter->vPos.y+= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_END))
	{
		spr_Scooter->vPos.y-= 1;
	}	

	if (pManager->cInputManager.cStdInput.KeyPressed(DIK_ESCAPE))
	{
		pManager->SetCurrentScene(1);
		return;
	}

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_U))
	{
		fScale+=0.001;
	}	

	if (pManager->cInputManager.cStdInput.KeyDown(DIK_D))
	{
		fScale-=0.001;
	}


	if (pManager->cInputManager.cStdInput.KeyReleased(DIK_ESCAPE))
	{
		pManager->SetCurrentScene(1);
		return;
	}

	sprintf(textob,"%.2f %0.2f %2f %.2f", spr_Scooter->vPos.x, spr_Scooter->vPos.y, spr_Scooter->vPos.z, fScale);

	posicao->SetText(textob);
	*/
}

/***********************************************************
*Name: MovimentaSprite() 
*Description: utilizado para o posicionamento de Sprites
*Params: Nenhum
*Return: Nenhum
************************************************************/
void SceneGame::MovimentaSprite(CVRSprite* sprite)
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

	sprintf(textob,"%.2f %0.2f %2f %.2f", sprite->fPosX, sprite->fPosY);
	posicao->SetText(textob);
}