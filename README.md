# MindScape

### Gênero

Suspense.

### Descrição

MindScape é um jogo plataforma com elementos de terror e suspense. Como o jogo se situa na mente da protagonista, há monstros surreais que são criados com base em seus medos.

Além disso, o jogo trará a arte como elemento de história do jogo. Nas fases iniciais, haverá a presença de muitas cores que eventualmente vão desbotando e ficando preto e branco, para demonstrar a ciência da menina de sua própria situação.


### História

A história acompanha uma menina que encontra-se em coma por um acidente misterioso. Ela acorda em sua mente onde deverá enfrentar seus medos para que possa acordar antes que seja tarde demais.

### Instruções

* Andar para frente: →  
* Andar para trás: ← 
* Pular:  ↑
* Atacar: F
* Pausar: Esq
* Despausar: Barra de espaço

### Envolvidos

| Nome | Ocupação | 
| :--: | :-----: |
| Luan Guimarães | Programador |
| Lucas Soares | Programador |
| Matheus Miranda | Programador |
| Victor Navarro | Programador |
| Bruna Figueirôa | Artista |
| Maria Monteiro | Artista |
| Amanda Santos | Artista |
| Natália Menezes | Artista |
| Aria Rita | Música |

### Dependências

As dependências estão listadas pelo nome do pacote. Dessa forma, em distribuições _linux_ baseadas em _Debian_, é necessário apenas rodar "sudo apt-get install nomeDoPacote".
* libsdl2-dev
* libsdl2-image-dev
* libsdl2-ttf-dev
* libsdl2-mixer-dev
* make
* gcc
* g++
* CMake (versão 3.1 ou maior)


### Compilando e Executando

Após clonar o repositório, entre na pasta MindScape. Nesse diretório, há um _script_ sh responsável pela interação com o CMake e, portanto, com a compilação e execução. Dentro da pasta, os comandos e suas funções são:

| Comando | Efeito |
| :----:  | :----: |
| `./control.sh build` | Gera os novos _Makefiles_ |
| `./control.sh make` | Usa os _Makefiles_ gerados para compilar o jogo |
| `./control.sh run` | Executa o jogo |

