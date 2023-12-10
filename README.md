# PG
Repositório para desenvolvimento do projeto da disciplina de processamento gráfico do curso de ciência da computação

## Link de instalação do MingW

[Compilador Cpp](https://sourceforge.net/projects/gcc-win64/) 

## Biblioteca externa (GLM - Open Gl Mathematics)

Neste projeto usaremos a biblioteca externa GLM para as definições matemáticas necessárias.<br>
[Bilbioteca GLM documentação](https://github.com/g-truc/glm)

## Comandos úteis

### Comandos para compilar o código c++:

Os códigos abaixo não funcionam no powershell

```bash
// um arquivo apenas
g++ ./nome_arquivo.cpp -o nome_arquivo

// arquivo principal com headers
g++ ./nome_arquivo.cpp ./outro_arquivo.cpp -o nome_arquivo

// arquivo principal com headers em outras pastas
g++ ./nome_arquivo.cpp ./caminhoDaOutraPasta/*.cpp -o nome_arquivo
```

### Comando para gerar o arquivo .ppm linux (ou git bash no windows):

```bash
./filename.out > output.ppm
```

### ou no Windows :

```bash
Opcão : cmd (recomendável)
file_name.exe > output.ppm
```

## Como visualizar arquivos .ppm

No windows o visualizador de fotos padrão não suporta visualização de arquivos .ppm então duas recomendações de aplicativos de terceiros para visualizar esses arquivos são :

1 - [IrfanView](https://www.irfanview.com/)

2 - [XnView](https://www.xnview.com/en/)

