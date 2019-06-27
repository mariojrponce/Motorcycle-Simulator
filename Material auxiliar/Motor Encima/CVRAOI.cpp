/***********************************************************************
*Nome: CVRAOI.cpp
*Descrição: Implementação da classe responsável pela criação de uma 
*			área de interesse em formato de esfera
*Data: 17/04/08
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRAOI.h"

#define BIGNUMBER 100000000.0 // cem mil 

/***********************************************************
*Name: CVRAOI()
*Description: construtor da classe default - cria uma área de interesse
*			  com raio 1 na posição (0,0,0), não visível
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRAOI::CVRAOI()
{
	fRadius = 1.0f;
	vPos = CVRVector(0.0f,0.0f,0.0f);
	vScale  = CVRVector(1.0f,1.0f,1.0f);
	vDirection = CVRVector(0.0f,0.0f,0.0f);
	bVisible = false;
}

/***********************************************************
*Name: CVRAOI()
*Description: construtor da classe - cria uma área de interesse
*			  com raio e posição especificados, não visível
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRAOI::CVRAOI(float radius, CVRVector pos, CVRVector scale)
{
	fRadius = radius;
	vPos = pos;
	vScale = scale;
	bVisible = false;
}

/***********************************************************
*Name: ~CVRAOI()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRAOI::~CVRAOI()
{
	
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAOI::Release()
{
	//Libera os elementos dos vectors
	for (int iIndex=(int)vObjStatic.size()-1; iIndex>=0; iIndex--)
	{
		vObjStatic[iIndex] = NULL;
		vObjStatic.erase(vObjStatic.begin()+iIndex);
	}

	for (int iIndex=(int)vObjDynamic.size()-1; iIndex>=0; iIndex--)
	{
		vObjDynamic[iIndex] = NULL;
		vObjDynamic.erase(vObjDynamic.begin()+iIndex);
	}
}

/***********************************************************
*Name: SetRadius()
*Description: configura o raio da área de interesse
*Params: int
*Return: Nenhum
************************************************************/
void CVRAOI::SetRadius(float radius)
{
	fRadius = radius;
}

/***********************************************************
*Name: GetRadius()
*Description: retorna o raio da área de interesse
*Params: Nenhum
*Return: float
************************************************************/
float CVRAOI::GetRadius()
{
	return fRadius;	
}

/***********************************************************
*Name: SetPosition()
*Description: Configura a posicao da área de interesse
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAOI::SetPosition(float fX, float fY, float fZ)
{
	vPos.SetX(fX);
	vPos.SetY(fY);
	vPos.SetZ(fZ);
}

/***********************************************************
*Name: GetPosition()
*Description: Retorna a posicao da área de interesse
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRVector CVRAOI::GetPosition()
{
	return vPos;
}

/***********************************************************
*Name: SetScale()
*Description: Configura a escala da área de interesse
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAOI::SetScale(float fX, float fY, float fZ)
{
	vScale.SetX(fX);
	vScale.SetY(fY);
	vScale.SetZ(fZ);
}

/***********************************************************
*Name: GetScale()
*Description: Retorna a escala da área de interesse
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRVector CVRAOI::GetScale()
{
	return vScale;
}

/***********************************************************
*Name: SetDirection()
*Description: Configura a direção da área de interesse
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAOI::SetDirection(float fX, float fY, float fZ)
{
	vDirection.SetX(fX);
	vDirection.SetY(fY);
	vDirection.SetZ(fZ);
}

/***********************************************************
*Name: GetDirection()
*Description: Retorna a direção da área de interesse
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRVector CVRAOI::GetDirection()
{
	return vDirection;
}

/***********************************************************
*Name: SetVisible()
*Description: configura se a área de interesse será visivel ou nao
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAOI::SetVisible(bool visible)
{
	bVisible = visible;
}

/***********************************************************
*Name: GetVisible()
*Description: retorna se a área de interesse será visivel ou nao
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRAOI::GetVisible()
{
	return bVisible;
}

/***********************************************************
*Name: DrawAOI()
*Description: desenha a área de interesse
*Params: bool
*Return: Nenhum
************************************************************/
void CVRAOI::DrawAOI()
{
	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glTranslatef(vPos.GetX(), vPos.GetY(), vPos.GetZ());
		glScalef(vScale.GetX(),vScale.GetY(),vScale.GetZ());
		auxSolidSphere(fRadius);
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glPopMatrix();
}

/***********************************************************
*Name: AddObjStatic()
*Description: adiciona um objeto estático ao vector de objetos estáticos
*Params: CVRObject3D
*Return: Nenhum
************************************************************/
void CVRAOI::AddObjStatic(CVRObject3D* obj)
{
    vObjStatic.push_back(obj);
}

/***********************************************************
*Name: AddObjDynamic()
*Description: adiciona um objeto dinâmico ao vector de objetos dinâmicos
*Params: CVRObject3D
*Return: Nenhum
************************************************************/
void CVRAOI::AddObjDynamic(CVRObject3D* obj)
{
	vObjDynamic.push_back(obj);
}

/***********************************************************
*Name: RemoveObjStatic()
*Description: remove um objeto estático ao vector de objetos estáticos
*Params: CVRObject3D
*Return: Nenhum
************************************************************/
void CVRAOI::RemoveObjStatic(CVRObject3D* obj)
{
	for (int iIndex=0; iIndex<(int)vObjStatic.size(); iIndex++)
	{
		if(vObjStatic[iIndex] == obj)
			vObjStatic.erase(vObjStatic.begin()+iIndex);
	}
}

/***********************************************************
*Name: RemoveObjStatic()
*Description: Remove um objeto estático ao vector de objetos estáticos
*Params: CVRObject3D
*Return: Nenhum
************************************************************/
void CVRAOI::RemoveObjDynamic(CVRObject3D* obj)
{
	for (int iIndex=0; iIndex<(int)vObjDynamic.size(); iIndex++)
	{
		if(vObjDynamic[iIndex] == obj)
			vObjDynamic.erase(vObjStatic.begin()+iIndex);
	}
}

/***********************************************************
*Name: TestCollision()
*Description: verifica se um objeto está dentro da área de interesse (AOI X BoundingSphere)
*Params: CVRObject3D*
*Return: bool
************************************************************/
bool CVRAOI::TestCollision(CVRObject3D* obj)
{
	CVRVector relPos = vPos - obj->GetPosition();
	float dist = relPos.GetX() * relPos.GetX() + relPos.GetY() * relPos.GetY() + relPos.GetZ() * relPos.GetZ();
	float minDist = fRadius + (obj->GetBSphere())->GetRadius();
	return dist <= minDist * minDist;
}


