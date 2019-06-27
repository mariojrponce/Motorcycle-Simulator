/***********************************************************************
*Nome: CVRObject2D.h
*Descrição: Cabeçalho da classe responsável pela renderização de um objeto 2D
*Data: 03/08/07
*Local: LNCC
************************************************************************/
#ifndef _CVROBJECT2D_
#define _CVROBJECT2D_

#include "CVRObject.h"

class CVRObject2D: public CVRObject
{
public:
		float fPosX, fPosY;
		float fAngle;
		bool bAutoRender;
		bool bVisible;
		unsigned int imageId;
		float fScaleX, fScaleY;
public:
	CVRObject2D();
	~CVRObject2D();
	virtual void Release()=0;
	virtual bool Init()=0;
	virtual void Render()=0;
	virtual void Update()=0;
	float GetPosX();
	float GetPosY();
	void SetPosX(float);
	void SetPosY(float);
	void SetPosXY(float, float);
	void SetVisible(bool);
	bool GetVisible();
	void SetScaleXY(float, float);
};
#endif;