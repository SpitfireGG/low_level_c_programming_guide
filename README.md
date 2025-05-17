# x86-64_AT-T_guide
Personal repository for learning the x86_64 assembly with AT&amp;T syntax

Okay, let's dive into the fascinating world of x86-64 assembly and how it connects to your goal of mastering C. Learning assembly *from the ground up* is a significant undertaking, but it provides an unparalleled understanding of how computers work and how your C code actually executes.

It's not about being "dumb" – assembly is simply a much lower level of abstraction than C. It requires thinking about the hardware directly. Let's build this knowledge step-by-step.

**Why Learn Assembly for C?**

Learning assembly isn't just for writing operating systems or device drivers anymore. For a C programmer, it gives you a deep understanding of:

1.  **Pointers and Memory:** What a pointer *really* is (just an address), how pointer arithmetic works at the byte level, and how memory is accessed.
2.  **Data Representation:** How different C data types (integers, floats, structs) are laid out in memory and manipulated by the CPU.
3.  **Function Calls:** How functions are called, how arguments are passed, how local variables are managed on the stack, and how return values are handled. This is *critical* for understanding recursion and potential stack overflows.
4.  **Performance:** Why some C code is faster than other equivalent code, and how to write code that translates efficiently to machine instructions.
5.  **Debugging:** Understanding assembly helps you use debuggers (like GDB) more effectively, stepping through code line by line at the machine level.
6.  **Security:** Understanding buffer overflows and other vulnerabilities becomes much clearer when you see how memory is manipulated.

**Prerequisites (Minimal):**

