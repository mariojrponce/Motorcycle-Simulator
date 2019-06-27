/***********************************************************************
*Nome: CVRCollisionManager.cpp
*Descrição: Classe que implementa os métodos para o gerenciamento da detecção de colisão
*Data: 18/06/08
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRCollisionManager.h"


/***********************************************************
*Name: CVRCollisionManager()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRCollisionManager::CVRCollisionManager()
{

}

/***********************************************************
*Name: ~CVRCollisionManager()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRCollisionManager::~CVRCollisionManager()
{
	
}


/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRCollisionManager::Release()
{
}

/***********************************************************
*Name: SphereSphereCollision()
*Description: verifica se há colisão entre dois objetos (BoundingSphere X BoundingSphere)
*Params: CVRBoundingSphere*, CVRBoundingSphere*
*Return: bool
************************************************************/
bool CVRCollisionManager::SphereSphereCollision(CVRBoundingSphere* obj1, CVRBoundingSphere* obj2)
{
	CVRVector relPos = obj2->GetPosition() - obj1->GetPosition();
	float dist = relPos.GetX() * relPos.GetX() + relPos.GetY() * relPos.GetY() + relPos.GetZ() * relPos.GetZ();
	float minDist = obj2->GetRadius()*obj2->GetScale().GetX() + obj1->GetRadius()*obj1->GetScale().GetX();
	return dist <= minDist * minDist;
}

/***********************************************************
*Name: BoxBoxCollision()
*Description: verifica se há colisão entre dois objetos (BoundingBox X BoundingBox)
*Params: CVRBoundingBox*, CVRBoundingBox*
*Return: bool
************************************************************/
bool CVRCollisionManager::BoxBoxCollision(CVRBoundingBox* obj1, CVRBoundingBox* obj2)
{
	float posMinXObj1, posMaxXObj1, posMinYObj1, posMaxYObj1, posMinZObj1, posMaxZObj1;
	float posMinXObj2, posMaxXObj2, posMinYObj2, posMaxYObj2, posMinZObj2, posMaxZObj2;

	// Obtém os pontos máximos e mínimos do BoundingBox do obj1
	CVRVector posObj1 = obj1->GetPosition();
	CVRVector scaleObj1 = obj1->GetScale();
	posMinXObj1 = (posObj1.GetX() - abs(obj1->GetDimension() * scaleObj1.GetX()));
	posMaxXObj1 = (posObj1.GetX() + abs(obj1->GetDimension() * scaleObj1.GetX()));
	posMinYObj1 = (posObj1.GetY() - abs(obj1->GetDimension() * scaleObj1.GetY()));
	posMaxYObj1 = (posObj1.GetY() + abs(obj1->GetDimension() * scaleObj1.GetY()));
	posMinZObj1 = (posObj1.GetZ() - abs(obj1->GetDimension() * scaleObj1.GetZ()));
	posMaxZObj1 = (posObj1.GetZ() + abs(obj1->GetDimension() * scaleObj1.GetZ()));

	// Obtém os pontos máximos e mínimos do BoundingBox do obj2
	CVRVector posObj2 = obj2->GetPosition();
	CVRVector scaleObj2 = obj2->GetScale();
	posMinXObj2 = (posObj2.GetX() - abs(obj2->GetDimension() * scaleObj2.GetX()));
	posMaxXObj2 = (posObj2.GetX() + abs(obj2->GetDimension() * scaleObj2.GetX()));
	posMinYObj2 = (posObj2.GetY() - abs(obj2->GetDimension() * scaleObj2.GetY()));
	posMaxYObj2 = (posObj2.GetY() + abs(obj2->GetDimension() * scaleObj2.GetY()));
	posMinZObj2 = (posObj2.GetZ() - abs(obj2->GetDimension() * scaleObj2.GetZ()));
	posMaxZObj2 = (posObj2.GetZ() + abs(obj2->GetDimension() * scaleObj2.GetZ()));

	// ------------ Verificação de colisão entre BoundingBoxes ----------------
	// Dois boundingBox estão colidindo se eles sobrepoem-se em todos os seus 3 eixos
	// Eixo x
	if(posMaxXObj1 < posMinXObj2 || posMinXObj1 > posMaxXObj2)
		return false;
	// Eixo z
	if(posMaxYObj1 < posMinYObj2 || posMinYObj1 > posMaxYObj2)
		return false;
	// Eixo z
	if(posMaxZObj1 < posMinZObj2 || posMinZObj1 > posMaxZObj2)
		return false;
	return true;
}

