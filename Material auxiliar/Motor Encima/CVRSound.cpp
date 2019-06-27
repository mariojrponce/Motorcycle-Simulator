/***********************************************************************
*Nome: CVRSound.h
*Descrição: Cabeçalho da classe responsável pelo carregamento de sons
*Data: 26/09/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRSound.h"

//Inicialização das variáveis estáticas
IDirectMusicPerformance8* CVRSound::DSperformance = NULL;
IDirectMusicLoader8* CVRSound::DSloader      = NULL;

/***********************************************************
*Name: CVRSound()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSound::CVRSound()
{
	SetNULL();
	iNumRepeat = 0;
}

/***********************************************************
*Name: ~CVRSound()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRSound::~CVRSound()
{
	
}

/***********************************************************
*Name: Initialize()
*Description: inicializa o DirectMusic
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSound::Init()
{

	char caminho[MAX_PATH];
	WCHAR wcharstr[MAX_PATH];

	//inicializa a COM
	CoInitialize(NULL);
	
	//cria performance
	if(FAILED(CoCreateInstance (CLSID_DirectMusicPerformance, NULL, CLSCTX_INPROC,
		IID_IDirectMusicPerformance8, (void**)&DSperformance )))
		return false;

	//cria loader
	if(FAILED(CoCreateInstance (CLSID_DirectMusicLoader, NULL, CLSCTX_INPROC,
	IID_IDirectMusicLoader8, (void**)&DSloader)))
		return false;
	
	//inicia o audio
	if(FAILED(DSperformance->InitAudio (NULL, NULL, NULL,DMUS_APATH_DYNAMIC_3D, 64,
					DMUS_AUDIOF_ALL, NULL  )))
		return false;

	//devolve o diretório corrente
	GetCurrentDirectory(MAX_PATH, LPWSTR(caminho));

	//converte char para WCHAR
	MultiByteToWideChar(CP_ACP, 0, caminho, -1, wcharstr, MAX_PATH);
		
	//coloca o arquivo 
	DSloader->SetSearchDirectory(GUID_DirectMusicAllTypes, LPWSTR(caminho), FALSE);   

	return true;
}

/***********************************************************
*Name: LoadSound()
*Description: carrega um som
*Params: char*
*Return: bool
************************************************************/
bool CVRSound::LoadSound(char* arquivo)
{ 
	WCHAR sound[MAX_PATH];

    //converte char para WCHAR
    MultiByteToWideChar(CP_ACP, 0, arquivo, -1, sound, MAX_PATH);

    //carrega o arquivo a ser tocado
	if(FAILED(DSloader->LoadObjectFromFile(CLSID_DirectMusicSegment,IID_IDirectMusicSegment8,
						sound, (void**)&DSsegment )))
		    return false;

    //converte o segmento para tipo WAV
    DSsegment->Download( DSperformance ); 

	return true;
}

/***********************************************************
*Name: InitInterface
*Description: inicia as interfaces de audio
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSound::InitInterface()
{
	// Cria o audiopath 3D 
	if (FAILED(DSperformance->CreateStandardAudioPath(DMUS_APATH_DYNAMIC_3D,64, TRUE, &DSaudiopath)))
	   return false;		

	// Obtem o buffer de som3D a partir do 3D audiopath
	if (FAILED(DSaudiopath->GetObjectInPath(DMUS_PCHANNEL_ALL, DMUS_PATH_BUFFER, 0,
										    GUID_NULL, 0, IID_IDirectSound3DBuffer8,(void**) &DSbuffer)))
       return false;
	DSbufferparam.dwSize = sizeof(DS3DBUFFER);
    DSbuffer->GetAllParameters(&DSbufferparam);
	DSbufferparam.dwMode = DS3DMODE_NORMAL;
	DSbuffer->SetAllParameters(&DSbufferparam,DS3D_IMMEDIATE);
	
	return true;
}

/***********************************************************
*Name: PlaySound()
*Description: executa o som
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSound::PlaySound()
{
		//Configura o numero de repetições
		if(iNumRepeat < 0)
		{
			DSsegment->SetRepeats(DMUS_SEG_REPEAT_INFINITE);
		}
		else
		{
			DSsegment->SetRepeats(iNumRepeat);			
		}

		//dá play no segmento
		DSsegment->Download(DSaudiopath);
		DSperformance->PlaySegmentEx(DSsegment, NULL, NULL, DMUS_SEGF_SECONDARY, 0, NULL, NULL, DSaudiopath);

	    return true;
}

/***********************************************************
*Name: StopSound()
*Description: para o som
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSound::StopSound()
{
	DSperformance->StopEx(DSsegment, 0, 0);
	return true;
}

/***********************************************************
*Name: GetIsPlaying()
*Description: retorna se o som está tocando ou não
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRSound::GetIsPlaying()
{
	return DSperformance->IsPlaying(DSsegment,NULL) == S_OK;
}

/***********************************************************
*Name: SetRepeat()
*Description: configura quantas vezes o som será repetido
essa função deve ser chamada antes do PlaySound() -1 repete
infinitas vezes
*Params: int
*Return: bool
************************************************************/
bool CVRSound::SetRepeat(int pNum)
{
	iNumRepeat = pNum;

	if(iNumRepeat < 0)
	{
		DSsegment->SetRepeats(DMUS_SEG_REPEAT_INFINITE);
		return true;
	}
	else
	{
		DSsegment->SetRepeats(iNumRepeat);			
		return true;
	}

	return false;
}

