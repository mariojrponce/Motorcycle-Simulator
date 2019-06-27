/***********************************************************************
*Nome: CVRBillboard.cpp
*Descrição: Implementação da classe responsável pela criação de um Billboard
*Data: 09/01/07
*Local: LNCC
************************************************************************/
#include "CVRBillboard.h"
#include "CVRImage.h"

/***********************************************************
*Name: CVRBillboard()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRBillboard::CVRBillboard()
{
	sprite = NULL;
	fSize = 1.0f;
}

/***********************************************************
*Name: CVRBillboard()
*Description: construtor da classe
*Params: CVRSprite*
*Return: Nenhum
************************************************************/
CVRBillboard::CVRBillboard(CVRSprite* pSprite)
{
	sprite = pSprite;
}

/***********************************************************
*Name: ~CVRBillboard()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRBillboard::~CVRBillboard()
{

}

/***********************************************************
*Name: SetSize()
*Description: configura o tamanho do billboard
*Params: float
*Return: Nenhum
************************************************************/
void CVRBillboard::SetSize(float pSize)
{
	fSize = pSize;
	CVRVector* vertex = new CVRVector();
	vertex->SetX(pSize);
	vertex->SetY(pSize);
	vertex->SetZ(pSize);
	CalculateBoundings(vertex, 1);
}

/***********************************************************
*Name: GetSize()
*Description: retorna a altura do billboard
*Params: Nenhum
*Return: float
************************************************************/
float CVRBillboard::GetSize()
{
	return fSize;
}

/***********************************************************
*Name: Update()
*Description: Atualiza a rotação do billboard
*Params: float*
*Return: Nenhum
************************************************************/
void CVRBillboard::Update(float *matrix)
{
	CVRObject3D::Update();

	vRight.x = matrix[0]; 
	vRight.y = matrix[4];
	vRight.z = matrix[8];
	
	vUp.x = matrix[1];
	vUp.y = matrix[5];
	vUp.z = matrix[9];
}

/***********************************************************
*Name: Update()
*Description: Atualiza a rotação do billboard
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBillboard::Update()
{
	CVRObject3D::Update();

	float matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

	vRight.x = matrix[0]; 
	vRight.y = matrix[4];
	vRight.z = matrix[8];
	
	vUp.x = matrix[1];
	vUp.y = matrix[5];
	vUp.z = matrix[9];
}

/***********************************************************
*Name: Render()
*Description: Desenha o billboard
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBillboard::Render()
{
	//Verifica se está visível
	if (!bVisible)
	{
		return;
	}

	//Verifica se o sprite existe
	if (!sprite)
	{
		return;
	}

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, sprite->imageId);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);

	glPushMatrix();

	glScalef(vScale.x,vScale.y,vScale.z);

	glBegin(GL_QUADS);
		CVRVector vTemp = vPos + ((vRight + vUp) * -fSize);
		glTexCoord2f(sprite->vQuads[sprite->iCurrentAnim]->GetCurrentFrame().fLeft, sprite->vQuads[sprite->iCurrentAnim]->GetCurrentFrame().fBottom);
		glVertex3f(vTemp.x, vTemp.y, vTemp.z);
	 
		vTemp = vPos + ((vRight - vUp) * fSize);
		glTexCoord2f(sprite->vQuads[sprite->iCurrentAnim]->GetCurrentFrame().fRight, sprite->vQuads[sprite->iCurrentAnim]->GetCurrentFrame().fBottom);
		glVertex3f(vTemp.x, vTemp.y, vTemp.z);

		vTemp = vPos + ((vRight + vUp) * fSize);
		glTexCoord2f(sprite->vQuads[sprite->iCurrentAnim]->GetCurrentFrame().fRight, sprite->vQuads[sprite->iCurrentAnim]->GetCurrentFrame().fTop);
		glVertex3f(vTemp.x, vTemp.y, vTemp.z);

		vTemp = vPos + ((vUp - vRight) * fSize);
		glTexCoord2f(sprite->vQuads[sprite->iCurrentAnim]->GetCurrentFrame().fLeft,sprite->vQuads[sprite->iCurrentAnim]->GetCurrentFrame().fTop);
		glVertex3f(vTemp.x, vTemp.y, vTemp.z);
	 glEnd();

	 glPopMatrix();
	 
	 glDepthMask(GL_TRUE);
	 glDisable(GL_BLEND);
	 glDisable(GL_TEXTURE_2D);
	 glBindTexture(GL_TEXTURE_2D,0);
}

/***********************************************************
*Name: SetPosition()
*Description: Configura a posicao do Billboard
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRBillboard::SetPosition(float fX, float fY, float fZ)
{
	vPos.x = fX;
	vPos.y = fY;
	vPos.z = fZ;
}

/***********************************************************
*Name: Release()
*Description: Libera a textura
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRBillboard::Release()
{
	pGraphicsManager->ReleaseBindImage(imageId);
	sprite = NULL;
	imageId = 0;
}

/***********************************************************
*Name: Init()
*Description: inicializa recuros
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRBillboard::Init()
{
	CVRObject3D::Init();
	return true;
}

/***********************************************************
*Name: GetSprite()
*Description: retorna o sprite do billboard
*Params: Nenhum
*Return: CVRSprite*
************************************************************/
CVRSprite* CVRBillboard::GetSprite()
{
	return sprite;
}
