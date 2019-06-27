/**
* @author Victor de Almeida Thomaz
* @change Bruno Oliveira de Alcântara.
* @changelog pequenas alterações para adaptação ao joystick de force feedback
* @version 1.0   
* Arquivo: CVRJoystick.cpp  
* Descrição: imlpementação das funções da classe responsável pelo 
* 			reconhecimanto dos joysticks .
*
* Data de Criação: 24/01/2008                                                                     
* Data da última modificação: 15/07/2008  
* Local: LNCC                                                                                      
*/

#include "CVRJoystick.h"

//Singleton object
CVRJoystick * CVRJoystick::ptrSingleton = NULL;

/***********************************************************
*Name: CVRJoystick()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRJoystick::CVRJoystick()
{
   //Inicialização dos objetos
   diObject = NULL;
   joystick = NULL;
   ZeroMemory (&JoyData, sizeof(DIDEVICEOBJECTDATA));
   ptrSingleton = this;
}
CVRJoystick::~CVRJoystick()
{
	Release();
}

/***********************************************************
*Name: Init()
*Description: Inicializa o DirectInput
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::Init()
{
	//Cria o objeto do DirectInput
   if (FAILED (DirectInput8Create(GetModuleHandle(NULL), 
	                               DIRECTINPUT_VERSION,
								   IID_IDirectInput8,
								   (void**) &diObject, NULL)))
   {
      return (false);
   }

   //Procura o primeiro joystick disponível
   if (FAILED (CVRJoystick::GetSingleton()->GetInput()->EnumDevices (
	           DI8DEVCLASS_GAMECTRL, CVRJoystick::enumJoysticksCallback, &joystick, DIEDFL_ATTACHEDONLY)) )
      return (false);
   

   //Certifica-se que o joystick foi encontrado
    if (joystick == NULL) 
        return (false);
   

   //Configura o formato de dados do joystick
   if (FAILED (joystick->SetDataFormat (&c_dfDIJoystick2)))
      return (false);
   

   //Configura o nível do joystick
   if (FAILED(joystick->SetCooperativeLevel(NULL, DISCL_EXCLUSIVE | DISCL_FOREGROUND)))
      //return (false);


   if( FAILED(joystick->EnumObjects( CVRJoystick::enumObjectsCallback, &joystick, DIDFT_ALL ) ) )
      return (false);


   //Obtem o joystick
   HRESULT hRet = joystick->Poll ();
   if (FAILED (hRet))
   {
      hRet = joystick->Acquire ();

      while (hRet == DIERR_INPUTLOST)
      {
         hRet = joystick->Acquire ();
      }
   }

   return (true);
}

/***********************************************************
*Name: Init()
*Description: Inicializa o DirectInput
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::Init(HWND hDlg)
{
	DIPROPDWORD dipdw;

   /*
	  Registra com o subsistema do DirectInput e obtem um ponteiro
	  IDirectInput para uma interface que podemos utilizar.
	*/
	if (FAILED (DirectInput8Create(GetModuleHandle(NULL), 
	                               DIRECTINPUT_VERSION,
								   IID_IDirectInput8,
								   (void**) &diObject, NULL)))
   {
      return (false);
   }

   //Procura o primeiro joystick disponível
   if (FAILED ( diObject->EnumDevices ( DI8DEVCLASS_GAMECTRL, enumJoysticksCallback,
							&joystick, DIEDFL_ATTACHEDONLY | DIEDFL_FORCEFEEDBACK )) )
      return (false);
   

   //Certifica-se que o joystick foi encontrado
    if (joystick == NULL) 
        return (false);
   
   // Definir o formato de dados para "joystick simples " - um formato de dados predefinidos. 
   if (FAILED (joystick->SetDataFormat (&c_dfDIJoystick)))
      return (false);
   

   /*
	  Definir o nível cooperativo para deixar o DInput saber como este dispositivo deve
      interagir com o sistema, e com outras aplicações de DInput.
      Exclusivo acesso é necessário quando se quer usar o force feedback.
	*/
   if (FAILED(joystick->SetCooperativeLevel( hDlg, DISCL_EXCLUSIVE | DISCL_FOREGROUND )))
		//return (false);

	/*
	  Uma vez que vamos estar jogando efeitos de force feedback, devemos desativar o
      Auto-centramento Spring que vem com o Jopystick por padrão.
	*/
    dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
    dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
    dipdw.diph.dwObj        = 0;
    dipdw.diph.dwHow        = DIPH_DEVICE;
    dipdw.dwData            = FALSE;

    if(FAILED(joystick->SetProperty(DIPROP_AUTOCENTER, &dipdw.diph)))
	      // return false;

	// Enumera e conta os eixos do joystick 
    if( FAILED(joystick->EnumObjects( enumObjectsCallback, (VOID*)&enumObjectParamTwo, 
										DIDFT_ALL | DIDFT_AXIS ) ) )
      return (false);

