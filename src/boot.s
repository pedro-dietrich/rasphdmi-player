.global start
.text
start:
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
    b main

halt:
    b halt
