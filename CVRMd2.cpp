/***********************************************************************
*Nome: CVRMd2.h
*Descrição:  Classe que implementa o modelo MD2
*Data: 25/01/07
*Local: LNCC
************************************************************************/

#include "CVRMd2.h"
#include "CVRLog.h"
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

/***********************************************************
*Name: CVRMd2()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRMd2::CVRMd2()
{
	frames = NULL;
	triangles = NULL;
	texCoordinates = NULL;
	verts = NULL;
	fSpeed = 1.0f;
	uiStartFrame = 0;
	uiEndFrame = 180;
	uiCurrentFrame = 0;
	imageId = 0;
	uiMSPerFrame = 0;			
	fLastInterp = 0.0f;
	bRepeat = true;
}

/***********************************************************
*Name: CVRMd2()
*Description: construtor da classe
*Params: char*
*Return: Nenhum
************************************************************/
CVRMd2::CVRMd2(char * fileName)
{
	frames = NULL;
	triangles = NULL;
	texCoordinates = NULL;
	verts = NULL;
	fSpeed = 1.0f;
	uiStartFrame = 0;
	uiEndFrame = 180;
	uiCurrentFrame = 0;
	imageId = 0;
	uiMSPerFrame = 0;			
	fLastInterp = 0.0f;
	bRepeat = true;
	Load(fileName);
}

