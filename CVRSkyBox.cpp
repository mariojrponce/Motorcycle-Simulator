/***********************************************************************
*Nome: CVRSkyBox.cpp
*Descrição: Implementação da classe implementa o sky box
*Data: 23/05/07
*Local: LNCC
************************************************************************/

#include "CVRSkyBox.h"
#include "CVRImage.h"


/***********************************************************
*Name: CVRSkyBox()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSkyBox::CVRSkyBox()
{
	vPos.x = 0.0f;
	vPos.y = 0.0f;
	vPos.z = 0.0f;

	bDrawGround = false;

	fWidth  = 50.0f;
	fHeight = 50.0f;
	fDepth  = 50.0f;
	fFloor = 0.0f;

	for (int iIndex=0; iIndex<6; iIndex++)
	{
		texIds[iIndex]= 0 ;
	}

	bDrawGround = false;
}

/***********************************************************
*Name: CVRSkyBox()
*Description: construtor da classe
*Params: float, float, float, float, float, float
*Return: Nenhum
************************************************************/
CVRSkyBox::CVRSkyBox(float pCentX, float pCentY, float pCentZ, float pWidth, float pHeight, float pDepth)
{
	vPos.x = pCentX;
	vPos.y = pCentY;
	vPos.z = pCentZ;

	bDrawGround = false;

	fWidth  = pWidth;
	fHeight = pHeight;
	fDepth  = pDepth;
	fFloor = 0.0f;

	for (int iIndex=0; iIndex<6; iIndex++)
	{
		texIds[iIndex]= 0 ;
	}
}

/***********************************************************
*Name: ~CVRSkyBox()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSkyBox::~CVRSkyBox()
{

}

/***********************************************************
*Name: GetCenterX()
*Description: retorna a posicao x do centro do box
*Params: Nenhum
*Return: float
************************************************************/
float CVRSkyBox::GetCenterX()
{
	return vPos.x;
}

/***********************************************************
*Name: Update()
*Description: Atualiza o skybox
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSkyBox::Update()
{
	//Chama o update do pai
	CVRObject3D::Update();
}

/***********************************************************
*Name: GetCenterY()
*Description: retorna a posicao y do centro do box
*Params: Nenhum
*Return: float
************************************************************/
float CVRSkyBox::GetCenterY()
{
	return vPos.y;
}

/***********************************************************
*Name: GetCenterZ()
*Description: retorna a posicao z do centro do box
*Params: Nenhum
*Return: float
************************************************************/
float CVRSkyBox::GetCenterZ()
{
	return vPos.z;
}

/***********************************************************
*Name: SetCenterBox
*Description: configura a posicao central do box
*Params: float, float, float
*Return: void
************************************************************/
void CVRSkyBox::SetCenterBox(float fCentX, float fCentY, float fCentZ)
{
	vPos.x = fCentX;
	vPos.y = fCentY;
	vPos.z = fCentZ;
}

