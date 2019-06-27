/***********************************************************************
*Nome: CVRListener.cpp
*Descrição: Cabeçalho da classe responsável implementação do ouvinte
*Data: 27/09/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRListener.h"
#include "CVRSoundManager.h"


/***********************************************************
*Name: CVRListener()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRListener::CVRListener()
{
	Listener = NULL;
	fDoppler = 0.0f; 
	soundManager = NULL;
}

/***********************************************************
*Name: CVRListener()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRListener::~CVRListener()
{
				
}

/***********************************************************
*Name: SetNull()
*Description: seta para NULL a interface do directsound
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRListener::SetNULL()
{
	Listener = NULL;
}

/***********************************************************
*Name: GetListener()
*Description: retorna a interface do directsound
*Params: Nenhum
*Return: IDirectSound3DListener*
************************************************************/
IDirectSound3DListener* CVRListener::GetListener()
{
	return Listener;
}

/***********************************************************
*Name: SetPosition()
*Description: seta a posicao x,y,z do ouvinte
*Params: float, float, float
*Return: void
************************************************************/
void CVRListener::SetPosition(float x, float y, float z)
{

	double difDistanciaX = 0.0;
	double difDistanciaY = 0.0;
	double difDistanciaZ = 0.0;
	double distanciaMaxSound = 0.0f;
   	
	Listener->SetPosition(x,y,-z, DS3D_IMMEDIATE);
    SetRolloff(10.0f);

	//testa se o ouvinte passou do máximo de distância do som
	for(int iIndex = (int)soundManager->sounds.size()-1; iIndex>=0; iIndex--)
	{
		difDistanciaX = GetX() - soundManager->sounds[iIndex]->GetX();
		difDistanciaY = GetY() - soundManager->sounds[iIndex]->GetY();
		difDistanciaZ = GetZ() - soundManager->sounds[iIndex]->GetZ();
        
		distanciaMaxSound = soundManager->sounds[iIndex]->GetMax();

		if ((difDistanciaX > distanciaMaxSound ) ||(difDistanciaY > distanciaMaxSound ) || (difDistanciaZ > distanciaMaxSound )||(-difDistanciaX > distanciaMaxSound ) ||(-difDistanciaY > distanciaMaxSound ) || (-difDistanciaZ > distanciaMaxSound ))
	
		       soundManager->sounds[iIndex]->MuteSound(true);
		
	    else
	
			   soundManager->sounds[iIndex]->MuteSound(false);
			
	}//fim do for       
	
}
/***********************************************************
*Name: SetX()
*Description: seta a posicao x
*Params: float
*Return: void
************************************************************/
void CVRListener::SetX(float x)
{
	Listener->SetPosition(x,NULL,NULL, DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetY()
*Description: seta a posicao y
*Params: float
*Return: void
************************************************************/
void CVRListener::SetY(float y)
{
	Listener->SetPosition(NULL,y,NULL, DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetZ()
*Description: seta a posicao z
*Params: float
*Return: void
************************************************************/
void CVRListener::SetZ(float z)
{
	Listener->SetPosition(NULL,NULL,-z, DS3D_IMMEDIATE);
}

/***********************************************************
*Name: GetPosition()
*Description: retorna um vetor com a posicao do som
*Params: void
*Return: void
************************************************************/
CVRVector CVRListener::GetPosition()
{
	CVRVector vetPos;
	D3DVECTOR d3dVector;
 	Listener->GetPosition(&d3dVector);
	vetPos.x = d3dVector.x;
	vetPos.y = d3dVector.y;
	vetPos.z = -d3dVector.z;
			
	return vetPos;
}

/***********************************************************
*Name: GetX()
*Description: retorna a posicao x do ouvinte
*Params: void
*Return: float
************************************************************/
float CVRListener::GetX()
{
	D3DVECTOR d3dVector;
	Listener->GetPosition(&d3dVector);

	return d3dVector.x;
}

/***********************************************************
*Name: GetY()
*Description: retorna a posicao Y do ouvinte
*Params: void
*Return: float
************************************************************/
float CVRListener::GetY()
{
	D3DVECTOR d3dVector;
	Listener->GetPosition(&d3dVector);

	return d3dVector.y;
}

/***********************************************************
*Name: GetZ()
*Description: retorna a posicao Z do ouvinte
*Params: void
*Return: float
************************************************************/
float CVRListener::GetZ()
{
	D3DVECTOR d3dVector;
	Listener->GetPosition(&d3dVector);
	d3dVector.z = -d3dVector.z;

  	return d3dVector.z;
}

/***********************************************************
*Name: SetDoppler()
*Description: seta o efeito doppler da aplicação
*Params: float
*Return: void
************************************************************/
void CVRListener::SetDoppler(float value)
{
	fDoppler =  value;
	Listener->SetDopplerFactor(value,DS3D_IMMEDIATE);
			
}

/***********************************************************
*Name: SetDistanceFactor()
*Description: Seta o Distance Factor da aplicação.
O distance factor é o número de metros 
numa unidade de vetor. Por definição, o distance factor é 1,0
*Params: float
*Return: void
************************************************************/
void CVRListener::SetDistanceFactor(float value)
{
	Listener->SetDistanceFactor(value,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetVelocity()
*Description: seta a velocidade do ouvinte nos eixos x,y,z
*Params: float, float, float
*Return: void
************************************************************/
void CVRListener::SetVelocity(float x,float y,float z)
{
	Listener->SetVelocity(x,y,z,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetVelocityAxe_x()
*Description: seta a velocidade do ouvinte no eixo x
*Params: float
*Return: void
************************************************************/
void CVRListener::SetVelocityAxe_x(float x)
{
	Listener->SetVelocity(x,NULL,NULL,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: setVelocityAxe_y()
*Description: seta a velocidade do ouvinte no eixo y
*Params: float
*Return: void
************************************************************/
void CVRListener::SetVelocityAxe_y(float y)
{
	Listener->SetVelocity(NULL,y,NULL,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetVelocityAxe_z()
*Description: seta a velocidade do ouvinte no eixo z
*Params: float
*Return: void
************************************************************/
void CVRListener::SetVelocityAxe_z(float z)
{
	Listener->SetVelocity(NULL,NULL,z,DS3D_IMMEDIATE);
}


/***********************************************************
*Name: SetRolloff()
*Description: Seta o efeito de rollof da aplicaçao.O Rolloff é a quantia de atenuação que 
é aplicada a sons, baseados na distância do ouvinte da fonte de som.
O DirectSound pode ignorar Rolloff, exagera-lo, ou lhe dar o mesmo efeito 
como no mundo real, dependendo de um parâmetro global chamado de  Rolloff factor
*Params: float
*Return: void
************************************************************/
void CVRListener::SetRolloff(float rolloff)
{
	Listener->SetRolloffFactor(rolloff,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetOrientation()
*Description: Seta a Orintação do Ouvinte(listener).
A orientação do ouvinte é definida pelo relacionamento
entre dois vetores que compartilham uma origem no centro 
da cabeça do ouvinte: os vetores do topo e  frontal
*Params: float, float, float, float, float, float
*Return: void
************************************************************/
void CVRListener::SetOrientation(float frontVectorX,float frontVectorY,float frontVectorZ,float topVectorX,float topVectorY,float topVectorZ)
{
	Listener->SetOrientation(frontVectorX,frontVectorY,frontVectorZ,topVectorX,topVectorY,topVectorZ,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: GetDoppler()
*Description: retorna o valor do fator doppler
*Params: void
*Return: float 
************************************************************/
float CVRListener::GetDoppler()
{
	Listener->GetDopplerFactor(&fDoppler);

	return fDoppler;
}

/***********************************************************
*Name: GetDistanceFactor()
*Description: retorna o valor do distance doppler
*Params: void
*Return: float
************************************************************/
float CVRListener::GetDistanceFactor()
{
	float vecDistanceFactor;
	Listener->GetDopplerFactor(&vecDistanceFactor);

	return vecDistanceFactor;
}

/***********************************************************
*Name: GetVelocity()
*Description: retorna um vetor com as velocidades dos eixos x,y,z
*Params: void
*Return: CVRVector
************************************************************/
CVRVector CVRListener::GetVelocity()
{
	CVRVector vetVel;
	D3DVECTOR vecVelocity;
	Listener->GetVelocity(&vecVelocity);
	vetVel.x = vecVelocity.x;
	vetVel.y = vecVelocity.y;
	vetVel.z = vecVelocity.z;

	return vetVel;
}

/***********************************************************
*Name: GetVelocityAxe_x()
*Description: retorna a velocidade do ouvinte em x
*Params: void
*Return: float
************************************************************/
float CVRListener::GetVelocityAxe_x()
{
	D3DVECTOR vecVelocity;
	Listener->GetVelocity(&vecVelocity);

    return vecVelocity.x;
}

/***********************************************************
*Name: GetVelocityAxe_y()
*Description: retorna a velocidade do ouvinte em y
*Params: void
*Return: float
************************************************************/
float CVRListener::GetVelocityAxe_y()
{
	D3DVECTOR vecVelocity;
    Listener->GetVelocity(&vecVelocity);

	return vecVelocity.y;
}

/***********************************************************
*Name: GetVelocityAxe_z()
*Description: retorna a velocidade do ouvinte em z
*Params: void
*Return: float
************************************************************/
float CVRListener::GetVelocityAxe_z()
{
	D3DVECTOR vecVelocity;
    Listener->GetVelocity(&vecVelocity);

	return vecVelocity.z;
}

/***********************************************************
*Name: Getorientation()
*Description: obtem a orientacao frontal e de topo do ouvinte
*Params: void
*Return: void
************************************************************/
void CVRListener::GetOrientation()
{
	Listener->GetOrientation(&vectorFront,&vectorTop);
}

/***********************************************************
*Name: GetorientationFront()
*Description: retorna a orientacao frontal
*Params: void
*Return: CVRVector
************************************************************/
CVRVector CVRListener::GetOrientationFront()
{	
	GetOrientation();
	CVRVector vetFront;
	vetFront.x = vectorFront.x;
	vetFront.y = vectorFront.y;
	vetFront.z = vectorFront.z;
    return vetFront;		 
}

/***********************************************************
*Name: GetorientationTop()
*Description: retorna a orientacao frontal
*Params: void
*Return: CVRVector
************************************************************/
CVRVector CVRListener::GetOrientationTop()
{
	GetOrientation();
    CVRVector vetTop;
	vetTop.x = vectorTop.x;
	vetTop.y = vectorTop.y;
	vetTop.z = vectorTop.z;
    return vetTop;
}

/***********************************************************
*Name: LinkSoundListener()
*Description: linka o ouvinte com os sons 3D
*Params: CVRSound*
*Return: bool
************************************************************/
bool CVRListener::LinkSoundListener(CVRSound *sound)
{
	// Obtem o ouvinte a partir do audiopath 3D
	if(FAILED(sound->GetAudiopath()->GetObjectInPath(0, DMUS_PATH_PRIMARY_BUFFER,
						0, GUID_All_Objects, 0,
						IID_IDirectSound3DListener8,
						(void **)&Listener)))
			return false;

	return true;
}//fim da função getOuvinte


/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: void
*Return: void
************************************************************/
void CVRListener::Release()
{
}