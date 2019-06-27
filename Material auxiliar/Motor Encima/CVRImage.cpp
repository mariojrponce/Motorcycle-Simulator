/***********************************************************************
*Nome: CVRImage.cpp
*Descrição: Implementação da classe responsável pelo carregamento de imagens
*Data: 18/01/07
*Local: LNCC
************************************************************************/
//Bibliotecas
#include "CVRImage.h"
#include "CVRLog.h"
#include <cmath>


/***********************************************************
*Name: CVRImage()
*Description: construtor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRImage::CVRImage()
{
	imageData = NULL;
	height = 0;
	width = 0;
	colorKey.R = 255;
	colorKey.G = 255;
	colorKey.B = 255;
	iReferences = 1;
	bAlpha = false;
}

/***********************************************************
*Name: CVRImage()
*Description: destrutor da classe
*Params: Nenhum
*Return: Nenhum
************************************************************/
CVRImage::~CVRImage()
{
	
}

/***********************************************************
*Name: getImage()
*Description: retorna os dados da imagem
*Params: Nenhum
*Return: Nenhum
************************************************************/
unsigned char* CVRImage::GetImageData()
{
	return imageData;
}

/***********************************************************
*Name: Release()
*Description: retorna os dados da imagem
*Params: Nenhum
*Return: bool
************************************************************/
void CVRImage::Release()
{
	if (imageData)
	{
		delete[] imageData;
		imageData = NULL;
	}
}

/***********************************************************
*Name: getWitdh()
*Description: retorna a largura da imagem
*Params: Nenhum
*Return: int
************************************************************/
int CVRImage::GetImageWidth()
{
	return width;
}

/***********************************************************
*Name: getHeight()
*Description: retorna a largura da imagem
*Params: Nenhum
*Return: int
************************************************************/
int CVRImage::GetImageHeight()
{
	return height;
}

/***********************************************************
*Name: getImageName()
*Description: retorna o nome da imagem
*Params: Nenhum
*Return: char *
************************************************************/
char* CVRImage::GetImageName()
{
	return imageName;
}

/***********************************************************
*Name: LoadBitmap()
*Description: Carrega um arquivo bmp
*Params: None
*Return: bool
************************************************************/
bool CVRImage::LoadBmpFile(char *fileName)
{
	unsigned char tempRGB;//Variavel auxilizar responsavel pela troca BGR - > RGB
	unsigned char *bitmapImage=NULL;//Irá armazenar os dados da imagem

	FILE *fileImage = NULL;//Ponteiro para o arquivo
	
	BITMAPFILEHEADER bitmapFileHeader;//Armazena os dados do arquivo
	BITMAPINFOHEADER bitmapInfoHeader;//Armazena os dados da imagem

	fileImage = fopen(fileName,"rb");//Abra o arquivo para a leitura

	//Testa se o arquivo foi aberto
	if (!fileImage)
	{
		LOG->WriteToLog("CVRImagem: Arquivo não encontrado",fileName);
		return false;
	}

	//Le o cabeçalho da imagem
	fread(&bitmapFileHeader,sizeof(BITMAPFILEHEADER),1,fileImage);

	//Testa o identificador universal do BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		LOG->WriteToLog("CVRImagem: Imagem BMP inválida",fileName);
		fclose(fileImage);
		return false;
	}

	//Le a imagem do arquivo
	fread(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,fileImage); 
	
	//Move o ponteiro para o inicio dos dados da imagem
	fseek(fileImage,bitmapFileHeader.bfOffBits,SEEK_SET);

	//Aloca memoria suficiente para os dados da imagem
	bitmapImage = new unsigned char[bitmapInfoHeader.biSizeImage+1];

	//Testa se a memoria da imagem foi alocada
	if (!bitmapImage)
	{
		LOG->WriteToLog("CVRImagem: Impossivel alocar memória",fileName);
		delete[] bitmapImage;
		fclose(fileImage);
		return false;
	}

	//Le a imagem do arquivo
	fread(bitmapImage,1,bitmapInfoHeader.biSizeImage,fileImage);


	//Testa se os dados da imagem foram lidos
	if (!bitmapImage)
	{
		LOG->WriteToLog("CVRImagem: Erro ao ler dados da imagem",fileName);
		fclose(fileImage);
		delete[] bitmapImage;
		return false;
	}

	//Troca os valores de B e R do formato BGR para RBG
	for (int iIndex=0; iIndex < (int)bitmapInfoHeader.biSizeImage; iIndex += 3)
	{
		tempRGB = bitmapImage[iIndex];
		bitmapImage[iIndex] = bitmapImage[iIndex+2];
		bitmapImage[iIndex+2] = tempRGB;
	}

	//Fecha o arquivo
	fclose(fileImage);

	//Preenche os campos da textura
	imageData = bitmapImage;
	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;
	strcpy(imageName,fileName);
	
	return true;
}