/***********************************************************
*Name: ~CVRMd2()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRMd2::~CVRMd2()
{
	
}

/***********************************************************
*Name: Release()
*Description: método que desaloca recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRMd2::Release()
{
	if(frames)
	{
		delete[] frames;
		frames = NULL;
	}
	if(texCoordinates)
	{
		delete[] texCoordinates;
		texCoordinates = NULL;
	}
	if(triangles)
	{
		delete[] triangles;
		triangles = NULL;
	}
	if(verts)
	{
		delete[] verts;
		verts = NULL;
	}

	if (pGraphicsManager)
	{
		pGraphicsManager->ReleaseBindImage(imageId);
	}
}

/***********************************************************
*Name: Load()
*Description: método carrega os dados do modelo
*Params: char*
*Return: Nenhum
************************************************************/
bool CVRMd2::Load(char *fileName)
{
	unsigned char *ucpBuffer = NULL;
	unsigned char *ucpPtr = NULL;
	unsigned char *ucpTmpPtr = NULL;

	int iFileSize = 0;

	FILE *file = NULL;

	file = fopen(fileName,"rb");

	if(!file)
	{
		LOG->WriteToLog("CVRMd2: Arquivo não encontrado ",fileName);
		return false;
	}

	//Descobre o tamanho do arquivo
	int startFile = ftell(file);
	fseek(file,0,SEEK_END);
	int endFile = ftell(file);
	fseek(file, 0, SEEK_SET);
	iFileSize = endFile - startFile;

	//Aloca memoria para o arquivo inteiro
	ucpBuffer = new unsigned char[iFileSize];
	ucpPtr = ucpBuffer;

	if (!ucpBuffer)
	{
		LOG->WriteToLog("CVRMd2: Impossivel alocar memória ",fileName);
		return false;
	}

	//Carrega todo o arquivo no buffer
	if(fread(ucpBuffer,1,iFileSize,file) != (unsigned)iFileSize)
	{
		LOG->WriteToLog("CVRMd2: Erro ao ler dados do modelo ",fileName);
		delete[] ucpBuffer;
		return false;
	}

	//Arquivo todo carregado na memoria, nao precisa mais dele
	fclose(file);

	//Le o cabeçalho do modelo
	memcpy(&header, ucpPtr, sizeof(SMD2HEADER));

	//Testa os valores do ID e da versão para ver se o formato do arquivo é correto
	if (header.iMd2Id!=844121161 || header.iVersion!=8)
	{
		LOG->WriteToLog("CVRMd2: Modelo MD2 invalido ",fileName);
		delete[] ucpBuffer;
		return false;
	}

	//Posiciona o ponteiro temporario no inicio dos dados dos frames
	ucpTmpPtr = ucpPtr;
	ucpTmpPtr += header.iOffsetFrames;

	//Aloca memoria para os frames(keyframes)
	frames = new SMD2FRAME[header.iNumFrames];

	//Le os frames
	for (int iIndex=0; iIndex<header.iNumFrames; iIndex++)
	{
		float fScale[3];
		float fTrans[3];

		//Aloca memoria para os vertices
		frames[iIndex].vertexList = new SMD2VERTEX[header.iNumVertices];
		
		//Expande os vertices
		memcpy(fScale, ucpTmpPtr, 12);
		memcpy(fTrans, ucpTmpPtr + 12, 12);
		memcpy(frames[iIndex].cFrameName, ucpTmpPtr + 24, 16);

		//Desloca o ponteiro
		ucpTmpPtr += 40;

		//Faz o Swap entre as coordenadas Y e Z
		for(int jIndex = 0; jIndex < header.iNumVertices; jIndex++)
		{
			frames[iIndex].vertexList[jIndex].fVertex[0] = ucpTmpPtr[0] * fScale[0] + fTrans[0];
			frames[iIndex].vertexList[jIndex].fVertex[1] = ucpTmpPtr[2] * fScale[2] + fTrans[2];
			frames[iIndex].vertexList[jIndex].fVertex[2] = ucpTmpPtr[1] * fScale[1] + fTrans[1];
			frames[iIndex].vertexList[jIndex].ucReserved = ucpTmpPtr[3];
			ucpTmpPtr += 4;
			
			// Calcula o Boundings do modelo
			CVRVector* vertex = new CVRVector();
			vertex->SetX(frames[iIndex].vertexList[jIndex].fVertex[0]);
			vertex->SetY(frames[iIndex].vertexList[jIndex].fVertex[1]);
			vertex->SetZ(frames[iIndex].vertexList[jIndex].fVertex[2]);
			CalculateBoundings(vertex,1);
		}
	}

	//Leitura dos triangulos
	ucpTmpPtr = ucpPtr;
	ucpTmpPtr += header.iOffsetTriangles;
	triangles = new SMD2TRIANGLE[header.iNumTriangles];
	memcpy(triangles, ucpTmpPtr, 12 * header.iNumTriangles);

	//Le as coordenadas de textura UV
	ucpTmpPtr = ucpPtr;
	ucpTmpPtr += header.iOffsetTexCoords;
	texCoordinates = new SMD2TEXCOORD[header.iNumTexCoods];

	short * sTexCoords = new short[header.iNumTexCoods*2];
	memcpy(sTexCoords, ucpTmpPtr, 4 * header.iNumTexCoods);

	for(int iIndex = 0; iIndex < header.iNumTexCoods; iIndex++)
	{
		texCoordinates[iIndex].texCoord[0] = (float)sTexCoords[2*iIndex] / header.iWidth;
		texCoordinates[iIndex].texCoord[1] = (float)sTexCoords[2*iIndex+1] / header.iHeight;
	}
	//Deleta o vetor de coordenadas
	delete [] sTexCoords;
	sTexCoords = NULL;

	//Deleta o buffer temporário
	delete [] ucpBuffer;
	
	return true;
}

