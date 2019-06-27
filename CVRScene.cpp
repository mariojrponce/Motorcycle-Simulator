/***********************************************************************
*Nome: CVRScene.cpp
*Descrição: Classe que implementa os métodos para o gerenciamento da cena
*Data: 31/07/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRScene.h"
#include "CVRManager.h"


/***********************************************************
*Name: CVRScene()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRScene::CVRScene()
{
	pManager = NULL;
	fps = NULL;
}

/***********************************************************
*Name: ~CVRScene()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRScene::~CVRScene()
{
	
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRScene::Release()
{
	//Libera os elementos 3D
	for (int iIndex=(int)vObject3D.size()-1; iIndex>=0; iIndex--)
	{
		vObject3D[iIndex]->Release();
		delete vObject3D[iIndex];
		vObject3D[iIndex] = NULL;
		vObject3D.erase(vObject3D.begin()+iIndex);
	}
	vObject3D.clear();

	//Libera os elementos 2D
	for (int iIndex=(int)vObject2D.size()-1; iIndex>=0; iIndex--)
	{
		vObject2D[iIndex]->Release();
		delete vObject2D[iIndex];
		vObject2D[iIndex] = NULL;
		vObject2D.erase(vObject2D.begin()+iIndex);
	}
	vObject2D.clear();

	//Configura o ponteiro da fonte para NULL
	fps = NULL;
}

/***********************************************************
*Name: UpdateFps()
*Description: atualiza o fps
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRScene::UpdateFps()
{
	//Configura a fonte 2D com o fps atual
	char cFps[STRINGSIZE];
	sprintf(cFps,"FPS %d",pManager->cTimeManager.GetFPS());
	fps->SetText(cFps);
}

/***********************************************************
*Name: ShowFps()
*Description: se o fps vai ser mostrado ou não
*Params: bool
*Return: Nenhum
************************************************************/
void CVRScene::ShowFps(bool pFps)
{
	//Configura o fps
	if (fps)
	{
		fps->SetVisible(pFps);
	}
}

/***********************************************************
*Name: Render()
*Description: renderiza elementos da cena de acordo com transf.
*Params: float*, float
*Return: Nenhum
************************************************************/
void CVRScene::Render(float fAngle, float distance)
{
	//Renderiza os objetos 2D
	CVRScene::SetOrthoMode(0,0,this->pManager->cMainWindow.lWindowWidth,this->pManager->cMainWindow.lWindowHeight);

	for (int iIndex=0; iIndex<(int)vObject2D.size(); iIndex++)
	{
		if (vObject2D[iIndex]->bAutoRender)
		{
			vObject2D[iIndex]->Render();
		}
	}

	///Renderiza os objetos 3D
	CVRScene::SetPerspectiveMode();

	//Atualiza a camera
	this->pManager->cView.UpdateView();

	glPushMatrix();
	glRotatef(fAngle,0.0f,1.0f,0.0f);
	glTranslatef(distance,0.0f,0.0f);
	for (int iIndex=0; iIndex<(int)vObject3D.size(); iIndex++)
	{
		if (vObject3D[iIndex]->bAutoRender)
		{
			vObject3D[iIndex]->Render();
		}
	}
	glPopMatrix();
}