*   Basic understanding of binary and hexadecimal numbers (you'll see a lot of hex addresses).
*   Familiarity with basic computer architecture concepts (CPU, memory).

**Choosing Our Environment: Linux and GAS (AT&T Syntax)**

There are different assembly syntaxes (Intel vs. AT&T) and different operating system conventions. For learning and connecting to C development, especially with GCC (the standard C compiler), using **Linux** and the **GNU Assembler (GAS)** with **AT&T syntax** is common and highly recommended. This is because GCC's default output is in AT&T syntax, making it easy to compare your C code to the generated assembly.

**AT&T Syntax Quick Notes:**

*   Source operand comes *before* the destination operand (e.g., `mov %eax, %ebx` means move the value in `%eax` to `%ebx`). This is the *opposite* of Intel syntax!
*   Register names are prefixed with `%` (e.g., `%rax`, `%rbx`).
*   Immediate values are prefixed with `$` (e.g., `mov $5, %eax`).
*   Memory addresses are often enclosed in parentheses `()` (e.g., `mov (%rbp), %rax`).

**Core Concepts of x86-64 Assembly**

1.  **Registers:** These are small, fast storage locations *inside* the CPU. They are where the CPU performs its operations directly. In x86-64 (64-bit), registers are generally 64 bits wide.

    *   **General-Purpose Registers:** The most common ones you'll use:
        *   `%rax`: Accumulator register. Used for arithmetic operations, function return values, and system call numbers.
        *   `%rbx`: Base register. General-purpose, often used for holding addresses.
        *   `%rcx`: Counter register. Used for loop counters and system call arguments.
        *   `%rdx`: Data register. Used for arithmetic, I/O, and system call arguments.
        *   `%rsi`: Source index register. Used as a source pointer for memory operations and system call arguments.
        *   `%rdi`: Destination index register. Used as a destination pointer for memory operations and system call arguments.
        *   `%rbp`: Base pointer register. Traditionally used to point to the base of the current function's stack frame.
        *   `%rsp`: Stack pointer register. Points to the *top* of the current stack. **This is crucial for understanding function calls.**
        *   `%r8` - `%r15`: Additional general-purpose registers introduced in x86-64. Used for arguments in function calls/system calls and general data.

    *   **Important Sub-registers:** You can access the lower parts of these 64-bit registers:
        *   `%eax`, `%ebx`, `%ecx`, `%edx`, `%esi`, `%edi`, `%ebp`, `%esp`: The lower 32 bits.
        *   `%ax`, `%bx`, `%cx`, `%dx`, `%si`, `%di`, `%bp`, `%sp`: The lower 16 bits.
        *   `%al`, `%bl`, `%cl`, `%dl`, `%sil`, `%dil`, `%bpl`, `%spl`: The lower 8 bits (byte).
        *   `%ah`, `%bh`, `%ch`, `%dh`: The *upper* 8 bits of the lower 16-bit registers (less common in 64-bit code).

    *   **Instruction Pointer (`%rip`):** Points to the *next* instruction to be executed. You cannot directly manipulate this register with standard instructions like `mov`, but control flow instructions (`jmp`, `call`, `ret`) change it.

    *   **Flags Register (`%rflags`):** Contains various status flags set by comparison and arithmetic operations (e.g., Zero Flag, Carry Flag, Sign Flag). Conditional jump instructions check these flags.

2.  **Memory:** This is your RAM. It's a large array of bytes, each with a unique address. The CPU can read data from and write data to specific memory addresses.
    *   **Addressing Modes:** How you refer to memory locations. Common modes:
        *   `($reg)`: The contents of the memory location pointed to by the address in `reg`. (e.g., `mov (%rax), %rbx` loads the 64-bit value *at* the address stored in `%rax` into `%rbx`).
        *   `$disp($reg)`: The contents of the memory location at `address in reg + displacement`. (e.g., `mov 8(%rbp), %rax` loads the value at `address in %rbp + 8` into `%rax`). This is how you access local variables or function arguments on the stack.
        *   `$disp($base_reg, $index_reg, $scale)`: More complex, used for arrays. Address is `displacement + base_reg + index_reg * scale`. (e.g., `mov (%rax, %rbx, 8), %rcx` loads the value at `address in %rax + address in %rbx * 8` into `%rcx` - useful for accessing an element in an array where `%rax` is the base address, `%rbx` is the index, and 8 is the size of each element in bytes).

3.  **Instructions:** These are the commands the CPU understands. Each instruction performs a very simple task.

    *   **Data Transfer:**
        *   `mov src, dest`: Copy data from source to destination. Can be register to register, immediate to register, immediate to memory, memory to register, register to memory. **Cannot** be memory to memory directly in one instruction (you need two `mov`s via a register).
        *   `push src`: Push a value onto the stack. Decrements `%rsp` by 8 (for 64-bit values) and writes `src` to the location `%rsp` now points to.
        *   `pop dest`: Pop a value from the stack. Reads the value from the location `%rsp` points to and increments `%rsp` by 8.

    *   **Arithmetic:**
        *   `add src, dest`: `dest = dest + src`
        *   `sub src, dest`: `dest = dest - src`
        *   `imul src, dest`: `dest = dest * src` (integer multiply, can have 1, 2, or 3 operands, forms vary)
        *   `idiv src`: Integer divide. Divides the 128-bit value in `%rdx:%rax` by `src`. Quotient goes into `%rax`, remainder into `%rdx`. Need to clear `%rdx` first for a 64-bit dividend (e.g., using `cqto`).
        *   `inc dest`: `dest = dest + 1`
        *   `dec dest`: `dest = dest - 1`
        *   `neg dest`: `dest = -dest`
        *   `not dest`: Bitwise NOT (one's complement)

    *   **Logical:**
        *   `and src, dest`: Bitwise AND
        *   `or src, dest`: Bitwise OR
        *   `xor src, dest`: Bitwise XOR (often used to set a register to 0: `xor %rax, %rax`)
        *   `shl count, dest`: Shift bits left
        *   `shr count, dest`: Shift bits right (logical, fills with 0)
        *   `sar count, dest`: Shift bits right (arithmetic, preserves sign bit)

    *   **Control Flow:**
        *   `jmp label`: Unconditional jump to `label`.
        *   `cmp op1, op2`: Compare `op2` and `op1` (conceptually `op2 - op1`), sets flags (`%rflags`).
        *   `test op1, op2`: Performs bitwise AND of `op1` and `op2`, sets flags. Useful for checking if a value is zero or testing specific bits.
        *   `je label`: Jump if Equal (ZF=1)
        *   `jne label`: Jump if Not Equal (ZF=0)
        *   `jg label`: Jump if Greater (signed)
        *   `jge label`: Jump if Greater or Equal (signed)
        *   `jl label`: Jump if Less (signed)
        *   `jle label`: Jump if Less or Equal (signed)
        *   `ja label`: Jump if Above (unsigned)
        *   `jae label`: Jump if Above or Equal (unsigned)
        *   `jb label`: Jump if Below (unsigned)
        *   `jbe label`: Jump if Below or Equal (unsigned)
        *   `call label`: Call a subroutine (function). Pushes the address of the *next* instruction onto the stack and jumps to `label`.
        *   `ret`: Return from a subroutine. Pops the return address from the stack and jumps to that address.

**Structure of a Basic Assembly Program (Linux x86-64)**

A simple executable assembly program for Linux typically has:

1.  `.section .data`: For initialized global/static data (strings, constants).
2.  `.section .bss`: For uninitialized global/static data.
3.  `.section .text`: For the executable code.
4.  `.globl _start`: Makes the `_start` label visible to the linker.
5.  `_start:`: The entry point of the program where execution begins.
6.  Calls to **System Calls** (`syscall`) to interact with the OS (like printing to the screen or exiting).

**Example: "Hello, World!" using a System Call**

```assembly
.section .data
    msg db "Hello, World!", 10  ; Our string, db = define byte
    len equ $ - msg             ; Calculate length (current address $ minus msg address)

.section .text
.globl _start

_start:
    ; Write syscall (sys_write = 1)
    mov $1, %rax       ; syscall number for write
    mov $1, %rdi       ; file descriptor 1 (stdout)
    mov $msg, %rsi     ; address of the string to write
    mov $len, %rdx     ; number of bytes to write
    syscall            ; Execute the syscall

    ; Exit syscall (sys_exit = 60)
    mov $60, %rax      ; syscall number for exit
    mov $0, %rdi       ; exit status 0 (success)
    syscall            ; Execute the syscall
```

**To assemble and link this on Linux:**

```bash
nasm -f elf64 hello.asm -o hello.o # Use nasm, easier syntax sometimes for simple programs, or gas
ld hello.o -o hello             # Link the object file
./hello                         # Run the program
```

*Self-Correction:* I used NASM syntax in the example because it's often considered slightly more readable for beginners than GAS AT&T for simple programs. However, since the goal is to connect to GCC/C, let's rewrite the example using GAS AT&T syntax, as requested by the context of linking to C:

**Example: "Hello, World!" using a System Call (GAS AT&T Syntax)**

```assembly
.section .data
    msg:
        .ascii "Hello, World!\n"  ; Our string, .ascii defines characters
    len = . - msg             ; Calculate length (current address . minus msg address)

.section .text
.globl _start

_start:
    ; Write syscall (sys_write = 1)
    mov $1, %rax       ; syscall number for write
    mov $1, %rdi       ; file descriptor 1 (stdout)
    mov $msg, %rsi     ; address of the string to write
    mov $len, %rdx     ; number of bytes to write
    syscall            ; Execute the syscall

    ; Exit syscall (sys_exit = 60)
    mov $60, %rax      ; syscall number for exit
    mov $0, %rdi       ; exit status 0 (success)
    syscall            ; Execute the syscall
```

**To assemble and link this on Linux using GAS:**

```bash
as --gstabs hello.s -o hello.o # Assemble using gas (usually 'as'), --gstabs for debugging symbols
ld hello.o -o hello             # Link the object file
./hello                         # Run the program
```
*(Note: The extension for GAS source files is typically `.s` or `.S`)*

**Connecting Assembly to C: How C Code Becomes Assembly**

This is where assembly truly helps your C understanding. Let's look at simple C constructs and how they map.

**1. Variables:**

*   **Global/Static Variables:** Declared outside functions or with `static` inside a function. They reside in the `.data` (if initialized) or `.bss` (if uninitialized) sections of the executable. In assembly, you'll refer to them by their label name.
    ```c
    int global_var = 10; // In .data
    static int static_var; // In .bss
    ```
    In assembly (`.data`):
    ```assembly
    .data
    .globl global_var
    global_var:
        .long 10 # Define a 4-byte integer with value 10
    ```
    In assembly (`.bss`):
    ```assembly
    .bss
    .globl static_var
    static_var:
        .zero 4 # Reserve 4 bytes, initialized to zero by the OS loader
    ```
*   **Local Variables (non-static):** Declared inside a function without `static`. They are typically stored on the **stack**.

**2. The Stack and Function Calls (The ABI)**

This is perhaps the *most* crucial part for understanding C functions. The **Application Binary Interface (ABI)** defines how functions interact at the assembly level (how arguments are passed, how the stack is used, etc.). For Linux x86-64, we typically use the **System V AMD64 ABI**.

Key aspects of the System V AMD64 ABI:

*   **Argument Passing:** The first 6 integer or pointer arguments are passed in registers in this order: `%rdi`, `%rsi`, `%rdx`, `%rcx`, `%r8`, `%r9`. Additional arguments are pushed onto the stack *in reverse order*.
*   **Return Value:** Integer or pointer return values are placed in `%rax`.
*   **Stack Usage:** The stack grows downwards (towards lower memory addresses). `%rsp` points to the *top* (lowest address) of the stack.
*   **Stack Frame:** Each function call typically creates a "stack frame" on the stack to manage its local variables and saved registers.
    *   `%rbp` (Base Pointer) is often used to mark the *base* of the current stack frame, providing a stable reference point to access local variables and arguments passed on the stack (if any).
    *   `%rsp` (Stack Pointer) changes as values are pushed (`push`) and popped (`pop`).
*   **Callee-Saved vs. Caller-Saved Registers:** Some registers (`%rbx`, `%rbp`, `%r12`-%r15`) must be *preserved* by a function that uses them (the "callee"). If the function needs to use, say, `%rbx`, it must `push %rbx` at the start and `pop %rbx` before returning. Other registers (`%rax`, `%rcx`, `%rdx`, `%rsi`, `%rdi`, `%r8`-%r11`) are *caller-saved*, meaning the *caller* is responsible for saving them if it needs their values after calling another function.

**Typical Function Structure (Assembly)**

Let's look at a simple C function and its corresponding assembly (compile with `gcc -S -O0 your_code.c` to see this, `-O0` disables optimizations which makes the assembly clearer for learning):

```c
int add_two_numbers(int a, int b) {
    int sum = a + b;
    return sum;
}
```

Corresponding Assembly (simplified, GAS AT&T, output of `gcc -S -O0`):

```assembly
    .text
    .globl add_two_numbers
    .type add_two_numbers, @function
add_two_numbers:
.LFB0: # Function start label (generated by compiler)
    .cfi_startproc # Debugger info

    ; --- Function Prologue ---
    pushq   %rbp        ; Save the caller's base pointer onto the stack
    .cfi_def_cfa_offset 16 # Debugger info
    .cfi_offset 6, -16     # Debugger info
    movq    %rsp, %rbp  ; Set the current base pointer to the current stack pointer
    .cfi_def_cfa_register 6 # Debugger info

    ; 'a' is in %rdi (first argument)
    ; 'b' is in %rsi (second argument)
    ; Local variable 'sum' will be on the stack, relative to %rbp

    ; --- Function Body ---
    ; Allocate space for local variable 'sum' on the stack (4 bytes for int)
    ; movl    %edi, -4(%rbp)  ; Move 'a' (32-bit) to stack location for sum
    ; movl    %esi, -8(%rbp)  ; Move 'b' (32-bit) to another stack location (not needed if we add directly)

    ; Calculate sum = a + b
    movl    %edi, %eax  ; Move 'a' (from %rdi) into %eax (use 32-bit register for int)
    addl    %esi, %eax  ; Add 'b' (from %rsi) to %eax (%eax now holds sum)
    ; Store sum back to the stack location (optional step by compiler, depends on usage)
    ; movl    %eax, -4(%rbp) ; Store result into the 'sum' variable's stack location

    ; The result (sum) is already in %eax, which is the register for return values

    ; --- Function Epilogue ---
    leave           ; Equivalent to: movq %rbp, %rsp; popq %rbp
                    ; Restores stack pointer and base pointer to caller's state
    .cfi_def_cfa 7, 8   # Debugger info
    ret             ; Pop return address from stack and jump there

.LFE0: # Function end label (generated by compiler)
    .cfi_endproc    # Debugger info
    .size   add_two_numbers, .-add_two_numbers
    .ident  "GCC: (GNU) 11.2.0" ; Compiler info
```

**Explanation of the C -> Assembly Mapping:**

*   `int a`, `int b`: These are arguments. In the ABI, the first two integer args go to `%rdi` and `%rsi` (using their 32-bit counterparts `%edi` and `%esi` since `int` is typically 32 bits).
*   `int sum;`: This is a local variable. It's allocated space on the stack. Accessing it uses an offset from `%rbp` (like `-4(%rbp)`).
*   `sum = a + b;`: The values from `%edi` and `%esi` are loaded into registers (here, `%edi` is moved to `%eax`, then `%esi` is added to `%eax`).
*   `return sum;`: The value to be returned is placed in the `%rax` register (using its 32-bit counterpart `%eax`).
*   **Prologue (`pushq %rbp`, `movq %rsp, %rbp`):** Sets up the stack frame. Saves the *caller's* `%rbp`, then makes the *current* `%rbp` point to the top of the stack (which is now the base of the new frame).
*   **Epilogue (`leave`, `ret`):** Tears down the stack frame. `leave` restores `%rsp` and `%rbp` to their state before the function call. `ret` pops the return address (which the `call` instruction pushed) off the stack and jumps back to the caller.

**Understanding Pointers and Arrays in Assembly**

*   A C pointer `int *p;` is just a variable (usually 8 bytes on x86-64) that stores a memory address.
*   Dereferencing `*p` means loading the value *at* the address stored in `p`. In assembly, if `p`'s value is in `%rax`, `*p` would be accessed using `(%rax)`.
*   Array access `arr[i]` is translated to pointer arithmetic: `*(arr + i)`. If `arr` is a pointer to the first element and `i` is the index, the assembly might calculate the address as `base_address + index * element_size` and then access memory at that calculated address.
    *   If `arr`'s base address is in `%rax` and the index `i` is in `%rbx`, and element size is 4 bytes (e.g., `int`), accessing `arr[i]` might involve an instruction like `movl (%rax, %rbx, 4), %ecx`. This loads the 4-byte value from the address calculated as `%rax + %rbx * 4` into `%ecx`.

**Exercises**

Start small and build up. Use an assembler (like `as` or `nasm`) and a linker (`ld`). Use a debugger (`gdb`) *early and often* (`layout asm`, `break _start`, `stepi`, `info registers`, `x/10x %rsp`) to see what's happening.

1.  **Register Movement:** Write an assembly program that moves a value from one register to another, then another value from memory into a register.
    *   Define a variable in `.data` (e.g., `my_var: .quad 123`).
    *   In `_start`, move an immediate value (like 42) into `%rax`.
    *   Move the value from `%rax` into `%rbx`.
    *   Move the value from `my_var` into `%rcx`.
    *   Use the `exit` syscall (60) with status 0. Assemble, link, and run it. (It won't print anything, you'd use GDB to inspect the registers).

2.  **Simple Arithmetic:** Write a program that adds two numbers and stores the result in a register.
    *   Move `10` into `%rax`.
    *   Move `20` into `%rbx`.
    *   Add `%rbx` to `%rax` (`add %rbx, %rax`).
    *   Exit. Use GDB to check the final value in `%rax`.

3.  **Using Memory:** Write a program that adds a value in a register to a value in memory and stores the result back in memory.
    *   Define two variables in `.data` (e.g., `var1: .quad 5`, `var2: .quad 7`).
    *   Move the value of `var1` into `%rax`.
    *   Add the value of `var2` to `%rax`.
    *   Store the result from `%rax` back into `var1`.
    *   Exit. Use GDB to check the value of `var1` in memory after the program runs (`x/g &var1` in GDB).

4.  **Basic Control Flow (If Statement):** Write a program that compares two numbers and jumps based on the result.
    *   Define `a = 5`, `b = 10` in registers.
    *   Compare `a` and `b` (`cmp %rbx, %rax` where `%rax` has `b`, `%rbx` has `a`).
    *   If `a` is greater than `b` (`jg`), jump to a label `is_greater`.
    *   If not, jump to a label `not_greater`.
    *   At `is_greater`, maybe put `1` in `%rax`. At `not_greater`, put `0` in `%rax`.
    *   Jump to an `end_program` label before exiting.
    *   Run in GDB, set a breakpoint at the end, and check `%rax`. Change the values of `a` and `b` and re-run.

5.  **Basic Control Flow (Loop):** Write a program that implements a simple loop (e.g., count down from 10 to 0).
    *   Initialize a counter register (e.g., `%rcx`) to 10.
    *   Create a label `loop_start`.
    *   Inside the loop, maybe print the counter (requires using the `write` syscall, more complex). Or just decrement the counter.
    *   Decrement the counter (`dec %rcx`).
    *   Compare the counter to 0 (`cmp $0, %rcx`).
    *   Jump back to `loop_start` if not equal (`jne loop_start`).
    *   Exit. Use GDB to trace the loop and check the counter.

6.  **Connecting to C (GCC Output Analysis):**
    *   Write simple C functions (e.g., `int multiply(int x, int y) { return x * y; }`, `void swap(int *a, int *b) { int temp = *a; *a = *b; *b = temp; }`).
    *   Compile them with `gcc -S -O0 your_file.c`.
    *   Examine the generated `.s` file. Try to identify:
        *   The function prologue and epilogue.
        *   Where arguments are read from (`%rdi`, `%rsi`, etc. or the stack).
        *   How local variables are accessed (offsets from `%rbp`).
        *   How the operations (multiplication, memory access for swap) are performed.
        *   Where the return value is placed (`%rax`).

**What's Crucial for In-depth C Understanding?**

*   **Mastering the Stack:** How function calls use it, how local variables are stored, how arguments are sometimes passed on it. This is key to understanding variable scope, recursion, and stack overflows.
*   **Understanding Pointers as Addresses:** Seeing memory access (`mov (%reg), ...` or `mov $offset(%reg), ...`) directly corresponds to pointer dereferencing or array indexing in C.
*   **The ABI:** Knowing which registers are used for arguments and return values explains why C functions behave the way they do.
*   **Data Representation:** How C data types map to byte sizes and memory layout (especially structs and arrays).
*   **Control Flow Translation:** Seeing how `if`, `else`, `while`, `for` in C are translated into `cmp`/`test` and conditional/unconditional `jmp` instructions.

**Next Steps**

*   **Get Tools:** Make sure you have `gcc`, `as` (or `nasm`), `ld`, and `gdb` installed on a Linux system.
*   **Work Through Exercises:** Start with the simplest ones and use GDB constantly.
*   **Read More:** Find good online tutorials or books specifically on x86-64 assembly for Linux (using GAS/AT&T). The "Assembly Language Step-by-Step" book is highly recommended.
*   **Experiment:** Write small C programs and compile them to assembly (`gcc -S -O0`) and analyze the output. Change optimization levels (`-O1`, `-O2`, `-O3`) and see how the assembly changes dramatically.
*   **Learn More Instructions:** As you encounter more complex C code, you'll need to learn more assembly instructions (bitwise operations, shifts, floating-point if needed, etc.).
*   **Explore the Heap:** Understand how `malloc`/`free` work at a lower level (though the heap is managed by the C standard library, not typically written in raw assembly by hand unless you're writing a `malloc` implementation).

Learning assembly is like learning the ABCs of your computer. It's challenging because it's low-level, but the payoff in understanding C (and computing in general) is enormous. Be patient with yourself, break down the concepts, and practice consistently. You've got this!
