/***********************************************************************
*Nome: CVRBoundingSphere.h
*Descrição: Cabeçalho da classe que implementa um envoltório no formato de esfera
*Data: 03/03/08
*Local: LNCC
************************************************************************/

#ifndef _CVRBOUNDINGSPHERE_
#define _CVRBOUNDINGSPHERE_

#include "CVRVector.h"
#include "CVRLog.h"

class CVRBoundingSphere
{
private:
	float fRadius;
	CVRVector vPos;
	CVRVector vScale;
	bool bVisible;
public:
	CVRBoundingSphere();
	~CVRBoundingSphere();	
	void SetRadius(float);
	float GetRadius();
	void SetPosition(float, float, float);
	CVRVector GetPosition();
	void SetScale(float, float, float);
	CVRVector GetScale();
	void SetVisible(bool);
	bool GetVisible();
};
#endif