/***********************************************************
*Name: SetFrontTexture()
*Description: configura a textura frontal do box
*Params: char*
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetFrontTexture(char *texName)
{

	LoadTexture(texName,FRONT);
}

/***********************************************************
*Name: SetFrontTexture()
*Description: configura a textura traseira do box
*Params: char*
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetBackTexture(char *texName)
{
	LoadTexture(texName,BACK);
}

/***********************************************************
*Name: SetLeftTexture()
*Description: configura a textura esquerda do box
*Params: char*
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetLeftTexture(char *texName)
{
	LoadTexture(texName,LEFT);
}

/***********************************************************
*Name: SetRightTexture()
*Description: configura a textura direita do box
*Params: char*
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetRightTexture(char *texName)
{
	LoadTexture(texName,RIGHT);
}

/***********************************************************
*Name: SetUPTexture()
*Description: configura a textura superior do box
*Params: char*
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetUpTexture(char *texName)
{
	LoadTexture(texName,UP);
}

/***********************************************************
*Name: SetDownTexture()
*Description: configura a textura inferior do box
*Params: char*
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetDownTexture(char *texName)
{
	LoadTexture(texName,DOWN);
}

/***********************************************************
*Name: SetAllTextures()
*Description: configura as texturas do box
*Params: char*
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetAllTextures(char* textName)
{
	for (int iIndex=0; iIndex<5; iIndex++)
	{
		LoadTexture(textName,iIndex);
	}
}

/***********************************************************
*Name: Render()
*Description: Renderiza o SkyBox
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSkyBox::Render()
{
	//Verifica se está visível
	if (!bVisible)
	{
		return;
	}

	float x = vPos.x - (fWidth  * 0.5f);
	float y = vPos.y - (fHeight * 0.5f);
	float z = vPos.z - (fDepth  * 0.5f);
	
	glEnable(GL_TEXTURE_2D);

	//Parede frontal
	glBindTexture(GL_TEXTURE_2D, texIds[FRONT]);
	glBegin(GL_QUADS);	
		glTexCoord2f(((256.f-0.5f) / 256.f), (0.5f / 256.f)); 
		glVertex3f(x, y, z+fDepth);
		
		glTexCoord2f(((256.f-0.5f) / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x, y+fHeight, z+fDepth);
		
		glTexCoord2f((0.5f / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x+fWidth, y+fHeight, z+fDepth); 
		
		glTexCoord2f((0.5f / 256.f), (0.5f / 256.f)); 
		glVertex3f(x+fWidth, y, z+fDepth);
	glEnd();

	//Parede traseira
	glBindTexture(GL_TEXTURE_2D, texIds[BACK]);
	glBegin(GL_QUADS);		
		glTexCoord2f(((256.f-0.5f) / 256.f), (0.5f / 256.f)); 
		glVertex3f(x+fWidth, y,	z);
		
		glTexCoord2f(((256.f-0.5f) / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x+fWidth, y+fHeight, z); 
		
		glTexCoord2f((0.5f / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x, y+fHeight, z);
		
		glTexCoord2f((0.5f / 256.f), (0.5f / 256.f)); 
		glVertex3f(x, y, z);
	glEnd();

	// Desenha o lado esquerdo
	glBindTexture(GL_TEXTURE_2D, texIds[LEFT]);
	glBegin(GL_QUADS);		
		glTexCoord2f(((256.f-0.5f) / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x, y+fHeight, z);	
		
		glTexCoord2f((0.5f / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x, y+fHeight, z+fDepth); 
		
		glTexCoord2f((0.5f / 256.f), (0.5f / 256.f)); 
		glVertex3f(x, y, z+fDepth);
		
		glTexCoord2f(((256.f-0.5f) / 256.f), (0.5f / 256.f)); 
		glVertex3f(x, y, z);		
	glEnd();

	// Desenha o lado direito
	glBindTexture(GL_TEXTURE_2D, texIds[RIGHT]);
	glBegin(GL_QUADS);		
		glTexCoord2f((0.5f / 256.f), (0.5f / 256.f)); 
		glVertex3f(x+fWidth, y,	z);
		
		glTexCoord2f(((256.f-0.5f) / 256.f), (0.5f / 256.f)); 
		glVertex3f(x+fWidth, y, z+fDepth);
		
		glTexCoord2f(((256.f-0.5f) / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x+fWidth, y+fHeight,	z+fDepth); 
		
		glTexCoord2f((0.5f / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x+fWidth, y+fHeight,	z);
	glEnd();

	//Desenha o lado superior
	glBindTexture(GL_TEXTURE_2D, texIds[UP]);
	glBegin(GL_QUADS);		
		glTexCoord2f((0.5f / 256.f), (0.5f / 256.f)); 
		glVertex3f(x+fWidth, y+fHeight, z);
		
		glTexCoord2f(((256.f-0.5f) / 256.f), (0.5f / 256.f)); 
		glVertex3f(x+fWidth, y+fHeight, z+fDepth); 
		
		glTexCoord2f(((256.f-0.5f) / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x, y+fHeight, z+fDepth);
		
		glTexCoord2f((0.5f / 256.f), ((256.f-0.5f) / 256.f)); 
		glVertex3f(x,y+fHeight,	z);
	glEnd();

	if (bDrawGround)
	{
		//Desenha o chao
		glBindTexture(GL_TEXTURE_2D, texIds[DOWN]);
		glBegin(GL_QUADS);		
			glTexCoord2f((0.5f / 256.f), (0.5f / 256.f)); 
			glVertex3f(x, y+fFloor, z);
			
			glTexCoord2f(((256.f-0.5f) / 256.f), (0.5f / 256.f));
			glVertex3f(x,y+fFloor,	z+fDepth);
			
			glTexCoord2f(((256.f-0.5f) / 256.f), ((256.f-0.5f) / 256.f)); 
			glVertex3f(x+fWidth, y+fFloor, z+fDepth); 
			
			glTexCoord2f((0.5f / 256.f), ((256.f-0.5f) / 256.f)); 
			glVertex3f(x+fWidth, y+fFloor, z);	
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
}

/***********************************************************
*Name: SetBoxSize()
*Description: Método que cofigura o tamanho do box
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetBoxSize(float pWidth, float pHeight, float pDepth)
{
	this->fWidth  = pWidth;
	this->fHeight = pHeight;
	this->fDepth  = pDepth;
}

/***********************************************************
*Name: Release)
*Description: Método que libera texturas do skybox
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSkyBox::Release()
{
	for (unsigned int iIndex=0; iIndex<6; iIndex++)
	{
		pGraphicsManager->ReleaseBindImage(texIds[iIndex]);
		texIds[iIndex] = 0;
	}
}

/***********************************************************
*Name: SetFloorHeigth()
*Description: Método que configura a algura do chao
*Params: float
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetFloorHeight(float fHeight)
{
	fFloor = fHeight;
}

/***********************************************************
*Name: SetDrawGround()
*Description: Método que seta se o chao será desenhado ou nao
*Params: bool
*Return: Nenhum
************************************************************/
void CVRSkyBox::SetDrawGround(bool bGround)
{
	bDrawGround = bGround;
}

/***********************************************************
*Name: GetDrawGround()
*Description: Método que retorna se o chao será desenhado ou 
              nao
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSkyBox::GetDrawGround()
{
	return bDrawGround;
}

/***********************************************************
*Name: Init()
*Description: Inicializa recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRSkyBox::Init()
{
	CVRObject3D::Init();
	return true;
}

/***********************************************************
*Name: LoadTexture
*Description: Carrega a textura do indice
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSkyBox::LoadTexture(char * fileName, int iIndex)
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

	this->texIds[iIndex] = pGraphicsManager->GetBindImage(image->GetImageName());
	if (!texIds[iIndex])
	{
		glGenTextures(1,&texIds[iIndex]);
		glBindTexture(GL_TEXTURE_2D,texIds[iIndex]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image->GetImageWidth(), image->GetImageHeight(), GL_RGB, GL_UNSIGNED_BYTE, image->GetImageData());
		pGraphicsManager->AddBindImage(image->GetImageName(),texIds[iIndex]);
	}
}