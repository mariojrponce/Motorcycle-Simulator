/***********************************************************************
*Nome: CVRView.cpp
*Descrição: Implementação da classe responsável pela movimentação da camera
*Data: 09/01/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRView.h"
#include "CVRManager.h"

/***********************************************************
*Name: CVRView()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRView::CVRView()
{
	vPosition = CVRVector(0.0f,0.0f,0.0f);
	vLookAt = CVRVector(0.0f,0.0f,0.0f);
	vUp = CVRVector(0.0f,1.0f,0.0f);
	vDirection = CVRVector(0.0f,0.0f,0.0f);
	
	fAngleX = 0.0f;
	fAngleY = 0.0f;
	fAngleZ = 0.0f;
	fSpeed = 1.0f;

	pManager = NULL;
}

/***********************************************************
*Name: ~CVRView()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRView::~CVRView()
{

}

/***********************************************************
*Name: SetView()
*Description: Configura as opcoes de camera
*Params: float, float, float, float, float, float
*Return: Nenhum
************************************************************/
void CVRView::SetView(float fPosX, float fPosY, float fPosZ,
					   float fViewX, float fViewY, float fViewZ,
					   float fUpX, float fUpY, float fUpZ)
{
	vPosition = CVRVector(fPosX,fPosY,fPosZ);
	vLookAt = CVRVector(fViewX,fViewY,fViewZ);
	vUp = CVRVector(fUpX,fUpY,fUpZ);
	vDirection = CVRVector(0.0f,0.0f,0.0f);
	
}

/***********************************************************
*Name: SetPosition()
*Description: Configura a posicao da camera
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRView::SetPosition(float fX, float fY, float fZ)
{
	vPosition.x = fX;
	vPosition.y = fY;
	vPosition.z = fZ;
	vLookAt.y = fY;
}

/***********************************************************
*Name: SetPositionX()
*Description: Configura a posicao X da camera
*Params: float
*Return: Nenhum
************************************************************/
void CVRView::SetPositionX(float fX)
{
	vPosition.x = fX;
}


/***********************************************************
*Name: SetPositionY()
*Description: Configura a posicao Y da camera
*Params: float
*Return: Nenhum
************************************************************/
void CVRView::SetPositionY(float fY)
{
	vPosition.y = fY;
	vLookAt.y = fY;
}

/***********************************************************
*Name: SetPositionZ()
*Description: Configura a posicao Z da camera
*Params: float
*Return: Nenhum
************************************************************/
void CVRView::SetPositionZ(float fZ)
{
	vPosition.z = fZ;
}

/***********************************************************
*Name: GetPositionX()
*Description: retorna a posicao X da camera
*Params: Nenhum
*Return: float
************************************************************/
float CVRView::GetPositionX()
{
	return vPosition.x;
}

/***********************************************************
*Name: GetPositionY()
*Description: retorna a posicao Y da camera
*Params: Nenhum
*Return: float
************************************************************/
float CVRView::GetPositionY()
{
	return vPosition.y;
}

/***********************************************************
*Name: GetPositionZ()
*Description: retorna a posicao Z da camera
*Params: Nenhum
*Return: float
************************************************************/
float CVRView::GetPositionZ()
{
	return vPosition.z;
}

/***********************************************************
*Name: GetPosition()
*Description: retorna o vetor com a posição da camera
*Params: Nenhum
*Return: CVRVector
************************************************************/
CVRVector CVRView::GetPosition()
{
	return vPosition;
}

