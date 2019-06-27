/***********************************************************************
*Nome: CVRTimer.h
*Descrição: Cabeçalho da classe responsável pelo gerenciamento do tempo
*Data: 24/01/07
*Local: LNCC
************************************************************************/
#ifndef _CVRTIMEMANAGER_
#define _CVRTIMEMANAGER_

//Bibliotecas
#include "CVRObject.h"

#define MININTERVAL 5

class CVRTimeManager: public CVRObject
{
private:
	unsigned int uiLastFrameTime;
	int iFrameTime;
	float fFrameSec;
	int iTimeAcum;
	int	iFrameCount;
	int	iFPS;

public:

	CVRTimeManager();

	~CVRTimeManager();

	void ResetTime();

	unsigned int GetLastFrameTime();

	int GetFrameTime();

	int GetFPS();

	float GetFPSec();

	int GetTimeAccum();

	int GetFrameCount();

	void Update();

	void Release();
};
#endif