/***********************************************************************
*Nome: CVRTerrain.cpp
*Descrição: Implementação da classe que responsavel pela criação de terrenos
*Data: 18/04/07
*Local: LNCC
************************************************************************/

#include "CVRTerrain.h"
#include "CVRObject3D.h"
#include "CVRImage.h"
#include <ctime>

//Cria uma definição para gerar valores randomicos
#define FRAND   (((float)rand()-(float)rand())/RAND_MAX)


/***********************************************************
*Name: CVRTerrain()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRTerrain::CVRTerrain()
{
	srand(clock());
	fScale = 2.0f;
	terrainData = NULL;
	iWidth=0;
	iDepth=0;
	imageId = 0;
	uiListId = 0;
}

/***********************************************************
*Name: CVRTerrain()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRTerrain::~CVRTerrain()
{

}

/***********************************************************
*Name: CreateBitmapTerrain()
*Description: cria um terreno a partir de um bitmap
*Params: char*, char*, float
*Return: Nenhum
************************************************************/
void CVRTerrain::CreateBitmapTerrain(char* fileName,char* textName, float pScale)
{
	//Carrega a imagem do terreno
	CVRImage* hTerrain = NULL;
	hTerrain = pGraphicsManager->LoadImage(fileName,false);

	unsigned char *imageData = NULL;
	imageData = hTerrain->GetImageData();

	if (imageData ==NULL)
	{
		return;
	}

	iWidth = hTerrain->GetImageWidth();
	iDepth = hTerrain->GetImageHeight();
	this->fScale = pScale;
	int size =iWidth*iDepth;

	//Tenta carregar a textura e testa
	LoadTexture(textName);
	if (!imageId)
	{
		return;
	}

	//Obtem o identificador da lista e testa
	uiListId = glGenLists(1);
	if (!uiListId)
	{
		return;
	}

	//Alocação de memoria
	terrainData = new float*[size];

	//Alocando a matriz
	for(int iIndex=0; iIndex<size; iIndex++)
	{
		terrainData[iIndex] = new float[3];
	}

	int iCurrentVertex = 0;
	for (int zIndex=0; zIndex<iDepth; zIndex++)
	{
			for (int xIndex=0; xIndex<iWidth; xIndex++)
			{
				iCurrentVertex = xIndex + (zIndex*iWidth);

				terrainData[iCurrentVertex][0] = float(xIndex)*fScale;
				terrainData[iCurrentVertex][1] = (float)imageData[iCurrentVertex*3];
				terrainData[iCurrentVertex][2] = -float(zIndex)*fScale;
			}
	}

	//Cria a Lista de visualização
	glNewList(uiListId,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, imageId);

	for (int zIndex=0; zIndex<iDepth-1; zIndex++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int xIndex=0; xIndex<iWidth-1; xIndex++)
		{
					//glColor3f(terrainData[(xIndex) + (zIndex*iWidth)][1]/255.0f,terrainData[(xIndex) + (zIndex*iWidth)][1]/255.0f,terrainData[(xIndex) + (zIndex*iWidth)][1]/255.0f);
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(terrainData[(xIndex) + (zIndex*iWidth)][0],
							   terrainData[(xIndex) + (zIndex*iWidth)][1],
							   terrainData[(xIndex) + (zIndex*iWidth)][2]);

					//glColor3f(terrainData[(xIndex+1) + (zIndex*iWidth)][1]/255.0f,terrainData[(xIndex+1) + (zIndex*iWidth)][1]/255.0f,terrainData[(xIndex+1) + (zIndex*iWidth)][1]/255.0f);
					glTexCoord2f(1.0f,0.0f);
					glVertex3f(terrainData[(xIndex+1) + (zIndex*iWidth)][0],
							   terrainData[(xIndex+1) + (zIndex*iWidth)][1],
							   terrainData[(xIndex+1) + (zIndex*iWidth)][2]);

					//glColor3f(terrainData[(xIndex) + ((zIndex+1)*iWidth)][1]/255.0f,terrainData[(xIndex) + ((zIndex+1)*iWidth)][1]/255.0f,terrainData[(xIndex) + ((zIndex+1)*iWidth)][1]/255.0f);
					glTexCoord2f(0.0f,1.0f);
					glVertex3f(terrainData[(xIndex) + ((zIndex+1)*iWidth)][0],
							   terrainData[(xIndex) + ((zIndex+1)*iWidth)][1],
							   terrainData[(xIndex) + ((zIndex+1)*iWidth)][2]);

					//glColor3f(terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][1]/255.0f,terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][1]/255.0f,terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][1]/255.0f);
					glTexCoord2f(1.0f,1.0f);
					glVertex3f(terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][0],
							   terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][1],
							   terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][2]);
		}
		glEnd();
	}
	glEndList();
	imageData = NULL;
	pGraphicsManager->DeleteImage(&hTerrain);
}

