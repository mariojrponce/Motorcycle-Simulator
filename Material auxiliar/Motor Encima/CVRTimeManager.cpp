/***********************************************************************
*Nome: CVRTimeManager.cpp
*Descrição: Implementação da classe responsável pelo gerenciamento do tempo
*Data: 20/07/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRTimeManager.h"

/***********************************************************
*Name: CVRTimeManager()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRTimeManager::CVRTimeManager()
{
	uiLastFrameTime = GetTickCount();
	iFrameTime = 0;
	fFrameSec = 0.0;
	iTimeAcum = 0;
	iFrameCount = 0;
	iFPS = 0;
}

/***********************************************************
*Name: CVRTimeManager()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRTimeManager::~CVRTimeManager()
{

}

/***********************************************************
*Name: GetLastFrameTime()
*Description: retorna o tempo de término do ultimo frame
*Params: Nenhum
*Return: unsigned int
************************************************************/
unsigned int CVRTimeManager::GetLastFrameTime()
{
	return uiLastFrameTime;
}

/***********************************************************
*Name: GetFrameTime()
*Description: retorna o tempo de atualização do frame
*Params: Nenhum
*Return: int
************************************************************/
int CVRTimeManager::GetFrameTime()
{
	return iFrameTime;
}

/***********************************************************
*Name: GetFPSec
*Description: retorna o tempo de atualizaçao do frame em segundos
*Params: Nenhum
*Return: float
************************************************************/
float CVRTimeManager::GetFPSec()
{
	return fFrameSec;
}

/***********************************************************
*Name: GetTimeAccum()
*Description: retorna o valor do acumulador de tempo no momento
*Params: Nenhum
*Return: int
************************************************************/
int CVRTimeManager::GetTimeAccum()
{
	return iTimeAcum;
}

/***********************************************************
*Name: GetFrameCount()
*Description: retorna o valor do contador de frames no momento
*Params: Nenhum
*Return: int
************************************************************/
int CVRTimeManager::GetFrameCount()
{
	return iFrameCount;
}


/***********************************************************
*Name: GetFPS
*Description: retorna o numero de frames por segundo no momento
*Params: Nenhum
*Return: int
************************************************************/
int CVRTimeManager::GetFPS()
{
	return iFPS;
}

/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTimeManager::Release()
{
	
}

/***********************************************************
*Name: Update()
*Description: atualiza os tempos e valores
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTimeManager::Update()
{
	iFrameTime = 0;

	unsigned int uiCurrentTime=0;

	do
	{
		uiCurrentTime = GetTickCount();
		iFrameTime = (uiCurrentTime > uiLastFrameTime) ? (uiCurrentTime - uiLastFrameTime) : 0;
		uiLastFrameTime = (uiCurrentTime >= uiLastFrameTime) ? uiLastFrameTime : uiCurrentTime;
	}
	while(! (iFrameTime >= MININTERVAL));

	iTimeAcum += iFrameTime;
	iFrameCount++;
	fFrameSec = (float)iFrameTime * 0.001f;

	if (iTimeAcum >= 1000)
	{
		iFPS = iFrameCount;
		iFrameCount = 0;
		iTimeAcum   = 0;
	}

	uiLastFrameTime = uiCurrentTime;
}

/***********************************************************
*Name: ResetTime()
*Description: reinicializa
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRTimeManager::ResetTime()
{
	uiLastFrameTime = GetTickCount();
}