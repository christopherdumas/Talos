bits 32

global  load_idt
global call_keyboard_handler

extern keyboard_handler

    ; load_idt - Loads the interrupt descriptor table (IDT).
    ; stack: [esp + 4] the address of the first entry in the IDT
    ;        [esp    ] the return address
load_idt:
    mov     eax, [esp+4]    ; load the address of the IDT into register eax
    lidt    [eax]           ; load the IDT
    ret                     ; return to the calling function

call_keyboard_handler:
    call keyboard_handler
    iretd
