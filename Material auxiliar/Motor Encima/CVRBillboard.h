/***********************************************************************
*Nome: CVRBillboard.h
*Descrição: Cabeçalho da classe responsável pela criação de um Billboard
*Data: 28/02/07
*Local: LNCC
************************************************************************/
#ifndef _CVRBILLBOARD_
#define _CVRBILLBOARD_

#include "CVRObject3D.h"
#include "CVRSprite.h"

class CVRBillboard: public CVRObject3D
{
private:
	CVRSprite* sprite;
	CVRVector vRight;
	CVRVector vUp;
	float fSize;

public:
	CVRBillboard();
	CVRBillboard(CVRSprite*);
	~CVRBillboard();
	void SetSize(float);
	float GetSize();
	void Update(float *);
	void Update();
	bool Init();
	void Render();
	void Release();
	void SetPosition(float, float, float);
	CVRSprite* GetSprite();
};
#endif