/***********************************************************
*Name: LoadBmpAlphaFile()
*Description: Carrega um arquivo bmp com alpha
*Params: None
*Return: bool
************************************************************/
bool CVRImage::LoadBmpAlphaFile(char *fileName)
{
	unsigned char *bitmapImage = NULL;//Armazena o bitmap
	unsigned char *bitmapAlpha = NULL;//Armazena o bitmap com alpha

	FILE *fileImage = NULL;//Ponteiro para o arquivo
	BITMAPFILEHEADER bitmapFileHeader;//Armazena informações do arquivo
	BITMAPINFOHEADER bitmapInfoHeader;//Armazena as informaçoes da imagem
	unsigned char tempRGB;

	fileImage = fopen(fileName,"rb");//Abre a imagem para a leitura

	//Testa se a imagem foi aberda
	if (!fileImage)
	{
		LOG->WriteToLog("CVRImagem: Arquivo não encontrado",fileName);
		return false;
	}

	//Le o cabeçalho da imagem
	fread(&bitmapFileHeader,sizeof(BITMAPFILEHEADER),1,fileImage);

	//Testa o identificador da imagem BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		LOG->WriteToLog("CVRImagem: Imagem BMP inválida",fileName);
		fclose(fileImage);
		return false;
	}

	//Le as informações do da imagem
	fread(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,fileImage); 
	
	//Move o ponteiro para o inicio dos dados da imagem
	fseek(fileImage,bitmapFileHeader.bfOffBits,SEEK_SET);

	//Aloca memoria suficiente para os dados da imagem
	bitmapImage = new unsigned char[bitmapInfoHeader.biSizeImage+1];

	//Aloca memoria suficente pra os dados da imagem Alpha
	bitmapAlpha = new unsigned char[((bitmapInfoHeader.biSizeImage * 4) / 3)+1];

	//Testa se a memoria foi alocada
	if (!bitmapImage)
	{
		LOG->WriteToLog("CVRImagem: Impossivel alocar memória",fileName);
		delete[] bitmapImage;
		fclose(fileImage);
		return false;
	}

	//Le os dados da imagem do arquivo
	fread(bitmapImage,1,bitmapInfoHeader.biSizeImage,fileImage);


	//Testa se a imagem foi lida
	if (!bitmapImage)
	{
		LOG->WriteToLog("CVRImagem: Erro ao ler dados da imagem",fileName);
		fclose(fileImage);
		delete[] bitmapImage;
		return false;
	}

	//Troca os valores do formato BGR para RGB
	for (int iIndex=0; iIndex < (int)bitmapInfoHeader.biSizeImage; iIndex += 3)
	{
		tempRGB = bitmapImage[iIndex];
		bitmapImage[iIndex] = bitmapImage[iIndex+2];
		bitmapImage[iIndex+2] = tempRGB;
	}

	//Configura os pixels da cor Alpha
	int iIndexAlpha = 0;
	for (int iIndex=0; iIndex < (int)bitmapInfoHeader.biSizeImage; iIndex += 3, iIndexAlpha+=4)
	{
		
		bitmapAlpha[iIndexAlpha] = bitmapImage[iIndex];
		bitmapAlpha[iIndexAlpha + 1] = bitmapImage[iIndex + 1];
		bitmapAlpha[iIndexAlpha + 2] = bitmapImage[iIndex + 2];

		if (bitmapImage[iIndex]     == colorKey.R     &&
			bitmapImage[iIndex + 1] == colorKey.G && bitmapImage[iIndex + 2] == colorKey.B)
		{
			bitmapAlpha[iIndexAlpha+3] = 0;
		}
		else
		{
			bitmapAlpha[iIndexAlpha+3] = 255;
		}
	}

	//Deleta a imagem sem alpha
	delete[] bitmapImage;

	//Close the file
	fclose(fileImage);

	//Preenche os campos da textura
	imageData = bitmapAlpha;
	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;
	strcpy(imageName,fileName);

	return true;
}


