/***********************************************************************
*Nome: KinectGame.cpp
*Descrição: Classe criada para implementar o cenário virtual da simulação
*Data: 04/04/12
*Local: UNITINS
************************************************************************/
#include "KinectGame.h"
#include "CVRManager.h"

//Definiçao que cria uma referencia para o teclado
#define KEYBOARD pManager->cInputManager.cStdInput

char strInf[50];

char vetNames[20][30]={{"Images\\juncao0.bmp"},{"Images\\juncao1.bmp"},{"Images\\juncao2.bmp"},
	                  {"Images\\juncao3.bmp"},{"Images\\juncao4.bmp"},{"Images\\juncao5.bmp"},
				      {"Images\\juncao6.bmp"},{"Images\\juncao7.bmp"},{"Images\\juncao8.bmp"},
	                  {"Images\\juncao9.bmp"},{"Images\\juncao10.bmp"},{"Images\\juncao11.bmp"},
				      {"Images\\juncao12.bmp"},{"Images\\juncao13.bmp"},{"Images\\juncao14.bmp"},
	                  {"Images\\juncao15.bmp"},{"Images\\juncao16.bmp"},{"Images\\juncao17.bmp"},
				      {"Images\\juncao18.bmp"},{"Images\\juncao19.bmp"},};


/***********************************************************
*Name: KinectGame()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
KinectGame::KinectGame()
{
	vrGameTime =NULL;
	timeFont = NULL;
	pointsFont = NULL;
	sprBord = NULL;

	for (int iIndex =0; iIndex < NUM_COINS; iIndex++)
	{
		vetSprite[iIndex] = NULL;;
	}

	for (int iIndex =0; iIndex < 1; iIndex++)
	{
		for (int jIndex = 0 ; jIndex < 20; ++jIndex)
		{
			vetJoins[iIndex][jIndex] = NULL;
		}
	}

	snd_clicks[0] = NULL;
	snd_clicks[1] = NULL;
	snd_clicks[2] = NULL;
}

/***********************************************************
*Name: ~KinectGame()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
KinectGame::~KinectGame()
{
	
}

/***********************************************************
*Name: Init()
*Description: inicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool KinectGame::Init()
{
	//Configura o OpenGL
	glClearColor(0.0f,0.0f,0.0f,0.5f);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	//Configura a cor do colorkey
	pManager->cGraphicsManager.SetColorKey(255,0,255);
	
	//Cria o timer para marcar os segundos
	vrGameTime = new CVRTimer();
	vrGameTime->Init(&pManager->cTimeManager);
	vrGameTime->ResetTime(1000);

	//Carega os elementos do jogo
	Load2DAssets();

	//Cria os efeitos de clique
	snd_clicks[0] = pManager->cSoundManager.LoadSound("\\Sounds\\btnClick.wav");
	snd_clicks[0]->SetVolume(0);
	snd_clicks[0]->SetMaxMin(800,300);
	
	snd_clicks[1] = pManager->cSoundManager.LoadSound("\\Sounds\\btnOn.wav");
	snd_clicks[1]->SetVolume(0);
	snd_clicks[1]->SetMaxMin(800,300);
	
	snd_clicks[2] = pManager->cSoundManager.LoadSound("\\Sounds\\btnOn.wav");
	snd_clicks[2]->SetVolume(0);
	snd_clicks[2]->SetMaxMin(800,300);

	//Chama o metodo de carregamento
	return true;
}

/***********************************************************
*Name: InitKinect()
*Description: realiza a inicialização dos recursos do sensor
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KinectGame::InitKinect()
{
	//Obtém o numero de sensores no sistema e certifica que algum tenha sido encontrado
	HRESULT hr = NuiGetSensorCount(&iSensorCount);
	if (HRESULT(hr) < 0)
    {
		pManager->Exit();
    }

	//Valida a referencia para o sensor zero e verifica se a validação foi sucesso
	 hr = NuiCreateSensorByIndex(0, &pNuiSensor);
     if (HRESULT(hr) < 0)
     {
            pManager->Exit();
     }

	//Verifica se a referencia foi inicializada com sucesso
	if (pNuiSensor != NULL)
    {
        //chama o metodo para inicializar o kinect com o recurso de esqueleto
        hr = pNuiSensor->NuiInitialize(NUI_INITIALIZE_FLAG_USES_SKELETON); 

        if (HRESULT(hr) >= 0)
		{
            //Cria um evento que sera disparado quando os dados do esqueleto estiverem disponiveis
            m_hNextSkeletonEvent = CreateEventW(NULL, TRUE, FALSE, NULL);

            //Abre uma Stream para receber os dados do esqueleto
            hr = pNuiSensor->NuiSkeletonTrackingEnable(m_hNextSkeletonEvent, 0); 
        }
    }

	//Verifica se a referencia foi criada
	if (pNuiSensor == NULL)
	{
		pManager->Exit();
	}
}

/***********************************************************
*Name: Execute()
*Description: executa a cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KinectGame::Execute()
{
	//Sai da aplicação
	if (pManager->cInputManager.cStdInput.KeyDown(DIK_ESCAPE))
	{
		pManager->Exit();
	}

	//Chama os metodos de atualizacao
	//UpdateKinect();
	UpdateSprites();
	HandleCollision();
}

/***********************************************************
*Name: UpdateKinect()
*Description: atualiza o sensor
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KinectGame::UpdateKinect()
{
	//Cria o vetor de eventos
	HANDLE hEvents[NUM_SKELETONS];

	//Valida a primeira posicao do vetor de Handles
	hEvents[0] = m_hNextSkeletonEvent;

	//Testa os kinects individualmente, no caso de ter mais de um cadastrado
    DWORD dwEvent = MsgWaitForMultipleObjects(1, hEvents, FALSE, INFINITE, QS_ALLINPUT);

	//Checa se já existe um novo evento
    if (dwEvent == WAIT_OBJECT_0)
    {
		//verifica se o ponteiro para o sensor está valido
		if (pNuiSensor == NULL)
		{
			return;
		}

		// Espera por 0ms, apenas um pequeno teste para saber se é hora de atualizar o esqueleto
		if (WaitForSingleObject(m_hNextSkeletonEvent, 0) ==  WAIT_OBJECT_0)
		{
			 NUI_SKELETON_FRAME skeletonFrame = {0};
			
			 HRESULT hr = pNuiSensor->NuiSkeletonGetNextFrame(0, &skeletonFrame);
			
			 //Verifica 
			 if (HRESULT(hr) <0)	
			 {
				return;
			 }

			  //Suaviza os dados do esqueleto
			 pNuiSensor->NuiTransformSmooth(&skeletonFrame, NULL);

			 //Passa por todos as possiveis pessoas reconhecíveis MAX 6
			 for (int iIndex = 0 ; iIndex < NUI_SKELETON_COUNT; ++iIndex)
			 { 
					//Se o esqueleto da pessoa atual é rastreável
					NUI_SKELETON_TRACKING_STATE trackingState = skeletonFrame.SkeletonData[iIndex].eTrackingState;

					 //Testa o resultado do estado do tracker
					 if (NUI_SKELETON_TRACKED == trackingState)
					 {
						//Passa por todos as possiveis pessoas reconhecíveis MAX 6						
						for (int jIndex = 0 ; jIndex < NUI_SKELETON_POSITION_COUNT; ++jIndex)
						{
							LONG x, y;
							USHORT depth;

							// calcula a posicao do esqueleto no screen
							// NuiTransformSkeletonToDepthImage retorna coordenadas na resolucao NUI_IMAGE_RESOLUTION_320 x 240
							NuiTransformSkeletonToDepthImage(skeletonFrame.SkeletonData[iIndex].SkeletonPositions[jIndex], &x, &y, &depth);

							float screenPointX = static_cast<float>(x * 320) / 320;
							float screenPointY = static_cast<float>((y * 240) / 240) + 300;
							
							//Seta a posicao do Sprite da juncao
							vetJoins[0][jIndex]->SetPosXY(200+screenPointX, screenPointY);
					   }

					  //Ja trackeou entao sai fora
					  break;
				 }
			 }
		}
	}
}


/***********************************************************
*Name: Load2DAssets()
*Description: metodo chamado para carrega a arte do jogo
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KinectGame::Load2DAssets()
{
	//Carrega as moedas
	for(int iIndice = 0; iIndice < NUM_COINS; iIndice++)
	{
		////Cria as moedas
		int numX = ((rand()%6)*100) + 100;
		int numY = 100; 

		vetSprite[iIndice] = CreateSprite("Images\\moeda.bmp",32,32,true);
		vetSprite[iIndice]->AddAnimation(1,true,1,0);
		vetSprite[iIndice]->SetPosXY(numX,numY - (iIndice * 100));
	}

	//Carrega o Sprite da borda superior
	sprBord = CreateSprite("Images\\borda.bmp",1024,128,true);
	sprBord->AddAnimation(1,true,1,0);
	sprBord->SetPosXY(512,20);

	//Carrega os Sprites referentes as juncoes dos esqueleto
	 for (int iIndex=0; iIndex < 1; iIndex++)
	 {
		 for (int jIndex=0; jIndex < 20; jIndex++)
		 {
			 vetJoins[iIndex][jIndex] = CreateSprite(vetNames[jIndex],32,32,true);
			 vetJoins[iIndex][jIndex]->AddAnimation(1,true,1,0);
		 }
	 }
		
	//Carrega as fontes
	timeFont = CreateFont2D("Tempo:",32,true);
	timeFont->SetPosXY(50,64);

	pointsFont = CreateFont2D("Grana:",32,true);
	pointsFont->SetPosXY(400,64);
}

/***********************************************************
*Name: HandleCollision()
*Description: Verifica se algum objeto foi atingido
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KinectGame::HandleCollision()
{
	//Passa por todos as possiveis joins do personagem						
	for (int iIndex = 0 ; iIndex < 1; ++iIndex)
	{
		for (int jIndex = 0; jIndex < 20; jIndex++)
		{
			if (vetJoins[0][iIndex]->GetQuad().Collide(vetSprite[jIndex]->GetQuad()))
			{
				vetSprite[jIndex]->bVisible = false;
				iIncPoints+=2000;
			}
		}
	}
}

/***********************************************************
*Name: AtualizaElementos()
*Description: atualiza a posicao dos elmentos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KinectGame::UpdateSprites()
{
	//Verifica se o jogador ainda tem pontos a receber
	if (iIncPoints > 0)
	{
		iTotalPoints++;
	}

	//Atualiza a posicao dos elementos
	for(int iIndice = 0; iIndice < NUM_COINS; iIndice++)
	{
		vetSprite[iIndice]->SetPosY(vetSprite[iIndice]->GetPosY() + 2);
	}
}


/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void KinectGame::Release()
{
	CVRScene::Release();
}
