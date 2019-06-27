/***********************************************************************
*Nome: CVRLog.h
*Descri��o: Cabe�alho da classe respons�vel pelo Log de informa��es
*Data: 25/01/07
*Local: LNCC
************************************************************************/
#ifndef _CVRLOG_
#define _CVRLOG_

#define LOG CVRLog::Get()

class CVRLog
{
private:
	//Instancia est�tica da aplica��o
	static CVRLog* pLog;
	char* fileName;
	//Construtor privado, esta classe n�o � instanciada
	CVRLog();
	~CVRLog();

public:
	bool Init(char*);

	void WriteToLog(char *, char*);
	
	static CVRLog* Get();
};

/***********************************************************
*Name: Get()
*Description: Retorna um ponteiro para uma instancia est�tica da classe
*Params: Nenhum
*Return: CVRLog
************************************************************/
inline CVRLog* CVRLog::Get()
{
	if(pLog == 0)
		pLog = new CVRLog;
	
	return pLog;
}

#endif