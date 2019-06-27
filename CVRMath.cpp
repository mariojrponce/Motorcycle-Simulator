/***********************************************************************
*Nome: CVRMath.cpp
*Descri��o: Implementa fun��es matem�ticos b�sicas
*Data: 18/06/08
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRMath.h"
#include <math.h>	// math.h incluido para podermos usar a fun��o sqrt()
#include <float.h>	// float.h incluido para podermos usar _isnan() para acos()

/***********************************************************
*Name: Normal()
*Description: retorna a normal de um pol�gono 
*Params: CVRVector*
*Return: CVRVector*
************************************************************/
CVRVector Normal(CVRVector vPolygon[])					
{	// Obt�m 2 vetors do pol�gono (2 lados), lembre a ordem!
	CVRVector vVector1 = vPolygon[2] - vPolygon[0];
	CVRVector vVector2 = vPolygon[1] - vPolygon[0];
	// Produto vetorial dos vetores para obter um vetor perpendicular
	CVRVector vNormal = vVector1.CrossProduct(vVector2);
	// Normalize a normal
	vNormal.Normalize();
	return vNormal;
}

/***********************************************************
*Name: Distance()
*Description: retorna a dist�ncia entre 2 pontos
*Params: CVRVector*, CVRVector*
*Return: float
************************************************************/
float Distance(CVRVector vPoint1, CVRVector vPoint2)
{
	// Dist�ncia = sqrt((P2.x - P1.x)^2 + (P2.y - P1.y)^2 + (P2.z - P1.z)^2)
	double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
						    (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
						    (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );

	return (float)distance;
}

/***********************************************************
*Name: ClosestPointOnLine()
*Description: retorna o ponto na linha vA-vB que � mais proximo do ponto vPoint
*Params: CVRVector*, CVRVector*, CVRVector*
*Return: CVRVector*
************************************************************/
CVRVector ClosestPointOnLine(CVRVector vA, CVRVector vB, CVRVector vPoint)
{
	// Cria o vetor do ponto final vA para o ponto vPoint.
	CVRVector vVector1 = vPoint - vA;

	// Cria um vetor dire��o nomalizado do ponto final vA para o ponto final vB
    CVRVector vVector2 = vB - vA;
	vVector2.Normalize();

	// Usa a formula da dist�ncia para encontrar a distance do segmento de linha (ou magnitude)
    float d = Distance(vA, vB);

	// Usando o produto vetorial projeta-se o vVector1 sobre o vetor vVector2, obtendo a dist�ncia do vetor projetado para vA.
	float t = vVector2.DotProduct(vVector1);

	// Se a dist�ncia projetada para vA, "t", � menor ou igual que 0, ela deve
	// estar pr�xima do ponto final vA. Retorna vA.
    if (t <= 0) 
		return vA;

	// Se a dist�ncia projetada para vA, "t", � maior ou igual a magnitude
	// ou a dist�ncia do segmento de linha, ela deve estar pr�xima do ponto final vB. Retorna vB.
    if (t >= d) 
		return vB;
 
	// Cria um vetor que � de tamanho t e na dire��o de vVector2
    CVRVector vVector3 = vVector2 * t;

	// Para encontrar o ponto mais pr�ximo do segmento de linha, adiciona vVector3 ao ponto final vA original
	CVRVector vClosestPoint = vA + vVector3;

	// Returna o ponto mais pr�ximo do segmento de reta
	return vClosestPoint;
}

/***********************************************************
*Name: PlaneDistance()
*Description: retorna a dist�ncia entre um plano e a origem (0, 0, 0), tomando a normal do
*			plano, ao longo de qualquer ponto que esteja sobre o plano (qualquer canto)
*Params: CVRVector*, CVRVector*
*Return: float
************************************************************/
float PlaneDistance(CVRVector Normal, CVRVector Point)
{	
	float distance = 0;	// Armazena a dist�ncia do plano a origem

	// Usa a equa��o do plano (Ax + By + Cz + D = 0) para encontrar a dist�ncia. 
	// D = -(Ax + By + Cz)
	// Basicamente nega o prodito vetorial da normal do plano e o ponto.
	distance = - ((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));
	return distance;
}

/***********************************************************
*Name: InsidePolygon()
*Description: retorna se um ponto est� dentro de um pol�gono
*Params: CVRVector*, CVRVector*, long
*Return: bool
************************************************************/
bool InsidePolygon(CVRVector vIntersection, CVRVector Poly[], long verticeCount)
{
	const double MATCH_FACTOR = 0.99;		// Usado para cobrir o erro no ponto flutuante
	double Angle = 0.0;						// Inicializa o �ngulo
	CVRVector vA, vB;						// Cria vetores tempor�rios
	
	for (int i = 0; i < verticeCount; i++)
	{	
		vA = Poly[i] - vIntersection; // Subtrai o ponto de intersec��o do v�rtice atual
		vB = Poly[(i + 1) % verticeCount] - vIntersection; // Subtrai o ponto do pr�ximo v�rtice						
		Angle += vA.Angle(vB);	// Encontra o �ngulo entre os 2 vetores
	}
	// Se o �ngulo � maior que 2 PI (360 graus), o ponto est� dentro do pol�gono											
	if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )	
		return true;
	return false;
}

