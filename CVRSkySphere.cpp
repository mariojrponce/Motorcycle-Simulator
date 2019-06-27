/***********************************************************************
*Nome: CVRSkySphere.cpp
*Descrição: Implementação da classe implementa o sky sphere
*Data: 04/06/07
*Local: LNCC
************************************************************************/

#include "CVRSkySphere.h"
#include "CVRImage.h"

GLUquadricObj *quadratic;

/***********************************************************
*Name: CVRSkySphere()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSkySphere::CVRSkySphere()
{
	fRadius = 50.0f;
	quadratic=gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);
}

/***********************************************************
*Name: CVRSkySphere()
*Description: construtor da classe
*Params: float, float, float, float
*Return: Nenhum
************************************************************/
CVRSkySphere::CVRSkySphere(float fPosX, float fPosY, float fPosZ, float fSize)
{
	quadratic=gluNewQuadric();
	gluQuadricNormals(quadratic, GLU_SMOOTH);
	gluQuadricTexture(quadratic, GL_TRUE);

	vPos.x = fPosX;
	vPos.y = fPosY;
	vPos.z = fPosZ;
	fRadius = fSize;
}

/***********************************************************
*Name: ~CVRSkySphere()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSkySphere::~CVRSkySphere()
{

}

/***********************************************************
*Name: SetTexture()
*Description: configura a textura da esfera
*Params: char*
*Return: Nenhum
************************************************************/
void CVRSkySphere::SetTexture(char* fileName)
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

	this->imageId  = pGraphicsManager->GetBindImage(image->GetImageName());
	if (!imageId)
	{
		glGenTextures(1,&imageId);
		glBindTexture(GL_TEXTURE_2D,imageId);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR_MIPMAP_LINEAR);
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image->GetImageWidth(), image->GetImageHeight(), GL_RGB, GL_UNSIGNED_BYTE, image->GetImageData());
		pGraphicsManager->AddBindImage(image->GetImageName(),imageId);
	}
}

/***********************************************************
*Name: Render()
*Description: Renderiza o SkySphere
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSkySphere::Render()
{
	//Verifica se está visível
	if (!bVisible)
	{
		return;
	}

	//Renderiza a esfera
	glEnable(GL_TEXTURE_2D);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glBindTexture(GL_TEXTURE_2D, imageId);
	glFrontFace(GL_CW);
	glDisable(GL_CULL_FACE);

	glPushMatrix();
		glTranslatef(vPos.x, vPos.y, vPos.z);
		glRotatef(90,1,0,1);
		gluSphere(quadratic,fRadius,20,20);
	glPopMatrix();

	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
}

/***********************************************************
*Name: SetCenterPos
*Description: configura a posicao central da esfera
*Params: float, float, float
*Return: void
************************************************************/
void CVRSkySphere::SetCenterPos(float fCentX, float fCentY, float fCentZ)
{
	vPos.x= fCentX;
	vPos.y = fCentY;
	vPos.z = fCentZ;
}

/***********************************************************
*Name: SetRadius()
*Description: configura o raio da esfera
*Params: float
*Return: void
************************************************************/
void CVRSkySphere::SetRadius(float fRad)
{
	fRadius = fRad;
}

/***********************************************************
*Name: Update()
*Description: atualiza o skysphere
*Params: Nenhum
*Return: void
************************************************************/
void CVRSkySphere::Update()
{
	//Chama o update do pai
	CVRObject3D::Update();
}

/***********************************************************
*Name: GetRadius()
*Description: Retorna o raio da esfera
*Params: Nenhum
*Return: float
************************************************************/
float CVRSkySphere::GetRadius()
{
	return fRadius;
}

/***********************************************************
*Name: Release()
*Description: Método que libera texturas do skySphere
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSkySphere::Release()
{
	pGraphicsManager->ReleaseBindImage(imageId);
}

/***********************************************************
*Name: Init()
*Description: Inicializa recursos
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSkySphere::Init()
{
	CVRObject3D::Init();
	return true;
}
