# Motorcycle Simulator
Este simulador foi desenvolvido por alunos do curso de Sistemas de Informação, em um projeto de Iniciação Científica da Faculdade Católica do Tocantins.  O objetivo deste jogo é a utilização da tecnologia de Realidade Virtual para o treinamento de motociclistas. Permitido assim que os candidatos ao exame nacional de habilitação a categoria “A” tenham mais experiencias antes de conduzir o veículo nas ruas. 

###Requisitos Motorcycle Simulator
* Microsoft Visual C++ 2010 Express
* Placa de vídeo externa

###Como abrir o projeto?
* Baixe este [repositório](https://github.com/mariojrponce/Motorcycle-Simulator.git).
* Baixe o Microsoft Visual Studio 2010 C++ Express.

- ###Configurando o projeto
	- Abra pelo Visual Studio 2010 C++ Express o projeto **Exemplo 7.sln**.
	
	- Na aba **Solution Explorer** clique com o botão direito do mouse em cima do nome **Exemplo 7**.
	
	- Abrirá uma janela chamada **Exemplo 7 Property Pages**.
	
	- Dentro da lista **Configuration Properties** clique em **VC++ Directories**.
	
	- Verifique os diretórios **Include Directories**, **Library Directories**, **Source Directories**, cada um possuem caminhos para suas respectivas pastas. 
	
		- **Include Directories**: 
			- Motorcycle-Simulator\Material auxiliar\Directx\Include
			- Motorcycle-Simulator\Material auxiliar\Motor Encima
			- Motorcycle-Simulator\Material auxiliar\Includes
			
		- **Library Directories**: 
			- Motorcycle-Simulator\Material auxiliar\Directx\Lib\x86
			- Motorcycle-Simulator\Material auxiliar\Libs
			
		- **Source Directories**:
			- Motorcycle-Simulator\Material auxiliar\Motor Encima
			
	- Para alterar o caminho destas pastas clique na seta para baixo, ao lado direito da janela, e vá em  **Edit**.
	
	- Aparecerá uma janela com o nome do diretório escolhido **Exemplo: Include Directories**, contendo alguns caminhos para diferentes pastas. É necessário alterar, **para o local onde você salvou o projeto**, os caminhos que **apenas contém** este início: **C:\Users\Mario Ponce Jr**
		- Exemplo: C:\Users\Mario Ponce Jr\Motorcycle-Simulator\Material auxiliar\Directx\Include
		
		- Clique duas vezes neste caminho, um icone com três pontos "..." surgirá, clique nele e selecione a pasta Include, que se encontra no projeto Motorcycle-Simulator\Material auxiliar\Directx.
		
	- Realize o procedimento para os três diretórios: **Include Directories**, **Library Directories**, **Source Directories**.
	- Depois que realizou essas configurações, vá em **Debug**, clique na opção que aparecerá abaixo **Build Solution**.
	
	- Na aba **Output** será possível visualizar a compilação do projeto.
	

###Como executar o jogo?
1. Abra a pasta "Release"
1. Execute o arquivo "Exemplo 7.exe"
