/***********************************************************************
*Nome: CVRMath.cpp
*Descrição: Implementa funções matemáticos básicas
*Data: 18/06/08
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRMath.h"
#include <math.h>	// math.h incluido para podermos usar a função sqrt()
#include <float.h>	// float.h incluido para podermos usar _isnan() para acos()

/***********************************************************
*Name: Normal()
*Description: retorna a normal de um polígono 
*Params: CVRVector*
*Return: CVRVector*
************************************************************/
CVRVector Normal(CVRVector vPolygon[])					
{	// Obtém 2 vetors do polígono (2 lados), lembre a ordem!
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
*Description: retorna a distância entre 2 pontos
*Params: CVRVector*, CVRVector*
*Return: float
************************************************************/
float Distance(CVRVector vPoint1, CVRVector vPoint2)
{
	// Distância = sqrt((P2.x - P1.x)^2 + (P2.y - P1.y)^2 + (P2.z - P1.z)^2)
	double distance = sqrt( (vPoint2.x - vPoint1.x) * (vPoint2.x - vPoint1.x) +
						    (vPoint2.y - vPoint1.y) * (vPoint2.y - vPoint1.y) +
						    (vPoint2.z - vPoint1.z) * (vPoint2.z - vPoint1.z) );

	return (float)distance;
}

/***********************************************************
*Name: ClosestPointOnLine()
*Description: retorna o ponto na linha vA-vB que é mais proximo do ponto vPoint
*Params: CVRVector*, CVRVector*, CVRVector*
*Return: CVRVector*
************************************************************/
CVRVector ClosestPointOnLine(CVRVector vA, CVRVector vB, CVRVector vPoint)
{
	// Cria o vetor do ponto final vA para o ponto vPoint.
	CVRVector vVector1 = vPoint - vA;

	// Cria um vetor direção nomalizado do ponto final vA para o ponto final vB
    CVRVector vVector2 = vB - vA;
	vVector2.Normalize();

	// Usa a formula da distância para encontrar a distance do segmento de linha (ou magnitude)
    float d = Distance(vA, vB);

	// Usando o produto vetorial projeta-se o vVector1 sobre o vetor vVector2, obtendo a distância do vetor projetado para vA.
	float t = vVector2.DotProduct(vVector1);

	// Se a distância projetada para vA, "t", é menor ou igual que 0, ela deve
	// estar próxima do ponto final vA. Retorna vA.
    if (t <= 0) 
		return vA;

	// Se a distância projetada para vA, "t", é maior ou igual a magnitude
	// ou a distância do segmento de linha, ela deve estar próxima do ponto final vB. Retorna vB.
    if (t >= d) 
		return vB;
 
	// Cria um vetor que é de tamanho t e na direção de vVector2
    CVRVector vVector3 = vVector2 * t;

	// Para encontrar o ponto mais próximo do segmento de linha, adiciona vVector3 ao ponto final vA original
	CVRVector vClosestPoint = vA + vVector3;

	// Returna o ponto mais próximo do segmento de reta
	return vClosestPoint;
}

/***********************************************************
*Name: PlaneDistance()
*Description: retorna a distância entre um plano e a origem (0, 0, 0), tomando a normal do
*			plano, ao longo de qualquer ponto que esteja sobre o plano (qualquer canto)
*Params: CVRVector*, CVRVector*
*Return: float
************************************************************/
float PlaneDistance(CVRVector Normal, CVRVector Point)
{	
	float distance = 0;	// Armazena a distância do plano a origem

	// Usa a equação do plano (Ax + By + Cz + D = 0) para encontrar a distância. 
	// D = -(Ax + By + Cz)
	// Basicamente nega o prodito vetorial da normal do plano e o ponto.
	distance = - ((Normal.x * Point.x) + (Normal.y * Point.y) + (Normal.z * Point.z));
	return distance;
}

/***********************************************************
*Name: InsidePolygon()
*Description: retorna se um ponto está dentro de um polígono
*Params: CVRVector*, CVRVector*, long
*Return: bool
************************************************************/
bool InsidePolygon(CVRVector vIntersection, CVRVector Poly[], long verticeCount)
{
	const double MATCH_FACTOR = 0.99;		// Usado para cobrir o erro no ponto flutuante
	double Angle = 0.0;						// Inicializa o ângulo
	CVRVector vA, vB;						// Cria vetores temporários
	
	for (int i = 0; i < verticeCount; i++)
	{	
		vA = Poly[i] - vIntersection; // Subtrai o ponto de intersecção do vértice atual
		vB = Poly[(i + 1) % verticeCount] - vIntersection; // Subtrai o ponto do próximo vértice						
		Angle += vA.Angle(vB);	// Encontra o ângulo entre os 2 vetores
	}
	// Se o ângulo é maior que 2 PI (360 graus), o ponto está dentro do polígono											
	if(Angle >= (MATCH_FACTOR * (2.0 * PI)) )	
		return true;
	return false;
}

