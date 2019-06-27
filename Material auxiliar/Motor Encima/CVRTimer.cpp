/***********************************************************************
*Nome: CVRTimer.cpp
*Descrição: Implementação da classe responsável pelo gerenciamento do tempo
*Data: 18/01/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRTimer.h"
#include "CVRTimeManager.h"

/***********************************************************
*Name: CVRTimer()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRTimer::CVRTimer()
{
	currentTime = 0;
	endTime = 1000;
	timeManager = NULL;
}

/***********************************************************
*Name: CVRTimer()
*Description: construtor da classe
*Params: long int
*Return: Nenhum
************************************************************/
CVRTimer::CVRTimer(unsigned int time)
{
	endTime = time;
	currentTime = 0; 
	timeManager = NULL;
}

/***********************************************************
*Name: CVRTimer()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRTimer::~CVRTimer()
{

}

/***********************************************************
*Name: Update()
*Description: Atualiza os intervalos de tempo
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTimer::Update()
{
	if (timeManager)
	{
		currentTime += (unsigned int)timeManager->GetFrameTime();
	}
}

/***********************************************************
*Name: TimerEnded()
*Description: Retorna se o tempo acabou ou nao
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRTimer::TimerEnded()
{
	if (currentTime >= endTime)
		return true;

	return false;
}

/***********************************************************
*Name: Reset()
*Description: Reinicializa os intervalos de tempo
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTimer::ResetTime()
{
	currentTime %= endTime;
}

/***********************************************************
*Name: Reset()
*Description: Reinicializa os intervalos de tempo com um novo final
*Params: undigned int
*Return: Nenhum
************************************************************/
void CVRTimer::ResetTime(unsigned int newTime)
{
	currentTime = 0;
	endTime = newTime;
}

/***********************************************************
*Name: GetCurrentTimeMS()
*Description: Retorna o tempo passado desde a inicialização do timer em ms
*Params: Nenhum
*Return: unsigned int
************************************************************/
unsigned int CVRTimer::GetCurrentTimeMS()
{
	return currentTime;
}

/***********************************************************
*Name: GetCurrentTime()
*Description: Retorna o tempo passado desde a inicialização do timer em s
*Params: Nenhum
*Return: float
************************************************************/
float CVRTimer::GetCurrentTimeS()
{
	return (float)currentTime/1000;
}

/***********************************************************
*Name: Init()
*Description: Inicia o timer
*Params: CVRTimeManager*
*Return: bool
************************************************************/
bool CVRTimer::Init(CVRTimeManager* pTimeManager)
{
	if (pTimeManager)
	{
		timeManager = pTimeManager;
		return true;
	}

	return false;
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: void
************************************************************/
void CVRTimer::Release()
{
	
}

/***********************************************************
*Name: GetElapsedTime()
*Description: retorna o tempo gasto pelo frame
*Params: Nenhum
*Return: unsigned int
************************************************************/
unsigned int CVRTimer::GetElapsedTime()
{
	if (timeManager)
	{
		return timeManager->GetFrameTime();
	}

	return 0;
}

