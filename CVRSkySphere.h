/***********************************************************************
*Nome: CVRSphere.h
*Descrição: Cabeçalho da classe que implementa o sky box
*Data: 21/05/07
*Local: LNCC
************************************************************************/
#ifndef _CVRSKYSPHERE_
#define _CVRSKYSPHERE_

#include "CVRObject3D.h"

class CVRSkySphere:public CVRObject3D
{
private:
	float fRadius;

public:
	CVRSkySphere(float, float, float, float);
	CVRSkySphere();
	~CVRSkySphere();

	void SetCenterPos(float, float, float);
	void SetRadius(float);
	void SetTexture(char*);

	float GetRadius();

	void Render();
	void Release();
	bool Init();
	void Update();
};
#endif