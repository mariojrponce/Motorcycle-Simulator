/***********************************************************************
*Nome: CVRObject3D.cpp
*Descrição: Classe que implementa os métodos para os objetos 3D
*Data: 03/08/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRObject3D.h"
#include "CVRTimeManager.h"
#include "CVRManager.h"

#define BIGNUMBER 100000000.0 // cem mil 

/***********************************************************
*Name: CVRObject3D()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRObject3D::CVRObject3D()
{
	pGraphicsManager = NULL;
	fRadius = 0.0;
	vPos = CVRVector(0.0f,0.0f,0.0f);
	vScale  = CVRVector(1.0f,1.0f,1.0f);
	vAngle  = CVRVector(0.0f,0.0f,0.0f);
	imageId = 0;
	bAutoRender = false;
	bVisible = true;
	bCollidable = true;
	pBoundingSphere = new CVRBoundingSphere();
	pBoundingBox = new CVRBoundingBox();
	pAOI = new CVRAOI();
}

/***********************************************************
*Name: ~CVRObject3D()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRObject3D::~CVRObject3D()
{
}

/***********************************************************
*Name: SetVisible()
*Description: configura se o objeto será visto ou nao
*Params: bool
*Return: Nenhum
************************************************************/
void CVRObject3D::SetVisible(bool visible)
{
	bVisible = visible;
}

/***********************************************************
*Name: GetVisible()
*Description: retorna se o objeto será visto ou nao
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRObject3D::GetVisible()
{
	return bVisible;
}

/***********************************************************
*Name: SetPosition()
*Description: Configura a posicao do objeto
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRObject3D::SetPosition(float fX, float fY, float fZ)
{
	vPos.x = fX;
	vPos.y = fY;
	vPos.z = fZ;
}

/***********************************************************
*Name: GetPosition()
*Description: Retorna a posicao do objeto
*Params: Nenhum
*Return: CVRVector
************************************************************/
CVRVector CVRObject3D::GetPosition()
{
	return vPos;
}

/***********************************************************
*Name: SetScale()
*Description: Configura a escala do objeto
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRObject3D::SetScale(float fX, float fY, float fZ)
{
	vScale.x = fX;
	vScale.y = fY;
	vScale.z = fZ;
	
	// Atualiza a escala dos Boundings
	pBoundingSphere->SetScale(fX, fY, fZ);
	pBoundingBox->SetScale(fX, fY, fZ);
}

/***********************************************************
*Name: GetScale()
*Description: Retorna a escala do objeto
*Params: Nenhum
*Return: CVRVector
************************************************************/
CVRVector CVRObject3D::GetScale()
{
	return vScale;
}

/***********************************************************
*Name: RotateAll()
*Description: Configura a rotação do objeto em todos os angulos
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRObject3D::RotAll(float fX, float fY, float fZ)
{
	vAngle.x = fX;
	vAngle.y = fY;
	vAngle.z = fZ;
}

/***********************************************************
*Name: RotX()
*Description: Configura a rotação do objeto no eixo X
*Params: float
*Return: Nenhum
************************************************************/
void CVRObject3D::RotX(float fX)
{
	vAngle.x = fX;
}

/***********************************************************
*Name: RotY()
*Description: Configura a rotação do objeto no eixo Y
*Params: float
*Return: Nenhum
************************************************************/
void CVRObject3D::RotY(float fY)
{
	vAngle.y = fY;
}

/***********************************************************
*Name: RotZ()
*Description: Configura a rotação do objeto no eixo Z
*Params: float
*Return: Nenhum
************************************************************/
void CVRObject3D::RotZ(float fZ)
{
	vAngle.z = fZ;
}

/***********************************************************
*Name: GetAngle()
*Description: retorna o vetor de angulos
*Params: Nenhum
*Return: CVRVector
************************************************************/
CVRVector CVRObject3D::GetAngle()
{
	return vAngle;
}

/***********************************************************
*Name: SetCollidable()
*Description: configura se o objeto será colidível ou nao
*Params: bool
*Return: Nenhum
************************************************************/
void CVRObject3D::SetCollidable(bool collidable)
{
	bCollidable = collidable;
}

/***********************************************************
*Name: GetCollidable()
*Description: retorna se o objeto será colídivel ou nao
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRObject3D::GetCollidable()
{
	return bCollidable;
}

/***********************************************************
*Name: CalculateBoundings()
*Description: calcula o raio do BoundingSphere e as dimensões do BoundingBox 
*			  baseado no valor do ponto mais distante do objeto
*Params: Nenhum
*Return: void
************************************************************/
void CVRObject3D::CalculateBoundings(CVRVector* vertex, long int size)
{
	// Percorrer por todos os vértices da geometria
	for(int i = 0; i < size; i++)
	{
		// Armazena o maior vértice
		if (fRadius <  abs(vertex[i].GetX()))
		{
			fRadius = abs(vertex[i].GetX());
		}

		if (fRadius < abs(vertex[i].GetY()))
		{
			fRadius = abs(vertex[i].GetY());
		}

		if (fRadius < abs(vertex[i].GetZ()))
		{
			fRadius = abs(vertex[i].GetZ());
		}
	}
	pBoundingSphere->SetRadius(fRadius);
	pBoundingBox->SetDimension(fRadius);
}

