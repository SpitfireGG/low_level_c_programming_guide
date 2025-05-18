section .text
    global _start

_start:
    mov rax, 60 ;; syscall for exit
    mov rsi, 0 ;;  is the first argument to the exit syscall, o means success like in c
    syscall


