/***********************************************************************
*Nome: CVRBoundingBox.h
*Descrição: Cabeçalho da classe que implementa um envoltório no formato de caixa
*Data: 03/03/08
*Local: LNCC
************************************************************************/

#ifndef _CVRBOUNDINGBOX_
#define _CVRBOUNDINGBOX_

#include "CVRVector.h"
#include "CVRLog.h"

class CVRBoundingBox
{
private:
	float fDimension;
	CVRVector vPos;
	CVRVector vScale;
	bool bVisible;
public:
	CVRBoundingBox();
	~CVRBoundingBox();	
	void SetDimension(float);
	float GetDimension();
	void SetPosition(float, float, float);
	CVRVector GetPosition();
	void SetScale(float, float, float);
	CVRVector GetScale();
	void SetVisible(bool);
	bool GetVisible();
};
#endif