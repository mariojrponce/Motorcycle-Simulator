/***********************************************************************
*Nome: CVRAnim.h
*Descrição: Cabeçalho da classe responsável pela representação de uma animação
*Data: 15/01/08
*Local: LNCC
************************************************************************/
#ifndef _CVRANIM_
#define _CVRANIM_

//Bibliotecas
#include "CVRTimer.h"
#include "CVRObject.h"
#include "CVRQuad.h"

class CVRManager;

class CVRAnim: public CVRObject
{
private:
	CVRTimer timer;
	int iFPS;

public:
	CVRManager* pManager;
	bool bRepeat;
	vector<CVRQuad> vIndexFrames;
	int iCurrentFrame;

public:
	CVRAnim();
	~CVRAnim();
	bool IsEnded();
	void Update();
	CVRQuad GetCurrentFrame();
	void Reset();
	void SetFrameInterval(int iFrameInterval,unsigned int uiTimeAccum = 0);
	void Release();
};
#endif