/*	//Esta amostra suporta apenas um ou dois eixos no joysticks
    if( enumObjectParamTwo > 2 )
        enumObjectParamTwo = 2;
*/
   //Obtem o joystick
   HRESULT hRet = joystick->Poll ();
   if (FAILED (hRet))
   {
      hRet = joystick->Acquire ();

      while (hRet == DIERR_INPUTLOST)
      {
         hRet = joystick->Acquire ();
      }
   }

   return (true);
}


/***********************************************************
*Name: Update()
*Description: Inicializa o DirectInput
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::Update()
{
   //Monitora o joystick
   if (FAILED (joystick->Poll()) )
   {
      //Obtem o joystick
      HRESULT hRet = joystick->Acquire();

      if ((FAILED (hRet)) && (hRet == DIERR_INPUTLOST))
      {
         joystick->Acquire();
      }
      else
      {
         return (false);
      }
   }

   //Retorna o dispositivo de dados
   if (FAILED (joystick->GetDeviceState(sizeof (DIJOYSTATE2),&JoyData)) )
   {
      return (false);
   }
   
   return (true);

}

/***********************************************************
*Name: Release()
*Description: Libera os recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRJoystick::Release()
{
   if (NULL != diObject)
   {
      diObject->Release();
      diObject = NULL;
   }

   if (NULL != joystick)
   {
      joystick->Unacquire();
      joystick->Release();
      joystick = NULL;
   }

   ptrSingleton = NULL;
}

/***********************************************************
*Name: GetSingleton()
*Description: Retorna um ponteiro para o ptrSingleton
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRJoystick* CVRJoystick::GetSingleton(void)
{
	assert (ptrSingleton);
	return ptrSingleton;
}

/***********************************************************
*Name: GetInput()
*Description: Retorna um objeto para DirectInput
*Params: Nenhum
*Return: Nenhum
************************************************************/
LPDIRECTINPUT8 CVRJoystick::GetInput(void)
{
   return (diObject);
}


/***********************************************************
*Name: IsButtonDonw()
*Description: Retorna um booleano para o botao verificado
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsButtonDown(int iButton)
{
   //verifica se o botao esta pressionado
   if (JoyData.rgbButtons [iButton] & (1 << 7))
   {
      return (true);
   }
   else
   {
      return (false);
   }
}

/***********************************************************
*Name: IsButtonUp()
*Description: Retorna um booleano para o botao verificado
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsButtonUp(int iButton)
{
   //verifica se o botao nao esta pressionado
   if (JoyData.rgbButtons [iButton] & (1<<7))
   {
      return (false);
   }
   else
   {
      return (true);
   }
}


/***********************************************************
*Name: GetXAxis()
*Description: Retorna o valor do eixo em X
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
int CVRJoystick::GetXAxis()
{
   return JoyData.lX;
}

/***********************************************************
*Name: GetYAxis()
*Description: Retorna o valor do eixo em Y
*Params: Nenhum
*Return: Nenhum
************************************************************/
int CVRJoystick::GetYAxis()
{
   return JoyData.lY;
}


/***********************************************************
*Name: GetYAxis()
*Description: Retorna o valor do eixo em Z
*Params: Nenhum
*Return: Nenhum
************************************************************/
int CVRJoystick::GetZAxis()
{
   return JoyData.lZ;
}

