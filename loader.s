extern main

bits 32
global loader

    KERNEL_STACK_SIZE equ 4096

section .bss
align 4
kernel_stack:
    resb KERNEL_STACK_SIZE

section .text
    mov esp, kernel_stack + KERNEL_STACK_SIZE
    call main
