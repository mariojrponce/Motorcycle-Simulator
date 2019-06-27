/***********************************************************************
*Nome: CVRWindow.cpp
*Descrição: Classe que implementa os métodos para criaçao e configuração da Janela
*Data: 17/07/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#undef UNICODE
#include "CVRWindow.h"


HDC CVRWindow::hdc;
HGLRC CVRWindow::hrc;
unsigned int CVRWindow::uiWindowDepth = 0;
long CVRWindow::lWindowWidth = 0;
long CVRWindow::lWindowHeight = 0;
float CVRWindow::mouseX = 0;
float CVRWindow::mouseY = 0;


/***********************************************************
*Name: MainWindowProc
*Description: CALLBACK que gerencia os eventos passados a janela
*Params: HWND, UINT, WPARAM, LPARAM
*Return: LRESULT
************************************************************/
LRESULT CALLBACK CVRWindow::MainWindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
		case WM_MOUSEMOVE:
		{
			mouseX = ((float)LOWORD(lParam));
			mouseY = ((float)HIWORD(lParam));
			break;
		}
		case WM_CREATE:
		{
			hdc = GetDC(hwnd);
			SetupPixelFormat(hdc);
			hrc = wglCreateContext(hdc);
			wglMakeCurrent(hdc, hrc);
			break;
		}
		case WM_DESTROY:
		case WM_QUIT:
		case WM_CLOSE:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_SIZE:
		{
			int width=0, height=0;
			width = LOWORD (lParam);
			height = HIWORD(lParam);
			if (height == 0)
			{
				height = 1;
			}
			glViewport(0, 0, width, height);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45.0f, width/height,1.0f, 50000.0f);
			glMatrixMode(GL_MODELVIEW);
			glLoadIdentity();
			break;
		}
		case WM_KEYDOWN:
		{
			int fwKeys;
			LPARAM keyData;
			fwKeys = (int) wParam;
			keyData = lParam;
			break;
		}
	}
	return DefWindowProc(hwnd,uMsg,wParam, lParam);
}


/***********************************************************
*Name: CVRWindow()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
CVRWindow::CVRWindow()
{
	bFullScreen = false;
	uiWindowDepth = 32;
	lWindowWidth = 800;
	lWindowHeight = 600;
	hInstance = GetModuleHandle(NULL);
	strcpy(cTitle,"EnCIMA - Default Application");
	r=0.0f;
	g=0.0f;
	b=0.0f;
	xPos = 0;
	yPos = 0;
}

/***********************************************************
*Name: ~CVRWindow()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/ 
CVRWindow::~CVRWindow()
{
	
}

/***********************************************************
*Name: SetFullScreen()
*Description: configura o modo fullscreen
*Params: bool
*Return: Nenhum
************************************************************/
void CVRWindow::SetFullScreen(bool pbFullScreen)
{
	bFullScreen = pbFullScreen;

	if (bFullScreen)
	{
		xPos = 0;
		yPos = 0;
	}
}

/***********************************************************
*Name: SetResolution
*Description: configura a resolução da janela
*Params: long, long, unsigned int
*Return: Nenhum
************************************************************/
void CVRWindow::SetResolution(long pWidth, long pHeight, unsigned int pDepth)
{
	uiWindowDepth = pDepth;
	lWindowWidth = pWidth;
	lWindowHeight = pHeight;
}

/***********************************************************
*Name: SetBackground
*Description: configura a cor de fundo da janela
*Params: float,float,float
*Return: Nenhum
************************************************************/
void CVRWindow::SetBackground(float R, float G, float B)
{
	r = R;
	g = G;
	b = B;
	glClearColor(r,g,b,0.0);
}

/***********************************************************
*Name: SetBackground
*Description: configura a cor de fundo da janela
*Params: int,int,int
*Return: Nenhum
************************************************************/
void CVRWindow::SetBackground(int R, int G, int B)
{
	r = (float)R/255;
	g = (float)G/255;
	b = (float)B/255;
	glClearColor(r,g,b,0.0);
}

