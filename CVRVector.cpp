/***********************************************************************
*Nome: CVRVector.cpp
*Descrição: Implementação da classe que representa um vetor
*Data: 07/01/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRVector.h"

/***********************************************************
*Name: CVRVector()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRVector::CVRVector()
{
	x = 0.0f;
	y = 0.0f;
	z = 0.0f;
}

/***********************************************************
*Name: CVRVector()
*Description: construtor da classe
*Params: float, float, float
*Return: Nenhum
************************************************************/
CVRVector::CVRVector(float px, float py, float pz)
{
	x = px;
	y = py;
	z = pz;
}

/***********************************************************
*Name: CVRVector()
*Description: construtor da classe
*Params: CVRVector
*Return: Nenhum
************************************************************/
CVRVector::CVRVector(CVRVector &pVector)
{
	x = pVector.x;
	y = pVector.y;
	z = pVector.z;
}

/***********************************************************
*Name: ~CVRVector()
*Description: destrutor da classe
*Params: nenhum
*Return: Nenhum
************************************************************/
CVRVector::~CVRVector()
{

}

/***********************************************************
*Name: Operador =
*Description: sobrecarga do operador =
*Params: CVRVector
*Return: CVRVector
************************************************************/
CVRVector& CVRVector:: operator=( CVRVector& pVector)
{
	x = pVector.x;
    y = pVector.y;
    z = pVector.z;
    
	return *this;
}

/***********************************************************
*Name: Operador ==
*Description: sobrecarga do operador ==
*Params: CVRVector
*Return: bool
************************************************************/
bool CVRVector:: operator==(CVRVector& pVector)
{
	return ((x == pVector.x) &&
			(y == pVector.y) &&
			(z == pVector.z));
}

/***********************************************************
*Name: Operador !=
*Description: sobrecarga do operador !=
*Params: CVRVector
*Return: bool
************************************************************/
bool CVRVector:: operator!=(CVRVector& pVector)
{
	return !(*this == pVector);
}

/***********************************************************
*Name: Operador +
*Description: sobrecarga do operador +
*Params: CVRVector
*Return: CVRVector
************************************************************/
CVRVector CVRVector:: operator+(CVRVector& pVector)const
{
	 return CVRVector(x+pVector.x, y+pVector.y, z+pVector.z);
}

/***********************************************************
*Name: Operador +=
*Description: sobrecarga do operador +=
*Params: CVRVector
*Return: CVRVector&
************************************************************/
CVRVector& CVRVector:: operator+=(CVRVector& pVector)
{
	  x += pVector.x;
      y += pVector.y;
      z += pVector.z;
      return *this;
}

/***********************************************************
*Name: Operador -
*Description: sobrecarga do operador -
*Params: CVRVector
*Return: CVRVector
************************************************************/
 CVRVector CVRVector:: operator-( CVRVector& pVector)
{
	return CVRVector(x - pVector.x, y - pVector.y, z - pVector.z);
}


/***********************************************************
*Name: Operador -=
*Description: sobrecarga do operador -=
*Params: CVRVector
*Return: CVRVector
************************************************************/
 CVRVector& CVRVector:: operator-=( CVRVector& pVector)
{
	x -= pVector.x;
	y -= pVector.y;
	z -= pVector.z;
	
	return *this;
}

/***********************************************************
*Name: Operador *=
*Description: sobrecarga do operador *=
*Params: float
*Return: CVRVector
************************************************************/
 CVRVector& CVRVector:: operator*=( float& pFloat)
{
	x *= pFloat;
	y *= pFloat;
	z *= pFloat;

	return *this;
}


/***********************************************************
*Name: Operador /=
*Description: sobrecarga do operador /=
*Params: float
*Return: CVRVector
************************************************************/
 CVRVector& CVRVector:: operator/=( float &pFloat)
{
	x /= pFloat;
	y /= pFloat;
	z /= pFloat;
	
	return *this;
}