/***********************************************************
*Name: BoxSphereCollision()
*Description: verifica se há colisão entre dois objetos (BoundingBox X BoundingSphere)
*Params: CVRBoundingBox*, CVRBoundingSphere*
*Return: bool
************************************************************/
bool CVRCollisionManager::BoxSphereCollision(CVRBoundingBox* obj1, CVRBoundingSphere* obj2)
{
	// Obtem a distância quadrada entre o centro da BoundingSphere e a BoundingBox
	float sqDist = SqDistPointAABB(obj2->GetPosition(), obj1);

    // BoundingSphere e a BoundingBox se intersectam se a distância quadrada entre elas é menor que o raio quadrado da esfera
	return sqDist <= obj2->GetRadius() * obj2->GetRadius();	
}

/***********************************************************
*Name: SqDistPointAABB()
*Description: calcula a distância quadrada entre um ponto p e um BoundingBox
*Params: CVRVector, CVRBoundingBox*
*Return: float
************************************************************/
// Computes the square distance between a point p and an AABB b
float CVRCollisionManager::SqDistPointAABB(CVRVector point, CVRBoundingBox* obj)
{
    float sqDist = 0.0f;
    
	// Obtém os pontos máximos e mínimos do BoundingBox do obj1
	CVRVector posObj = obj->GetPosition();
	CVRVector scaleObj = obj->GetScale();
	CVRVector vMinObj;
	vMinObj.SetX(posObj.GetX() - abs(obj->GetDimension() * scaleObj.GetX())); 
	vMinObj.SetY(posObj.GetY() - abs(obj->GetDimension() * scaleObj.GetY()));
	vMinObj.SetZ(posObj.GetZ() - abs(obj->GetDimension() * scaleObj.GetZ()));
	CVRVector vMaxObj;
	vMaxObj.SetX(posObj.GetX() + abs(obj->GetDimension() * scaleObj.GetX()));
	vMaxObj.SetY(posObj.GetY() + abs(obj->GetDimension() * scaleObj.GetY()));
	vMaxObj.SetZ(posObj.GetZ() + abs(obj->GetDimension() * scaleObj.GetZ()));
	
	// Para cada eixo armazena qualquer excesso de distância fora da extensão da caixa
	// Eixo X
	float p = point.GetX();
	float pMin = vMinObj.GetX();
	float pMax = vMaxObj.GetX();
	if(p < pMin)
		sqDist += (pMin - p) * (pMin - p);
	if(p > pMax)
		sqDist += (p - pMax) * (p - pMax);

	// Eixo Y
	p = point.GetY();
	pMin = vMinObj.GetY();
	pMax = vMaxObj.GetY();
	if(p < pMin)
		sqDist += (pMin - p) * (pMin - p);
	if(p > pMax)
		sqDist += (p - pMax) * (p - pMax);

	// Eixo Z
	p = point.GetZ();
	pMin = vMinObj.GetZ();
	pMax = vMaxObj.GetZ();
	if(p < pMin)
		sqDist += (pMin - p) * (pMin - p);
	if(p > pMax)
		sqDist += (p - pMax) * (p - pMax);

	return sqDist;
}

