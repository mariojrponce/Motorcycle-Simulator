/***********************************************************************
*Nome: CVRManager.cpp
*Descrição: Classe que implementa os métodos para o controle da Engine
*Data: 18/07/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRManager.h"

/***********************************************************
*Name: CVRManager()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRManager::CVRManager()
{
	//Inicializaçao do LOG
	LOG->Init("AppLog.txt");
	bRunning = true;
	
	//Configuração dos managers
	cGraphicsManager.pManager = this;
	cInputManager.pManager = this;
	cView.pManager = this;
	
	//Inicia o som
	cSoundManager.Init();
	pScene = NULL;
}

/***********************************************************
*Name: ~CVRManager()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRManager::~CVRManager()
{
	
}

/***********************************************************
*Name: CVRLoop()
*Description: Loop principal da engine
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRManager::Loop()
{
	MSG	msg;

	//Chama comandos de inicializaçao
	Init();

	while(bRunning)
	{	
		//Atualiza a simulacao da cena atual
		Update();

		//Troca o front buffer pelo back buffer
		SwapBuffers(cMainWindow.hdc);

		//Trata as mensagens do windows
		while(PeekMessage(&msg, NULL, 0, 0,  PM_NOREMOVE))
		{
			if (!GetMessage(&msg, NULL, 0, 0))
			{
				bRunning = false;
				break;
			}

			if (msg.message == WM_QUIT)
			{
				bRunning = false;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	Release();
}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRManager::Release()
{
	if (pScene)
	{
		pScene->Release();
		pScene = NULL;
	}

	cMainWindow.Release();
	cGraphicsManager.Release();
	cSoundManager.Release();
	cInputManager.Release();
	cView.Release();
}

/***********************************************************
*Name: Update()
*Description: Atualiza a simulacao
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRManager::Update()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	cTimeManager.Update();
	cInputManager.Update();
	
	if (pScene)
	{
		pScene->Execute();
		pScene->Update();
		pScene->Render();
	}
}

/***********************************************************
*Name: Init()
*Description: Inicializa os recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRManager::Init()
{
	//Inicializa a cor do background
	glClearColor(cMainWindow.r,cMainWindow.g, cMainWindow.b,0.0);

	//Habilita estados do OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	//Cria fonte de luz padrão
	GLfloat ambientColor[] = {1.0f,1.0f,1.0f};
	glLightfv(GL_LIGHT0,GL_AMBIENT,ambientColor);
	glEnable(GL_LIGHT0);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	glShadeModel(GL_SMOOTH);

	//Inicia os dispositivos de entrada();
	cInputManager.Init();
}

/***********************************************************
*Name: Exit()
*Description: Termina o programa
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRManager::Exit()
{
	bRunning = false;
}

/***********************************************************
*Name: SetCurrentScene()
*Description: configura a cena que está sendo exibida no momento
*Params: int
*Return: Nenhum
************************************************************/
void CVRManager::SetCurrentScene(int index)
{
	if(index < (int)vScenes.size())
	{
		//Pega a nova cena
		CVRScene* prNewScene = vScenes[index];
		
		//Se existe a cena
		if(prNewScene)
		{	
			//Se a cena anterior existir, libera
			if(pScene)
			{
				pScene->Release();
				pScene = NULL;
			}

			//Configura a nova cena
			pScene = prNewScene;
			
			//atribui o gerenciador à cena
			pScene->pManager = this;

			//inicializa a nova cena
			pScene->Init();

			//Reinicializa o tempo
			cTimeManager.ResetTime();
		}
	}
}

/***********************************************************
*Name: AddNewScene()
*Description: Adiciona uma nova cena
*Params: CVRScene*
*Return: Nenhum
************************************************************/
void CVRManager::AddNewScene(CVRScene* prScene)
{
	if (prScene)
	{
		vScenes.push_back(prScene);

		if (vScenes.size() == 1)
		{
			SetCurrentScene(0);
		}
	}
}

/***********************************************************
*Name: GetCurrentScene()
*Description: retorna a cena atual
*Params: Nenhum
*Return: CVRScene*
************************************************************/
CVRScene* CVRManager::GetCurrentScene()
{
	return pScene;
}

/***********************************************************
*Name: SwapBuffers()
*Description: Faz a troca dos buffes
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRManager::SwpBuffers()
{
	//Troca o front buffer pelo back buffer
	SwapBuffers(cMainWindow.hdc);
}

/***********************************************************
*Name: ClearBuffer()
*Description: Limpa o Buffer de cor
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRManager::ClearBuffer()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
	
