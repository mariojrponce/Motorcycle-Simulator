/***********************************************************************
*Nome: CVRVector.h
*Descrição: Cabeçalho da classe que implementa um vetor
*Data: 07/02/07
*Local: LNCC
************************************************************************/
#ifndef _CVRVECTOR_
#define _CVRVECTOR_

//Bibliotecas
#include "CVRObject.h"
#include <cmath>

#define PI 3.14159265359f
#define DEGTORAD(DEG) ((DEG*PI)/180)
#define RADTODEG(RAD) ((RAD*180)/PI)

class CVRVector: public CVRObject
{
public:
	float x;
	float y;
	float z;

public:

	CVRVector();
	CVRVector(float, float, float);
	CVRVector(CVRVector&);
	~CVRVector();
	 CVRVector& operator=(CVRVector&);
	 bool       operator==(CVRVector &) ;
	 bool       operator!=(CVRVector &) ;
	 CVRVector  operator+(CVRVector &) const;
	 CVRVector& operator+=(CVRVector& vec);
	 CVRVector  operator-(CVRVector& vec) ;
	 CVRVector  operator-() ;
	 CVRVector& operator-=(CVRVector&);
	 CVRVector& operator*=(float &);
	 CVRVector& operator/=(float &);
	 CVRVector  operator*(float )const;
	 CVRVector  operator*(CVRVector&) ;
	 CVRVector  operator/(float) ;
	 CVRVector CrossProduct(CVRVector &) ;
	 float DotProduct(CVRVector &) ;
	 float Length() ;
	 CVRVector UnitVector() ;
	void Normalize();
	 float Angle(CVRVector&) ;
	 float GetX();
	 float GetY();
	 float GetZ();
	void SetX(float);
	void SetY(float );
	void SetZ(float);
	void Release();
};

#endif