/***********************************************************
*Name: MuteSound()
*Description: dependendo do parametro o som para de tocar
*Params: bool
*Return: void
************************************************************/
void CVRSound::MuteSound(bool mute)
{
	if(mute)

		DSaudiopath->SetVolume(-10000,0);
	else
		DSaudiopath->SetVolume(0,0);
}

/***********************************************************
*Name: SetMaxMin()
*Description: seta a distancia maxima e mínima para um som 3D
*Params: float, float
*Return: bool
************************************************************/
bool CVRSound::SetMaxMin(float maximo, float minimo)
{
	if(((DSbuffer->SetMinDistance(minimo,DS3D_IMMEDIATE) == S_OK))&&(DSbuffer->SetMaxDistance(maximo,DS3D_IMMEDIATE)== S_OK))
		  return true;
    else
		  return false;	

}

/***********************************************************
*Name: GetSound()
*Description: retorna a posicao do som no espaço
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRVector CVRSound::GetPosition()
{
	CVRVector vetPos;
	D3DVECTOR d3dVector;
 	DSbuffer->GetPosition(&d3dVector);
	vetPos.x = d3dVector.x;
	vetPos.y = d3dVector.y;
	vetPos.z = -d3dVector.z;
  	
  	return vetPos;
}

/***********************************************************
*Name: GetX()
*Description: retorna a posicao X do xom
*Params: Nenhum
*Return: float
************************************************************/
float CVRSound::GetX()
{
	D3DVECTOR d3dVector;
    DSbuffer->GetPosition(&d3dVector);
    return d3dVector.x;
}

/***********************************************************
*Name: GetX()
*Description: retorna a posicao Y do xom
*Params: Nenhum
*Return: float
************************************************************/
float CVRSound::GetY()
{
	D3DVECTOR d3dVector;
    DSbuffer->GetPosition(&d3dVector);
    return d3dVector.y;
}

/***********************************************************
*Name: GetX()
*Description: retorna a posicao Z do xom
*Params: Nenhum
*Return: float
************************************************************/
float CVRSound::GetZ()
{
	D3DVECTOR d3dVector;
    DSbuffer->GetPosition(&d3dVector);
    d3dVector.z = -d3dVector.z;
    return d3dVector.z;
}

/***********************************************************
*Name: GetMin()
*Description: retorna a distancia minima do som
*Params: Nenhum
*Return: float
************************************************************/
float CVRSound::GetMin()
{
	float ret = 0.0f; 
    DSbuffer->GetMinDistance(&ret);
    return ret;
}

/***********************************************************
*Name: GetMin()
*Description: retorna a distancia maxima do som
*Params: Nenhum
*Return: float
************************************************************/
float CVRSound::GetMax()
{
	float ret = 0.0f;
	DSbuffer->GetMaxDistance(&ret);
	return ret;
}

/***********************************************************
*Name: SetVolume
*Description: configura o volume do som (-9600 até 0)
*Params: long
*Return: void
************************************************************/
void CVRSound::SetVolume(long vol)
{
	//coloca o volume e a duração do volume 
    DSaudiopath->SetVolume(vol,0); 			
}

