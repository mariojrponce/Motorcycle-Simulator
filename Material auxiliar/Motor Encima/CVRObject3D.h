/***********************************************************************
*Nome: CVRObject3D.h
*Descrição: Cabeçalho da classe responsável pela renderização de um objeto 3D
*Data: 03/08/07
*Local: LNCC
************************************************************************/
#ifndef _CVROBJECT3D_
#define _CVROBJECT3D_

#include "CVRObject.h"
#include "CVRVector.h"
#include "CVRGraphicsManager.h"
#include "CVRTimer.h"
#include "CVRBoundingSphere.h"
#include "CVRBoundingBox.h"
#include "CVRAOI.h"

class CVRAOI;
class CVRObject3D: public CVRObject
{
public:
	CVRGraphicsManager* pGraphicsManager;
	unsigned int imageId;
	CVRVector vPos;
	CVRVector vScale;
	CVRVector vAngle;
	CVRVector vInitMove;
	CVRVector vEndMove;
	CVRTimer moveTimer;
	bool bAutoRender;
	bool bVisible;
	bool bCollidable;
	CVRBoundingSphere* pBoundingSphere;
	CVRBoundingBox* pBoundingBox;
	CVRAOI* pAOI;
	
public:
	CVRObject3D();
	~CVRObject3D();
	virtual void Release()=0;
	virtual bool Init();
	virtual void Render();
	virtual void Update();
	void SetVisible(bool);
	bool GetVisible();
	void SetPosition(float, float, float);
	CVRVector GetPosition();
	void SetScale(float, float, float);
	CVRVector GetScale();
	void RotAll(float, float, float);
	void RotX(float);
	void RotY(float);
	void RotZ(float);
	CVRVector GetAngle();
	void SetCollidable(bool);
	bool GetCollidable();
	void CalculateBoundings(CVRVector*, long int);
	CVRBoundingSphere* GetBSphere();
	CVRBoundingBox* GetBBox();
	void UpdateBoundings();
	CVRAOI* GetAOI();
	void UpdateAOI();
	void Interpolate(unsigned int, CVRVector);
	bool InterpolateEnded();
	void UpdateMovement();
	void SetBoundingFactor(float);
private:
	float fRadius;
};
#endif;