/***********************************************************
*Name: Show()
*Description: exibe a janela
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRWindow::Show()
{
	WNDCLASSEX	windowClass;//Window class
	DWORD		dwExStyle;//Window extended style
	DWORD		dwStyle;//Window style
	RECT		windowRect;//Rect used to store the window dimensions

	/*Init window rect values*/
	windowRect.left = (long) 0;
	windowRect.right = lWindowWidth;
	windowRect.top = (long) 0;
	windowRect.bottom = lWindowHeight;

	/*Fill out the window class structure*/
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = MainWindowProc;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = hInstance;
	windowClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);//Default icon
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);//Default arrow
	windowClass.hbrBackground = NULL;//Don´t need background
	windowClass.lpszMenuName = NULL;//No Menu
	windowClass.lpszClassName = "DefaultApp";//Window class name
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);//Windows logo small

	//Register the window class
	if (!RegisterClassEx(&windowClass))
	{
		return;
	}

	/*Testing the fullScreen flag*/
	if (bFullScreen)
	{
		DEVMODE dmScreenSettings;//Device mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));//Inits the device
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);//configure the size
		dmScreenSettings.dmPelsWidth = lWindowWidth;//Screen width
		dmScreenSettings.dmPelsHeight = lWindowHeight;//Screen height
		dmScreenSettings.dmBitsPerPel = uiWindowDepth;//bits per pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;//Config the pixels type
		
		/*Test if the screen change was sucessful*/
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			//Setting display mode failed, switch to windowed
			MessageBox(NULL, "Configuração de vídeo não disponível",NULL, MB_OK);//Show the error message
			bFullScreen = false;//Change resolution back
		}
	}

	//Verify if we are still in fullscreen mode
	if (bFullScreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(FALSE);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_CAPTION |WS_SYSMENU;
	}

	/*****Adjust window to true requested size******/
	AdjustWindowRectEx(&windowRect,dwStyle, FALSE, dwExStyle);


	/******Class registered, so now we will create our window*****/
	hwnd = CreateWindowEx(NULL, 
						"DefaultApp",
						cTitle,
						dwStyle | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
						xPos, yPos,
						windowRect.right - windowRect.left,
						windowRect.bottom - windowRect.top,
						NULL,
						NULL,
						hInstance,
						NULL);

	/******Show the window*****/
	ShowWindow(hwnd,SW_SHOW);
}


/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRWindow::Release()
{
	if (bFullScreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor(TRUE);
	}
	wglMakeCurrent(hdc, NULL);
	wglDeleteContext(hrc);
}


/***********************************************************
*Name: SetTitle
*Description: Configura o titulo da janela
*Params: char*
*Return: Nenhum
************************************************************/
void CVRWindow::SetTitle(char* pTitle)
{
	strcpy(cTitle,pTitle);
}

/***********************************************************
*Name: SetPosition
*Description: Configura a posicao da janela
*Params: int, int
*Return: Nenhum
************************************************************/
void CVRWindow::SetPosition(int x, int y)
{
	xPos = x;
	yPos=y;
	
	if (bFullScreen)
	{
		xPos = 0;
		yPos = 0;
	}
}


/***********************************************************
*Name: SetPixelFormat
*Description: Configura o formato do pixels
*Params: HDC
*Return: Nenhum
************************************************************/
void CVRWindow::SetupPixelFormat(HDC hDC)
{
	int pixelFormat = 0;

	PIXELFORMATDESCRIPTOR pfd = 
	{
		sizeof(PIXELFORMATDESCRIPTOR),								//Size
		1,															//Version
		PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,	//OpenGL window, render to window, double-buffering
		PFD_TYPE_RGBA,												//Color type
		uiWindowDepth,												//Color depth
		0, 0, 0, 0, 0, 0,											//Color bits(ignored)
		0,															//No alpha buffer
		0,															//Alpha bits (ignored)
		0,															//No accumulation buffer
		0, 0, 0, 0,													//Accum bits (ignored)												//depth buffer
		16,															//Depth buffer
		0,															//No stencil buffer
		0,															//No auxliary buffer
		PFD_MAIN_PLANE,												//Main layer
		0,															//Reserved
		0, 0, 0,};													//no layer, visible, damage masks

	pixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, pixelFormat, &pfd);
}

/***********************************************************
*Name: GetHdc()
*Description: retorna o hdc
*Params: Nenhum
*Return: HDC
************************************************************/
HDC CVRWindow::GetHdc()
{
	return hdc;
}
