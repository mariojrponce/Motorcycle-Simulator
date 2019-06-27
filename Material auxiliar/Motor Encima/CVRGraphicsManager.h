/***********************************************************************
*Nome: CVRGraphicsManager.h
*Descrição: Cabeçalho da classe responsável pelo gerenciamento de recursos gráficos
*Data: 25/07/07
*Local: LNCC
************************************************************************/
#ifndef _CVRGRAPHICSMANAGER_
#define _CVRGRAPHICSMANAGER_

//Bibliotecas
#include "CVRObject.h"
#include "CVRImage.h"
#include "CVRFont.h"

class CVRManager;

struct sBindImage
{
	char name[STRINGSIZE];
	unsigned int code;
	int references;
};

class CVRGraphicsManager: public CVRObject
{
public:
	CVRManager* pManager;
	short r, g, b;
	
public:
	CVRGraphicsManager();
	~CVRGraphicsManager();
	void Release();
	void SaveScreenShot(char* fileName=NULL, int x=0, int y=0, int width=800, int height=600);
	void SetColorKey(short, short, short);
	CVRImage* LoadImage(char* fileName=NULL, bool transparency=false);
	CVRImage* LoadImage(char* fileName=NULL, char* alphaName=NULL);
	void DeleteImage(CVRImage**);
	unsigned int GetBindImage(char*);
	void AddBindImage(char*, unsigned int);
	void ReleaseBindImage(unsigned int);
	CVRImage* GetImage(char*);

private:
	vector<CVRImage *> vImages;
	vector<sBindImage> vBImages;
};
#endif