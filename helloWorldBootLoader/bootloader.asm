[BITS 16]
[ORG 0X7C00]

%define ENDL 0x0D, 0X0A
%define ENDS 0x00

main:

  call cls
  call print_string
.loop:
  hlt
  jmp .loop


print_string:
  push si 
  push ax 
  mov si, string
.loop:
  lodsb
  or al, al
  jz .done

  mov ah, 0x0E ;high bit set to print function
  mov bh, 0
  int 0x10 ;print interrupt
jmp .loop

.done:
  pop ax 
  pop si 
  ret 

cls:
  pusha
  mov al, 0x03
  mov ah, 0x00 
  int 0x10
  popa
  ret 


;data
string: db 'hello world', ENDL, ENDS 
times 510 - ($ - $$) db 0 ; pad to 510 bytes
dw 0xAA55                ; boot signature
