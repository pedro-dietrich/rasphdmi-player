.global start
.text
start:
    // Carrega o vetor de interrupções em 0x00000000
    ldr r0, =interrupt_vector
    mov r1, #0x0
    ldmia r0!, {r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!, {r2,r3,r4,r5,r6,r7,r8,r9}
    ldmia r0!, {r2,r3,r4,r5,r6,r7,r8,r9}
    stmia r1!, {r2,r3,r4,r5,r6,r7,r8,r9}

    // Modo supervisor (SVC)
    mov r0, #0xd3
    msr cpsr_c, r0

    // Configura o stack pointer
    ldr sp, =stack_addr

    // Configura o segmento BSS
    ldr r0, =bss_begin
    ldr r1, =bss_end
    mov r2, #0
loop_bss:
    cmp r0, r1
    bge done_bss
    strb r2, [r0], #1
    b loop_bss
done_bss:

    // Chama a função main (em main.c)
    bl main
    b halt

// Vetor de interrupções
interrupt_vector:
    ldr pc, reset_addr
    ldr pc, undef_addr
    ldr pc, swi_addr
    ldr pc, inst_abort_addr
    ldr pc, data_abort_addr
    nop
    ldr pc, irq_addr
    ldr pc, fiq_addr

// Endereços das rotinas de interrupções
reset_addr: .word reset
undef_addr: .word undef_serv
swi_addr: .word swi_serv
inst_abort_addr: .word inst_abort_serv
data_abort_addr: .word data_abort_serv
irq_addr: .word irq_serv
fiq_addr: .word fiq_serv

// Rotinas de interrupções
reset:
undef_serv:
swi_serv:
inst_abort_serv:
data_abort_serv:
fiq_serv:
    b halt

irq_serv:
    bl irq_service

// Trava o processador
halt:
    b halt