/***********************************************************
*Name: GetBSphere()
*Description: retorna uma referência para o envoltório esfera do objeto
*Params: Nenhum
*Return: CVRBoundingSphere*
************************************************************/
CVRBoundingSphere* CVRObject3D::GetBSphere()
{
	return pBoundingSphere;
}

/***********************************************************
*Name: GetBBox()
*Description: retorna uma referência para o envoltório caixa do objeto
*Params: Nenhum
*Return: CVRBoundingBox*
************************************************************/
CVRBoundingBox* CVRObject3D::GetBBox()
{
	return pBoundingBox;
}

/***********************************************************
*Name: UpdateBounding()
*Description: atualiza o movimento dos boundings do objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject3D::UpdateBoundings()
{
	pBoundingSphere->SetPosition(vPos.x, vPos.y, vPos.z);
	pBoundingBox->SetPosition(vPos.x, vPos.y, vPos.z);
}

/***********************************************************
*Name: GetAOI()
*Description: retorna uma referência para a área de interesse do objeto
*Params: Nenhum
*Return: CVRAOI*
************************************************************/
CVRAOI* CVRObject3D::GetAOI()
{
	return pAOI;
}

/***********************************************************
*Name: UpdateAOI()
*Description: atualiza o movimento do área de interesse do objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject3D::UpdateAOI()
{
	pAOI->SetPosition(vPos.x, vPos.y, vPos.z);
}


/***********************************************************
*Name: InterpolateEnded()
*Description: verifica se esta ou nao em movimento
*Params: Nenhum
*Return: boolean
************************************************************/
bool CVRObject3D::InterpolateEnded()
{
	return (moveTimer.endTime == 0);
}

/***********************************************************
*Name: MoveTo()
*Description: move o billboard para uma posição usando o tempo
*Params: int, float, float, float
*Return: Nenhum
************************************************************/
void CVRObject3D::Interpolate(unsigned int iTime, CVRVector vNewPos)
{
	vInitMove = vPos;
	vEndMove = vNewPos;

	if (iTime<=0 || (vInitMove == vEndMove))
	{
		vPos = vEndMove;
		moveTimer.ResetTime(0);
	}
	else
	{
		moveTimer.ResetTime(iTime);
	}
}

/***********************************************************
*Name: UpdateMovement()
*Description: atualiza o movimento do objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject3D::UpdateMovement()
{
	moveTimer.Update();

	if (moveTimer.endTime !=0)
	{
		if (!moveTimer.TimerEnded())
		{
			vPos.x = vInitMove.x;
			vPos.x += (vInitMove.x < vEndMove.x) ? -((vInitMove.x - vEndMove.x) * moveTimer.currentTime)/moveTimer.endTime: -(abs(vInitMove.x - vEndMove.x) * moveTimer.currentTime)/moveTimer.endTime;

			vPos.y = vInitMove.y;
			vPos.y += (vInitMove.y < vEndMove.y) ? -((vInitMove.y - vEndMove.y) * moveTimer.currentTime)/moveTimer.endTime: -(abs(vInitMove.y - vEndMove.y) * moveTimer.currentTime)/moveTimer.endTime;

			vPos.z = vInitMove.z;
			vPos.z += (vInitMove.z < vEndMove.z) ? -((vInitMove.z - vEndMove.z) * moveTimer.currentTime)/moveTimer.endTime: -(abs(vInitMove.z - vEndMove.z) * moveTimer.currentTime)/moveTimer.endTime;
		}
		else
		{
			vPos = vEndMove;
			moveTimer.ResetTime(0);
		}
	}
}

/***********************************************************
*Name: Update()
*Description: realiza as atualizações no objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject3D::Update()
{
	// Atualiza movimento do objeto
	UpdateMovement();
	// Atualiza movimento dos bounds
	UpdateBoundings();
	// Atualiza o movimento da área de interesse
	UpdateAOI();
}

/***********************************************************
*Name: Init()
*Description: realiza as inicializações
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRObject3D::Init()
{
	moveTimer.Init(&(pGraphicsManager->pManager->cTimeManager));
	moveTimer.ResetTime(0);
	return true;
}

/***********************************************************
*Name: Render()
*Description: renderiza o objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRObject3D::Render()
{
}

/***********************************************************
*Name: SetBoundingFactor()
*Description: configura o fator de ajuste dos bounds
*Params: float
*Return: Nenhum
************************************************************/
void CVRObject3D::SetBoundingFactor(float pFactor)
{
	GetBSphere()->SetRadius(GetBSphere()->GetRadius() * pFactor);
	GetBBox()->SetDimension(GetBBox()->GetDimension() * pFactor);
}