/***********************************************************
*Name: CreateRandomTerrain()
*Description: cria um terreno a partir de valores randomicos
*Params: char*, int, float
*Return: Nenhum
************************************************************/
void CVRTerrain::CreateRandomTerrain(char* textName, int size, float pScale)
{
	iWidth = size;
	iDepth = size;
	size*=size;
	fScale = pScale;
	imageId = 0;
	uiListId = 0;

	//Tenta carregar a textura e testa
	LoadTexture(textName);
	if (!imageId)
	{
		return;
	}

	//Obtem o identificador da lista e testa
	uiListId = glGenLists(1);
	if (!uiListId)
	{
		return;
	}

	//Alocação de memoria
	terrainData = new float*[size];

	//Alocando a matriz
	for(int iIndex=0; iIndex<size; iIndex++)
	{
		terrainData[iIndex] = new float[3];
	}

	//Inicialização das coordenadas
	int iCurrentVertex = 0;
	for (int zIndex=0; zIndex<iDepth; zIndex++)
	{
			for (int xIndex=0; xIndex<iWidth; xIndex++)
			{
				iCurrentVertex = xIndex + (zIndex*iWidth);

				terrainData[iCurrentVertex][0] = float(xIndex)*fScale;
				terrainData[iCurrentVertex][1] = 5.0f + FRAND * 5.0f;
				terrainData[iCurrentVertex][2] = -float(zIndex)*fScale;
			}
	}

	//Cria a Lista de visualização
	glNewList(uiListId,GL_COMPILE);
	glBindTexture(GL_TEXTURE_2D, imageId);

	for (int zIndex=0; zIndex<iDepth-1; zIndex++)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for (int xIndex=0; xIndex<iWidth-1; xIndex++)
		{
					glTexCoord2f(0.0f,0.0f);
					glVertex3f(terrainData[(xIndex) + (zIndex*iWidth)][0],
							   terrainData[(xIndex) + (zIndex*iWidth)][1],
							   terrainData[(xIndex) + (zIndex*iWidth)][2]);

					glTexCoord2f(1.0f,0.0f);
					glVertex3f(terrainData[(xIndex+1) + (zIndex*iWidth)][0],
							   terrainData[(xIndex+1) + (zIndex*iWidth)][1],
							   terrainData[(xIndex+1) + (zIndex*iWidth)][2]);

					glTexCoord2f(0.0f,1.0f);
					glVertex3f(terrainData[(xIndex) + ((zIndex+1)*iWidth)][0],
							   terrainData[(xIndex) + ((zIndex+1)*iWidth)][1],
							   terrainData[(xIndex) + ((zIndex+1)*iWidth)][2]);

					glTexCoord2f(1.0f,1.0f);
					glVertex3f(terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][0],
							   terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][1],
							   terrainData[(xIndex+1) + ((zIndex+1)*iWidth)][2]);
		}
		glEnd();
	}
	glEndList();
}

/***********************************************************
*Name: LoadTexture()
*Description: carrega a textura para o terreno
*Params: char*
*Return: Nenhum
************************************************************/
void CVRTerrain::LoadTexture(char* fileName)
{
	
	if (!pGraphicsManager)
	{
		return;
	}
	CVRImage* image = pGraphicsManager->LoadImage(fileName,false);

	if (!image || !image->GetImageData())
	{
		return;
	}

	this->imageId = pGraphicsManager->GetBindImage(image->GetImageName());
	if (!imageId)
	{
		glGenTextures(1,&imageId);
		glBindTexture(GL_TEXTURE_2D,imageId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
		//glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,image->GetImageWidth(), image->GetImageHeight(),0,GL_RGB,GL_UNSIGNED_BYTE,image->GetImageData());
		gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image->GetImageWidth(), image->GetImageHeight(), GL_RGB, GL_UNSIGNED_BYTE, image->GetImageData());
		pGraphicsManager->AddBindImage(image->GetImageName(),imageId);	
	}
}

