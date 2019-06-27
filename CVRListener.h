/***********************************************************************
*Nome: CVRListener.h
*Descri��o: Cabe�alho da classe respons�vel pelo configura��o do ouvinte
*Data: 27/09/07
*Local: LNCC
***********************************************************************/
#ifndef _CVRLISTENER_
#define _CVRLISTENER_

//Bibliotecas
#include "CVRObject.h"
#include "CVRVector.h"
#include "CVRSound.h"

class CVRSoundManager;

class CVRListener: public CVRObject 
{
    private:

		//interface do ouvinte
        IDirectSound3DListener8 *Listener;

		//vetores da Orienta��o do ouvinte
		D3DVECTOR vectorFront;
		D3DVECTOR vectorTop;

		//vari�vel que guarda o DopplerFactor
		float fDoppler;
       
	public:

		CVRSoundManager *soundManager;

		//construtora
		CVRListener();
		
		//destrutora
		~CVRListener(); 

        //linka o ouvinte com o som
		bool LinkSoundListener(CVRSound*);

		//seta a interface Ouvinte para NULL
		void SetNULL();
		
		//retorna a interface Ouvinte
		IDirectSound3DListener* GetListener();
				 
		//seta as posi��es x,y e z do ouvinte
		void SetPosition(float x,float y,float z);
		
		//seta a posi��o x do ouvinte
	    void SetX(float x);
		
	    //seta a posi��o y do ouvinte
	    void SetY(float y);
		
	    //seta a posi��o z do ouvinte
	    void SetZ(float z);
		
		//retorna as posi��es x,y e z do ouvinte
		CVRVector GetPosition();
		
		//retorna a posi��o X do ouvinte
		float GetX();
		
		//retorna a posi��o Y do ouvinte
		float GetY();
		
		//retorna a posi��o Z do ouvinte
		float GetZ();
		
		//seta o Doppler efect
		void SetDoppler(float value);
		
		//seta o Distance Factor
	    void SetDistanceFactor(float value);
	
		//seta a velocidade do ouvinte
	    void SetVelocity(float x,float y,float z);

		//seta a velocidade do ouvin te no eixo x
		void SetVelocityAxe_x(float x);

		//seta a velocidade do ouvin te no eixo y
		void SetVelocityAxe_y(float y);

		//seta a velocidade do ouvin te no eixo z
		void SetVelocityAxe_z(float z);
			
		//seta o valor de rolloff factor
		void SetRolloff(float rolloff);
				 
		//seta a orienta��o do ouvinte.Os 3 primeiros par�metros da fun��o s�o do vetor da frente da cabe�a
		//do ouvinte com os eixos x, y e z, os 3 �ltimos par�metros da fun��o s�o do vetor do topo da 
	    //cabe�a do ouvinte com os eixos x, y e z
	    void SetOrientation(float frontVectorX,float frontVectorY,float frontVectorZ,float topVectorX,float topVectorY,float topVectorZ);
	
		//retorna o valor de Doppler
	    float GetDoppler();
	
		//retorna o Distance Factor
	    float GetDistanceFactor();
			
		//retorna um D3DVECTOR com a velocidade do ouvinte nos 3 eixos(x,y,z)
		CVRVector GetVelocity();

		//retorna a velocidade no eixo x
		float GetVelocityAxe_x();

		//retorna a velocidade no eixo y
		float GetVelocityAxe_y();

		//retorna a velocidade no eixo z
		float GetVelocityAxe_z();

		//retorna os valores dos vetores de front e top da orienta��o do ouvinte
	    void GetOrientation();
		
		//retorna o vetor da frente da cabe�a do ouvinte
		CVRVector GetOrientationFront();
		
		//retorna o vetor do topo da cabe�a do ouvinte
		CVRVector GetOrientationTop();

		//Libera recursos
		void Release();

};//fim da classe Listener 
#endif