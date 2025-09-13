[bits 64]
global isr0
global isr1
; ... up to isr31

extern isr_handler  ; C-level function

isr_common_stub:
;these 3 lines print an I to terminal
;  mov al, 'I'
;  mov dx, 0x3F8
;  out dx, al
    push r15
    push r14
    push r13
    push r12
    push r11
    push r10
    push r9
    push r8
    push rdi
    push rsi
    push rbp
    push rbx
    push rdx
    push rcx
    push rax

    mov rdi, rsp  ; pass pointer to registers as first argument
    call isr_handler

    pop rax
    pop rcx
    pop rdx
    pop rbx
    pop rbp
    pop rsi
    pop rdi
    pop r8
    pop r9
    pop r10
    pop r11
    pop r12
    pop r13
    pop r14
    pop r15
    add rsp, 16 ; pop error code + interrupt number
    iretq

%macro ISR_NOERR 1
isr%1:
    push 0               ; dummy error code so common stub can add 16
    push %1              ; interrupt number
    jmp isr_common_stub
%endmacro

%macro ISR_ERR 1
isr%1:
    push 0
    push %1              ; interrupt number
    jmp isr_common_stub
%endmacro

ISR_NOERR 0
ISR_NOERR 1
; ...
; Use ISR_ERR for those that push an error code, like 8, 10–14, 17, etc.
