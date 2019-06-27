/***********************************************************************
*Nome: CVRSTDInput
*Descrição: Implementação da classe responsável pela gerenciamento dos dispo-
sitivos padrao
*Data: 24/08/07
*Local: LNCC
************************************************************************/

//Bibliotecas
#include "CVRSTDInput.h"
#include "CVRManager.h"


/***********************************************************
*Name: CVRTimer()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSTDInput::CVRSTDInput()
{
	pManager = NULL;
	p_DInput = NULL;
	p_DevKeyboard = NULL;
	p_DevMouse = NULL;
	ZeroMemory(KeyboardState,sizeof(KeyboardState));
	ZeroMemory(LastKeyboardState,sizeof(LastKeyboardState));	
	ZeroMemory(&MouseState,sizeof(MouseState));
	ZeroMemory(&LastMouseState,sizeof(LastMouseState));
}

/***********************************************************
*Name: ~CVRTimer()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSTDInput::~CVRSTDInput()
{

}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: void
*Return: Nenhum
************************************************************/
void CVRSTDInput::Release()
{
	//Libera o Teclado
	if(p_DevKeyboard)
	{ 
		p_DevKeyboard->Unacquire();
		p_DevKeyboard->Release();
		p_DevKeyboard = NULL;
	}

	//Libera o mouse
	if(p_DevMouse)
	{ 
		p_DevMouse->Unacquire();
		p_DevMouse->Release();
		p_DevMouse = NULL;
	}

	//Libera o DirectInput
	if(p_DInput)
	{   
		p_DInput->Release();
		p_DInput = NULL;
	} 	

	//Configura o ponteiro do manager para nulo
	if (this->pManager)
	{
		pManager = NULL;
	}
}

/***********************************************************
*Name: InitKeyboard()
*Description: inicia os recursos do teclado
*Params: void
*Return: Nenhum
************************************************************/
void CVRSTDInput::InitKeyboard()
{
	if(p_DInput)
	{
		if(FAILED(p_DInput->CreateDevice(GUID_SysKeyboard,&p_DevKeyboard,NULL)))
		{
			LOG->WriteToLog("Erro! ","Teclado nao inicializado");
			return;
		}
		
		if(FAILED(p_DevKeyboard->SetDataFormat(&c_dfDIKeyboard))) 
		{
			LOG->WriteToLog("Erro! ","Teclado nao inicializado");
			return;
		}

		p_DevKeyboard->Acquire();
	}
}

/***********************************************************
*Name: InitMouse()
*Description: inicia os recursos do mouse
*Params: void
*Return: Nenhum
************************************************************/
void CVRSTDInput::InitMouse()
{
	if(p_DInput)
	{
		if(FAILED(p_DInput->CreateDevice(GUID_SysMouse,&p_DevMouse,NULL)))
		{
			LOG->WriteToLog("Erro! ","Mouse nao inicializado");
			return;
		}
		
		if(FAILED(p_DevMouse->SetDataFormat(&c_dfDIMouse))) 
		{
			LOG->WriteToLog("Erro! ","Mouse nao inicializado");
			return;
		}

		p_DevMouse->Acquire();

		MousePos.x = (float)pManager->cMainWindow.lWindowWidth/2;
		MousePos.y = (float)pManager->cMainWindow.lWindowHeight/2;
		
	}
}

/***********************************************************
*Name: Init()
*Description: inicia os recursos de input
*Params: void
*Return: Nenhum
************************************************************/
bool CVRSTDInput::Init()
{
	if(FAILED(DirectInput8Create((HINSTANCE)pManager->cMainWindow.hInstance,DIRECTINPUT_VERSION,IID_IDirectInput8,(void**)&p_DInput, NULL)))
	{
		LOG->WriteToLog("Erro! ","DirectInput não inicializado");
		return false;
	}

	InitKeyboard();
	
	InitMouse();

	return true;
}

/***********************************************************
*Name: GetMousePosition()
*Description: retorna a posicao do mouse
*Params: void
*Return: CVRVector
************************************************************/
CVRVector CVRSTDInput::GetMousePosition()
{
	return MousePos;
}

/***********************************************************
*Name: KeyDown()
*Description: retorna se a tecla está pressionada
*Params: unsigned char
*Return: bool
************************************************************/
bool CVRSTDInput::KeyDown(unsigned char cbyKeyCode)
{
	return (KeyboardState[cbyKeyCode] & 0x80) ? true : false;
}