/***********************************************************
*Name: LoadPcxFile()
*Description: Carrega um arquivo de imagem do tipo PCX
*Params: None
*Return: bool
************************************************************/
bool CVRImage::LoadPcxFile(char* fileName)
{
	 int idx = 0;                  //Contador
     int c;                        //usado para obter um caractere do arquivo
     int numRepeat;      
     FILE *filePtr;                //Ponteiro para o arquivo
     int width;                    //Largura da imagem
     int height;                   //Altura da imagem
     unsigned char *pixelData;     //Armazena os dados da imagem
     unsigned char *paletteData;   //Armazena os dados da palleta da imagem
	 PCXHEADER pcxHeader;		   //Cabeçalho do arquivo
	 unsigned char *unscaledData;// used to calculate pcx

     //Abre o arquivo
     filePtr = fopen(fileName, "rb");
     if (filePtr == NULL)
	 {
		 LOG->WriteToLog("CVRImagem: Arquivo não encontrado",fileName);
		 return false;
	 }

     //Retira o primeiro caractere do arquivo, deve ser igual a 10
     c = getc(filePtr);
     if (c != 10)
     {
          fclose(filePtr);
          return false;
     }

     //Retira o proximo caractere do arquivo, deve ser igual a 5
     c = getc(filePtr);
     if (c != 5)
     {
          fclose(filePtr);
          return false;
     }

     //Reposiciona o ponteiro no inicio do arquivo
     rewind(filePtr);

     //Le mais quatro caracteres
     fgetc(filePtr);
     fgetc(filePtr);
     fgetc(filePtr);
     fgetc(filePtr);

     //Retira os dados da imagem para X min (canto esquerdo)
     pcxHeader.xMin = fgetc(filePtr);      
     pcxHeader.xMin |= fgetc(filePtr) << 8;

     //Retira os dados da imagem para Y min (canto inferior)
     pcxHeader.yMin = fgetc(filePtr);       
     pcxHeader.yMin |= fgetc(filePtr) << 8; 

     //Retira os dados da imagem para X max (canto direito)
     pcxHeader.xMax = fgetc(filePtr);      
     pcxHeader.xMax |= fgetc(filePtr) << 8; 

     //Retira os dados da imagem para Y max (canto superior)
     pcxHeader.yMax = fgetc(filePtr);       
     pcxHeader.yMax |= fgetc(filePtr) << 8; 

     //Calcula a largura e a altura da imagem com base nos cantos
     width = pcxHeader.xMax - pcxHeader.xMin + 1;
     height = pcxHeader.yMax - pcxHeader.yMin + 1;

     //Aloca memoria para os dados da imagem
     pixelData = new unsigned char[width*height+1];

     //Configura o ponteiro do arquivo para o 128 byte onde os dados da imagem iniciam
     fseek(filePtr, 128, SEEK_SET);
     
     //Decodifica os dados do pixel e armazena
     while (idx < (width*height))
     {
          c = getc(filePtr);
          if (c > 0xbf)
          {
               numRepeat = 0x3f & c;
               c = getc(filePtr);

               for (int i = 0; i < numRepeat; i++)
               {
                    pixelData[idx++] = c;
               }
          }
          else
               pixelData[idx++] = c;

          fflush(stdout);
     }

     //Aloca memoria para a palleta do pcx
     paletteData = new unsigned char[768];

     //A paleta esta localizada nos 769 ultimos bytes do arquivo
     fseek(filePtr, -769, SEEK_END);

     //Verifica o primeiro caractere da paleta, deve ser 12
     c = getc(filePtr);
     if (c != 12)
     {
          fclose(filePtr);
          return false;
     }

     //Le e armazena toda a palleta
     for (int i = 0; i < 768; i++)
     {
          c = getc(filePtr);
          paletteData[i] = c;
     }

     //Fecha o arquivo e armazena os dados
     fclose(filePtr);
     pcxHeader.palette = paletteData;

     //Preenche os campos da textura
	this->width = pcxHeader.xMax - pcxHeader.xMin + 1;;
	this->height = pcxHeader.yMax - pcxHeader.yMin + 1;;
	strcpy(imageName,fileName);
	this->imageData = pixelData;

	//Aloca memoria para os dados nao escalados
    unscaledData = new unsigned char[(this->width*this->height*4)+1];

	//Armazena os dados da palleta
     for (int j = 0; j < this->height; j++) 
     {
          for (int i = 0; i < this->width; i++) 
          {
               unscaledData[4*(j*this->width+i)+0] = (unsigned char)pcxHeader.palette[3*imageData[j*this->width+i]+0];
               unscaledData[4*(j*this->width+i)+1] = (unsigned char)pcxHeader.palette[3*imageData[j*this->width+i]+1];
               unscaledData[4*(j*this->width+i)+2] = (unsigned char)pcxHeader.palette[3*imageData[j*this->width+i]+2];
               unscaledData[4*(j*this->width+i)+3] = (unsigned char)255;
          }
     }

	 int lwidth = this->width;
     int lheight = this->height;

	 int i = 0;
     while (lwidth)
     {
          lwidth /= 2;
          i++;
     }

	long scaledHeight = (long)pow(2.0, i-1);

     i = 0;
     while (lheight)
     {
          lheight /= 2;
          i++;
     }
   long scaledWidth = (long)pow(2.0, i-1);

	if (imageData != NULL)
     {
          delete[] imageData;
          imageData = NULL;
		  pixelData = NULL;
     }

	  //Realoca memoria para os dados da textura
     imageData = new unsigned char[(scaledWidth*scaledHeight*4)+1];
	 strcpy(imageName,fileName);

	 gluScaleImage (GL_RGBA, this->width, this->height, GL_UNSIGNED_BYTE, unscaledData, scaledWidth, scaledHeight, GL_UNSIGNED_BYTE, imageData);
    
	 delete[] paletteData;
	 delete[] unscaledData;

	return true;
}

