/***********************************************************************
*Nome: CVRAnim.cpp
*Descrição: Implementação da classe responsável por uma animação
*Data: 11/01/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRAnim.h"
#include "CVRManager.h"
#include "CVRLog.h"


/***********************************************************
*Name: CVRAnim()
*Description: construtor da classe 
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRAnim::CVRAnim()
{
	bRepeat					= false;
	iCurrentFrame			= 0;
	iFPS					= 1;
	pManager				= NULL;
}

/***********************************************************
*Name: CVRAnim()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRAnim::~CVRAnim()
{
	
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAnim::Release()
{
	
}

/***********************************************************
*Name: IsEnded()
*Description: verifica se a animação já terminou
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRAnim::IsEnded()
{
	return (bRepeat)? false : iCurrentFrame >= (int)vIndexFrames.size();
}

/***********************************************************
*Name: GetCurrentFrame()
*Description: retorna o frame atual da animacao
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRQuad CVRAnim::GetCurrentFrame()
{
	return (iCurrentFrame >= 0 && iCurrentFrame < (int)vIndexFrames.size())? vIndexFrames[iCurrentFrame] : vIndexFrames[vIndexFrames.size()-1];
}

/***********************************************************
*Name: Reset()
*Description: reinicia a animaçao
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAnim::Reset()
{
	timer.ResetTime((iFPS) ? 1000/iFPS : 1);
	iCurrentFrame = 0;
}

/***********************************************************
*Name: SetFrameInterval()
*Description: configura o intervalo entre frames
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAnim::SetFrameInterval(int interval,unsigned int iTime)
{
	iFPS = interval;
	timer.Init(&pManager->cTimeManager);
	timer.ResetTime((iFPS) ? 1000/iFPS : 1);
	timer.currentTime = iTime;
}

/***********************************************************
*Name:Update()
*Description: configura o intervalo entre frames
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRAnim::Update()
{
	if (pManager)
	{
		timer.Update();

		if (timer.TimerEnded())
		{
			unsigned int frameInterval = (iFPS)? 1000/iFPS : 1;

			int iSum = (int)(timer.currentTime / frameInterval);

			if(bRepeat)
			{
				iCurrentFrame += iSum;
				iCurrentFrame %= vIndexFrames.size();
			}
			else
			{
				iCurrentFrame += (iCurrentFrame < (char)vIndexFrames.size())? iSum : 0;
			}
			timer.ResetTime();
		}
	}
}