/***********************************************************
*Name: GetXRot()
*Description: Retorna o valor de rotação em X
*Params: Nenhum
*Return: Nenhum
************************************************************/
int CVRJoystick::GetXRot()
{
	return JoyData.lRx;
}

/***********************************************************
*Name: GetYRot()
*Description: Retorna o valor de rotação em Y
*Params: Nenhum
*Return: Nenhum
************************************************************/
int CVRJoystick::GetYRot()
{
	return JoyData.lRy;
}

/***********************************************************
*Name: GetZRot()
*Description: Retorna o valor de rotação em Z
*Params: Nenhum
*Return: Nenhum
************************************************************/
int CVRJoystick::GetZRot()
{
	return JoyData.lRz;
}

/***********************************************************
*Name: IsXAxisFront()
*Description: Retorna um booleano se o eixo X está deslocado a
frente
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsXAxisFront()
{
    if (GetXAxis() == JOYMAX )
	   return (true);
	else
       return (false);
}

/***********************************************************
*Name: IsXAxisBack()
*Description: Retorna um booleano se o eixo X está deslocado 
*para tras
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsXAxisBack()
{
    if (GetXAxis() == JOYMIN )
	   return (true);
	else
       return (false);
}

/***********************************************************
*Name: IsYAxisUp()
*Description: Retorna um booleano se o eixo Y está deslocado 
*para cima
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsYAxisUp()
{
    if (GetYAxis() == JOYMIN )
	   return (true);
	else
       return (false);
}

/***********************************************************
*Name: HasJoystick()
*Description: Verifica se existe joystick ou nao 
*para baixo
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::HasJoystick()
{
    if (this->joystick==NULL)
		return false;
	return true;
}

/***********************************************************
*Name: IsYAxisDown()
*Description: Retorna um booleano se o eixo Y está deslocado 
*para baixo
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsYAxisDown()
{
    if (GetYAxis() == JOYMAX )
	   return (true);
	else
       return (false);
}

/***********************************************************
*Name: IsZAxisFront()
*Description: Retorna um booleano se o eixo Z está deslocado 
*para frente
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsZAxisFront()
{
    if (GetZAxis() == JOYMAX )
	   return (true);
	else
       return (false);
}

/***********************************************************
*Name: IsZAxisBack()
*Description: Retorna um booleano se o eixo Z está deslocado 
*para trás
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsZAxisBack()
{
    if (GetZAxis() == JOYMIN )
	   return (true);
	else
       return (false);
}

/***********************************************************
*Name: IsZRotUp()
*Description: Retorna um booleano se rotação Z está deslocada 
*para cima
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsZRotUp()
{
    if (GetZRot() == JOYMIN )
	   return (true);
	else
       return (false);
}

/***********************************************************
*Name: IsZRotDown()
*Description: Retorna um booleano se rotação Z está deslocada 
*para baixo
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRJoystick::IsZRotDown()
{
    if (GetZRot() == JOYMAX )
	   return (true);
	else
       return (false);
}

/**********************************************************************************
* Nome: enumJoysticksCallback  
* Objetivo: Descobrir os joysticks conectados no computador.
***********************************************************************************/
//BOOL CALLBACK CVRJoystick::enumJoysticksCallback(const DIDEVICEINSTANCE* instance, VOID* context)
//{
//    LPDIRECTINPUTDEVICE8 pDevice;
//    HRESULT              hr = NULL;
//
//    //Obtem uma interface com o dispositivo de force feedback enumerado.
//	hr = CVRJoystick::GetSingleton()->GetInput()->CreateDevice( instance->guidInstance, &pDevice, NULL );
//	
//    /*
//	  Se a função CreateDevice falhar, então nós não podemos usar 
//	  este dispositivo por alguma razão.
//	*/
//    if(FAILED(hr)) 
//        return DIENUM_CONTINUE;
//
//    /*
//	 Nós criamos uma interface IDirectInputDevice8 com êxito. Então pare 
//	 a função por aqui retornando flag DIENUM_STOP.
//	*/
//    GetSingleton()->setJoystick(pDevice);
//
//    return DIENUM_STOP;
//
//}//fim BOOL CALLBACK Joystick::enumJoysticksCallback(const DIDEVICEINSTANCE* instance, VOID* context)
BOOL CALLBACK CVRJoystick::enumJoysticksCallback(const DIDEVICEINSTANCE* instance, VOID* context)
{
  
	 LPDIRECTINPUTDEVICE8 * ptrJoystick = (LPDIRECTINPUTDEVICE8 *) context;

   /* Create joystick device */
   if (FAILED(CVRJoystick::GetSingleton()->GetInput()->CreateDevice (
       instance->guidInstance, ptrJoystick, NULL)) )
   {
      return DIENUM_CONTINUE;
   }
   else
   {
      return DIENUM_STOP;
   }

}//fim BOOL CALLBACK Joystick::enumJoysticksCallback(const DIDEVICEINSTANCE* instance, VOID* context)