/***********************************************************
*Name: LoadTGAFile()
*Description: Carrega um arquivo de imagem do tipo TGA
*Params: None
*Return: bool
************************************************************/
bool CVRImage::LoadTGAFile(char* fileName) 
{
	FILE *filePtr;//Ponteiro para o arquivo
	
	unsigned char uCharBad;//Variavel para os caracteres discartaveis

	short int sintBad;//Variavel para os valores short descartaveis

	long imageSize;//Tamanho da imagem TGA

	int colorMode;//valor 4 para RGBA e 3 para RGB

	unsigned char colorSwap;//variavel usada para o Swap de cores

	TGAFILE tgaFile;//Estrutura que guarda os dados da imagem

	//Abre o arquivo TGA
	filePtr = fopen(fileName,"rb");

	//Testa se foi aberto com sucesso
	if (!filePtr)
	{
		LOG->WriteToLog("CVRImagem: Arquivo não encontrado",fileName);
		return false;
	}

	//Le os primeiros dois bytes de dados que serão descartados
	fread(&uCharBad,sizeof(unsigned char),1,filePtr);
	fread(&uCharBad,sizeof(unsigned char),1,filePtr);

	//Le o tipo de imagem
	fread(&tgaFile.imageTypeCode,sizeof(unsigned char),1,filePtr);

	//Verifica o tipo, deve ser o valor 2 ou 3
	if ((tgaFile.imageTypeCode!= 2) && (tgaFile.imageTypeCode!= 3))
	{
		LOG->WriteToLog("CVRImagem: Imagem TGA inválida",fileName);
		fclose(filePtr);
		return false;
	}

	//Le 13 bytes de dados que nao são necessários
	fread(&sintBad,sizeof(short int),1,filePtr);
	fread(&sintBad,sizeof(short int),1,filePtr);
	fread(&uCharBad,sizeof(unsigned char),1,filePtr);
	fread(&sintBad,sizeof(short int),1,filePtr);
	fread(&sintBad,sizeof(short int),1,filePtr);

	//Le as dimensões da imagem
	fread(&tgaFile.imageWidth,sizeof(short int),1,filePtr);
	fread(&tgaFile.imageHeight,sizeof(short int),1,filePtr);

	//Le os bits de profundade da imagem
	fread(&tgaFile.bitCount,sizeof(unsigned char),1,filePtr);

	//Le um byte que será descartado
	fread(&uCharBad,sizeof(unsigned char),1,filePtr);

	//Calcula o formato da imagem
	colorMode = tgaFile.bitCount / 8;
	imageSize = tgaFile.imageWidth * tgaFile.imageHeight * colorMode;

	//Aloca memoria para os dados da imagem
	tgaFile.imageData = new unsigned char[(sizeof(unsigned char*)*imageSize+1)];

	//Le os dados da imagem
	fread(tgaFile.imageData,sizeof(unsigned char),imageSize,filePtr);

	//Faz a troca do formato BGR para RGB
	for (int imageIdx = 0; imageIdx < imageSize; imageIdx += colorMode)
	{
		colorSwap = tgaFile.imageData[imageIdx];
		tgaFile.imageData[imageIdx] = tgaFile.imageData[imageIdx + 2];
		tgaFile.imageData[imageIdx+2] = colorSwap;
	}

	fclose(filePtr);

	this->imageData = tgaFile.imageData;
	this->width = tgaFile.imageWidth;
	this->height = tgaFile.imageHeight;
	strcpy(imageName,fileName);

	return true;
}