/***********************************************************
*Name: Render()
*Description: renderiza o modelo
*Params: none
*Return: Nenhum
************************************************************/
void CVRMd2::Render()
{										
	//Verifica se está visível
	if (!bVisible)
	{
		return;
	}

	//Se a animaçao acabou renderiza somente o ultimo frame
	if (this->AnimationEnded())
	{
		RenderFrame(uiEndFrame);
		return;
	}

	//habilita a textura
	glEnable(GL_TEXTURE_2D);

	//Assina a textura
	glBindTexture(GL_TEXTURE_2D,imageId);

	//Posiciona o objeto
	glPushMatrix();
		glTranslatef(vPos.x,vPos.y, vPos.z);
		glRotatef(vAngle.x,1.0f,0.0f,0.0f);
		glRotatef(vAngle.y,0.0f,1.0f,0.0f);
		glRotatef(vAngle.z,0.0f,0.0f,1.0f);
		glScalef(vScale.x,vScale.y,vScale.z);

	//Renderiza o modelo
	glBegin(GL_TRIANGLES);
	for(int x = 0; x < header.iNumTriangles; x++)
	{
		glTexCoord2fv(texCoordinates[triangles[x].texture[0]].texCoord);
		glVertex3fv(verts[triangles[x].vertex[0]].fVertex);
		
		glTexCoord2fv(texCoordinates[triangles[x].texture[1]].texCoord);
		glVertex3fv(verts[triangles[x].vertex[1]].fVertex);
		
		glTexCoord2fv(texCoordinates[triangles[x].texture[2]].texCoord);
		glVertex3fv(verts[triangles[x].vertex[2]].fVertex);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
}

/***********************************************************
*Name: RenderFrame()
*Description: renderiza um frame do modelo
*Params: int
*Return: Nenhum
************************************************************/
void CVRMd2::RenderFrame(int iIndex)
{
	//Verifica se está visível
	if (!bVisible)
	{
		return;
	}

	//habilita a textura
	glEnable(GL_TEXTURE_2D);

	//Assina a textura
	glBindTexture(GL_TEXTURE_2D,imageId);
	
	//Posiciona o objeto
	glPushMatrix();
		glTranslatef(vPos.x,vPos.y, vPos.z);
		glRotatef(vAngle.x,1.0f,0.0f,0.0f);
		glRotatef(vAngle.y,0.0f,1.0f,0.0f);
		glRotatef(vAngle.z,0.0f,0.0f,1.0f);
		glScalef(vScale.x,vScale.y,vScale.z);

	//Renderiza o frame do modelo
	glBegin(GL_TRIANGLES);
	for(int x = 0; x < header.iNumTriangles; x++)
	{
		glTexCoord2fv(texCoordinates[triangles[x].texture[0]].texCoord);
		glVertex3fv(frames[iIndex].vertexList[triangles[x].vertex[0]].fVertex);
		
		glTexCoord2fv(texCoordinates[triangles[x].texture[1]].texCoord);
		glVertex3fv(frames[iIndex].vertexList[triangles[x].vertex[1]].fVertex);
		
		glTexCoord2fv(texCoordinates[triangles[x].texture[2]].texCoord);
		glVertex3fv(frames[iIndex].vertexList[triangles[x].vertex[2]].fVertex);
	}
	glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,0);
}

/***********************************************************
*Name: SetAnimSpeed()
*Description: configura a velocidade da animação
*Params: float
*Return: Nenhum
************************************************************/
void CVRMd2::SetAnimSpeed(float pSpeed)
{
	if (pSpeed <=0 )
	{
		fSpeed = 1.0f;
		return;
	}
	fSpeed = pSpeed;
}

/***********************************************************
*Name: SetAnimSpeed()
*Description: configura a velocidade da animação
*Params: float
*Return: Nenhum
************************************************************/
void CVRMd2::SetAnimFrames(unsigned int iStart, unsigned int iEnd)
{
	uiStartFrame = iStart;
	uiEndFrame = iEnd;
	uiCurrentFrame = iStart;
}