/***********************************************************
*Name: Release()
*Description: Libera os recursos do terreno
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTerrain::Release()
{
	pGraphicsManager->ReleaseBindImage(imageId);
	imageId = 0;
	ReleaseTerrain();
}

/***********************************************************
*Name: SetScale()
*Description: Configura a escala do terreno
*Params: float
*Return: Nenhum
************************************************************/
void CVRTerrain::SetTerrainScale(float pScale)
{
	fScale = pScale;
}

/***********************************************************
*Name: Render()
*Description: Renderiza o terreno
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTerrain::Render()
{
	//Verifica se está visível
	if (!bVisible)
	{
		return;
	}

	//Habilita a textura
	glEnable(GL_TEXTURE_2D);
	//Posiciona o objeto
	glPushMatrix();
		glTranslatef(vPos.x,vPos.y, vPos.z);
		glRotatef(vAngle.x,1.0f,0.0f,0.0f);
		glRotatef(vAngle.y,0.0f,1.0f,0.0f);
		glRotatef(vAngle.z,0.0f,0.0f,1.0f);
		glScalef(vScale.x,vScale.y,vScale.z);
		glCallList(uiListId);
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
}

/***********************************************************
*Name: GetScale()
*Description: Retorna a escala do terreno
*Params: Nenhum
*Return: float
************************************************************/
float CVRTerrain::GetScale()
{
	return fScale;
}

/***********************************************************
*Name: GetSize()
*Description: Retorna a dimensao do terreno
*Params: Nenhum
*Return: int
************************************************************/
int CVRTerrain::GetSize()
{
	return iWidth;
}

/***********************************************************
*Name: ReleaseTerrain()
*Description: Libera os recursos do terreno
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTerrain::ReleaseTerrain()
{
	int size = (iWidth*iDepth);

	//Libera os dados do terreno
	if (terrainData)
	{
		for (int iIndex=0; iIndex<size; iIndex++)
		{
			delete[] terrainData[iIndex];
		}

		delete[] terrainData;
		terrainData = NULL;
	} 

	//Libera a textura alocada
	if (imageId != 0)
	{
		glDeleteTextures(1, &imageId);
	}

	//Libera a lista de visualização
	if (uiListId != 0)
	{
		glDeleteLists(uiListId,1);
		uiListId = 0;
	}
}

/***********************************************************
*Name: GetHeight()
*Description: retorna a altura do terreno no ponto especificado
*Params: float, float
*Return: float
************************************************************/
float CVRTerrain::GetHeight(float xPos, float zPos)
{
	float pointX = xPos / fScale;
	float pointZ = -zPos / fScale;

	//Testa os limites
	if (!(pointX >=0 && pointX < (iWidth-1) &&
		pointZ >=0 && pointZ< (iDepth-1)))
		return 0.0f;

	//obtendo os cantos superiores e inferiores do poligono
	int iHeightX0 = int(pointX);
	int iHeightZ0 = int(pointZ);
	int iHeightX1 = iHeightX0 + 1;
	int iHeightZ1 = iHeightZ0 + 1;

	float fHeight00 = terrainData[iHeightX0 + iHeightZ0 * iWidth][1];
	float fHeight01 = terrainData[iHeightX1 + iHeightZ0 * iWidth][1];
	float fHeight11 = terrainData[iHeightX1 + iHeightZ1 * iWidth][1];
	float fHeight10 = terrainData[iHeightX0 + iHeightZ1 * iWidth][1];

	float x = pointX - float(iHeightX0);
	float y = pointZ - float(iHeightZ0);

	float xy = x*y;

	return fHeight00 * (1.0f - y - x + xy)  +
		               fHeight01 * (x - xy) + 
					   fHeight11 * xy       +
					   fHeight10 * (y - xy);

}

/***********************************************************
*Name:Init()
*Description: Inicializa recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRTerrain::Init()
{
	CVRObject3D::Init();
	return true;
}

/***********************************************************
*Name:Update()
*Description: atualiza o terreno
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTerrain::Update()
{
	//Chama o update do pai
	CVRObject3D::Update();
}