/***********************************************************
*Name: UpdateCamera()
*Description: atualiza a posicao da camera
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRView::UpdateView()
{
	glLoadIdentity();

	float fRotAngle = fAngleY-90;

	float moveZ = vDirection.z * fSpeed * pManager->cTimeManager.GetFrameTime()/1000;
	float moveX = vDirection.x * fSpeed * pManager->cTimeManager.GetFrameTime()/1000;

	float cosYaw = cos(DEGTORAD(fRotAngle));
    float sinYaw = sin(DEGTORAD(fRotAngle));
	float sinPitch = sin(DEGTORAD(fAngleX));

	vPosition.x += (float)(cos(DEGTORAD(fAngleY)))* moveX;
	vPosition.z += (float)(sin(DEGTORAD(fAngleY)))* moveX;

	vPosition.x += (moveZ * cosYaw);
	vPosition.z += (moveZ * sinYaw); 

	vLookAt.x = float(vPosition.x + cosYaw);
	vLookAt.y = float(vPosition.y + sinPitch);
    vLookAt.z = float(vPosition.z + sinYaw);
	
	gluLookAt(vPosition.x, vPosition.y, vPosition.z,
			  vLookAt.x, vLookAt.y, vLookAt.z,
			  vUp.x, vUp.y, vUp.z);

	vDirection = CVRVector(0.0f,0.0f,0.0f);
}

/***********************************************************
*Name: RotY()
*Description: Rotaciona a camera em y
*Params: float
*Return: Nenhum
************************************************************/
void CVRView::RotY(float fAngle)
{
	if (fAngle > 360 || fAngle<-360)
	{
          fAngle = fmod(fAngle,360.0f);
	}
	
	fAngleY = fAngle;
}

/***********************************************************
*Name: RotX()
*Description: Rotaciona a camera em X
*Params: float
*Return: Nenhum
************************************************************/
void CVRView::RotX(float fAngle)
{
	if (fAngle>60)
	{
		fAngle=60;
	}
	else if (fAngle<-60)
	{
		fAngle=-60;
	}

	fAngleX = fAngle;
}

/***********************************************************
*Name: RotZ()
*Description: Rotaciona a camera em Z
*Params: float
*Return: Nenhum
************************************************************/
void CVRView::RotZ(float fAngle)
{
	fAngleZ = fAngle;
}

/***********************************************************
*Name: GetAngleX()
*Description: Retorna o angulo de rotação em X
*Params: Nenhum
*Return: float
************************************************************/
float CVRView::GetAngleX()
{
	return fAngleX;
}

/***********************************************************
*Name: GetAngleY()
*Description: Retorna o angulo de rotação em Y
*Params: Nenhum
*Return: Float Angulo
************************************************************/
float CVRView::GetAngleY()
{
	return fAngleY;
}

/***********************************************************
*Name: GetAngleZ()
*Description: Retorna o angulo de rotação em Z
*Params: Nenhum
*Return: float
************************************************************/
float CVRView::GetAngleZ()
{
	return fAngleZ;
}

/***********************************************************
*Name: MoveForward()
*Description: Avança a camera de acordo com a velocidade
*Params: nenhum
*Return: nenhum
************************************************************/
void CVRView::MoveForward()
{
	vDirection.z = 1.0f;
}

/***********************************************************
*Name: MoveBackWard()
*Description: retrocede a camera de acordo com a velocidade
*Params: nenhum
*Return: nenhum
************************************************************/
void CVRView::MoveBackward()
{
	vDirection.z = -1.0f;
}

/***********************************************************
*Name: MoveLeft()
*Description: desloca a camera para a esquerda
*Params: nenhum
*Return: nenhum
************************************************************/
void CVRView::MoveLeft()
{
	vDirection.x = -1.0f;
}

/***********************************************************
*Name: MoveRight()
*Description: desloca a camera para a direita
*Params: nenhum
*Return: nenhum
************************************************************/
void CVRView::MoveRight()
{
	vDirection.x = 1.0f;
}

/***********************************************************
*Name: SetSpeed()
*Description: configura a velocidade da camera
*Params: float
*Return: nenhum
************************************************************/
void CVRView::SetSpeed(float pSpeed)
{
	this->fSpeed = pSpeed;
}

/***********************************************************
*Name: GetSpeed()
*Description: retorna a velocidade da camera
*Params: nenhum
*Return: float
************************************************************/
float CVRView::GetSpeed()
{
	return fSpeed;
}

/***********************************************************
*Name: GetDirection()
*Description: retorna a direção da câmera
*Params: nenhum
*Return: CVRVector
************************************************************/
CVRVector CVRView::GetDirection()
{
	CVRVector vDirection;

	vDirection = vLookAt - vPosition;

	vDirection.Normalize();

	return vDirection;
}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRView::Release()
{
	
}