/***********************************************************
*Name: LoadImage()
*Description: Carrega uma imagem com canal alpha
*Params: char*, char*
*Return: bool
************************************************************/
bool CVRImage::LoadImage(char* fileName, char* alphaName) 
{
	unsigned char* bitmapImage=NULL;//Irá armazenar os dados da imagem
	unsigned char* alphaImage=NULL;//Irá armazenar os dados do alpha
	unsigned char* bitmapAlpha=NULL;//Irá armazenar os dados do alpha

	//Valor temporário utilizado para a troca de cores
	unsigned char tempRGB;

	FILE* fileImage = NULL;//Ponteiro para o arquivo da imagem
	FILE* fileAlpha = NULL;//Ponteiro para o arquivo do alfa
	
	BITMAPFILEHEADER bitmapFileHeader;//Armazena os dados do arquivo
	BITMAPINFOHEADER bitmapInfoHeader;//Armazena os dados da imagem
	
	BITMAPFILEHEADER alphaFileHeader;//Armazena os dados do arquivo alpha
	BITMAPINFOHEADER alphaInfoHeader;//Armazena os dados da imagem alpha

	fileImage = fopen(fileName,"rb");//Abra o arquivo para a leitura
	fileAlpha = fopen(alphaName,"rb");//Abra o arquivo para a leitura

	//Testa se o arquivo foi aberto
	if (!fileImage)
	{
		LOG->WriteToLog("CVRImagem: Arquivo não encontrado",fileName);
		return false;
	}

	//Testa se o arquivo alpha foi aberto
	if (!fileAlpha)
	{
		LOG->WriteToLog("CVRImagem: Arquivo não encontrado",alphaName);
		return false;
	}

	//Le o cabeçalho da imagem
	fread(&bitmapFileHeader,sizeof(BITMAPFILEHEADER),1,fileImage);
	//Le o cabeçalho do alpha
	fread(&alphaFileHeader,sizeof(BITMAPFILEHEADER),1,fileAlpha);

	//Testa o identificador universal do BMP
	if (bitmapFileHeader.bfType != BITMAP_ID)
	{
		LOG->WriteToLog("CVRImagem: Imagem BMP inválida",fileName);
		fclose(fileImage);
		fclose(fileAlpha);
		return false;
	}

	//Testa o identificador universal do BMP
	if (alphaFileHeader.bfType != BITMAP_ID)
	{
		LOG->WriteToLog("CVRImagem: Imagem BMP inválida ",alphaName);
		fclose(fileImage);
		fclose(fileAlpha);
		return false;
	}

	//Le a imagem do arquivo
	fread(&bitmapInfoHeader,sizeof(BITMAPINFOHEADER),1,fileImage); 
	//Le a imagem do alpha
	fread(&alphaInfoHeader,sizeof(BITMAPINFOHEADER),1,fileAlpha); 
	
	//Move o ponteiro para o inicio dos dados da imagem
	fseek(fileImage,bitmapFileHeader.bfOffBits,SEEK_SET);
	//Move o ponteiro para o inicio dos dados do alpha
	fseek(fileAlpha,alphaFileHeader.bfOffBits,SEEK_SET);

	//Aloca memoria suficiente para os dados da imagem
	bitmapImage = new unsigned char[bitmapInfoHeader.biSizeImage+1];

	//Testa se a memoria da imagem foi alocada
	if (!bitmapImage)
	{
		LOG->WriteToLog("CVRImagem: Impossivel alocar memória ",fileName);
		delete[] bitmapImage;
		fclose(fileImage);
		fclose(fileAlpha);
		return false;
	}

	//Aloca memoria suficiente para os dados da imagem
	alphaImage = new unsigned char[alphaInfoHeader.biSizeImage+1];

	//Testa se a memoria da imagem foi alocada
	if (!alphaImage)
	{
		LOG->WriteToLog("CVRImagem: Impossivel alocar memória ",alphaName);
		delete[] bitmapImage;
		delete[] alphaImage;
		fclose(fileImage);
		fclose(fileAlpha);
		return false;
	}
	//Aloca memoria suficiente para os dados da imagem
	bitmapAlpha = new unsigned char[((bitmapInfoHeader.biSizeImage * 4) / 3)+1];

	//Testa se a memoria da imagem foi alocada
	if (!bitmapAlpha)
	{
		LOG->WriteToLog("CVRImagem: Impossivel alocar memória ","BitmapAlhpa");
		delete[] bitmapImage;
		delete[] alphaImage;
		delete[] bitmapAlpha;
		fclose(fileImage);
		fclose(fileAlpha);
		return false;
	}

	//Le a imagem do arquivo
	fread(bitmapImage,1,bitmapInfoHeader.biSizeImage,fileImage);
	//Le a imagem do alpha
	fread(alphaImage,1,alphaInfoHeader.biSizeImage,fileAlpha);

	//Testa se os dados da imagem foram lidos
	if (!bitmapImage)
	{
		LOG->WriteToLog("CVRImagem: Erro ao ler dados da imagem",fileName);
		delete[] bitmapImage;
		delete[] alphaImage;
		delete[] bitmapAlpha;
		fclose(fileImage);
		fclose(fileAlpha);
		return false;
	}

	//Testa se a memoria da imagem foi alocada
	if (!alphaImage)
	{
		LOG->WriteToLog("CVRImagem: Impossivel alocar memória",alphaName);
		delete[] bitmapImage;
		delete[] alphaImage;
		delete[] bitmapAlpha;
		fclose(fileImage);
		fclose(fileAlpha);
		return false;
	}

	//Troca os valores de B e R do formato BGR para RBG
	for (int iIndex=0; iIndex < (int)bitmapInfoHeader.biSizeImage; iIndex += 3)
	{
		tempRGB = bitmapImage[iIndex];
		bitmapImage[iIndex] = bitmapImage[iIndex+2];
		bitmapImage[iIndex+2] = tempRGB;
	}

	//Aplica o canal alpha
	for (int iIndexAlpha=0, iIndex=0; iIndex < (int)bitmapInfoHeader.biSizeImage; iIndex += 3, iIndexAlpha+=4)
	{
		bitmapAlpha[iIndexAlpha] =   bitmapImage[iIndex];
		bitmapAlpha[iIndexAlpha+1] = bitmapImage[iIndex+1];
		bitmapAlpha[iIndexAlpha+2] = bitmapImage[iIndex+2];
		bitmapAlpha[iIndexAlpha+3] = alphaImage[iIndex];
	}

	//Fecha o arquivo
	fclose(fileImage);
	fclose(fileAlpha);
	delete[] alphaImage;
	delete[] bitmapImage;

	//Preenche os campos da textura
	imageData = bitmapAlpha;
	width = bitmapInfoHeader.biWidth;
	height = bitmapInfoHeader.biHeight;
	strcpy(imageName,fileName);
	
	return true;
}