/***********************************************************
*Name: KeyPressed()
*Description: retorna se a tecla foi pressionada agora
*Params: unsigned char
*Return: bool
************************************************************/ 
bool CVRSTDInput::KeyPressed(unsigned char cbyKeyCode)
{
	return (!(LastKeyboardState[cbyKeyCode] & 0x80) && (KeyboardState[cbyKeyCode] & 0x80)) ? true : false;
}


/***********************************************************
*Name: KeyReleased()
*Description: retorna se a tecla foi solta
*Params: unsigned char
*Return: bool
************************************************************/ 
bool CVRSTDInput::KeyReleased(unsigned char cbyKeyCode)
{
	return ((LastKeyboardState[cbyKeyCode] & 0x80) && !(KeyboardState[cbyKeyCode] & 0x80)) ? true : false;
}

/***********************************************************
*Name: MouseBtnDown
*Description: retorna se o botao do mouse foi pressionado
*Params: unsigned char
*Return: bool
************************************************************/ 
bool CVRSTDInput::MouBtnDown(unsigned char cbyBtnCode)
{
	return MouseState.rgbButtons[cbyBtnCode] & 0x80 ? true : false;
}

/***********************************************************
*Name: MouseBtnPressed
*Description: retorna se o botao do mouse foi pressionado neste instante
*Params: unsigned char
*Return: bool
************************************************************/ 
bool CVRSTDInput::MouBtnPressed(unsigned char cbyBtnCode)
{
	return (!(LastMouseState.rgbButtons[cbyBtnCode] & 0x80) && (MouseState.rgbButtons[cbyBtnCode] & 0x80)) ? true : false;
}

/***********************************************************
*Name: MouseBtnReleased
*Description: retorna se o botao do mouse foi solto
*Params: unsigned char
*Return: bool
************************************************************/ 
bool CVRSTDInput::MouBtnReleased(unsigned char cbyBtnCode)
{
	return ((LastMouseState.rgbButtons[cbyBtnCode] & 0x80) && !(MouseState.rgbButtons[cbyBtnCode] & 0x80)) ? true : false;
}

/***********************************************************
*Name: SetWindowsMousePos
*Description: configura a posicao do mouse na janela
*Params: CVRVector
*Return: Nenhum
************************************************************/
void CVRSTDInput::SetWindowsMousePos(CVRVector &cNewPos)
{
	MousePos = cNewPos;
	SetCursorPos((int)MousePos.x, (int)MousePos.y);	
}

/***********************************************************
*Name: UpdateKeyboard()
*Description: atualiza as informações do teclado
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSTDInput::UpdateKeyboard()
{
	HRESULT hr;

	memcpy(LastKeyboardState,KeyboardState,sizeof(LastKeyboardState));	

	ZeroMemory(KeyboardState,sizeof(KeyboardState));
	
	hr = p_DevKeyboard->GetDeviceState(sizeof(KeyboardState),(LPVOID)&KeyboardState);
	
	if(FAILED(hr))
	{ 
		hr = p_DevKeyboard->Acquire();
		
		while(hr == DIERR_INPUTLOST)
		{
			hr = p_DevKeyboard->Acquire();
		}

		if(FAILED(hr))
		{
			return;
		}
	}
}

/***********************************************************
*Name: UpdateMouse()
*Description: atualiza as informações do mouse
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSTDInput::UpdateMouse()
{
	HRESULT hr;

	memcpy(&LastMouseState,&MouseState,sizeof(LastMouseState));	

	ZeroMemory(&MouseState,sizeof(MouseState));
	
	hr = p_DevMouse->GetDeviceState(sizeof(MouseState),(LPVOID)&MouseState);
	
	if(FAILED(hr))
	{ 
		hr = p_DevMouse->Acquire();
		
		while(hr == DIERR_INPUTLOST)
		{
			hr = p_DevMouse->Acquire();
		}

		if(FAILED(hr))
		{
			return;
		}
	}
	this->MousePos.x = this->pManager->cMainWindow.mouseX;
	this->MousePos.y = this->pManager->cMainWindow.mouseY;
}

/***********************************************************
*Name: Update()
*Description: atualiza as informações dos dispositivos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRSTDInput::Update()
{
	if(p_DevKeyboard)
	{
		UpdateKeyboard();
	}
	if(p_DevMouse)
	{
		UpdateMouse();
	}
}

