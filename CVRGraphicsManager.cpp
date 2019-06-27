/***********************************************************************
*Nome: CVRGraphicsManager.cpp
*Descrição: Classe que implementa os métodos para o gerenciamento de recursos gráficos
*Data: 25/07/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRGraphicsManager.h"
#include "CVRManager.h"
#include "cmath"

/***********************************************************
*Name: CVRGraphicsManager()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRGraphicsManager::CVRGraphicsManager()
{
	pManager = NULL;
	r = 255;
	g = 255;
	b = 255;
}

/***********************************************************
*Name: ~CVRGrapchisManager()
*Description: desstrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRGraphicsManager::~CVRGraphicsManager()
{
	
}


/***********************************************************
*Name: Release()
*Description: libera recursos
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRGraphicsManager::Release()
{
	//Limpa o vetor de imagens alocadas
	for (int iIndex=(int)vImages.size()-1; iIndex>=0; iIndex--)
	{
		if (vImages[iIndex])
		{
			vImages[iIndex]->Release();
			delete vImages[iIndex];
		}
	}
	vImages.clear();

	//Limpa o vetor de texturas alocadas
	if (vBImages.size())
	{
		vBImages.clear();
	}
}


/***********************************************************
*Name: SaveScreenShot()
*Description: Tira um screen shot da aplicação e salva em disco
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRGraphicsManager::SaveScreenShot(char* fileName, int x, int y, int width, int height)
{
	FILE *filePtr = NULL;
	BITMAPFILEHEADER bitmapFileHeader;
	BITMAPINFOHEADER bitmapInfoHeader;
	unsigned char tempRGB;
	unsigned char* bmpImageReader = (unsigned char*) malloc((width * height * 3));
	
	memset(bmpImageReader,0,(width * height * 3));

	glReadPixels(x,y,width-1,height-1,GL_RGB,GL_UNSIGNED_BYTE, bmpImageReader);

	//Abrindo o arquivo para leitura
	filePtr = fopen(fileName,"wb");

	if (!filePtr)
		return;

	bitmapFileHeader.bfSize = sizeof (BITMAPFILEHEADER);
	bitmapFileHeader.bfType  = 0x4D42;
	bitmapFileHeader.bfReserved1 =0;
	bitmapFileHeader.bfReserved2 =0;
	bitmapFileHeader.bfOffBits = sizeof (BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

	bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitmapInfoHeader.biPlanes = 1;
	bitmapInfoHeader.biWidth = width;
	bitmapInfoHeader.biHeight = height;
	bitmapInfoHeader.biBitCount = 24;
	bitmapInfoHeader.biCompression = BI_RGB;
	bitmapInfoHeader.biXPelsPerMeter = 0;
	bitmapInfoHeader.biYPelsPerMeter = 0;
	bitmapInfoHeader.biClrImportant = 0;
	bitmapInfoHeader.biClrUsed = 0;
	bitmapInfoHeader.biSizeImage = width*abs(height)*3;

	for (int i=0; i<(int)bitmapInfoHeader.biSizeImage; i+=3)//faz a troca de BGR para RGB
	{
		tempRGB = bmpImageReader[i];
		bmpImageReader[i]=bmpImageReader[i+2];
		bmpImageReader[i+2]=tempRGB;
	}

	//Write to file
	fwrite(&bitmapFileHeader,1,sizeof(BITMAPFILEHEADER),filePtr);
	fwrite(&bitmapInfoHeader,1,sizeof(BITMAPINFOHEADER),filePtr);
	fwrite(bmpImageReader,1,bitmapInfoHeader.biSizeImage,filePtr);

	//close file
	fclose(filePtr);
	free(bmpImageReader);
	bmpImageReader=NULL;
}

/***********************************************************
*Name: LoadImage()
*Description: carrega uma imagem com alpha
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRImage* CVRGraphicsManager::LoadImage(char* fileName, char* alphaName)
{
	//Verifica se a imagem pretendida já nao se encontra na memoria
	for (int iIndex=0; iIndex<(int)vImages.size(); iIndex++)
	{
		if (strcmp(fileName,vImages[iIndex]->GetImageName())==0)
		{
			vImages[iIndex]->iReferences++;
			return vImages[iIndex];
		}
	}
	
	//Se nao existir na memoria, carrega uma nova
	CVRImage* pNewImage = new CVRImage();

	if (pNewImage)
	{
		pNewImage->LoadImage(fileName,alphaName);
		
		if (pNewImage->GetImageData())
		{
			vImages.push_back(pNewImage);
			return pNewImage;
		}
	}

	//Imagem não encontrada
	delete pNewImage;
	return NULL;
}

/***********************************************************
*Name: LoadImage()
*Description: carrega uma imagem
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRImage* CVRGraphicsManager::LoadImage(char* fileName, bool transparency)
{
	//Verifica se a imagem pretendida já nao se encontra na memoria
	for (int iIndex=0; iIndex<(int)vImages.size(); iIndex++)
	{
		if (strcmp(fileName,vImages[iIndex]->GetImageName())==0)
		{
			vImages[iIndex]->iReferences++;
			return vImages[iIndex];
		}
	}

	//Se nao existir na memoria, carrega uma nova
	CVRImage* pNewImage = new CVRImage();

	if (pNewImage)
	{
		pNewImage->SetColorKey(r,g,b);
		pNewImage->LoadImage(fileName,transparency);
		
		if (pNewImage->GetImageData())
		{
			vImages.push_back(pNewImage);
			return pNewImage;
		}
	}

	//Imagem não encontrada
	delete pNewImage;
	return NULL;
}

/***********************************************************
*Name: DeleteImage()
*Description: Deleta uma imagem
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRGraphicsManager::DeleteImage(CVRImage** pImage)
{
	if (pImage && *pImage)
	{
		for (int iIndex=(int)vImages.size()-1; iIndex >= 0; iIndex--)
		{
			if (vImages[iIndex] == *pImage)
			{
				if (vImages[iIndex]->iReferences > 1)
				{
					vImages[iIndex]->iReferences--;
				}
				else
				{
					for (int jIndex = (int)vBImages.size()-1; jIndex >= 0; jIndex--)
					{
						if (strcmp(vImages[iIndex]->GetImageName(),vBImages[jIndex].name)==0)
						{
							vBImages.erase(vBImages.begin()+jIndex);
							break;
						}
					}
					(*pImage)->Release();
					delete *pImage;
					vImages.erase(vImages.begin()+iIndex);
				}
				*pImage = NULL;
				return;
			}
		}
	}
}

/***********************************************************
*Name: SetColorKey()
*Description: Configura o color key da imagem
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRGraphicsManager::SetColorKey(short pr, short pg, short pb)
{
	r = pr;
	g = pg;
	b = pb;
}

/***********************************************************
*Name: GetImage()
*Description: retorna a referencia para uma imagem
*Params: char*
*Return: CVRImage
************************************************************/
CVRImage* CVRGraphicsManager::GetImage(char* imageName)
{
	for (int iIndex=0; iIndex<(int)vImages.size(); iIndex++)
	{
		if (strcmp(imageName,vImages[iIndex]->GetImageName())==0)
		{
			return vImages[iIndex];
		}
	}
	return NULL;
}

