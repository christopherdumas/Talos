bits 32
section .text
    ;; MULTIBOOT SPEC
align 4
    dd 0x1BADB002            ;magic
    dd 0x00                  ;flags
    dd - (0x1BADB002 + 0x00) ;checksum. m+f+c should be zero

    STACK_SIZE equ 8192

global start
extern kmain

start:
    cli
    mov esp, stack_space
    call kmain
    hlt

section .bss
    resb STACK_SIZE
stack_space:
