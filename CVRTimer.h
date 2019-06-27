/***********************************************************************
*Nome: CVRTimer.h
*Descrição: Cabeçalho da classe responsável pelo gerenciamento do tempo
*Data: 24/01/07
*Local: LNCC
************************************************************************/
#ifndef _CVRTIMER_
#define _CVRTIMER_

#include "CVRObject.h"

class CVRTimeManager;

class CVRTimer: public CVRObject
{
//Atributos do tempo
public:
	unsigned int endTime;
	unsigned int currentTime; 
	CVRTimeManager* timeManager;

//Métodos do tempo
public:

	CVRTimer();
	CVRTimer(unsigned int);
	~CVRTimer();
	void Update();
	bool TimerEnded();
	void ResetTime();
	void ResetTime(unsigned int);
	unsigned int GetCurrentTimeMS();
	float GetCurrentTimeS();
	bool Init(CVRTimeManager*);
	void Release();
	unsigned int GetElapsedTime();
};
#endif;