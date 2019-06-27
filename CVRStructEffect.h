/**
* @author Bruno Oliveira de Alcântara.
* @version 1.0   
* Arquivo: CVRStructEffect.h  
* Descrição: header da classe responsável pela estrutura   
* dos efeitos de Force Feedback do joystick.
* Data de Criação: 24/01/2008                                                                     
* Data da última modificação: 15/07/2008  
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

		/**  Estrutura de foerças condicionais. */
		DICONDITION   conditForce;

		/** Estrutura descreve forças customizadas, e definidas. */
		DICUSTOMFORCE customForce;

		/** Estrutura usada pela estrutura DIEFFECT para especificar
		 um envelope opcional para parâmetros de um efeito.
		 */
		DIENVELOPE    envelope;
	    
		/** Estrutura descreve um efeito periódico. */
		DIPERIODIC    periodic;

		/** Estrutura para efeitos de força constante */
		DICONSTANTFORCE  constantForce;

		/**  Vetor com as direções dos eixos x, y, e z do joystick */
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

		//Funções da estrutura DIEFFECT 
		
		/** Seta todos os valores do atributo effect da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alcântara.
		* @param diEffect - estrutura DIEFFECT 
		*/
		void setDIEFFECT( DIEFFECT diEffect );
		
		/** seta o atributo effect.dwFlags da estrutura DIEFFECT
		*
		* @author Bruno Oliveira de Alcântara.
		* @param flag - effect.dwFlags
		*/		
		void setFlagsEffect( DWORD flag );    
		
		/** Seta o tempo de duração de um efeito
		*
		* @author Bruno Oliveira de Alcântara.
		* @param duration - effect.dwDuration
		*/
		void setDurationEffect( DWORD duration );
		
		/** Seta o período de amostragem do efeito
		*
		* @author Bruno Oliveira de Alcântara.
		* @param period - effect.dwSamplePeriod
		*/
		void setPeriodEffect( DWORD );
		
		/** Seta o ganho do efeito criado na estrutura effect(DIEFFECT)
		*
		* @author Bruno Oliveira de Alcântara.
		* @param gain - effect.dwGain
		*/
		void setGainEffect( DWORD gain );
		
		/** Seta o botão que dispara um efeito e o intervalo de
		* 	repetição do efeito para o evento com este botão.
		*  
		* @author Bruno Oliveira de Alcântara.
		* @param button - effect.dwTriggerButton  
		* @param rInterval - effect.dwTriggerRepeatInterval
		*/
		void setButtonEffect( DWORD button, DWORD rInterval );
		
		/** seta valores para os eixos do joystick
		*	
		* @author Bruno Oliveira de Alcântara.
		* @param vectorAxes - effect.rgdwAxes, direções dos eixos no vetor
		* @param countAxes - effect.cAxes, número de eixos do joystick
		*/
		void setAxesEffect( LPDWORD vectorAxes, DWORD countAxes );
		
		/** Seta o atributo cAxes da estrutura effect(DIEFFECT)
		*
		* @author Bruno Oliveira de Alcântara.
		* @param countAxes - número de eixos do joytisck
		*/
		void setNumAxesEffect( DWORD countAxes );

		/** Seta os valores do vetor de direções rglDirection da 
		* 	estrutura effect(DIEFFECT).
		*
		* @author Bruno Oliveira de Alcântara.
		* @param directionX - direção no eixo X
		* @param directionY - direção no eixo Y
		*/
		void setDirectionEffect( int directionX, int directionY );
		
		/** Seta os valores do vetor de direções rglDirection da 
		* 	estrutura effect(DIEFFECT).
		*
		* @author Bruno Oliveira de Alcântara.
		* @param directionX - direção no eixo X
		* @param directionY - direção no eixo Y
		* @param directionY - direção no eixo Z
		*/
		void setDirectionEffect( int directionX, int directionY,  
												int directionZ );
		
		/** Seta o atributo lpEnvelope da estrutura effect(DIEFFECT).
		*
		* @author Bruno Oliveira de Alcântara. 
		* @param envelope - envelope para um efeito.
		*/
		void setEnvelopeEffect( LPDIENVELOPE envelope );
		
		/** Seta parâmetros da estrutura usada construçãod o efeito.
		* 	Exemplo: 
		*	setTypeSpecificParamsEffect( &cCVRStructEffect.getConditForce(), 
		*								sizeof(DICONDITION));
		*
		* @author Bruno Oliveira de Alcântara.
		* @param lType - referência da estrutura usada na construção do efeito
		* @param cType - tamanho da estrutura passada
		*/
		void setTypeSpecificParamsEffect( LPVOID lType ,DWORD cType );
		
		/** Seta o delay do efeito.
		*
		* @author Bruno Oliveira de Alcântara. 
		* @param delay - delay do efeito.
		*/
		void setDelayEffect( DWORD delay );
	
		//Funções da estrutura DICONDITION
		
		/** Seta todos os valores do atributo conditForce 
		*	da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alcântara.
		* @param diCONDITION - estrutura do tipo DICONDITION.
		*/
		void setDICONDITION( DICONDITION diCONDITION );

		/** Seta o valor de offset para o valor de condição entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param ioffset - offset para o valor de condição.
		*/
		void setIoffset( LONG ioffset );
		
		/** Coeficiente constante do lado positivo entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param pCoefficient - coeficiente positivo.
		*/
        void setLpositiveCoefficient( LONG pCoefficient );
        
        /** Coeficiente constante do lado negativo entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param nCoefficient - coeficiente negativo.
		*/
        void setLnegativeCoefficient( LONG nCoefficient );
        
        /** Seta a força máxima de saída do lado positivo 
		*      do offset no valor entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param pSaturation - saturação positiva do offset
		*/
        void setDwPositiveSaturation( DWORD pSaturation );
        
        /** Seta a força máxima de saída do lado negativo 
		*      do offset no valor entre -10,000 e 10,000.
		*     - Se o dispositivo não suportar separar saturação positiva da negativa
		* 	o valor para nSaturation será ignorado e o valor de pSaturation  
		*	é usado para iniciar o lado positivo e negativo de saturação de offset.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param nSaturation - saturação negativa do offset
		*/
        void setDwNegativeSaturation( DWORD nSaturation );
        
        /** Seta o valor para a região fora do offset com a qual a 
		*      condição não é ativada, este valor pode variar de 0 a 10,000.
		*     - A condição não é ativada entre ofsset - dBand e offset + dband.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dBand - 
		*/
        void setLdeadBand( LONG dBand );
        
       	//Funções da estrutura DICUSTOMFORCE

		/** Seta todos os valores do atributo customForce
		* 	da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alcântara. 
		* @param diCUSTOMFORCE - estrutura do tipo DICUSTOMFORCE
		*/
		void setDICUSTOMFORCE( DICUSTOMFORCE diCUSTOMFORCE );
        
        /** Seta o número de canais (eixos) afetados pela força.
		*     - O primeiro canal é associado ao primeiro eixo do dispositivo, 
		*      os egundo canal é associado ao segundo eixo, e assim por diante.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param channels - númeor de canais(eixos).
		*/
		void setCchannels( DWORD channels );
		
		/** Seta a amostra do período em microsegundos.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dSamplePeriod - tempo em microsegundos.
		*/
        void setDwSamplePeriod( DWORD dSamplePeriod );
        
        /** Seta o número total de amostras em rglForceData. 
		*
		* @author Bruno Oliveira de Alcântara.
		* @param samples - número total de amostras.
		*/
        void setCsamples( DWORD samples);
        
        /** Seta a referência para um array de valores de  força representando 
		* a força customizada. Se existem multiplos canais os valores são 
		* intercalados. Po exemplo: se o cChannels é 3,  o primeiro elemnto do 
		* array será o primeiro canal , o segundo para o segundo 
		* e assim por diante. 
		*
		* @author Bruno Oliveira de Alcântara.
		* @param rForceData - referência para o ponteiro de elementos
		*/
        void setRglForceData( LPLONG rForceData );

		//Funções da estrutura DIENVELOPE

		/** Seta todos os valores do atributo envelope da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alcântara.
		* @param diENVELOPE - estrutura do tipo DIENVELOPE
		*/
		void setDIENVELOPE( DIENVELOPE diENVELOPE );
        
        /** Seta a amplitude para o início do envelope relativo 
		*     a base de 0 a 10000.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dAttackLevel - valor de amplitude para o início do envelope.
		*/
		void setDwAttackLevel( DWORD dAttackLevel );
		
		/** Seta o tempo em microsegundos para o sustain  do nível(dAttackLevel).
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dAttackTime - tempo em microsegundos.
		*/
        void setDwAttackTime( DWORD dAttackTime );
        
        /** Seta a amplitude para o final do envelope relativo 
		*     a base de 0 a 10000.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dFadeLevel - valor da amplitude para o final do envelope.
		*/
		void setDwFadeLevel( DWORD dFadeLevel );
		
		/** Seta o tempo em microsegundos para o sustain  do nível(dFadeLevel).
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dFadeTime - tempo em microsegundos.
		*/
        void setDwFadeTime( DWORD dFadeTime );

		//Funções da estrutura DIPERIODIC

		/** Seta todos os valores do atributo periodic da classe CVRStructEffect
		*
		* @author Bruno Oliveira de Alcântara.
		* @param diPERIODIC - estrutura do tipo DIPERIODIC
		*/
		void setDIPERIODIC( DIPERIODIC diPERIODIC );
        
        /** Seta o valor da magnitude da força entre 0 e 10,000.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dMagnitude - valor de magnitude da força.
		*/
		void setDwMagnitude( DWORD dMagnitude );
		
		/** Seta o valor de offset para o valor de 
		* força periódica entre -10,000 e 10,000.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param ioffset - offset para o valor de força periódica.
		*/
		void setLoffset( LONG loffset );
        
        /** Seta o valor da posição em ciclos de período do efeito com o 
		* qual o playback foi inciado, entre um range de 0 e 35,999. 
		* 	- Se o dispositivo  não suportar valores de dwPhase.  Neste
		* 	caso o valor será arredondado para um valor suportado.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dPhase - valor possível entre 0 e 35,999. 
		*/
        void setDwPhase( DWORD dPhase );
        
        /** Seta o período do efeito em microsegundos.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param dPeriod - tempo em microsegundos.
		*/
        void setDwPeriod( DWORD dPeriod );

		//Funções da estrutura DICONSTANTFORCE
        
        /** Seta o valor da magnitude da força
		*
		* @author Bruno Oliveira de Alcântara.
		* @param cForce - Valor para a força constante do joystick 
		*				  que pode variar de 0 a 10000(DI_FFNOMINALMAX).
		*/
		void setConstantForce( LONG  cForce );

};
#endif
