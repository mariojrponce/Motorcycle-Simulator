/***********************************************************************
*Nome: CVRLoadingBar.h
*Descri��o: Cabe�alho da classe respons�vel pela cria��o da barra de 
			loading
*Data: 29/02/08
*Local: LNCC
************************************************************************/
#ifndef _CVRLOADINGBAR_
#define _CVRLOADINGBAR_

#include "CVRObject2D.h"
#include "CVRQuad.h"

class CVRLoadingBar: public CVRObject2D
{
private:
	int iRight;
	int iHeight;
	int iWidth;
	int iPercentage;
	
	float fullColor[3];
	float emptyColor[3];

public:
	CVRLoadingBar(int,int);

	~CVRLoadingBar();

	void SetPercentage(int);

	void SetBorderColor(float, float, float);

	void SetBarColor(float, float, float);

	void Render();

	void Update();

	void Release();

	bool Init();

	int GetPercentage();
};
#endif