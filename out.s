bits 32
global outb
global inb
global set_gdt

outb:
    mov al, [esp + 8]
    mov dx, [esp + 4]
    out dx, al
    ret

inb:
    mov dx, [esp + 4]
    in  al, dx
    ret

gdtr:
    dw 0 ; For limit storage
    dd 0 ; For base storage

set_gdt:
    mov   eax, [esp + 4]
    mov   [gdtr + 2], eax
    mov   ax, [esp + 8]
    mov   [gdtr], ax
    lgdt  [gdtr]
    ret
