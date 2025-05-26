section .data
    msg  db 'hello world', 0x0a, 0x0a ;; hello world  ( 0x0a is hex value for \n ) x2 ( 2 new lines )
    msg_len equ $ - msg

section .text
    global _start

_start:
    ;print hello world
    ;; syscall ( 1 )
    mov rax, 1
    mov rsi, msg
    mov rdx, msg_len
    syscall

    ; exit the program
    mov rax, 60
    mov rdi, 60
    syscall

