/**
* @author Bruno Oliveira de Alc�ntara.
* @version 1.0    
* Arquivo: CVRForceFeedbackManager.h  
* Descri��o: Classe respons�vel pelo gerenciamento 
* de force feedbackheader.  
* Data de Cria��o: 24/01/2008                                                                     
* Data da �ltima modifica��o: 15/07/2008  
* Local: LNCC                                                                                      
*/

#ifndef _CVRFORCEFEEDBACKMANAGER_
#define _CVRFORCEFEEDBACKMANAGER_

// Includes
#include <dinput.h>
#include <math.h>
#include <stdio.h>
#include "CVRStructEffect.h"
#include "CVRJoystick.h"

/*
// linka as libs necess�rias para a aplica��o
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxerr.lib")
*/

//Define a vers�o do DirectInput 
#pragma message(__FILE__ ": DIRECTINPUT_VERSION undefined. Defaulting to version 0x0800")

//largura da janela(para uso com aplica��es com interface gr�fica)
#define FEEDBACK_WINDOW_WIDTH   200

class CVRForceFeedbackManager: public CVRJoystick
{
	private:
	
		/** Interface of DirectInput used to 
		* manage effects of force-feedback devices.
        */
		LPDIRECTINPUTEFFECT	joystickEffect;
	
		/** define o n�mero de eixos para o Joystick */
		DWORD numEixos; 

		/** tempo do efeito*/
		DWORD timeEffect;
		
		//Eixos do joystick - delimitando o joystick a apenas 3 eixos
		
		/** Valor eixo X do joystick */
		int eixoX;
		
		/** Valor eixo Y do joystick */
		int eixoY;
		
		/** Valor eixo Z do joystick */
		int eixoZ;

	public:

		/**enumera as dire��es do joystick*/
		enum direcao{ ESQUERDA=1, DIREITA=2, FRENTE=3, 
			TRAS=4, DIAGONAL_DIR_FRENTE=5, DIAGONAL_DIR_TRAS=6,
			DIAGONAL_ESQ_FRENTE=7, DIAGONAL_ESQ_TRAS=8 };

		/** Construtora Default da classe forceFeedbackManager */
		CVRForceFeedbackManager();

		/** Construtora da classe forceFeedbackManager 
		* 
		* @param HWND - Handle da aplica��o da janela do windows 
		*/
		CVRForceFeedbackManager(HWND hDlg);

		/** Destrutora da classe forceFeedbackManager */
		~CVRForceFeedbackManager(){ release(); }

		/**Fun��o que inicia o Joystick, as
		* Interfaces de DirectInput, e as interfaces
		* Do joystick force feedback, esta fun��o
		* � chamada uma vez para cada joystick inicializado
		* Pelo aplicativo.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param hDlg HWND - Handle da aplica��o da janela do windows         
		*
		* @return bool
		*/
		bool initFFManager( HWND );


		/** Fun��o usada para liberar as interfaces de DirectInput 
		* e finalizar a implementa��o do joystick. 
		*
		* @author Bruno Oliveira de Alc�ntara.
		*
		* @return bool
		*/
		bool release();

		/** Seta um efeito em joystickEffect
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param CVRStructEffect - Estrutura de dados de efeitos
		* @param GUID - tipo de efeito passado para a cria��o:
		*		- GUID_ConstantForce 
		*		- GUID_RampForce 
		*		- GUID_Square 
		*		- GUID_Sine 
		*		- GUID_Triangle 
		*		- GUID_SawtoothUp 
		*		- GUID_SawtoothDown 
		*		- GUID_Spring 
		*		- GUID_Damper 
		*		- GUID_Inertia 
		*		- GUID_Friction 
		*		- GUID_CustomForce
		* @return bool			
		*/
		bool createEffect( CVRStructEffect, GUID );

		/** seta a posi��o do efeito nos eixos X e Y do joystick
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param int - posi��o do eixo x
		* @param int - posi��o do eixo y
		* @param CVRStructEffect - Estrutura de dados de efeitos
		* @return bool
		*/
		bool setPosition(int, int, CVRStructEffect );

		/** seta a posi��o do efeito nos eixos X, Y e Z do joystick
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param int - posi��o do eixo x
		* @param int - posi��o do eixo y
		* @param int - posi��o do eixo z
		* @param CVRStructEffect - Estrutura de dados de efeitos
		* @return bool
		*/
		bool setPosition(int, int, int, CVRStructEffect );
		
		/** retorna o valor do eixo X do joystick.
		* @author Bruno Oliveira de Alc�ntara.
		* @return eixoX
		*/
		int getEixoX(){ return eixoX;}
		
		/** retorna o valor do eixo Y do joystick.
		* @author Bruno Oliveira de Alc�ntara.
		* @return eixoY
		*/
		int getEixoY(){ return eixoY;}
		
		/** retorna o valor do eixo Z do joystick.
		* @author Bruno Oliveira de Alc�ntara.
		* @return eixoZ
		*/
		int getEixoZ(){ return eixoZ;}

		/** Seta o n�mero de eixos do joystick
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param n - n�mero de eixos(x,y...)
		*/
		void setNumEixos( int n ){ numEixos = n; }

