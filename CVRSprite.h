/***********************************************************************
*Nome: CVSprite.h
*Descrição: Cabeçalho da classe responsável pela criação de um Sprite
*Data: 18/01/08
*Local: LNCC
************************************************************************/
#ifndef _CVRSPRITE_
#define _CVRSPRITE_

//Bibliotecas
#include "CVRObject2D.h"
#include "CVRImage.h"
#include "CVRAnim.h"
#include "CVRQuad.h"

class CVRManager;

class CVRSprite: public CVRObject2D
{
public:
	CVRManager* pManager;
	CVRImage* pImage;
	int iCurrentAnim;
	vector<CVRAnim*> vQuads;
	int frameSizeX, frameSizeY;
	bool bFade;
	unsigned int uiFadeTime;
	unsigned int uiElapsedFadeTime;
	float fAlpha;
	float fFadeRange, fFadeTo;

public:

	CVRSprite();

	~CVRSprite();

	void Release();

	void Create(char*,int, int);

	void Create(char*,char*,int, int);

	void AddAnimation(int, bool, int,...);

	void ResetAnimation(void);

	void SetCurrentAnimation(int);

	bool AnimationEnded();

	CVRQuad GetQuad(void);

	bool Init();

	void Render();

	CVRQuad CreateQuad(int);

	void Update();
	
	void Fade(float, float, unsigned int);
	
	void FadeIn(unsigned int);
	
	void FadeOut(unsigned int);
	
	void UpdateFade();

	bool FadeEnded();
};
#endif