/***********************************************************************
*Nome: CVRCollisionManager.h
*Descrição: Cabeçalho da classe responsável pelo gerenciamento da detecção de colisão
*Data: 18/06/08
*Local: LNCC
************************************************************************/
#ifndef _CVRCOLLISIONMANAGER_
#define _CVRCOLLISIONMANAGER_

//Bibliotecas
#include "CVRObject.h"
#include "CVRObject3D.h"
#include "CVRMath.h"


// Constantes usadas em ClassifySphere()
#define S_BEHIND		0	// Retornado se a esfera está completamente atrás do plano
#define S_INTERSECTS	1	// Retornado se a esfera intersecta o plano
#define S_FRONT		2	// Retornado se a esfera está completamente na frente do plano

class CVRCollisionManager: public CVRObject
{
	public:
		CVRCollisionManager();
		~CVRCollisionManager();
		void Release();
		bool SphereSphereCollision(CVRBoundingSphere*, CVRBoundingSphere*);
		bool BoxBoxCollision(CVRBoundingBox*, CVRBoundingBox*);
		bool BoxSphereCollision(CVRBoundingBox*, CVRBoundingSphere*);
		bool SpherePolygonCollision(CVRBoundingSphere*, CVRVector*, int);
		bool BoxTriangleCollision(CVRBoundingBox*, CVRVector*);
		
		bool PolygonLineCollision(CVRVector*, CVRVector*, int);
		

		// SphereLine
		// BoxLine
		// PolygonPoint
				
	private:
		bool EdgeSphereCollision(CVRVector &vCenter, CVRVector vPolygon[], int vertexCount, float radius);
		int ClassifySphere(CVRVector&, CVRVector&, CVRVector&, float, float&);
		bool IntersectedPlane(CVRVector*, CVRVector*, CVRVector &, float &);
		CVRVector IntersectionPoint(CVRVector, CVRVector*, double);
		float SqDistPointAABB(CVRVector, CVRBoundingBox*);
};
#endif