/**********************************************************************************
* Nome: enumObjectsCallback  
* Objetivo: Descobrir os objetos(botões, etc...) disponíveis no joystick.
***********************************************************************************/
BOOL CALLBACK CVRJoystick::enumObjectsCallback(const DIDEVICEOBJECTINSTANCE* pdidoi, VOID* pContext)
{
    LPDIRECTINPUTDEVICE8 * ptrJoystick = (LPDIRECTINPUTDEVICE8 *) pContext;
   
    DWORD* pdwNumForceFeedbackAxis = (DWORD*) pContext;
	
    if( (pdidoi->dwFlags & DIDOI_FFACTUATOR) != 0 )
        (*pdwNumForceFeedbackAxis)++;

	// If this object is an axis type object, attempt to set its range
	if( pdidoi->dwType & DIDFT_AXIS )
    {
	    // Create a DIPROPRANGE structure
        DIPROPRANGE diprg;
		DIPROPDWORD dipdw;
		HRESULT hr = NULL;

		// Each structure requires that a DIPROPHEADER structure be initialized
		diprg.diph.dwSize = sizeof(DIPROPRANGE);
		diprg.diph.dwHeaderSize = sizeof(DIPROPHEADER);
		diprg.diph.dwHow = DIPH_BYID;
		diprg.diph.dwObj = pdidoi->dwType; // Specify the enumerated axis
		  
		// The minimum and maximum portions of the range are being set here
		diprg.lMin = JOYMIN;
		diprg.lMax = JOYMAX;
	      
		// Seta o range dos eixos 
		hr = CVRJoystick::GetSingleton()->joystick->SetProperty( DIPROP_RANGE, &diprg.diph );
		 
		if FAILED ( hr )
			return DIENUM_STOP;

		//***Set Saturation*** 
		dipdw.diph.dwSize       = sizeof( dipdw );
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);//sizeof( dipdw.diph ); 
		dipdw.diph.dwObj        = pdidoi->dwType;
		dipdw.diph.dwHow        = DIPH_BYID;
		dipdw.dwData            = JOYSAT;

		hr = CVRJoystick::GetSingleton()->joystick->SetProperty( DIPROP_SATURATION, &dipdw.diph );
		// Check to see if setting the Saturation property was successful
		if FAILED ( hr )
			return DIENUM_STOP;  

		//***Set DeadZone***
		dipdw.diph.dwSize       = sizeof( dipdw ); 
		dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);//sizeof( dipdw.diph ); 
		dipdw.diph.dwObj        = pdidoi->dwType;
		dipdw.diph.dwHow        = DIPH_BYID;
		dipdw.dwData            = JOYDEAD;

		hr = CVRJoystick::GetSingleton()->joystick->SetProperty( DIPROP_DEADZONE, &dipdw.diph );
			// Check to see if setting the DeadZone property was successful
			if FAILED ( hr )
				return DIENUM_STOP;
    }     

    return DIENUM_CONTINUE;

} //fim BOOL CALLBACK Joystick::enumObjectsCallback(const DIDEVICEOBJECTINSTANCE* instance, VOID* context)
