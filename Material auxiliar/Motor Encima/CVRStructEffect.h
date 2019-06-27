/**
* @author Bruno Oliveira de Alc�ntara.
* @version 1.0   
* Arquivo: CVRStructEffect.h  
* Descri��o: header da classe respons�vel pela estrutura   
* dos efeitos de Force Feedback do joystick.
* Data de Cria��o: 24/01/2008                                                                     
* Data da �ltima modifica��o: 15/07/2008  
* Local: LNCC                                                                                      
*/

#include <dinput.h>

#ifndef _CVRSTRUCTEFFECT_
#define _CVRSTRUCTEFFECT_

class CVRStructEffect
{
	private:
		
		/** Estrutura primaria de efeitos. */
		DIEFFECT effect;

		/**  Estrutura de foer�as condicionais. */
		DICONDITION   conditForce;

		/** Estrutura descreve for�as customizadas, e definidas. */
		DICUSTOMFORCE customForce;

		/** Estrutura usada pela estrutura DIEFFECT para especificar
		 um envelope opcional para par�metros de um efeito.
		 */
		DIENVELOPE    envelope;
	    
		/** Estrutura descreve um efeito peri�dico. */
		DIPERIODIC    periodic;

		/** Estrutura para efeitos de for�a constante */
		DICONSTANTFORCE  constantForce;

		/**  Vetor com as dire��es dos eixos x, y, e z do joystick */
		LONG axesDirection[3];

	public:
		
		CVRStructEffect();
		~CVRStructEffect();
		DIEFFECT getEffect(){ return effect; }
		DICONDITION getConditForce(){ return conditForce; }
		DICUSTOMFORCE getCustomForce(){ return customForce; }
		DIENVELOPE getEnvelope(){ return envelope; }
		DIPERIODIC getPeriodic(){ return periodic; }
		DICONSTANTFORCE getConstForce(){ return constantForce; }

		/** @Override */
		void Release();

		//Fun��es da estrutura DIEFFECT 
		
		/** Seta todos os valores do atributo effect da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param diEffect - estrutura DIEFFECT 
		*/
		void setDIEFFECT( DIEFFECT diEffect );
		
		/** seta o atributo effect.dwFlags da estrutura DIEFFECT
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param flag - effect.dwFlags
		*/		
		void setFlagsEffect( DWORD flag );    
		
		/** Seta o tempo de dura��o de um efeito
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param duration - effect.dwDuration
		*/
		void setDurationEffect( DWORD duration );
		
		/** Seta o per�odo de amostragem do efeito
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param period - effect.dwSamplePeriod
		*/
		void setPeriodEffect( DWORD );
		
		/** Seta o ganho do efeito criado na estrutura effect(DIEFFECT)
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param gain - effect.dwGain
		*/
		void setGainEffect( DWORD gain );
		
		/** Seta o bot�o que dispara um efeito e o intervalo de
		* 	repeti��o do efeito para o evento com este bot�o.
		*  
		* @author Bruno Oliveira de Alc�ntara.
		* @param button - effect.dwTriggerButton  
		* @param rInterval - effect.dwTriggerRepeatInterval
		*/
		void setButtonEffect( DWORD button, DWORD rInterval );
		
		/** seta valores para os eixos do joystick
		*	
		* @author Bruno Oliveira de Alc�ntara.
		* @param vectorAxes - effect.rgdwAxes, dire��es dos eixos no vetor
		* @param countAxes - effect.cAxes, n�mero de eixos do joystick
		*/
		void setAxesEffect( LPDWORD vectorAxes, DWORD countAxes );
		
		/** Seta o atributo cAxes da estrutura effect(DIEFFECT)
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param countAxes - n�mero de eixos do joytisck
		*/
		void setNumAxesEffect( DWORD countAxes );

		/** Seta os valores do vetor de dire��es rglDirection da 
		* 	estrutura effect(DIEFFECT).
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param directionX - dire��o no eixo X
		* @param directionY - dire��o no eixo Y
		*/
		void setDirectionEffect( int directionX, int directionY );
		
		/** Seta os valores do vetor de dire��es rglDirection da 
		* 	estrutura effect(DIEFFECT).
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param directionX - dire��o no eixo X
		* @param directionY - dire��o no eixo Y
		* @param directionY - dire��o no eixo Z
		*/
		void setDirectionEffect( int directionX, int directionY,  
												int directionZ );
		
		/** Seta o atributo lpEnvelope da estrutura effect(DIEFFECT).
		*
		* @author Bruno Oliveira de Alc�ntara. 
		* @param envelope - envelope para um efeito.
		*/
		void setEnvelopeEffect( LPDIENVELOPE envelope );
		
		/** Seta par�metros da estrutura usada constru��od o efeito.
		* 	Exemplo: 
		*	setTypeSpecificParamsEffect( &cCVRStructEffect.getConditForce(), 
		*								sizeof(DICONDITION));
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param lType - refer�ncia da estrutura usada na constru��o do efeito
		* @param cType - tamanho da estrutura passada
		*/
		void setTypeSpecificParamsEffect( LPVOID lType ,DWORD cType );
		
		/** Seta o delay do efeito.
		*
		* @author Bruno Oliveira de Alc�ntara. 
		* @param delay - delay do efeito.
		*/
		void setDelayEffect( DWORD delay );
	
		//Fun��es da estrutura DICONDITION
		
		/** Seta todos os valores do atributo conditForce 
		*	da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param diCONDITION - estrutura do tipo DICONDITION.
		*/
		void setDICONDITION( DICONDITION diCONDITION );

