/**
* @author Bruno Oliveira de Alcântara.
* @version 1.0    
* Arquivo: CVRForceFeedbackManager.h  
* Descrição: Classe responsável pelo gerenciamento 
* de force feedbackheader.  
* Data de Criação: 24/01/2008                                                                     
* Data da última modificação: 15/07/2008  
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
// linka as libs necessárias para a aplicação
#pragma comment(lib,"dxguid.lib")
#pragma comment(lib,"dinput8.lib")
#pragma comment(lib,"dxerr.lib")
*/

//Define a versão do DirectInput 
#pragma message(__FILE__ ": DIRECTINPUT_VERSION undefined. Defaulting to version 0x0800")

//largura da janela(para uso com aplicações com interface gráfica)
#define FEEDBACK_WINDOW_WIDTH   200

class CVRForceFeedbackManager: public CVRJoystick
{
	private:
	
		/** Interface of DirectInput used to 
		* manage effects of force-feedback devices.
        */
		LPDIRECTINPUTEFFECT	joystickEffect;
	
		/** define o número de eixos para o Joystick */
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

		/**enumera as direções do joystick*/
		enum direcao{ ESQUERDA=1, DIREITA=2, FRENTE=3, 
			TRAS=4, DIAGONAL_DIR_FRENTE=5, DIAGONAL_DIR_TRAS=6,
			DIAGONAL_ESQ_FRENTE=7, DIAGONAL_ESQ_TRAS=8 };

		/** Construtora Default da classe forceFeedbackManager */
		CVRForceFeedbackManager();

		/** Construtora da classe forceFeedbackManager 
		* 
		* @param HWND - Handle da aplicação da janela do windows 
		*/
		CVRForceFeedbackManager(HWND hDlg);

		/** Destrutora da classe forceFeedbackManager */
		~CVRForceFeedbackManager(){ release(); }

		/**Função que inicia o Joystick, as
		* Interfaces de DirectInput, e as interfaces
		* Do joystick force feedback, esta função
		* É chamada uma vez para cada joystick inicializado
		* Pelo aplicativo.
		*
		* @author Bruno Oliveira de Alcântara.
		* @param hDlg HWND - Handle da aplicação da janela do windows         
		*
		* @return bool
		*/
		bool initFFManager( HWND );


		/** Função usada para liberar as interfaces de DirectInput 
		* e finalizar a implementação do joystick. 
		*
		* @author Bruno Oliveira de Alcântara.
		*
		* @return bool
		*/
		bool release();

		/** Seta um efeito em joystickEffect
		*
		* @author Bruno Oliveira de Alcântara.
		* @param CVRStructEffect - Estrutura de dados de efeitos
		* @param GUID - tipo de efeito passado para a criação:
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

		/** seta a posição do efeito nos eixos X e Y do joystick
		*
		* @author Bruno Oliveira de Alcântara.
		* @param int - posição do eixo x
		* @param int - posição do eixo y
		* @param CVRStructEffect - Estrutura de dados de efeitos
		* @return bool
		*/
		bool setPosition(int, int, CVRStructEffect );

		/** seta a posição do efeito nos eixos X, Y e Z do joystick
		*
		* @author Bruno Oliveira de Alcântara.
		* @param int - posição do eixo x
		* @param int - posição do eixo y
		* @param int - posição do eixo z
		* @param CVRStructEffect - Estrutura de dados de efeitos
		* @return bool
		*/
		bool setPosition(int, int, int, CVRStructEffect );
		
		/** retorna o valor do eixo X do joystick.
		* @author Bruno Oliveira de Alcântara.
		* @return eixoX
		*/
		int getEixoX(){ return eixoX;}
		
		/** retorna o valor do eixo Y do joystick.
		* @author Bruno Oliveira de Alcântara.
		* @return eixoY
		*/
		int getEixoY(){ return eixoY;}
		
		/** retorna o valor do eixo Z do joystick.
		* @author Bruno Oliveira de Alcântara.
		* @return eixoZ
		*/
		int getEixoZ(){ return eixoZ;}

		/** Seta o número de eixos do joystick
		*
		* @author Bruno Oliveira de Alcântara.
		* @param n - número de eixos(x,y...)
		*/
		void setNumEixos( int n ){ numEixos = n; }

		/** Retorna o número de eixos do joystick
		*
		* @author Bruno Oliveira de Alcântara.
		* @return DWORD
		*/
		DWORD getNumEixos(){ return numEixos; }
		
		/** inicia um efeito de force feedback
		*
		* @author Bruno Oliveira de Alcântara.
		* @param DWORD - time , qtd de vezes que o efeito executa
		*
		* @return bool
		*/
		bool startEffect(DWORD time);