/***********************************************************
*Name: SpherePolygonCollision()
*Description: verifica se há colisão entre uma BoundingSphere e um polígono
*Params: CVRBoundingSphere*, CVRVector*, int
*Return: bool
************************************************************/
bool CVRCollisionManager::SpherePolygonCollision(CVRBoundingSphere* obj, CVRVector* vPolygon, int vertexCount)
{
	// 1) Encontra a classificação da esfera
	
	// Encontra a normal do polígono
	CVRVector vNormal = Normal(vPolygon);

	// Variável que armazenará a distância da esfera ao plano
	float distance = 0.0f;

	// Determina se a esfera está na frente, atrás ou intersecta o plano
	int classification = ClassifySphere(obj->GetPosition(), vNormal, vPolygon[0], obj->GetRadius(), distance);

	if(classification == S_INTERSECTS) 
	{
		// 2) Encontra o pseudo ponto de intersecção com o plano
		CVRVector vOffset = vNormal * distance;
		CVRVector vPosition = obj->GetPosition() - vOffset;

		// 3) Verifica se o ponto de intersecção está dentro do perimetro do polígono
		if(InsidePolygon(vPosition, vPolygon, vertexCount))
			return true;	// Ocorreu colisão
		else
		{
			// 4) Verifica se a esfera intersecta as arestas do polígono
			if(EdgeSphereCollision(obj->GetPosition(), vPolygon, vertexCount, obj->GetRadius()))
			{
				return true;	// Ocorreu colisão
			}
		}
	}
	// Não ocorreu colisão
	return false;
}

/***********************************************************
*Name: EdgeSphereCollision()
*Description: retorna se a esfera está intersectando qualquer aresta de um polígono
*Params: CVector3&, CVector3[], int, float
*Return: bool
************************************************************/
bool CVRCollisionManager::EdgeSphereCollision(CVRVector &vCenter, CVRVector vPolygon[], int vertexCount, float radius)
{
	CVRVector vPoint;

	for(int i = 0; i < vertexCount; i++)
	{
		// Obtem o ponto mais próximo na aresta atual para o centro da esfera
		vPoint = ClosestPointOnLine(vPolygon[i], vPolygon[(i + 1) % vertexCount], vCenter);
		
		// Calcula a distancia entre o ponto mais proximo e o centro
		float distance = Distance(vPoint, vCenter);
	
		// Se a distancia é menor que o raio, há colisão
		if(distance < radius)
			return true;
	}

	// Não há colisão
	return false;
}

/***********************************************************
*Name: ClassifySphere()
*Description: retorna se uma esfera está atrás (BEHIND), na frente (FRONT) ou intersecta (INTERSECTS)
*			um plano, e também sua distância
*Params: CVRVector&, CVRVector&, CVRVector&, float, float&
*Return: int
************************************************************/
int CVRCollisionManager::ClassifySphere(CVRVector &vCenter, CVRVector &vNormal, CVRVector &vPoint, float radius, float &distance)
{
	// Encontra a distância em que o plano do polígono está da origem.
	float d = (float)PlaneDistance(vNormal, vPoint);

	// Encontra a distância que oo ponto central da esfera está do plano do polígono
	// Ax + By + Cz + d = 0 com ABC = Normal, XYZ = Point
	distance = (vNormal.x * vCenter.x + vNormal.y * vCenter.y + vNormal.z * vCenter.z + d);

	// Se o valor absoluto da distância é menor que o raio, a esfera intersecta o plano.
	if(abs(distance) < radius)
		return S_INTERSECTS;
	// Se a distância é maior ou igual ao raio, a esfera está completamente na frente do plano.
	else if(distance >= radius)
		return S_FRONT;
	// Esfera está completamente atrás do plano.
	return S_BEHIND;
}