/***********************************************************
*Name: Render()
*Description: renderiza elementos da cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRScene::Render()
{
	//Renderiza os objetos 2D
	CVRScene::SetOrthoMode(0,0,this->pManager->cMainWindow.lWindowWidth,this->pManager->cMainWindow.lWindowHeight);

	//Verifica se o FPS vai ser renderizado
	if (fps && fps->GetVisible())
	{
		UpdateFps();
	}

	//Renderiza os elementos 2D
	for (int iIndex=(int)vObject2D.size()-1; iIndex>=0; iIndex--)
	{
		if (vObject2D[iIndex]->bAutoRender)
		{
			vObject2D[iIndex]->Render();
		}
	}

	//Renderiza os objetos 3D
	CVRScene::SetPerspectiveMode();

	//Atualiza a camera
	this->pManager->cView.UpdateView();

	//Renderiza os elementos 3D
	for (int iIndex=0; iIndex<(int)vObject3D.size(); iIndex++)
	{
		if (vObject3D[iIndex]->bAutoRender)
		{
			vObject3D[iIndex]->Render();
		}
	}
}

/***********************************************************
*Name: RemoveObject2D()
*Description: atualiza os elementos da cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRScene::RemoveObject2D(CVRObject2D* pObject)
{
	//Atualiza os elementos 2D
	for (int iIndex = (int)vObject2D.size() - 1; iIndex >= 0; iIndex--)
	{
		if (pObject == vObject2D[iIndex])
		{
			vObject2D.erase(vObject2D.begin() + iIndex);
			break;
		}
	}
}

/***********************************************************
*Name: Update()
*Description: atualiza os elementos da cena
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRScene::Update()
{
	//Cria a fonte 2D caso ainda nao tenha sido criada
	//COMENTADO PARA A OCASIAO
	/*if (!fps)
	{
		fps = CreateFont2D("FPS",30,true);
		fps->SetPosX(700);
		fps->SetPosY(50);
		fps->SetColor(1.0f,1.0f,0.0f);
	}*/

	//Atualiza a camera
	this->pManager->cView.UpdateView();

	//Atualiza os elementos 2D
	for (int iIndex=0; iIndex<(int)vObject2D.size(); iIndex++)
	{
		vObject2D[iIndex]->Update();
	}

	//Atualiza os elementos 3D
	for (int iIndex=0; iIndex<(int)vObject3D.size(); iIndex++)
	{
		vObject3D[iIndex]->Update();
	}
}

/***********************************************************
*Name: SetOrthoMode()
*Description: configura a projeção para o modo ortogonal (2D)
*Params: int, int, int, int
*Return: Nenhum
************************************************************/
void CVRScene::SetOrthoMode(int left, int top, int right, int bottom)
{
	glMatrixMode(GL_PROJECTION);						

	glPushMatrix();									
	
	glLoadIdentity();								

	glOrtho(left, right, bottom, top, 0, 1);	
	
	glMatrixMode(GL_MODELVIEW);								
	
	glLoadIdentity();	
}

/***********************************************************
*Name: SetPerspectiveMode()
*Description: configura a projeção para o modo perspectivo
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRScene::SetPerspectiveMode()
{
	glMatrixMode( GL_PROJECTION );							
	
	glPopMatrix();											
	
	glMatrixMode( GL_MODELVIEW );

	glLoadIdentity();
}

/***********************************************************
*Name: CreateFont2D()
*Description: cria uma fonte 2D
*Params: char*, int, bool
*Return: CVRFont*
************************************************************/
CVRFont* CVRScene::CreateFont2D(char* text, int size, bool autoRender)
{
	CVRFont* pNewFont = new CVRFont(text,size);

	if (pNewFont)
	{
		pNewFont->g_HDC = &pManager->cMainWindow.hdc;
		pNewFont->Init();
		pNewFont->bAutoRender = autoRender;
		vObject2D.push_back(pNewFont);
		return pNewFont;
	}

	return NULL;
}

/***********************************************************
*Name: CreateObjGeneric()
*Description: cria um objeto genérico
*Params: CVRObjGeneric*
*Return: CVRObjGeneric*
************************************************************/
CVRObjGeneric* CVRScene::CreateObjGeneric(CVRObjGeneric* obj, bool autoRender)
{
	if (obj)
	{
		obj->pGraphicsManager = &pManager->cGraphicsManager;
		obj->Init();
		obj->bAutoRender = autoRender;
		vObject3D.push_back(obj);

		return obj;
	}
	return NULL;
}

/***********************************************************
*Name: CreateBillboard()
*Description: cria um billboard
*Params: CVRSprite*, bool
*Return: CVRBillboard*
************************************************************/
CVRBillboard* CVRScene::CreateBillboard(CVRSprite* pSprite, bool autoRender)
{
	CVRBillboard* newBillboard = new CVRBillboard(pSprite);
	
	if (newBillboard)
	{
		newBillboard->pGraphicsManager = &pManager->cGraphicsManager;
		newBillboard->Init();
		newBillboard->bAutoRender = autoRender;
		vObject3D.push_back(newBillboard);

		return newBillboard;
	}

	return NULL;
}