		/** pára um efeito de force feedback
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool stopEffect();

		/** Descarrega um efeito do joystick
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool unloadEffect();
		
		/** Seta o tempo para um efeito do joystick
		*
		* @author Bruno Oliveira de Alcântara.
		* @param time - tempo
		*/
		void setTimeEffect( DWORD time ){ timeEffect = time; }

		/** Retorna o tempo para um efeito do joystick
		*
		* @author Bruno Oliveira de Alcântara.
		* @return DWORD - tempo
		*/
		DWORD getTimeEffect(){ return timeEffect; }

		/** Retorna a interface LPDIRECTINPUTEFFECT
		* do Directinput
		*
		* @author Bruno Oliveira de Alcântara.
		* @return LPDIRECTINPUTEFFECT
		*/
		LPDIRECTINPUTEFFECT getJoystickEffect(){ return joystickEffect; }

		/*===================EFEITOS========================================*/

		/** simula um efeito demetralhadora com o joystick
		*
		* OBS: este efeito ainda não está funcionando corretamente
		*
		* @author Bruno Oliveira de Alcântara.
		* @return DWORD - tempo
		*/
		bool metralhadora();

		/** Seta a direção para um efeito de vibração, 
		* cria e incializa este efeito
		*
		* @author Bruno Oliveira de Alcântara.
		* @param, direcao - enum de direções
		* @return bool
		*/
		bool vibrarDirecao( direcao );

		/** Seta a direção do efeito vibrar para a frente:
		*  x = 0 y = 1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool vibrarFrente();
		
		/** Seta a direção do efeito vibrar para a trás:
		*  x = 0 y = -1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool vibrarTras();

		/** Seta a direção do efeito vibrar para a direita:
		*  x = -1000 y = 0
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool vibrarDireita();

		/** Seta a direção do efeito vibrar para a esquerda:
		*  x = 1000 y = 0
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool vibrarEsquerda();

		/** Seta a direção do efeito vibrar para a diagonal,
		* direita, frente:  x = -1000 y = 1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool vibrarDiagDirFrente();

		
		/** Seta a direção do efeito vibrar para a diagonal,
		* direita, trás:  x = -1000 y = -1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool vibrarDiagDirTras();

		
		/** Seta a direção do efeito vibrar para a diagonal,
		* esquerda, frente:  x = 1000 y = 1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool vibrarDiagEsqFrente();
		
		
		/** Seta a direção do efeito vibrar para a diagonal,
		* direita, trás:  x = 1000 y = -1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool vibrarDiagEsqTras();

		/** Seta a direção para um efeito de força constante, 
		* cria e incializa este efeito
		*
		* @author Bruno Oliveira de Alcântara.
		* @param, direcao - enum de direções
		* @return bool
		*/
		bool forceDirecao( direcao );

		/** Seta a direção do efeito força para a frente:
		*  x = 0 y = 1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool forceFrente();

		/** Seta a direção do efeito força para a trás:
		*  x = 0 y = -1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool forceTras();

		/** Seta a direção do efeito força para a direita:
		*  x = -1000 y = 0
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool forceDireita();

		/** Seta a direção do efeito força para a esquerda:
		*  x = 1000 y = 0
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool forceEsquerda();

		/** Seta a direção do efeito força para a diagonal,
		* direita, frente:  x = -1000 y = 1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool forceDiagDirFrente();

		/** Seta a direção do efeito força para a diagonal,
		* direita, trás:  x = -1000 y = -1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool forceDiagDirTras();

		/** Seta a direção do efeito força para a diagonal,
		* esquerda, frente:  x = 1000 y = 1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool forceDiagEsqFrente();

		/** Seta a direção do efeito força para a diagonal,
		* direita, trás:  x = 1000 y = -1000
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool forceDiagEsqTras();

		/** Simula efeito de  condição do joystick
		* sensção de mexer algo condensado:
		* Exemplo com uma colher mexendo sopa
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool condensado();
		
		
		/** Simula efeito do joystick com atrito a superfície
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		bool atrito();

		/** Controla a direção do joystick com os parâmetros da função:
		* Exemplo: objJoy.controle(520,520);
		* o joystick move-se com força constante 
		* para a posição x = 520 e y = 520.
		*
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/	
		bool controle(int, int);

		/** Converte a coordenada 0 <= nCoord <= FEEDBACK_WINDOW_WIDTH
		*   para um valor de entre -DI_FFNOMINALMAX to +DI_FFNOMINALMAX.
		*	- DI_FFNOMINALMAX = 10000
		*   - FEEDBACK_WINDOW_WIDTH = 200
		* 
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
		int  coordToForce( int nCoord );
		
		/** Função criada para afzer testes com novos efeitos.
		*
		* OBS: Apenas utilizada no modo debuger ou para DEMO.
		* 
		* @author Bruno Oliveira de Alcântara.
		* @return bool
		*/
        bool test();
};
#endif