/***********************************************************
*Name: LoadTexture()
*Description: carrega uma textura para o modelo
*Params: char*
*Return: Nenhum
************************************************************/
bool CVRMd2::LoadTexture(char *fileName)
{
	if (!pGraphicsManager)
	{
		return false;
	}

	imageId = pGraphicsManager->GetBindImage(fileName);

	if (imageId)
	{
		return true;
	}

	CVRImage* image = pGraphicsManager->LoadImage(fileName,true);

	if (!image || !image->GetImageData())
	{
		return false;
	}

	glGenTextures(1,&imageId);
	glBindTexture(GL_TEXTURE_2D,imageId);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);	
	if (image->bAlpha)
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, image->GetImageWidth(), image->GetImageHeight(),
		GL_RGBA, GL_UNSIGNED_BYTE, image->GetImageData());
	}
	else
	{
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, image->GetImageWidth(), image->GetImageHeight(),
		GL_RGB, GL_UNSIGNED_BYTE, image->GetImageData());
	}
	pGraphicsManager->AddBindImage(image->GetImageName(),imageId);

	pGraphicsManager->DeleteImage(&image);
	image = NULL;

	return true;
}

/***********************************************************
*Name: Init()
*Description: inicializa recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
bool CVRMd2::Init()
{
	CVRObject3D::Init();
	return true;
}

/***********************************************************
*Name: AnimationEnded()
*Description: verifica se a animação atual já acabou
*Params: Nenhum
*Return: bool
************************************************************/
bool CVRMd2::AnimationEnded()
{
	return (bRepeat)? false : uiCurrentFrame >= uiEndFrame;
}

/***********************************************************
*Name: SetRepeat()
*Description: configura a repetição da animação
*Params: bool
*Return: Nenhum
************************************************************/
void CVRMd2::SetRepeat(bool pRepeat)
{
	bRepeat = pRepeat;
}

/***********************************************************
*Name: Update()
*Description: atualiza o md2
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRMd2::Update()
{
	//Chama o update do pai
	CVRObject3D::Update();

	//Alocando memoria para os vertices
	if(!verts)
	{
		verts = new SMD2VERTEX[header.iNumVertices];
	}

	//Calcula o tempo em ms por frame
	uiMSPerFrame = (unsigned int)(1000 / this->fSpeed);

	//Atualiza o timer
	timer.Update();

	//Calcula o proximo frame e o valor da interpolação
	unsigned int uiTime = timer.GetElapsedTime();
	float fInterpValue = ((float) uiTime / uiMSPerFrame) + fLastInterp;
	fLastInterp = fInterpValue;

	//Se o valor da interpolação for maior que 1, então passa para o proximo frame
	while(fInterpValue > 1.0f)
	{
		uiCurrentFrame ++;
		if(uiCurrentFrame >= uiEndFrame)
		{
			if (bRepeat)
			{
				LOG->WriteToLog("Entrou: ","repeat");
				uiCurrentFrame = uiStartFrame;
			}
			else
			{
				LOG->WriteToLog("Entrou: ","nao repeat");
				uiCurrentFrame = uiEndFrame;
			}
		}
		fInterpValue -= 1.0f;
		fLastInterp = 0.0f;
	}

	//Aloca memoria para o frame atual e para o proximo frame
	SMD2FRAME* pCurFrame = &frames[uiCurrentFrame];
	SMD2FRAME* pNextFrame = &frames[uiCurrentFrame+1];

	if(uiCurrentFrame == uiEndFrame-1)
	{
		pNextFrame = &frames[uiStartFrame];
	}

	//Interpola os vértices
	for(int x = 0; x < header.iNumVertices; x++)
	{
		verts[x].fVertex[0] = pCurFrame->vertexList[x].fVertex[0] + (pNextFrame->vertexList[x].fVertex[0] - pCurFrame->vertexList[x].fVertex[0]) * fInterpValue;
		verts[x].fVertex[1] = pCurFrame->vertexList[x].fVertex[1] + (pNextFrame->vertexList[x].fVertex[1] - pCurFrame->vertexList[x].fVertex[1]) * fInterpValue;
		verts[x].fVertex[2] = pCurFrame->vertexList[x].fVertex[2] + (pNextFrame->vertexList[x].fVertex[2] - pCurFrame->vertexList[x].fVertex[2]) * fInterpValue;
	}
}