/***********************************************************
*Name: CreateSkyBox()
*Description: cria um skyBox
*Params: char*, bool
*Return: CVRSkyBox*
************************************************************/
CVRSkyBox* CVRScene::CreateSkyBox(char* textName, bool autoRender)
{
	CVRSkyBox* newSkyBox = new CVRSkyBox();
	
	if (newSkyBox)
	{
		newSkyBox->pGraphicsManager = &pManager->cGraphicsManager;
		newSkyBox->Init();
		newSkyBox->SetAllTextures(textName);
		newSkyBox->bAutoRender = autoRender;
		vObject3D.push_back(newSkyBox);

		return newSkyBox;
	}
	return NULL;
}

/***********************************************************
*Name: CreateSkyBox()
*Description: cria um skyBox
*Params: bool
*Return: CVRSkyBox*
************************************************************/
CVRSkyBox* CVRScene::CreateSkyBox(bool autoRender)
{
	CVRSkyBox* newSkyBox = new CVRSkyBox();
	
	if (newSkyBox)
	{
		newSkyBox->pGraphicsManager = &pManager->cGraphicsManager;
		newSkyBox->Init();
		newSkyBox->bAutoRender = autoRender;
		vObject3D.push_back(newSkyBox);

		return newSkyBox;
	}
	return NULL;
}

/***********************************************************
*Name: CreateSkySphere()
*Description: cria um skySphere
*Params: char*, bool
*Return: CVRSkySphere
************************************************************/
CVRSkySphere* CVRScene::CreateSkySphere(char* textName, bool autoRender)
{
	CVRSkySphere* newSkySphere = new CVRSkySphere();
	
	if (newSkySphere)
	{
		newSkySphere->pGraphicsManager = &pManager->cGraphicsManager;
		newSkySphere->Init();
		newSkySphere->SetTexture(textName);
		newSkySphere->bAutoRender = autoRender;
		vObject3D.push_back(newSkySphere);

		return newSkySphere;
	}
	return NULL;
}

/***********************************************************
*Name: CreateRandomTerrain()
*Description: cria um terreno randomico
*Params: char*, int, float, bool
*Return: CVRTerrain*
************************************************************/
CVRTerrain* CVRScene::CreateRandomTerrain(char* textName,int size, float scale, bool autoRender)
{
	CVRTerrain* newTerrain = new CVRTerrain();

	if(newTerrain)
	{
		newTerrain->pGraphicsManager = &pManager->cGraphicsManager;
		newTerrain->Init();
		newTerrain->CreateRandomTerrain(textName,size,scale);
		newTerrain->bAutoRender = autoRender;
		vObject3D.push_back(newTerrain);

		return newTerrain;
	}

	return NULL;
}

/***********************************************************
*Name: CreateBmpTerrain()
*Description: cria um terreno com base em um bmp 
*Params: char*, char*, float, bool
*Return: CVRTerrain*
************************************************************/
CVRTerrain* CVRScene::CreateBmpTerrain(char* bmpName,char* texName, float scale, bool autoRender)
{
	CVRTerrain* newTerrain = new CVRTerrain();

	if(newTerrain)
	{
		newTerrain->pGraphicsManager = &pManager->cGraphicsManager;
		newTerrain->Init();
		newTerrain->CreateBitmapTerrain(bmpName,texName,scale);
		newTerrain->bAutoRender = autoRender;
		vObject3D.push_back(newTerrain);

		return newTerrain;
	}

	return NULL;
}

