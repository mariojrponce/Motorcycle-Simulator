/***********************************************************************
*Nome: CVRMath.h
*Descri��o: Cabe�alho respons�vel por oferecer fun��es matem�ticos b�sicas
*Data: 18/06/08
*Local: LNCC
************************************************************************/
#ifndef _CVRMATH_
#define _CVRMATH_

//Bibliotecas
#include "CVRVector.h"
#include "CVRObject3D.h"

CVRVector Normal(CVRVector vPolygon[]);
float Distance(CVRVector vPoint1, CVRVector vPoint2);
CVRVector ClosestPointOnLine(CVRVector vA, CVRVector vB, CVRVector vPoint);
float PlaneDistance(CVRVector Normal, CVRVector Point);
bool InsidePolygon(CVRVector vIntersection, CVRVector Poly[], long verticeCount);

#endif