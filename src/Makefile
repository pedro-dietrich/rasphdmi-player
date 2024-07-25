PROJETO = rasphdmi_player

FONTES = boot.s main.c gpio.c
LDSCRIPT = linker.ld

# Arquivos de saída
EXEC = ${PROJETO}.elf
MAP = ${PROJETO}.map
IMAGE = ${PROJETO}.img
LIST = ${PROJETO}.list
HEXFILE = ${PROJETO}.hex

# Caminhos
ROOT_PATH = ".."
SD_CARD = "../SD Card"

# Comandos e opções
PREFIXO = arm-none-eabi-
AS = ${PREFIXO}as
LD = ${PREFIXO}ld
GCC = ${PREFIXO}gcc
OBJCPY = ${PREFIXO}objcopy
OBJDMP = ${PREFIXO}objdump

OPTS = -march=armv7-a -mtune=cortex-a7 -g
LD_OPTS = -lgcc -L/usr/lib/gcc/arm-none-eabi/10.3.1/

# Arquivos objetos
OBJ_ASM = $(FONTES:.s=.o)
OBJETOS = $(OBJ_ASM:.c=.o)

all: ${EXEC} ${IMAGE} ${LIST} ${HEXFILE}

# Gerar executável
${EXEC}: ${OBJETOS}
	${LD} -T ${LDSCRIPT} -M=${MAP} -o $@ ${OBJETOS} ${LD_OPTS}

# Gerar imagem (.img)
${IMAGE}: ${EXEC}
	${OBJCPY} ${EXEC} -O binary ${IMAGE}
	cp ${IMAGE} ${SD_CARD}

# Gerar arquivo HEX para o bootloader
${HEXFILE}: ${EXEC}
	${OBJCPY} ${EXEC} -O ihex ${HEXFILE}

# Gerar listagem
${LIST}: ${EXEC}
	${OBJDMP} -std ${EXEC} > ${LIST}

# Montar arquivos em assembly
.s.o:
	${AS} -g -o $@ $<

# Compilar arquivos em C
.c.o:
	${GCC} ${OPTS} -c -o $@ $<

# Iniciar qemu
qemu: ${EXEC}
	qemu-system-arm -s -M virt -kernel ${EXEC} &

# Iniciar gdb
gdb: ${EXEC} qemu
	gdb-multiarch -ex "set architecture arm" \
		-ex "target extended-remote:1234" \
		-ex "load" \
		${EXEC}

# Finalizar processos, caso estejam em execução
stop:
	-pkill qemu-system-arm
	-pkill gdb-multiarch

# Limpar os arquivos criados
clean: stop
	rm -f *.o ${EXEC} ${MAP} ${LIST} ${IMAGE} ${HEXFILE}

# Remover os arquivos gerados e criar novamente
rebuild: clean all