/***********************************************************
*Name: BoxPolygonCollision()
*Description: verifica se há colisão entre um BoundingBox e um triângulo
*Params: CVRBoundingBox, CVRVector*
*Return: bool
************************************************************/
bool CVRCollisionManager::BoxTriangleCollision(CVRBoundingBox* obj, CVRVector* vPolygon)
{
	/*float p0, p1, p2, p2, r;

	// Obtém os pontos máximos e mínimos do BoundingBox do obj
	CVRVector posObj = obj->GetPosition();
	CVRVector scaleObj = obj->GetScale();
	CVRVector vMinObj;
	vMinObj.SetX(posObj.GetX() - abs(obj->GetDimension() * scaleObj.GetX())); 
	vMinObj.SetY(posObj.GetY() - abs(obj->GetDimension() * scaleObj.GetY()));
	vMinObj.SetZ(posObj.GetZ() - abs(obj->GetDimension() * scaleObj.GetZ()));
	CVRVector vMaxObj;
	vMaxObj.SetX(posObj.GetX() + abs(obj->GetDimension() * scaleObj.GetX()));
	vMaxObj.SetY(posObj.GetY() + abs(obj->GetDimension() * scaleObj.GetY()));
	vMaxObj.SetZ(posObj.GetZ() + abs(obj->GetDimension() * scaleObj.GetZ()));

	// Obtem o centro da caixa e extensoes
	CVRVector center = (vMinObj + vMaxObj) * 0.5f;
	float extX = (vMaxObj.GetX() - vMinObj.GetX()) * 0.5f;
	float extY = (vMaxObj.GetY() - vMinObj.GetY()) * 0.5f;
	float extZ = (vMaxObj.GetZ() - vMinObj.GetZ()) * 0.5f;

	// Translada o triangulo movendo AABB para origem
	vPolygon[0] = vPolygon[0] - center; 
	vPolygon[1] = vPolygon[1] - center;
	vPolygon[2] = vPolygon[2] - center;

	// Obtem as arestas do triângulo
	CVRVector f0 = vPolygon[1] - vPolygon[0];
	CVRVector f1 = vPolygon[2] - vPolygon[1];
	CVRVector f2 = vPolygon[0] - vPolygon[2];

	// Testa os 9 eixos correspondentes ao produto vetorial entre as 3 arestas do AABB e as 3 do triangulo
	p0 = vPolygon[0].GetZ()*vPolygon[1].GetY() - vPolygon[0].GetY()*vPolygon[1].GetZ();
	p2 = vPolygon[2].GetZ()*(vPolygon[1].GetY()-vPolygon[0].GetY()) - vPolygon[2].GetZ()*(vPolygon[1].GetZ()-vPolygon[0].GetY());
	r = extY*abs(f0.GetZ()) + extZ*abs(f0.GetY());
	if()
		return false; // Eixo é um eixo separado

				return true;	// Ocorreu colisão
			}
		}
	}
	// Não ocorreu colisão*/
	return false;
}

/***********************************************************
*Name: LinePolygonCollision()
*Description: verifica se há colisão entre um polígono e uma linha
*Params: CVRVector*, CVRVector*, int
*Return: bool
************************************************************/
bool CVRCollisionManager::PolygonLineCollision(CVRVector* vPoly, CVRVector* vLine, int verticeCount)
{
	CVRVector vNormal;
	float originDistance = 0;

	// Verifica se a linha intersecta o plano
	if(!IntersectedPlane(vPoly, vLine,   vNormal,   originDistance))
		return false;

	// Calcula o ponto de intersecção
	CVRVector vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

	// Verifica se o ponto de intersecção está dentro do polígono
	if(InsidePolygon(vIntersection, vPoly, verticeCount))
		return true;	// Ocorreu colisão
	return false;		// Não ocorreu colisão
}

