/***********************************************************************
*Nome: CVRMath.h
*Descrição: Cabeçalho responsável por oferecer funções matemáticos básicas
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