/***********************************************************
*Name: LoadImage()
*Description: Carrega uma imagem com base no seu tipo
*Params: char*, bool
*Return: bool
************************************************************/
bool CVRImage::LoadImage(char* fileName, bool transparency) 
{
	char *extStr;
	CVRImage image;

	//Posiciona o ponteiro no inicio da extensão do nome
	extStr = strchr(fileName, '.');
	extStr++;

	//Descobre qual a extensão do arquivo e chama o método apropriado
	if ((strcmp(extStr, "BMP") == 0) || (strcmp(extStr, "bmp") == 0))//Imagem bmp
	{
		if (transparency)//bmp com transparencia
		{
			bAlpha = transparency;
			return LoadBmpAlphaFile(fileName);
		}
		else//bmp sem transparencia
		{
			bAlpha = transparency;
			return LoadBmpFile(fileName);
		}
	}
	else if ((strcmp(extStr, "PCX") == 0) || (strcmp(extStr, "pcx") == 0) )//Imagem pcx
	{
		bAlpha = true;
		return LoadPcxFile(fileName);
	}
	else if ((strcmp(extStr, "TGA") == 0) || (strcmp(extStr, "tga") == 0) )//Imagem tga
	{
		bAlpha = transparency;
		return LoadTGAFile(fileName);
	}

	return false;
}

/***********************************************************
*Name: SetColorKey()
*Description: configura o colorkey da imagem
*Params: None
*Return: None
************************************************************/
void CVRImage::SetColorKey(short r, short g, short b)
{
	colorKey.R = r;
	colorKey.G = g;
	colorKey.B = b;
}