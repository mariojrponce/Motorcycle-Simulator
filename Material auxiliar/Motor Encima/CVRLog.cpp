/***********************************************************************
*Nome: CVRLog.cpp
*Descrição: Implementação da classe responsável pelo log de informações
*Data: 25/01/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRLog.h"
#include <cstdlib>
#include <cstdio>


//Instancia estática da classe
CVRLog * CVRLog::pLog = NULL;

/***********************************************************
*Name: CVRLog()
*Description: Construtor
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRLog::CVRLog()
{
	fileName = NULL;
}

/***********************************************************
*Name: ~CVRLog()
*Description: Destrutor
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRLog::~CVRLog()
{
	
}

/***********************************************************
*Name: Init()
*Description: Inicia o arquivo de log
*Params: char*
*Return: Nenhum
************************************************************/
bool CVRLog::Init(char* pFileName)
{
#ifdef _CVRDEBUG_
	FILE *pFile = NULL;

	pFile = fopen(pFileName,"wt");

	if(!pFile)
	{
		return false;
	}

	fprintf(pFile,"*************************************************\n");
	fprintf(pFile,"                   CVRLOG                        \n");
	fprintf(pFile,"*************************************************\n\n");

	fileName = pFileName;

	fclose(pFile);

	return true;
#endif

	return true;
}

/***********************************************************
*Name: WriteToLog
*Description: Escreve uma mensagem no log
*Params: char*, char*
*Return: Nenhum
************************************************************/
void CVRLog::WriteToLog(char* message, char* resource)
{
#ifdef _CVRDEBUG_
	FILE *pFile = NULL;

	pFile = fopen(fileName,"a");

	if(!pFile)
	{
		return;
	}

	fprintf(pFile,"%s %s\n",message,resource);

	fclose(pFile);
#endif
}