/***********************************************************
*Name: BindImage()
*Description: verifica se já existe a assinatura da imagem
*Params: Nenhum
*Return: Nenhum
************************************************************/
unsigned int CVRGraphicsManager::GetBindImage(char* imageName)
{
	for (int iIndex=0; iIndex<(int)vBImages.size(); iIndex++)
	{
		if (strcmp(imageName,vBImages[iIndex].name)==0)
		{
			vBImages[iIndex].references++;
			return vBImages[iIndex].code;
		}
	}

	return 0 ;
}

/***********************************************************
*Name: SetBindImage()
*Description: assina uma imagem e devolve o código
*Params: Nenhum
*Return: Nenhum
************************************************************/
void CVRGraphicsManager::AddBindImage(char* imageName, unsigned int code)
{
	sBindImage newImage;
	newImage.code = 0;
	newImage.references = 1;

	newImage.code = code;
	strcpy(newImage.name,imageName);

	vBImages.push_back(newImage);
}

/***********************************************************
*Name: ReleaseBindImage()
*Description: libera recursos de textura
*Params: Nenhum
*Return: Nenhum
************************************************************/
void   CVRGraphicsManager::ReleaseBindImage(unsigned int code)
{	
	for (int iIndex=0; iIndex < (int)vBImages.size(); iIndex++)
	{
		if (vBImages[iIndex].code == code)
		{
			if (vBImages[iIndex].references > 1)
			{
				vBImages[iIndex].references--;
			}
			else
			{
				glDeleteTextures(1,&vBImages[iIndex].code);
				vBImages[iIndex].references = 0;
				vBImages.erase(vBImages.begin()+iIndex);
				return;
			}
		}
	}
}

