/***********************************************************************
*Nome: CVRSprite.cpp
*Descrição: Implementação da classe responsável pela representação de um Sprite
*Data: 18/01/08
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRSprite.h"
#include "CVRLog.h"
#include "CVRManager.h"


/***********************************************************
*Name: CVRSprite()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSprite::CVRSprite()
{
	iCurrentAnim	= -1;
	pManager		= NULL;
	pImage			= NULL;
	frameSizeX = 0;
	frameSizeY = 0;
	imageId = 0;
	bFade = false;
	fFadeRange = 0.0f;
	fFadeTo = 0.0f;
	uiFadeTime			= 0;
	uiElapsedFadeTime	= 0;
	fAlpha = 0.0f;
	fScaleX = 1.0f;
	fScaleY = 1.0f;
}

/***********************************************************
*Name: ~CVRSprite()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSprite::~CVRSprite()
{

}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSprite::Release()
{
	char* name = pImage->GetImageName();
	pManager->cGraphicsManager.DeleteImage(&pImage);

	for(int iIndex = (int)vQuads.size()-1; iIndex >=0; iIndex--)
	{
		//vQuads[iIndex]->Release();
		delete vQuads[iIndex];
		vQuads[iIndex] = NULL;
		vQuads.erase(vQuads.begin()+iIndex);
	}
	vQuads.clear();
}


/***********************************************************
*Name: GetQuad()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRQuad CVRSprite::GetQuad()
{
	CVRQuad quad;
	quad.fLeft = fPosX - frameSizeX/2;  
	quad.fTop = fPosY - frameSizeY/2;
	quad.fRight = (quad.fLeft+ frameSizeX);
	quad.fBottom = (quad.fTop + frameSizeY);
	
	return quad;
}

/***********************************************************
*Name: GetQuad()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
void CVRSprite::SetCurrentAnimation(int iAnim)
{
	if(iAnim != iCurrentAnim)
	{
		iCurrentAnim = iAnim;
		ResetAnimation();
	}
}

/***********************************************************
*Name: Update()
*Description: Atualiza o sprite
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
void CVRSprite::Update()
{
	UpdateFade();
	if((this->iCurrentAnim >= 0) && (iCurrentAnim < (int)this->vQuads.size()))
	{
		vQuads[iCurrentAnim]->Update();
	}
}

/***********************************************************
*Name: ResetAnimation()
*Description: Reinicializa a animaçao
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
void CVRSprite::ResetAnimation()
{
	if(iCurrentAnim >= 0 && iCurrentAnim < (int)vQuads.size())
	{
		vQuads[iCurrentAnim]->Reset();
	}
}

/***********************************************************
*Name: EndedAnimation()
*Description: verifica se a animação do sprite acabou
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
bool CVRSprite::AnimationEnded()
{
	return vQuads[iCurrentAnim]->IsEnded();
}

/***********************************************************
*Name: AddAnimation
*Description: adiciona uma animação ao sprite
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSprite::AddAnimation(int iFPS, bool bRepeat, int iFrameCount,...)
{
	CVRAnim* anim= new CVRAnim();

	if (this->iCurrentAnim == -1)
	{
		iCurrentAnim = 0;
	}

	anim->pManager = this->pManager;
	anim->bRepeat = bRepeat;
	anim->SetFrameInterval(iFPS);

	va_list marker;
	va_start(marker,iFrameCount);

	for (int iIndex=0; iIndex<iFrameCount; iIndex++)
	{
		CVRQuad temp;

		int frameNumber = va_arg(marker,int);
		
		temp = CreateQuad(frameNumber);

		anim->bRepeat = bRepeat;
		anim->vIndexFrames.push_back(temp);
	}

	va_end(marker);

	vQuads.push_back(anim);
}

/***********************************************************
*Name: CreateQuad
*Description:cria um quadro para o sprite
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
CVRQuad CVRSprite::CreateQuad(int frameNumber)
{
	CVRQuad temp;

	int nLin = (int)pImage->GetImageHeight()/frameSizeY;
	int nCol = (int)pImage->GetImageWidth()/frameSizeX; 
	int indexLin = 0;
	int indexCol = 0;

	if (nCol > 0)
	{
		indexLin = (frameNumber / nCol);
		indexCol = (frameNumber % nCol);
	}

	temp.fTop = 1.0f - (indexLin * (1.0f / nLin));
	temp.fBottom = temp.fTop - (1.0f / nLin);

	temp.fLeft = indexCol * (1.0f / nCol);
	temp.fRight = temp.fLeft + (1.0f / nCol);

	return temp;
}

/***********************************************************
*Name: Draw
*Description:Faz as inicializações de variáveis
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
bool CVRSprite::Init()
{
	return true;
}

/***********************************************************
*Name: Init
*Description:Renderiza o sprite
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
void CVRSprite::Render()
{
	if (!bVisible)
	{
		return;
	}

	CVRQuad temp = GetQuad();

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,imageId);

	glEnable(GL_BLEND);
	glColor4f(1.0f,1.0f,1.0f,1.0f - fAlpha);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glAlphaFunc(GL_GREATER, 0.0);
	glEnable(GL_ALPHA_TEST);
	
	glPushMatrix();
	glScalef(fScaleX,fScaleY,1.0f);
	glTranslatef(fPosX, fPosY,0.0f);
	glRotatef(fAngle,0.0f,0.0f,1.0f);
	
	glBegin(GL_QUADS);
		glTexCoord2f(vQuads[iCurrentAnim]->GetCurrentFrame().fLeft, vQuads[iCurrentAnim]->GetCurrentFrame().fTop);
		glVertex2f(-frameSizeX/2,-frameSizeY/2);
		
		glTexCoord2f(vQuads[iCurrentAnim]->GetCurrentFrame().fLeft, vQuads[iCurrentAnim]->GetCurrentFrame().fBottom);
		glVertex2f(-frameSizeX/2, frameSizeY/2);
		
		glTexCoord2f(vQuads[iCurrentAnim]->GetCurrentFrame().fRight, vQuads[iCurrentAnim]->GetCurrentFrame().fBottom);
		glVertex2f(frameSizeX/2, frameSizeY/2);

		glTexCoord2f(vQuads[iCurrentAnim]->GetCurrentFrame().fRight,vQuads[iCurrentAnim]->GetCurrentFrame().fTop);
		glVertex2f(frameSizeX/2, -frameSizeY/2);
	glEnd();
	glPopMatrix();

	glDisable(GL_BLEND);
	glDisable(GL_ALPHA_TEST);
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
}

/***********************************************************
*Name: Create()
*Description:Cria o sprite
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
void CVRSprite::Create(char* fileName, char* alphaName, int x, int y)
{
	if(pManager)
	{
		imageId = pManager->cGraphicsManager.GetBindImage(fileName);

		frameSizeX = x;
		frameSizeY = y;

		if (imageId)
		{
			this->pImage = pManager->cGraphicsManager.GetImage(fileName);
			return;
		}

		pImage = pManager->cGraphicsManager.LoadImage(fileName, alphaName);

		if (!pImage || !pImage->GetImageData())
		{
			return;
		}
		
		glGenTextures(1,&imageId);
		glBindTexture(GL_TEXTURE_2D,imageId);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImage->GetImageWidth(), pImage->GetImageHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pImage->GetImageData());
		pManager->cGraphicsManager.AddBindImage(pImage->GetImageName(),imageId); 
	}
}

/***********************************************************
*Name: Create()
*Description:Cria o sprite
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
void CVRSprite::Create(char* fileName,int x, int y)
{
	if(pManager)
	{
		imageId = pManager->cGraphicsManager.GetBindImage(fileName);

		frameSizeX = x;
		frameSizeY = y;

		if (imageId)
		{
			this->pImage = pManager->cGraphicsManager.GetImage(fileName);
			return;
		}

		pImage = pManager->cGraphicsManager.LoadImage(fileName,true);

		if (!pImage || !pImage->GetImageData())
		{
			return;
		}
		
		glGenTextures(1,&imageId);
		glBindTexture(GL_TEXTURE_2D,imageId);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pImage->GetImageWidth(), pImage->GetImageHeight(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pImage->GetImageData());
		pManager->cGraphicsManager.AddBindImage(pImage->GetImageName(),imageId); 
	}
}

/***********************************************************
*Name: FadeOut()
*Description: faz o objeto sumir
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSprite::FadeOut(unsigned int time)
{
	if(fAlpha >= 0.0f)
	{
		Fade(0.0f,1.0f,time);
	}
}

/***********************************************************
*Name: FadeOut()
*Description: faz o objeto aparecer
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSprite::FadeIn(unsigned int time)
{
	if(fAlpha < 1.0f)
	{
		Fade(1.0f,0.0f,time);
	}
}

/***********************************************************
*Name: Fade()
*Description: aplica o fade ao objeto
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSprite::Fade(float fadeFrom, float fadeTo, unsigned int time)
{
	uiFadeTime = time;
	fFadeTo = fadeTo;
	fAlpha = fadeFrom;
	fFadeRange = abs(fadeFrom - fadeTo);
	bFade = (fadeFrom > fadeTo);

	if (time == 0)
	{
		fAlpha = fadeTo;
	}
}

/***********************************************************
*Name: UpdateFade()
*Description: atualiza o valor do fade
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSprite::UpdateFade()
{
	if (uiFadeTime)
	{
		uiElapsedFadeTime += (unsigned int)pManager->cTimeManager.GetFrameTime();

		if (uiFadeTime > uiElapsedFadeTime)
		{
			fAlpha = (fFadeRange * uiElapsedFadeTime) / uiFadeTime;
			fAlpha = (bFade) ? fFadeRange - fAlpha : fAlpha;
		}
		else
		{
			uiElapsedFadeTime = 0;
			uiFadeTime    = 0;
			fAlpha = fFadeTo;
			if (fFadeTo == 1.0f)
			{
				bVisible = false;
			}
		}
	}
}

/***********************************************************
*Name: FadeEnded()
*Description: verifica se o fade já acabou
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRSprite::FadeEnded()
{
	return (uiFadeTime <= 0);
}