/***********************************************************
*Name: Operador *
*Description: sobrecarga do operador *
*Params: float
*Return: CVRVector
************************************************************/
 CVRVector CVRVector:: operator*( float pFloat)const
{
	return CVRVector(x*pFloat, y*pFloat, z*pFloat);
}


/***********************************************************
*Name: Operador *
*Description: sobrecarga do operador *
*Params: CVRVector
*Return: CVRVector
************************************************************/
 CVRVector CVRVector:: operator*( CVRVector& pVector) 
{
	return CVRVector(x*pVector.x, y*pVector.y, z*pVector.z);
}

/***********************************************************
*Name: Operador /
*Description: sobrecarga do operador /
*Params: float
*Return: CVRVector
************************************************************/
 CVRVector CVRVector:: operator/(float pFloat) 
{
	return CVRVector(x/pFloat, y/pFloat, z/pFloat);
}

/***********************************************************
*Name: CrossProduct
*Description: Realiza o produto vetorial entre os vetores
*Params: CVRVector
*Return: CVRVector
************************************************************/
 CVRVector CVRVector::CrossProduct( CVRVector &pVector) 
{
	return CVRVector(y*pVector.z - z*pVector.y, z*pVector.x - x*pVector.z, x*pVector.y - y*pVector.x);
}

/***********************************************************
*Name: DotProduct
*Description: Realiza o produto escalar entre os vetores
*Params: CVRVector
*Return: float
************************************************************/
 float CVRVector:: DotProduct( CVRVector &pVector) 
{
	return x*pVector.x + y*pVector.y + z*pVector.z;
}

/***********************************************************
*Name: Lenght
*Description: Devolve o tamanho do vetor
*Params: Nenhum
*Return: float
************************************************************/
 float CVRVector::Length() 
{
	return (float)sqrt((double)(x*x + y*y + z*z));
}


/***********************************************************
*Name: UnitVector
*Description: Devolve o vetor unidade
*Params: Nenhum
*Return: float
************************************************************/
 CVRVector CVRVector::UnitVector() 
{
	return CVRVector(x/Length(),y/Length(),z/Length());
}

/***********************************************************
*Name: Normalize()
*Description: Faz a normalização do vetor
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRVector::Normalize()
{
	float fLength = Length();
	x /= fLength;
	y /= fLength;
	z /= fLength;
}

/***********************************************************
*Name: Angle()
*Description: Retorna o angulo entre dois vetores
*Params: Nenhum
*Return: float
************************************************************/
 float CVRVector::Angle( CVRVector& pVector) 
{
	return acosf(DotProduct(pVector));
}

/***********************************************************
*Name: GetX()
*Description: Retorna o valor de x
*Params: Nenhum
*Return: float
************************************************************/
 float CVRVector::GetX()
{
	return x;
}

/***********************************************************
*Name: GetY()
*Description: Retorna o valor de y
*Params: Nenhum
*Return: float
************************************************************/
 float CVRVector::GetY()
{
	return y;
}

/***********************************************************
*Name: GetZ()
*Description: Retorna o valor de z
*Params: Nenhum
*Return: float
************************************************************/
 float CVRVector::GetZ()
{
	return z;
}

/***********************************************************
*Name: SetX()
*Description: Ajusta o valor de x
*Params: float
*Return: Nenhum
************************************************************/
void CVRVector::SetX( float pX)
{
	x = pX;
}

/***********************************************************
*Name: SetY()
*Description: Ajusta o valor de y
*Params: float
*Return: Nenhum
************************************************************/
void CVRVector::SetY( float pY)
{
	y = pY;
}

/***********************************************************
*Name: SetZ()
*Description: Ajusta o valor de z
*Params: float
*Return: Nenhum
************************************************************/
void CVRVector::SetZ( float pZ)
{
	z = pZ;
}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: void
*Return: Nenhum
************************************************************/
void CVRVector::Release()
{
	
}