/***********************************************************
*Name: CreateMd2()
*Description: cria um modelo animado md2
*Params: char*, char*, bool
*Return: CVRMd2*
************************************************************/
CVRMd2* CVRScene::CreateMd2(char* fileName, char* textName, bool autoRender)
{
	CVRMd2* newMd2 = new CVRMd2(fileName);

	if (newMd2)
	{
		newMd2->pGraphicsManager = &pManager->cGraphicsManager;
		newMd2->Init();
		newMd2->timer.Init(&pManager->cTimeManager);
		newMd2->LoadTexture(textName);
		newMd2->bAutoRender = autoRender;
		vObject3D.push_back(newMd2); 
		return newMd2;
	}

	return NULL;
}

/***********************************************************
*Name: CreateObj()
*Description: cria um modelo estatico obj
*Params: char*, char*, bool
*Return: CVRObjLoader*
************************************************************/
CVRObjLoader* CVRScene::CreateObj(char* fileName, char* workDirectory, bool autoRender, bool bGetGeometry)
{
	CVRObjLoader* newObj = new CVRObjLoader();

	if (newObj)
	{
		newObj->pGraphicsManager = &pManager->cGraphicsManager;
		newObj->Init();
		newObj->SetWorkDirectory(workDirectory);
		if (!newObj->Load(fileName,bGetGeometry))
		{
			newObj->pGraphicsManager = NULL;
			delete newObj;
			return NULL;
		}
		newObj->bAutoRender = autoRender;
		vObject3D.push_back(newObj);
		return newObj;
	}
	return NULL;
}

/***********************************************************
*Name: CreateSprite()
*Description: carrega uma música
*Params: char*, int, int, bool
*Return: CVRSprite*
************************************************************/
CVRSprite* CVRScene::CreateSprite(char* fileName, char* alphaName, int width, int height, bool autoRender)
{
	CVRSprite* sprite = new CVRSprite();
	if (sprite)
	{
		sprite->pManager = pManager;
		sprite->Create(fileName,alphaName, width,height);
		sprite->bAutoRender = autoRender;
		vObject2D.push_back(sprite);
		return sprite;
	}
	
	return NULL;
}


/***********************************************************
*Name: CreateSprite()
*Description: carrega uma música
*Params: char*, int, int, bool
*Return: CVRSprite*
************************************************************/
CVRSprite* CVRScene::CreateSprite(char* fileName, int width, int height, bool autoRender)
{
	CVRSprite* sprite = new CVRSprite();
	if (sprite)
	{
		sprite->pManager = pManager;
		sprite->Create(fileName,width,height);
		sprite->bAutoRender = autoRender;
		vObject2D.push_back(sprite);
		return sprite;
	}
	
	return NULL;
}

/***********************************************************
*Name: CreateLoadinBar()
*Description: carrega uma música
*Params: int, int, bool
*Return: CVRLoadingBar*
************************************************************/
CVRLoadingBar* CVRScene::CreateLoadingBar(int width, int height, bool autoRender)
{
	CVRLoadingBar* bar = new CVRLoadingBar(width,height);

	if (bar)
	{
		bar->bAutoRender = autoRender;
		vObject2D.push_back(bar);
		return bar;
	}

	return NULL;
}

/***********************************************************
*Name: GetListener()
*Description: retorna uma referencia para o ouvinte
*Params: Nenhum
*Return: CVRListener*
************************************************************/
CVRListener* CVRScene::GetListener()
{	
	return pManager->cSoundManager.GetListener();
}

/***********************************************************
*Name: LoadSound()
*Description: carrega um som 3D
*Params: char*
*Return: CVRSound*
************************************************************/
CVRSound* CVRScene::LoadSound(char* fileName)
{	
	return pManager->cSoundManager.LoadSound(fileName);
}

/***********************************************************
*Name: LoadMusic()
*Description: carrega uma música
*Params: char*
*Return: void
************************************************************/
void CVRScene::LoadMusic(char* fileName)
{
	pManager->cSoundManager.LoadMusic(fileName);
}

/***********************************************************
*Name: GetCurrentMusic()
*Description: carrega uma música
*Params: char*
*Return: void
************************************************************/
CVRMusic CVRScene::GetCurrentMusic()
{
	return pManager->cSoundManager.GetMusic();
}