		/** Retorna o n�mero de eixos do joystick
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return DWORD
		*/
		DWORD getNumEixos(){ return numEixos; }
		
		/** inicia um efeito de force feedback
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param DWORD - time , qtd de vezes que o efeito executa
		*
		* @return bool
		*/
		bool startEffect(DWORD time);

		/** p�ra um efeito de force feedback
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool stopEffect();

		/** Descarrega um efeito do joystick
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool unloadEffect();
		
		/** Seta o tempo para um efeito do joystick
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param time - tempo
		*/
		void setTimeEffect( DWORD time ){ timeEffect = time; }

		/** Retorna o tempo para um efeito do joystick
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return DWORD - tempo
		*/
		DWORD getTimeEffect(){ return timeEffect; }

		/** Retorna a interface LPDIRECTINPUTEFFECT
		* do Directinput
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return LPDIRECTINPUTEFFECT
		*/
		LPDIRECTINPUTEFFECT getJoystickEffect(){ return joystickEffect; }

		/*===================EFEITOS========================================*/

		/** simula um efeito demetralhadora com o joystick
		*
		* OBS: este efeito ainda n�o est� funcionando corretamente
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return DWORD - tempo
		*/
		bool metralhadora();

		/** Seta a dire��o para um efeito de vibra��o, 
		* cria e incializa este efeito
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param, direcao - enum de dire��es
		* @return bool
		*/
		bool vibrarDirecao( direcao );

		/** Seta a dire��o do efeito vibrar para a frente:
		*  x = 0 y = 1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool vibrarFrente();
		
		/** Seta a dire��o do efeito vibrar para a tr�s:
		*  x = 0 y = -1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool vibrarTras();

		/** Seta a dire��o do efeito vibrar para a direita:
		*  x = -1000 y = 0
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool vibrarDireita();

		/** Seta a dire��o do efeito vibrar para a esquerda:
		*  x = 1000 y = 0
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool vibrarEsquerda();

		/** Seta a dire��o do efeito vibrar para a diagonal,
		* direita, frente:  x = -1000 y = 1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool vibrarDiagDirFrente();

		
		/** Seta a dire��o do efeito vibrar para a diagonal,
		* direita, tr�s:  x = -1000 y = -1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool vibrarDiagDirTras();

		
		/** Seta a dire��o do efeito vibrar para a diagonal,
		* esquerda, frente:  x = 1000 y = 1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool vibrarDiagEsqFrente();
		
		
		/** Seta a dire��o do efeito vibrar para a diagonal,
		* direita, tr�s:  x = 1000 y = -1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool vibrarDiagEsqTras();

		/** Seta a dire��o para um efeito de for�a constante, 
		* cria e incializa este efeito
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @param, direcao - enum de dire��es
		* @return bool
		*/
		bool forceDirecao( direcao );

		/** Seta a dire��o do efeito for�a para a frente:
		*  x = 0 y = 1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool forceFrente();

		/** Seta a dire��o do efeito for�a para a tr�s:
		*  x = 0 y = -1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool forceTras();

		/** Seta a dire��o do efeito for�a para a direita:
		*  x = -1000 y = 0
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool forceDireita();

		/** Seta a dire��o do efeito for�a para a esquerda:
		*  x = 1000 y = 0
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool forceEsquerda();

		/** Seta a dire��o do efeito for�a para a diagonal,
		* direita, frente:  x = -1000 y = 1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool forceDiagDirFrente();

		/** Seta a dire��o do efeito for�a para a diagonal,
		* direita, tr�s:  x = -1000 y = -1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool forceDiagDirTras();

		/** Seta a dire��o do efeito for�a para a diagonal,
		* esquerda, frente:  x = 1000 y = 1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool forceDiagEsqFrente();

		/** Seta a dire��o do efeito for�a para a diagonal,
		* direita, tr�s:  x = 1000 y = -1000
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool forceDiagEsqTras();

		/** Simula efeito de  condi��o do joystick
		* sens��o de mexer algo condensado:
		* Exemplo com uma colher mexendo sopa
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool condensado();
		
		
		/** Simula efeito do joystick com atrito a superf�cie
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		bool atrito();

		/** Controla a dire��o do joystick com os par�metros da fun��o:
		* Exemplo: objJoy.controle(520,520);
		* o joystick move-se com for�a constante 
		* para a posi��o x = 520 e y = 520.
		*
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/	
		bool controle(int, int);

		/** Converte a coordenada 0 <= nCoord <= FEEDBACK_WINDOW_WIDTH
		*   para um valor de entre -DI_FFNOMINALMAX to +DI_FFNOMINALMAX.
		*	- DI_FFNOMINALMAX = 10000
		*   - FEEDBACK_WINDOW_WIDTH = 200
		* 
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
		int  coordToForce( int nCoord );
		
		/** Fun��o criada para afzer testes com novos efeitos.
		*
		* OBS: Apenas utilizada no modo debuger ou para DEMO.
		* 
		* @author Bruno Oliveira de Alc�ntara.
		* @return bool
		*/
        bool test();
};
#endif
