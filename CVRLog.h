/***********************************************************************
*Nome: CVRLog.h
*Descrição: Cabeçalho da classe responsável pelo Log de informações
*Data: 25/01/07
*Local: LNCC
************************************************************************/
#ifndef _CVRLOG_
#define _CVRLOG_

#define LOG CVRLog::Get()

class CVRLog
{
private:
	//Instancia estática da aplicação
	static CVRLog* pLog;
	char* fileName;
	//Construtor privado, esta classe não é instanciada
	CVRLog();
	~CVRLog();

public:
	bool Init(char*);

	void WriteToLog(char *, char*);
	
	static CVRLog* Get();
};

/***********************************************************
*Name: Get()
*Description: Retorna um ponteiro para uma instancia estática da classe
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