/***********************************************************
*Name: IntersectedPlane()
*Description: verifica se há colisão entre uma linha e um plano
*Params: CVRVector*, CVRVector*, CVRVector&, float&
*Return: bool
************************************************************/					
bool CVRCollisionManager::IntersectedPlane(CVRVector* vPoly, CVRVector* vLine, CVRVector &vNormal, float &originDistance)
{
	float distance1=0, distance2=0;	// As distâncias dos 2 pontos da linha para o plano
	
	// Obtem a normal do plano
	vNormal = Normal(vPoly);

	// Obtem a distância do plano para a origem 
	originDistance = PlaneDistance(vNormal, vPoly[0]);

	// Obtem a distância do point1 do plano usando Ax + By + Cz + D = (a distância do plano)
	distance1 = ((vNormal.x * vLine[0].x)  +					// Ax +
		         (vNormal.y * vLine[0].y)  +					// Bx +
				 (vNormal.z * vLine[0].z)) + originDistance;	// Cz + D
	
	// Obtem a distância do point2 do plano usando Ax + By + Cz + D = (a distância do plano)
	distance2 = ((vNormal.x * vLine[1].x)  +					// Ax +
		         (vNormal.y * vLine[1].y)  +					// Bx +
				 (vNormal.z * vLine[1].z)) + originDistance;	// Cz + D

	// Verifica se as distâncias são ambas positivas ou negativasCheck to see if both point's distances are both negative or both positive
	if(distance1 * distance2 >= 0)
	   return false; // distâncias ambas positivas ou ambas negativas: pontos estão de um mesmo lado do plano
	return true; // distâncias com sinais diferentes: a linha intersecta o plano
}

/***********************************************************
*Name: IntersectionPoint()
*Description: retorna o ponto de intersecção da linha que intersecta o plano
*Params: CVRVector, CVRVector*, double
*Return: CVRVector
************************************************************/					
CVRVector CVRCollisionManager::IntersectionPoint(CVRVector vNormal, CVRVector* vLine, double distance)
{
	CVRVector vPoint, vLineDir;	// Variaveis que armazenarão o ponto e a direção da linha
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	// 1)  Obtem o vetor da linha e normaliza-o
	vLineDir = vLine[1] - vLine[0];
	vLineDir.Normalize();

	// 2) Usa a equação do plano (distancia = Ax + By + Cz + D) para encontrar a distância de um dos 5 pontos do plano
	Numerator = - (vNormal.x * vLine[0].x +	
				   vNormal.y * vLine[0].y +
				   vNormal.z * vLine[0].z + distance);

	// 3) Obtem o produto vetorial entre o vetor da linha e a normal do polígono
	Denominator = vNormal.DotProduct(vLineDir);
				  
	// Verifica se há divisão por 0: 0 significa que há infinitos pontos devido a linha estar sobre o plano
	// Normal é perpendicular a linha - Normal.Vector = 0
	if( Denominator == 0.0)
		return vLine[0]; // Retorna um ponto arbitrário da linha

	dist = Numerator / Denominator;	
	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;	// Retorna o ponto de intersecção
}

/***********************************************************
*Name: TestCollisionBSphereRay()
*Description: verifica se há colisão entre uma BoundingSphere e um raio
*Params: CVRObject3D*, CVRVector*
*Return: bool
************************************************************/
/*bool CVRCollisionManager::TestCollisionBSphereRay(CVRObject3D* obj1, CVRVector* obj2)
{
	
}*/



/***********************************************************
*Name: TestCollisionBBoxPolygon()
*Description: verifica se há colisão entre uma BoundingBox e um polígono
*Params: CVRObject3D*, CVRVector*
*Return: bool
************************************************************/
/*bool CVRCollisionManager::TestCollisionBBoxPolygon(CVRObject3D* obj1, CVRVector* obj2)
{
	
}*/

/***********************************************************
*Name: TestCollisionBBoxRay()
*Description: verifica se há colisão entre uma BoundingBox e um raio
*Params: CVRObject3D*, CVRVector*
*Return: bool
************************************************************/
/*bool CVRCollisionManager::TestCollisionBBoxRay(CVRObject3D* obj1, CVRVector* obj2)
{
	
}*/

/***********************************************************
*Name: TestCollisionPolygonPoint()
*Description: verifica se há colisão entre um polígono e um ponto
*Params: CVRVector*, CVRVector*
*Return: bool
************************************************************/
/*bool CVRCollisionManager::TestCollisionPolygonPoint(CVRVector* obj1, CVRVector* obj2)
{
	
}*/




