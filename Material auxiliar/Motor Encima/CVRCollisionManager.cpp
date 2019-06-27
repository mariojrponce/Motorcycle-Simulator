/***********************************************************************
*Nome: CVRCollisionManager.cpp
*Descri��o: Classe que implementa os m�todos para o gerenciamento da detec��o de colis�o
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
*Description: verifica se h� colis�o entre dois objetos (BoundingSphere X BoundingSphere)
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
*Description: verifica se h� colis�o entre dois objetos (BoundingBox X BoundingBox)
*Params: CVRBoundingBox*, CVRBoundingBox*
*Return: bool
************************************************************/
bool CVRCollisionManager::BoxBoxCollision(CVRBoundingBox* obj1, CVRBoundingBox* obj2)
{
	float posMinXObj1, posMaxXObj1, posMinYObj1, posMaxYObj1, posMinZObj1, posMaxZObj1;
	float posMinXObj2, posMaxXObj2, posMinYObj2, posMaxYObj2, posMinZObj2, posMaxZObj2;

	// Obt�m os pontos m�ximos e m�nimos do BoundingBox do obj1
	CVRVector posObj1 = obj1->GetPosition();
	CVRVector scaleObj1 = obj1->GetScale();
	posMinXObj1 = (posObj1.GetX() - abs(obj1->GetDimension() * scaleObj1.GetX()));
	posMaxXObj1 = (posObj1.GetX() + abs(obj1->GetDimension() * scaleObj1.GetX()));
	posMinYObj1 = (posObj1.GetY() - abs(obj1->GetDimension() * scaleObj1.GetY()));
	posMaxYObj1 = (posObj1.GetY() + abs(obj1->GetDimension() * scaleObj1.GetY()));
	posMinZObj1 = (posObj1.GetZ() - abs(obj1->GetDimension() * scaleObj1.GetZ()));
	posMaxZObj1 = (posObj1.GetZ() + abs(obj1->GetDimension() * scaleObj1.GetZ()));

	// Obt�m os pontos m�ximos e m�nimos do BoundingBox do obj2
	CVRVector posObj2 = obj2->GetPosition();
	CVRVector scaleObj2 = obj2->GetScale();
	posMinXObj2 = (posObj2.GetX() - abs(obj2->GetDimension() * scaleObj2.GetX()));
	posMaxXObj2 = (posObj2.GetX() + abs(obj2->GetDimension() * scaleObj2.GetX()));
	posMinYObj2 = (posObj2.GetY() - abs(obj2->GetDimension() * scaleObj2.GetY()));
	posMaxYObj2 = (posObj2.GetY() + abs(obj2->GetDimension() * scaleObj2.GetY()));
	posMinZObj2 = (posObj2.GetZ() - abs(obj2->GetDimension() * scaleObj2.GetZ()));
	posMaxZObj2 = (posObj2.GetZ() + abs(obj2->GetDimension() * scaleObj2.GetZ()));

	// ------------ Verifica��o de colis�o entre BoundingBoxes ----------------
	// Dois boundingBox est�o colidindo se eles sobrepoem-se em todos os seus 3 eixos
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
*Description: verifica se h� colis�o entre dois objetos (BoundingBox X BoundingSphere)
*Params: CVRBoundingBox*, CVRBoundingSphere*
*Return: bool
************************************************************/
bool CVRCollisionManager::BoxSphereCollision(CVRBoundingBox* obj1, CVRBoundingSphere* obj2)
{
	// Obtem a dist�ncia quadrada entre o centro da BoundingSphere e a BoundingBox
	float sqDist = SqDistPointAABB(obj2->GetPosition(), obj1);

    // BoundingSphere e a BoundingBox se intersectam se a dist�ncia quadrada entre elas � menor que o raio quadrado da esfera
	return sqDist <= obj2->GetRadius() * obj2->GetRadius();	
}

/***********************************************************
*Name: SqDistPointAABB()
*Description: calcula a dist�ncia quadrada entre um ponto p e um BoundingBox
*Params: CVRVector, CVRBoundingBox*
*Return: float
************************************************************/
// Computes the square distance between a point p and an AABB b
float CVRCollisionManager::SqDistPointAABB(CVRVector point, CVRBoundingBox* obj)
{
    float sqDist = 0.0f;
    
	// Obt�m os pontos m�ximos e m�nimos do BoundingBox do obj1
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
	
	// Para cada eixo armazena qualquer excesso de dist�ncia fora da extens�o da caixa
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
*Description: verifica se h� colis�o entre uma BoundingSphere e um pol�gono
*Params: CVRBoundingSphere*, CVRVector*, int
*Return: bool
************************************************************/
bool CVRCollisionManager::SpherePolygonCollision(CVRBoundingSphere* obj, CVRVector* vPolygon, int vertexCount)
{
	// 1) Encontra a classifica��o da esfera
	
	// Encontra a normal do pol�gono
	CVRVector vNormal = Normal(vPolygon);

	// Vari�vel que armazenar� a dist�ncia da esfera ao plano
	float distance = 0.0f;

	// Determina se a esfera est� na frente, atr�s ou intersecta o plano
	int classification = ClassifySphere(obj->GetPosition(), vNormal, vPolygon[0], obj->GetRadius(), distance);

	if(classification == S_INTERSECTS) 
	{
		// 2) Encontra o pseudo ponto de intersec��o com o plano
		CVRVector vOffset = vNormal * distance;
		CVRVector vPosition = obj->GetPosition() - vOffset;

		// 3) Verifica se o ponto de intersec��o est� dentro do perimetro do pol�gono
		if(InsidePolygon(vPosition, vPolygon, vertexCount))
			return true;	// Ocorreu colis�o
		else
		{
			// 4) Verifica se a esfera intersecta as arestas do pol�gono
			if(EdgeSphereCollision(obj->GetPosition(), vPolygon, vertexCount, obj->GetRadius()))
			{
				return true;	// Ocorreu colis�o
			}
		}
	}
	// N�o ocorreu colis�o
	return false;
}

/***********************************************************
*Name: EdgeSphereCollision()
*Description: retorna se a esfera est� intersectando qualquer aresta de um pol�gono
*Params: CVector3&, CVector3[], int, float
*Return: bool
************************************************************/
bool CVRCollisionManager::EdgeSphereCollision(CVRVector &vCenter, CVRVector vPolygon[], int vertexCount, float radius)
{
	CVRVector vPoint;

	for(int i = 0; i < vertexCount; i++)
	{
		// Obtem o ponto mais pr�ximo na aresta atual para o centro da esfera
		vPoint = ClosestPointOnLine(vPolygon[i], vPolygon[(i + 1) % vertexCount], vCenter);
		
		// Calcula a distancia entre o ponto mais proximo e o centro
		float distance = Distance(vPoint, vCenter);
	
		// Se a distancia � menor que o raio, h� colis�o
		if(distance < radius)
			return true;
	}

	// N�o h� colis�o
	return false;
}

/***********************************************************
*Name: ClassifySphere()
*Description: retorna se uma esfera est� atr�s (BEHIND), na frente (FRONT) ou intersecta (INTERSECTS)
*			um plano, e tamb�m sua dist�ncia
*Params: CVRVector&, CVRVector&, CVRVector&, float, float&
*Return: int
************************************************************/
int CVRCollisionManager::ClassifySphere(CVRVector &vCenter, CVRVector &vNormal, CVRVector &vPoint, float radius, float &distance)
{
	// Encontra a dist�ncia em que o plano do pol�gono est� da origem.
	float d = (float)PlaneDistance(vNormal, vPoint);

	// Encontra a dist�ncia que oo ponto central da esfera est� do plano do pol�gono
	// Ax + By + Cz + d = 0 com ABC = Normal, XYZ = Point
	distance = (vNormal.x * vCenter.x + vNormal.y * vCenter.y + vNormal.z * vCenter.z + d);

	// Se o valor absoluto da dist�ncia � menor que o raio, a esfera intersecta o plano.
	if(abs(distance) < radius)
		return S_INTERSECTS;
	// Se a dist�ncia � maior ou igual ao raio, a esfera est� completamente na frente do plano.
	else if(distance >= radius)
		return S_FRONT;
	// Esfera est� completamente atr�s do plano.
	return S_BEHIND;
}

/***********************************************************
*Name: BoxPolygonCollision()
*Description: verifica se h� colis�o entre um BoundingBox e um tri�ngulo
*Params: CVRBoundingBox, CVRVector*
*Return: bool
************************************************************/
bool CVRCollisionManager::BoxTriangleCollision(CVRBoundingBox* obj, CVRVector* vPolygon)
{
	/*float p0, p1, p2, p2, r;

	// Obt�m os pontos m�ximos e m�nimos do BoundingBox do obj
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

	// Obtem as arestas do tri�ngulo
	CVRVector f0 = vPolygon[1] - vPolygon[0];
	CVRVector f1 = vPolygon[2] - vPolygon[1];
	CVRVector f2 = vPolygon[0] - vPolygon[2];

	// Testa os 9 eixos correspondentes ao produto vetorial entre as 3 arestas do AABB e as 3 do triangulo
	p0 = vPolygon[0].GetZ()*vPolygon[1].GetY() - vPolygon[0].GetY()*vPolygon[1].GetZ();
	p2 = vPolygon[2].GetZ()*(vPolygon[1].GetY()-vPolygon[0].GetY()) - vPolygon[2].GetZ()*(vPolygon[1].GetZ()-vPolygon[0].GetY());
	r = extY*abs(f0.GetZ()) + extZ*abs(f0.GetY());
	if()
		return false; // Eixo � um eixo separado

				return true;	// Ocorreu colis�o
			}
		}
	}
	// N�o ocorreu colis�o*/
	return false;
}

/***********************************************************
*Name: LinePolygonCollision()
*Description: verifica se h� colis�o entre um pol�gono e uma linha
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

	// Calcula o ponto de intersec��o
	CVRVector vIntersection = IntersectionPoint(vNormal, vLine, originDistance);

	// Verifica se o ponto de intersec��o est� dentro do pol�gono
	if(InsidePolygon(vIntersection, vPoly, verticeCount))
		return true;	// Ocorreu colis�o
	return false;		// N�o ocorreu colis�o
}

/***********************************************************
*Name: IntersectedPlane()
*Description: verifica se h� colis�o entre uma linha e um plano
*Params: CVRVector*, CVRVector*, CVRVector&, float&
*Return: bool
************************************************************/					
bool CVRCollisionManager::IntersectedPlane(CVRVector* vPoly, CVRVector* vLine, CVRVector &vNormal, float &originDistance)
{
	float distance1=0, distance2=0;	// As dist�ncias dos 2 pontos da linha para o plano
	
	// Obtem a normal do plano
	vNormal = Normal(vPoly);

	// Obtem a dist�ncia do plano para a origem 
	originDistance = PlaneDistance(vNormal, vPoly[0]);

	// Obtem a dist�ncia do point1 do plano usando Ax + By + Cz + D = (a dist�ncia do plano)
	distance1 = ((vNormal.x * vLine[0].x)  +					// Ax +
		         (vNormal.y * vLine[0].y)  +					// Bx +
				 (vNormal.z * vLine[0].z)) + originDistance;	// Cz + D
	
	// Obtem a dist�ncia do point2 do plano usando Ax + By + Cz + D = (a dist�ncia do plano)
	distance2 = ((vNormal.x * vLine[1].x)  +					// Ax +
		         (vNormal.y * vLine[1].y)  +					// Bx +
				 (vNormal.z * vLine[1].z)) + originDistance;	// Cz + D

	// Verifica se as dist�ncias s�o ambas positivas ou negativasCheck to see if both point's distances are both negative or both positive
	if(distance1 * distance2 >= 0)
	   return false; // dist�ncias ambas positivas ou ambas negativas: pontos est�o de um mesmo lado do plano
	return true; // dist�ncias com sinais diferentes: a linha intersecta o plano
}

/***********************************************************
*Name: IntersectionPoint()
*Description: retorna o ponto de intersec��o da linha que intersecta o plano
*Params: CVRVector, CVRVector*, double
*Return: CVRVector
************************************************************/					
CVRVector CVRCollisionManager::IntersectionPoint(CVRVector vNormal, CVRVector* vLine, double distance)
{
	CVRVector vPoint, vLineDir;	// Variaveis que armazenar�o o ponto e a dire��o da linha
	double Numerator = 0.0, Denominator = 0.0, dist = 0.0;

	// 1)  Obtem o vetor da linha e normaliza-o
	vLineDir = vLine[1] - vLine[0];
	vLineDir.Normalize();

	// 2) Usa a equa��o do plano (distancia = Ax + By + Cz + D) para encontrar a dist�ncia de um dos 5 pontos do plano
	Numerator = - (vNormal.x * vLine[0].x +	
				   vNormal.y * vLine[0].y +
				   vNormal.z * vLine[0].z + distance);

	// 3) Obtem o produto vetorial entre o vetor da linha e a normal do pol�gono
	Denominator = vNormal.DotProduct(vLineDir);
				  
	// Verifica se h� divis�o por 0: 0 significa que h� infinitos pontos devido a linha estar sobre o plano
	// Normal � perpendicular a linha - Normal.Vector = 0
	if( Denominator == 0.0)
		return vLine[0]; // Retorna um ponto arbitr�rio da linha

	dist = Numerator / Denominator;	
	vPoint.x = (float)(vLine[0].x + (vLineDir.x * dist));
	vPoint.y = (float)(vLine[0].y + (vLineDir.y * dist));
	vPoint.z = (float)(vLine[0].z + (vLineDir.z * dist));

	return vPoint;	// Retorna o ponto de intersec��o
}

/***********************************************************
*Name: TestCollisionBSphereRay()
*Description: verifica se h� colis�o entre uma BoundingSphere e um raio
*Params: CVRObject3D*, CVRVector*
*Return: bool
************************************************************/
/*bool CVRCollisionManager::TestCollisionBSphereRay(CVRObject3D* obj1, CVRVector* obj2)
{
	
}*/



/***********************************************************
*Name: TestCollisionBBoxPolygon()
*Description: verifica se h� colis�o entre uma BoundingBox e um pol�gono
*Params: CVRObject3D*, CVRVector*
*Return: bool
************************************************************/
/*bool CVRCollisionManager::TestCollisionBBoxPolygon(CVRObject3D* obj1, CVRVector* obj2)
{
	
}*/

/***********************************************************
*Name: TestCollisionBBoxRay()
*Description: verifica se h� colis�o entre uma BoundingBox e um raio
*Params: CVRObject3D*, CVRVector*
*Return: bool
************************************************************/
/*bool CVRCollisionManager::TestCollisionBBoxRay(CVRObject3D* obj1, CVRVector* obj2)
{
	
}*/

/***********************************************************
*Name: TestCollisionPolygonPoint()
*Description: verifica se h� colis�o entre um pol�gono e um ponto
*Params: CVRVector*, CVRVector*
*Return: bool
************************************************************/
/*bool CVRCollisionManager::TestCollisionPolygonPoint(CVRVector* obj1, CVRVector* obj2)
{
	
}*/