		/** Seta o valor de offset para o valor de condi��o entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param ioffset - offset para o valor de condi��o.
		*/
		void setIoffset( LONG ioffset );
		
		/** Coeficiente constante do lado positivo entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param pCoefficient - coeficiente positivo.
		*/
        void setLpositiveCoefficient( LONG pCoefficient );
        
        /** Coeficiente constante do lado negativo entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param nCoefficient - coeficiente negativo.
		*/
        void setLnegativeCoefficient( LONG nCoefficient );
        
        /** Seta a for�a m�xima de sa�da do lado positivo 
		*      do offset no valor entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param pSaturation - satura��o positiva do offset
		*/
        void setDwPositiveSaturation( DWORD pSaturation );
        
        /** Seta a for�a m�xima de sa�da do lado negativo 
		*      do offset no valor entre -10,000 e 10,000.
		*     - Se o dispositivo n�o suportar separar satura��o positiva da negativa
		* 	o valor para nSaturation ser� ignorado e o valor de pSaturation  
		*	� usado para iniciar o lado positivo e negativo de satura��o de offset.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param nSaturation - satura��o negativa do offset
		*/
        void setDwNegativeSaturation( DWORD nSaturation );
        
        /** Seta o valor para a regi�o fora do offset com a qual a 
		*      condi��o n�o � ativada, este valor pode variar de 0 a 10,000.
		*     - A condi��o n�o � ativada entre ofsset - dBand e offset + dband.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dBand - 
		*/
        void setLdeadBand( LONG dBand );
        
       	//Fun��es da estrutura DICUSTOMFORCE

		/** Seta todos os valores do atributo customForce
		* 	da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alc�ntara. 
		* @param diCUSTOMFORCE - estrutura do tipo DICUSTOMFORCE
		*/
		void setDICUSTOMFORCE( DICUSTOMFORCE diCUSTOMFORCE );
        
        /** Seta o n�mero de canais (eixos) afetados pela for�a.
		*     - O primeiro canal � associado ao primeiro eixo do dispositivo, 
		*      os egundo canal � associado ao segundo eixo, e assim por diante.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param channels - n�meor de canais(eixos).
		*/
		void setCchannels( DWORD channels );
		
		/** Seta a amostra do per�odo em microsegundos.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dSamplePeriod - tempo em microsegundos.
		*/
        void setDwSamplePeriod( DWORD dSamplePeriod );
        
        /** Seta o n�mero total de amostras em rglForceData. 
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param samples - n�mero total de amostras.
		*/
        void setCsamples( DWORD samples);
        
        /** Seta a refer�ncia para um array de valores de  for�a representando 
		* a for�a customizada. Se existem multiplos canais os valores s�o 
		* intercalados. Po exemplo: se o cChannels � 3,  o primeiro elemnto do 
		* array ser� o primeiro canal , o segundo para o segundo 
		* e assim por diante. 
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param rForceData - refer�ncia para o ponteiro de elementos
		*/
        void setRglForceData( LPLONG rForceData );

		//Fun��es da estrutura DIENVELOPE

		/** Seta todos os valores do atributo envelope da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param diENVELOPE - estrutura do tipo DIENVELOPE
		*/
		void setDIENVELOPE( DIENVELOPE diENVELOPE );
        
        /** Seta a amplitude para o in�cio do envelope relativo 
		*     a base de 0 a 10000.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dAttackLevel - valor de amplitude para o in�cio do envelope.
		*/
		void setDwAttackLevel( DWORD dAttackLevel );
		
		/** Seta o tempo em microsegundos para o sustain  do n�vel(dAttackLevel).
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dAttackTime - tempo em microsegundos.
		*/
        void setDwAttackTime( DWORD dAttackTime );
        
        /** Seta a amplitude para o final do envelope relativo 
		*     a base de 0 a 10000.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dFadeLevel - valor da amplitude para o final do envelope.
		*/
		void setDwFadeLevel( DWORD dFadeLevel );
		
		/** Seta o tempo em microsegundos para o sustain  do n�vel(dFadeLevel).
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dFadeTime - tempo em microsegundos.
		*/
        void setDwFadeTime( DWORD dFadeTime );

		//Fun��es da estrutura DIPERIODIC

		/** Seta todos os valores do atributo periodic da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param diPERIODIC - estrutura do tipo DIPERIODIC
		*/
		void setDIPERIODIC( DIPERIODIC diPERIODIC );
        
        /** Seta o valor da magnitude da for�a entre 0 e 10,000.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dMagnitude - valor de magnitude da for�a.
		*/
		void setDwMagnitude( DWORD dMagnitude );
		
		/** Seta o valor de offset para o valor de 
		* for�a peri�dica entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param ioffset - offset para o valor de for�a peri�dica.
		*/
		void setLoffset( LONG loffset );
        
        /** Seta o valor da posi��o em ciclos de per�odo do efeito com o 
		* qual o playback foi inciado, entre um range de 0 e 35,999. 
		* 	- Se o dispositivo  n�o suportar valores de dwPhase.  Neste
		* 	caso o valor ser� arredondado para um valor suportado.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dPhase - valor poss�vel entre 0 e 35,999. 
		*/
        void setDwPhase( DWORD dPhase );
        
        /** Seta o per�odo do efeito em microsegundos.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param dPeriod - tempo em microsegundos.
		*/
        void setDwPeriod( DWORD dPeriod );

		//Fun��es da estrutura DICONSTANTFORCE
        
        /** Seta o valor da magnitude da for�a
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param cForce - Valor para a for�a constante do joystick 
		*				  que pode variar de 0 a 10000(DI_FFNOMINALMAX).
		*/
		void setConstantForce( LONG  cForce );

};
#endif