/***********************************************************
*Name: SetPosition()
*Description: configura a posicao do som no espaço
*Params: float, float, float
*Return: Nenhum
************************************************************/
void CVRSound::SetPosition(float x,float y,float z)
{
	//configura a posição do som
    DSbuffer->SetPosition( x, y, -z, DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetX()
*Description: configura a posicao X do som no espaço
*Params: float
*Return: void
************************************************************/
void CVRSound::SetX(float x)
{
	DSbuffer->SetPosition(x,NULL,NULL,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetY()
*Description: configura a posicao Y do som no espaço
*Params: float
*Return: void
************************************************************/
void CVRSound::SetY(float y)
{
	DSbuffer->SetPosition(NULL,y,NULL,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetZ()
*Description: configura a posicao Z do som no espaço
*Params: float
*Return: void
************************************************************/
void CVRSound::SetZ(float z)
{
	DSbuffer->SetPosition(NULL,NULL,-z,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetVelocity()
*Description: configura a velocidade do som nas coordenadas
x,y,z
*Params: float, float, float
*Return: void
************************************************************/
void CVRSound::SetVelocity(float x, float y, float z)
{
	DSbuffer->SetVelocity(x,y,z,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetVelocityAxe_x()
*Description: configura a posicao X do som no espaço
*Params: float
*Return: void
************************************************************/
void CVRSound::SetVelocityAxe_x(float x)
{
	DSbuffer->SetVelocity(x,NULL,NULL,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetVelocityAxe_y()
*Description: configura a posicao Y do som no espaço
*Params: float
*Return: void
************************************************************/
void CVRSound::SetVelocityAxe_y(float y)
{
	DSbuffer->SetVelocity(NULL,y,NULL,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetVelocityAxe_z()
*Description: configura a posicao Z do som no espaço
*Params: float
*Return: void
************************************************************/
void CVRSound::SetVelocityAxe_z(float z)
{
	DSbuffer->SetVelocity(NULL,NULL,z,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetConeAngle_Inside()
*Description: seta o angulo interno do cone do som 3D
*Params: DWORD
*Return: void
************************************************************/
void CVRSound::SetConeAngle_Inside(DWORD insideAngle)
{
	DSbuffer->SetConeAngles(insideAngle,NULL,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: SetConeAngle_Outside()
*Description: seta o angulo externo do cone do som 3D
*Params: DWORD
*Return: void
************************************************************/
void CVRSound::SetConeAngle_Outside(DWORD outsideAngle)
{
	DSbuffer->SetConeAngles(NULL,outsideAngle,DS3D_IMMEDIATE);
}

/***********************************************************
*Name: GetConeAngle_Inside()
*Description: retorna o angulo interno do cone do som 3D
*Params: void
*Return: DWord
************************************************************/
DWORD CVRSound::GetConeAngle_Inside()
{
	DWORD inside, outside;

	DSbuffer->GetConeAngles(&inside,&outside);
	coneAngleInside = inside;

	return coneAngleInside;
}

/***********************************************************
*Name: GetConeAngle_Outside()
*Description: seta o angulo externo do cone do som 3D
*Params: void
*Return: DWORD
************************************************************/
DWORD CVRSound::GetConeAngle_Outside()
{
	DWORD inside, outside;

	DSbuffer->GetConeAngles(&inside,&outside);
	coneAngleOutside = outside;

	return coneAngleOutside;
}

/***********************************************************
*Name: setNull()
*Description: inicializa as interfaces do DirectSound
*Params: void
*Return: void
************************************************************/
void CVRSound::SetNULL()
{	
	DSbuffer = NULL;
	DSsegment = NULL;
	DSaudiopath = NULL;
}

/***********************************************************
*Name: GetBuffer()
*Description: retorna as interfaces do directSound
*Params: void
*Return: IDirectSound3DBuffer8*
************************************************************/
IDirectSound3DBuffer8* CVRSound::GetBuffer()
{
	return DSbuffer;
}

/***********************************************************
*Name: GetBuffer()
*Description: retorna as interfaces do directMusic
*Params: void
*Return: IDirectSound3DBuffer8*
************************************************************/
IDirectMusicSegment8* CVRSound::GetSegment()
{
	return DSsegment;
}


/***********************************************************
*Name: GetBuffer()
*Description: retorna as interfaces do IDirectMusicAudioPath do DirectMusic
*Params: void
*Return: IDirectMusicAudioPath*
************************************************************/
IDirectMusicAudioPath* CVRSound::GetAudiopath()
{
	return DSaudiopath;
}

/***********************************************************
*Name: GetBuffer()
*Description: retorna a estrutura DS3DBUFFER do DirectMusic
*Params: void
*Return: DS3DBUFFER
************************************************************/
DS3DBUFFER CVRSound::GetBufferparam()
{
	return DSbufferparam;
}

/***********************************************************
*Name: Release()
*Description: Libera recursos
*Params: void
*Return: void
************************************************************/
void CVRSound::Release()
{
	GetSegment()->Release();
	GetBuffer()->Release();
	GetAudiopath()->Release();
}