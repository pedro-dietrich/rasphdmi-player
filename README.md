# RaspHDMI Player

## Descrição

Projeto com o intuito de criar um player de vídeo em C *bare metal*, para um Raspberry Pi 2.


## Integrantes

Beatriz Alves Bessa - 9348814

Pedro Martins Dietrich - 12550730


## Instruções

Para executar o programa em um Raspberry Pi 2, basta copiar os arquivos da pasta `SD Card` para a raiz de um micro SD, formatado corretamente.

Para compilar o programa, é necessário utilizar o comando `make` dentro da pasta `src`. Note que é necessário ter o *toolchain* **arm-none-eabi** instalado.
A compilação também exige um arquivo `video.data`, que é explicado na seção seguinte.


## Configurando vídeo para reprodução

A reprodução de um vídeo pelo programa exige que os dados do vídeo sejam carregados diretamente na RAM do Raspberry, e para isso, os dados devem estar presente no executável, e consequentemente, na imagem a ser colocada no cartão SD.

Carregar o vídeo no programa requer criar um arquivo `video.data` (dentro da pasta `src/`), e para isso foi criado um programa a parte, localizado em `Raw Frames to C Array/`.

Primeiramente, é necessário criar arquivos `.raw`, numerados, contendo a imagem de cada frame do vídeo em formato bruto. Isso pode ser feito com um programa como `ffmpeg`, com o comando de exemplo a seguir:

```bash
ffmpeg -i example_video.mp4 -vf scale=192:144 -pix_fmt gray -vframes 1200 path/to/frame_%04d.raw
```

O comando de exemplo cria vários arquivos nomeados `frame_0001.raw` a `frame_1200.raw` a partir do arquivo de vídeo `example_video.mp4` (pode ser qualquer formato aceito pelo **ffmpeg**), gerando 1200 arquivos (conforme especificado pelo parâmetro `-vframes`), com resolução de 192x144 e paleta de cores de 8 bpp em preto e branco (conforme especificado por `-pix_fmt gray`).

É possível utilizar outros parâmetros, e nesse caso será necessário atualizar o arquivo `config.h` de acordo. Dito isso, é bom ter em mente que o Raspberry Pi 2 possui apenas 1 GB de RAM, então é necessário limitar a resolução e a duração para tamanhos adequados.

Em seguida, na pasta `Raw Frames to C Array/`, compile o programa C++ com:

```bash
cmake -S . -B build/
cd build
make
```

Com isso, é possível executar o programa com:
```bash
./bin_to_array 192 144 8 path/to/frame_*.raw
```

Onde 192 e 144 são as resoluções horizontal e vertical, 8 é a profundidade de cor em bpp e o último argumento é o caminho para os arquivos das imagens (frames), substituindo o número de cada arquivo por `*`.

Finalmente, isso irá gerar um arquivo `video.data`, que deve ser movido para a pasta `src/`, e então será possível compilar o programa e rodar no Raspberry Pi 2.

