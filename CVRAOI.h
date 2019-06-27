/***********************************************************************
*Nome: CVRAOI.h
*Descrição: Cabeçalho da classe que implementa uma área de interesse
*Data: 17/04/08
*Local: LNCC
************************************************************************/

#ifndef _CVRAOI_
#define _CVRAOI_

#include "CVRVector.h"
#include "CVRObject3D.h"

class CVRObject3D;
class CVRAOI
{
private:
	float fRadius;
	CVRVector vPos;
	CVRVector vScale;
	CVRVector vDirection;
	bool bVisible;

	vector<CVRObject3D *> vObjStatic;
	vector<CVRObject3D *> vObjDynamic;

public:
	CVRAOI();
	CVRAOI(float, CVRVector, CVRVector);
	~CVRAOI();	
	void Init();
	void Release();
	void SetRadius(float);
	float GetRadius();
	void SetPosition(float, float, float);
	CVRVector GetPosition();
	void SetScale(float, float, float);
	CVRVector GetScale();
	void SetDirection(float, float, float);
	CVRVector GetDirection();	
	void SetVisible(bool);
	bool GetVisible();
	void DrawAOI();
	void AddObjStatic(CVRObject3D*);
	void AddObjDynamic(CVRObject3D*);
	void RemoveObjStatic(CVRObject3D*);
	void RemoveObjDynamic(CVRObject3D*);
	bool TestCollision(CVRObject3D* obj);
};
#endif