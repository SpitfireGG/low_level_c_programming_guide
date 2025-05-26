# Preface

A machine instruction is an instruction that can be directly recognized and executed by the CPU in binary code, and different CPU architectures have different machine instruction sets. The assembly instruction is to map the machine instruction to a string that is easy to remember and write (note that it is not a one-to-one correspondence, there may be multiple assembly instructions corresponding to one machine instruction in the same assembler), and the assembly instruction is translated into a machine instruction by the assembler for the CPU to execute after the assembly instruction is written.

Different assemblers can have different assembly instructions for the same machine instruction, as long as the assembler can eventually translate them correctly. Different assemblers correspond to different assembly instruction formats, and different assembly instruction formats derive different assembly instruction syntax. There is no one assembler that can correctly translate all assembly syntax into machine instructions, so with the development of computers, different manufacturers have formed their own assembly language systems and have their own assemblers.

Common assemblers are:
- GNU Assembler (GAS): Uses AT&T assembly syntax.
- Microsoft Macro Assembler (MASM): Uses Intel assembly syntax.
- Netwide Assembler (NASM): Uses assembly syntax similar to Intel assembly syntax, but is a bit simpler.
- Flat Assembler (FASM) et al.

**Note:** This article uses the assembly syntax used by NASM as an example.

## Sentence Structure

The basic sentence structure of NASM can be made up of four parts: `label: instruction operand(s) ; comment`.

*   Theoretically, all four of the above parts are optional, but at least one of them exists, and a statement can have no instructions and only one label.
*   The colon after the label can also be omitted.

## Space

The NASM syntax has no requirements or limits on the number of spaces, and any number of spaces can be added between any two sections (at least one is used to distinguish between the two sections).

## Line Continuation

In NASM, a backslash (`\`) is used as a continuation of a line, and if a line ends with a backslash, the next line of the current line is considered a continuation of the current line.

## Labels

Labels can use letters, digits, underscores (`_`), dollar characters (`$`), hashtags (`#`), at signs (`@`), tildes (`~`), periods (`.`), and question marks (`?`). It has a special meaning starting with a full stop (`.`) (see below for details).

## Local Labels

In NASM, labels that start with a full stop (`.`) are considered local, and all local labels are considered to be related to the previous non-local label.

```asm
label1:
    some code

.loop:
    some code
    jne .loop
    ret

label2:
    some code

.loop:
    some code
    jne .loop
    ret

label3:
    some code
    jmp label1.loop
```

In the snippet, all the `jne` directives jump to the `.loop` label next to it, because the `.loop` label is defined as a local label, so the two `.loop` labels are associated with the nearest global label above them. In the case of special designation, local labels can only take effect under the global label associated with them, but they can also be used through the "global label.local label" syntax.

## Special Symbols

*   **\`\` : Escape Operator**
    NASM uses C-style escape characters followed by a backslash followed by an escape code, which includes: character escape, octal escape, hexadecimal escape. The character to be escaped needs to be quoted in backticks:

    ```asm
    db `\x61` ; Equivalent to db 'a'
    ```

    Note: Backticks can also be used to define normal strings.

*   **\[] : Index Operator**
    In some places, it is called an "index operator", which indicates an indirect way of taking operands, that is, taking the operands corresponding to the memory address in parentheses, similar to the pointer concept in C.

    The parentheses generally contain a memory address, which can be a memory address represented by registers, a memory address represented by labels, or a memory address directly represented by operands.

    ```asm
    mov ax, [var]
    mov byte [es:0x00], 'L'
    ```

*   **$ and $$**
    Indicates the current instruction position after NASM compilation (`$` is the start of the current line, `$$` is the start of the current section);

*   **ptr**
    `ptr` -> pointer is an abbreviation for a pointer that is used to temporarily specify a type, which can be compared to a cast type conversion in C.

    ```asm
    mov ax, bx            ; Since registers ax and bx are both word type, there is no need to add word
    mov ax, word ptr [bx] ; Take the value at the memory address ds:bx, convert it to word type, and store it in ax
    ```

## Pseudo-directives

Pseudo-directives are not real directives, but exist for the convenience of the NASM assembler, but they have the same status as real directives.

*   **Data Size Directives**
    Usually exists between an action instruction and an operand, and is used to indicate the operand unit size used by the action instruction.

    | directive | Representative data size (bits) |
    | :-------- | :------------------------------ |
    | byte      | 8                               |
    | word      | 16                              |
    | dword     | 32                              |
    | qword     | 64                              |
    | tword     | 80                              |
    | oword     | 128                             |
    | yword     | 256                             |

*   **db Family: Define Initialized Data**
    A set of pseudo-directives to declare and initialize data:

    | directive | function                          | remark                                   |
    | :-------- | :-------------------------------- | :--------------------------------------- |
    | db        | Define byte data                  |                                          |
    | dw        | Define word data                  |                                          |
    | dd        | Define doubleword data            | You can define single-precision floats   |
    | dq        | Define quadword data              | You can define double-precision floats   |
    | dt        | Define ten-byte data (tword)      | You can define extended-precision floats |
    | do        | Define oword                      | You can define quad-precision floats     |
    | dy        | Define yword                      | YMM data can be defined                  |

    Note: dt, do, dy do not accept integer values.

*   **resb Family: Define Uninitialized Data**
    In contrast to the `db` family, directives from the `resb` family only declare an uninitialized memory space at compile time, but do not set an initial value for it.

    `resb`: reserve byte

    | directive | function                                   |
    | :-------- | :----------------------------------------- |
    | resb      | Declare a piece of uninitialized data in bytes |
    | resw      | Declare a piece of uninitialized data in words |
    | resd      | Declare a piece of uninitialized data in doublewords |
    | resq      | Declare a piece of uninitialized data in quadwords |
    | rest      | Declare a piece of uninitialized data in ten-bytes (tword) |
    | reso      | Declare a piece of uninitialized data in owords |
    | resy      | Declare a piece of uninitialized data in ywords |

*   **incbin: Include Binary Files**
    NASM provides a way to include binary files using the `incbin` pseudo-directive, which is used to contain data files such as graphics and sound.

*   **equ: Define a Constant**
    The `equ` pseudo-directive is used to assign an integer constant to an identifier, similar to the C `#define`:

    ```asm
    a equ 0             ; Correct
    b equ 'abcd'        ; Executable, b = 0x64636261
    c equ 'abcdefghi'   ; Executable will prompt warning, c = 0x64636261
    d equ 1.2           ; Error
    ```

    In this example, `b` and `c` store the ASCII code corresponding to the string, and since the integer constant is up to quadword (8 bytes), the string corresponding to `c` is automatically truncated to 'abcd'. `d`, on the other hand, stores non-integer values, so an error is reported.

*   **times: Repeat Execution**
    Used to repeat instructions (or pseudo-instructions), here's a classic example:

    ```asm
    ; Used for padding boot code
    times 510-($-$$) db 0
    dw 0xaa55
    ```

*   **Unicode Strings**
    NASM supports one or two operands to define Unicode strings:

    ```asm
    dw __utf16__('你好世界') ; You Good World (Hello World)
    dd __utf32__('你好世界') ; You Good World (Hello World)
    ```

## SECTION | SEGMENT: Custom Sections

In NASM, `SECTION` and `SEGMENT` directives are synonymous and can change which section the code is assigned to. In some object file formats, the number of sections is fixed; in other formats, users can customize the section to suit their needs.

This section uses NASM's `bin` output formats as an example to illustrate the usage of multiple sections.

NASM supports the standard `.data`, `.text`, `.bss` sections, and the order of the memory addresses in the program file after compilation is `.text`, `.data`, user sections. Sections with the same name will be placed in the same contiguous memory after compilation.

**Section Features:**

*   A section can be specified as `progbits` or `nobits`, defaulting to `progbits` (`.bss` defaults to `nobits`).
*   A section can be defined with `align` or `start` to specify the alignment byte. The difference is that `align` only accepts powers of 2, while `start` can accept any integer value. `align=start=`
*   A section can be defined with `vstart` that defines a virtual start address, which will be used to calculate all memory references within the section. `vstart=`
*   Sections can be sorted using `follows` or `vfollows` when defined. `follows=<section>`, `vfollows=<section>`
*   By default, all code before a explicitly defined section is stored in a `.text` section.
*   If no `ORG` statement is given, `ORG` defaults to zero.
*   Unless `start=`, `vstart=`, `follows`, or `vfollows` is specified explicitly, the `.bss` section will be placed after the last `progbits` section.
*   Unless the section explicitly specifies an alignment, all sections are aligned to a doubleword (4 bytes) boundary.
*   Sections must not overlap.
*   NASM provides a hidden label for each section to get the starting address of the section: `section.<secname>.start`.

**Expand:**

*   `progbits`: Program content, including code, data, and debugging-related information.
*   `nobits`: Similar to `PROGBITS`, the only difference is that it does not take up space in the file, and the corresponding memory space is allocated when loading.

```asm
db '11'
section test1 align=16
db '12'
section test2 start=12
db '13'
section test3 vstart=0x7c00
db '14'
section test4 follows=test1
db '15'
section .text start=100
db '16'
```

# Data Transfer Instructions

## Common Data Transfer Commands

*   mov
*   movsx
*   movzx
*   push
*   pop
*   pusha
*   popa
*   pushad
*   popad
*   bswap
*   xchg
*   cmpxchg
*   xadd
*   xlat

## Input and Output Port Instructions

*(No specific instructions listed in the source text for this section)*

## Arithmetic Instructions

The arithmetic operation instructions mainly include binary fixed-point, floating-point addition, subtraction, multiplication and division instructions; invert, complement, add one, subtract one, compare instructions; decimal addition and subtraction instructions, etc. The support for arithmetic instructions varies greatly from computer to computer.

*   **add**
    `add <Destination Operand>, <Source Operand>`

    Influence flags: OF, SF, ZF, AF, PF, CF.
    Add the source operand to the destination operand (the results are stored on the destination operand).
    The source and destination operands must be of the same type, and they cannot use memory operands at the same time.

*   **adc**
    `adc <Destination Operand>, <Source Operand>`

    The addition instruction with carry is basically the same as `ADD`, except that the value of the flag bit CF will be added to the destination operand before the instruction is executed, which is mostly used for multi-byte addition operations.

    ```asm
    mov DX, 0x2FFF
    mov AX, 0xFF00
    add AX, 0x5678
    adc dx, 0x1234
    ; The above instructions implement the addition of multi-byte numbers 0x2FFFFF00 and 0x12345678
    ; Where DX stores the higher part (0x2FFF) and AX stores the lower part (0xFF00)
    ; When executing the third step, the lower 16 bits are added: 0xFF00 + 0x5678 = 0x15578. The result stored in AX is 0x5578, and the carry flag CF is set to 1.
    ; When executing the fourth step, the higher 16 bits are added: 0x2FFF + 0x1234 = 0x4233. Then the carry from the carry flag (1) is added: 0x4233 + 1 = 0x4234. This result is stored in DX.
    ; Finally, we get 0x2FFFFF00 + 0x12345678 = 0x42345578
    ```

*   **inc**
    `inc <Destination Operand>`

    Add one command to add one to the value of the destination operand.

*   **sub**
    `sub <Destination Operand>, <Source Operand>`

    Subtract the source operand from the destination operand (the result is stored on the destination operand).
    The source and destination operands must be of the same type, and they cannot use memory operands at the same time.

*   **sbb**
    *(No explanation provided in source)*

*   **dec**
    `dec <Destination Operand>`

    Subtract one command to subtract one from the destination operand.

*   **neg**
    `neg <Destination Operand>`

    Used to find the two's complement of the destination operand (negation + 1).
    The destination operand can be a register or a memory location.

*   **cmp**
    Used to compare source and destination operands.

    The `CMP` instruction is similar to the `SUB` instruction, except that it does not save the result of the computation but affects the flag registers. Other instructions can determine the comparison result by checking these affected flag register bits.

    In the directive, the destination operand is the object being measured, and the source operand is used as the base for the measurement. The instruction performs the destination operand minus the source operand and affects the flag register without saving the result.

    The flags that will be affected are: overflow (OF), sign (SF), zero (ZF), carry (CF), auxiliary carry (AF), parity (PF).

    ```asm
    mov ax, 8
    mov bx, 3
    cmp ax, bx
    ; Execution result: ax = 8 | ZF = 0 | PF = 1 | SF = 0 | CF = 0 | OF = 0
    ```

*   aas
    *(No explanation provided in source)*
*   ads
    *(No explanation provided in source)*
*   **mul**
    `mul <Source Operand>`

    Unsigned multiplication, and the result is an integer.
    The `mul` instruction can accept an 8- or 16-bit multiplier via registers or memory locations:
    If the multiplier is 8 bits: then the result of multiplying the source operand by the 8 bits in register AL is stored in AX;
    If the multiplier is 16 bits: then the result of multiplying the source operand by the 16 bits in register AX is stored in DX:AX;

    After `mul` is executed, if the high part of the result is all zero, the OF and CF are cleared, otherwise they are set to one. The impact on the SF, ZF, AF, and PF flags is undefined.

*   imul
    *(No explanation provided in source)*
*   aam
    *(No explanation provided in source)*
*   **div**
    `div <Source Operand>`

    Used to perform unsigned division operations, the result is an integer (quotient and remainder).
    The divisor is passed in as a source operand and stored in registers or memory locations.
    By default, dividends are stored in AX (up to 16 bits) or AX and DX (32 bits, DX holds the high part, AX stores the low part).

    The result of the `div` operation is divided into quotient and remainder.
    If the divisor is 8 bits, then the quotient is stored in AL and the remainder is stored in AH.
    If the divisor is 16 bits, then the quotient is stored in AX and the remainder in DX.

    Execution conditions:

    *   The high part of the dividend must be less than the divisor (otherwise the quotient cannot be stored).
    *   If the divisor is 16 bits, the DX register needs to be zeroed before the `div` instruction can be run (unless the dividend is 16 bits or less).

*   idiv
    *(No explanation provided in source)*
*   aad
    *(No explanation provided in source)*
*   **cbw**
    Extends the highest bit of data in register AL into AH. AH is set to `00H` if the highest bit in AL is 0, and AH is set to `FFH` if the highest bit in AL is 1.

*   **cwd**
    Extends the highest bit of data in register AX into DX. DX is set to `0000H` if the highest bit in AX is 0, and DX is set to `FFFFH` if the highest bit in AX is 1.

*   cwde
    *(No explanation provided in source)*
*   cdq
    *(No explanation provided in source)*

# Logical Instructions

*   **and**
    `and <Destination Operand>, <Source Operand>`

    Performs a bitwise logical AND operation on the destination operand and source operand, and stores the result in the destination operand.

*   **or**
    `or <Destination Operand>, <Source Operand>`

    Performs a bitwise logical OR operation on the destination operand and the source operand, and stores the result in the destination operand.

*   **xor**
    `xor <Destination Operand>, <Source Operand>`

    Performs a bitwise logical XOR operation on the destination operand and the source operand, and stores the result in the destination operand.

*   **not**
    `not <Destination Operand>`

    Performs a bitwise logical NOT (inversion) on the destination operand, and stores the result in the destination operand.

*   **test**
    `test <Destination Operand>, <Source Operand>`

    Performs a bitwise logical AND operation on destination operands and source operands *without* storing the results. It only affects the flags.

*   **shl & sal**
    ```asm
    shl <Destination Operand> <Source Operand (Shift Count)>
    sal <Destination Operand> <Source Operand (Shift Count)>
    ```
    SHL (Shift Left Logical) and SAL (Shift Left Arithmetic) have exactly the same effect.
    The purpose of both is to shift the destination operand to the left by the source operand (shift count), filling the lowest bit(s) with 0 and shifting the highest displacement bit(s) into the carry flag (CF).

*   **shr & sar**
    ```asm
    shr <Destination Operand> <Source Operand (Shift Count)>
    sar <Destination Operand> <Source Operand (Shift Count)>
    ```
    SHR (Logical Right Shift) and SAR (Arithmetic Right Shift) are different:
    *   `shr`: The high bit(s) are filled with 0, and the low displacement bit(s) are moved into the carry flag (CF).
    *   `sar`: The high bit(s) are filled with the sign bit, and the low displacement bit(s) are moved into the carry flag (CF).

*   **rol**
    ```asm
    rol <Destination Operand>, <Source Operand (Shift Count)>
    ```
    rol (Rotate Left): Shifts the target operand to the left a specified number of times, wrapping the highest bit(s) around to the lowest bit(s) and also sending the last bit shifted out to the carry flag (CF).

*   **ror**
    ```asm
    ror <Destination Operand>, <Source Operand (Shift Count)>
    ```
    ror (Rotate Right): Shifts the destination operand to the right a specified number of times, wrapping the lowest bit(s) around to the highest bit(s) and also sending the last bit shifted out to the carry flag (CF).

*   rcr
    *(No explanation provided in source - Rotate Right through Carry)*
*   rcl
    *(No explanation provided in source - Rotate Left through Carry)*

# String Instructions

*   **movs (movsb, movsw, movsd, movsq)**
    ```asm
    movsw     ; Execute once
    rep movsw ; Use the rep command to repeat execution
    ```
    Serial transmission: Batch data is transferred from a source address to a destination address.
    In 16-bit mode, the source address is DS:SI, and the destination address is ES:DI.
    In 32-bit mode, the source address is DS:ESI, and the destination address is ES:EDI.
    In 64-bit mode, the source address is RSI, and the destination address is RDI.
    According to the size of the data transferred, it is divided into `movsb` (1 byte), `movsw` (1 word/2 bytes), `movsd` (doubleword/4 bytes), and `movsq` (quadword/8 bytes).

    The `movs` command can be executed repeatedly using repeat prefixes (`rep`, `repe`, `repne`). The direction flag DF determines whether the source/destination index registers (SI/RSI, DI/RDI) increase (DF=0, forward) or decrease (DF=1, backward) after a single operation.
    The size of each change depends on the specific execution command: `movsb` -> 1B | `movsw` -> 2B | `movsd` -> 4B | `movsq` -> 8B.

*   cmps
    *(No explanation provided in source - Compare String)*
*   scas
    *(No explanation provided in source - Scan String)*
*   lods
    *(No explanation provided in source - Load String)*
*   stos
    *(No explanation provided in source - Store String)*

*   **rep**
    ```asm
    rep movsw
    ```
    Repeat prefix instructions, which cannot be used alone. They can be used to repeat the following string instructions. The number of repetitions is controlled by the CX (or ECX/RCX) register (CX/ECX/RCX is decremented by one per repeat, stopping when the value is zero).

*   repe & repz
    *(No explanation provided in source - Repeat while Equal / Repeat while Zero)*
*   repne & repnz
    *(No explanation provided in source - Repeat while Not Equal / Repeat while Not Zero)*
*   repc
    *(No explanation provided in source - Repeat while Carry)*
*   repnc
    *(No explanation provided in source - Repeat while Not Carry)*

# Control Flow Instructions

Instructions that can modify the IP (Instruction Pointer) or modify the contents of both the CS (Code Segment) and IP registers are collectively referred to as transfer instructions. It can be popularly understood as an instruction that controls which instruction in memory the CPU executes next.

In 8086, according to the transfer behavior, it can be divided into:

*   **Intra-segment transfer:** Only the IP address is modified.
    *   Short transfer: IP modification range is -128 ~ 127 (8-bit displacement).
    *   Near Transfer: The IP modification range is -32768 ~ 32767 (16-bit displacement).
*   **Intersegment Transfer (Far Transfer):** Modify both CS and IP at the same time.

According to different functions, transfer instructions can be subdivided into the following types:

## Unconditional Jump Instructions

**Description:** The unconditional transfer instruction can control the next execution of the instruction corresponding to any memory address in the code segment (CS) by the CPU.

*   **offset**
    Operator, handled by the compiler, whose function is to get the offset address of the label.

    ```asm
    start: mov ax,offset start ; Equivalent to mov ax,0
    next: mov ax,offset next ; Equivalent to mov ax,3 | The length of the first instruction is three bytes, so the offset address of next is 3
    ```

*   **jmp**
    **Description:** The transfer destination address can be indicated in the instruction itself (as a label), a memory location, or a register. You can modify only the IP (intra-segment jump) or modify both CS and IP (intersegment jump).

    There are two types of information that you need to provide when using JMP instructions:
    *   The destination address of the transfer.
    *   The type of transfer (intersegment transfer (far jump), intrasegment short jump, intrasegment near jump).

    **Syntax:**

    ### Jump to a Label

    *   **Syntax:** `jmp short <label>`
        **Description:** This format of `JMP` instructions implements intra-segment short jumps, with `short` being the short jump flag.
        **Principle:** `ip = ip + 8-bit displacement`. The 8-bit offset = label address - the address of the first byte after the JMP instruction.
        This instruction redirects to the current instruction position (i.e., the current IP). The 8-bit displacement range is -128 to 127, which is calculated by the compiler at compile time.
        **Example:**
        ```asm
        start:
            mov ax,0
            jmp short next
            add ax,1
        next:
            inc ax
        ; Final result: the value inside ax is 1
        ```

    *   **Syntax:** `jmp near ptr <label>`
        **Description:** JMP instructions in this format implement a near-shift within a segment, with `near ptr` being the near-shift flag.
        **Principle:** `ip = ip + 16-bit displacement`. The 16-bit offset = label address - the address of the first byte after the JMP instruction.
        This instruction also redirects relative to the current instruction position (i.e., the current IP). The 16-bit displacement range is -32768 to 32767, which is calculated by the compiler at compile time.

    *   **Syntax:** `jmp far ptr <label>`
        **Description:** JMP instructions in this format implement inter-segment transfer (i.e., far jump), with `FAR PTR` as the far-jump flag.
        **Principle:** `cs = the segment address of the segment where the label belongs` | `ip = offset in the segment in which the label is located`. This type of jump usually involves the address being stored as a segment:offset pair, with the higher memory location storing the segment address and the lower location storing the offset address.

    ### Jump to an Address in Memory

    *   **Syntax:** `jmp word ptr <[memory_address]>`
        **Description:** JMP instructions in this format implement intra-segment transfers, and `Word PTR` indicates that the destination address is a 16-bit offset.
        **Principle:** `ip = value stored in the memory address`.

    *   **Syntax:** `jmp dword ptr <[memory_address]>`
        **Description:** JMP instructions in this format implement inter-segment transfers (i.e., far-jumps), with `dword ptr` indicating that the destination address is a 32-bit segment:offset pair.
        **Principle:** `cs = content stored at (memory_address + 2)` | `ip = content stored at (memory_address)`. (Note: This assumes the segment is stored after the offset at the memory address).
        **Example:**
        ```asm
        mov ax,0123H
        mov ds:[0],ax         ; Store 0123H (offset) at DS:0
        mov word ptr ds:[2],0 ; Store 0000H (segment) at DS:2
        jmp dword ptr ds:[0]  ; Jump to the dword at DS:0 (which is 0000:0123H)
        ; After execution: cs = 0 | ip = 0123H
        ```
        *(Note: In practice, for 32/64-bit flat memory models, segment registers are often less directly manipulated for jumps unless dealing with protected mode segments or specific OS structures. This example reflects an older segmented memory model context).*

    ### Jump to an Address in a Register

    *   **Syntax:** `jmp <16-bit register>`
        **Description:** JMP instructions in this format implement intra-segment transfers.
        **Principle:** `IP = content of the 16-bit register`.

    *   **Syntax:** `jmp <[segment_register:offset_register]>`
        **Description:** This syntax looks like a jump to an address *pointed to* by a segment and offset register combination, rather than the content of a single register. It would typically be used with memory addressing. *Assuming the source text intends an inter-segment jump using registers:* This could potentially load CS and IP from a memory location whose address is calculated from segment:offset registers (less common syntax), or it might be a less precise description of loading a far pointer from memory into a register pair or stack before a different type of far jump. Given the ambiguity and common usage, `jmp reg` is the primary "jump to address in register" form (intra-segment).

## Conditional Jump Instructions

Instructions that jump only if specific flags are set or clear after a previous operation (like `CMP`, arithmetic, etc.).

*   **jz (je) & jnz (jne) | Zero judgment (equality judgment)**
    `JZ` and `JE` mean the same thing, just are different mnemonics (Jump if Zero / Jump if Equal).
    `JNZ` and `JNE` mean the same thing (Jump if Not Zero / Jump if Not Equal).

    *   `jz`: If the flag bit ZF = 1, it will jump to the specified address.
    *   `jnz`: If the flag bit ZF = 0, it will jump to the specified address.

    `ZF`: zero flag, indicates whether the result of the relevant command was zero | 0 -> No | 1 -> Yes.

*   **jc & jnc | Carry judgment**
    *   `jc`: If the flag bit CF = 1, it will jump to the specified address.
    *   `jnc`: If the flag bit CF = 0, the specified address is redirected.

    `CF`: Carry flag, indicates whether a carry or borrow was generated after the execution of the relevant instruction | 0 -> did not produce | 1 -> generated.

*   **jp (jpe) & jnp (jpo) | Parity judgment**
    `JP` and `JPE` mean the same thing (Jump if Parity / Jump if Parity Even).
    `JNP` and `JPO` mean the same thing (Jump if Not Parity / Jump if Parity Odd).

    *   `jp`: If the flag bit PF = 1, it will jump to the specified address.
    *   `jnp`: If the flag bit PF = 0, it will jump to the specified address.

    `PF`: the parity flag bit, indicates whether the number of set bits (1s) in the low byte of the result after the execution of the relevant instruction is an even number | 0 -> odd parity | 1 -> even parity.

*   **js & jns | Sign judgment**
    *   `js`: If the flag bit SF = 1, it will jump to the specified address.
    *   `jns`: If the flag bit SF = 0, the specified address is redirected.

    `SF`: the sign flag bit, indicates whether the result of the relevant command is negative | 0 -> non-negative | 1 -> negative number.

*   **jo & jno | Overflow judgment**
    *   `jo`: If the flag bit OF = 1, it will jump to the specified address.
    *   `jno`: If the flag bit OF = 0, the specified address is redirected.
    *(Note: the source text had `jnp` here, corrected to `jno`)*

    `OF`: overflow flag, indicates whether the result of a *signed* arithmetic operation produced overflow | 0 -> No | 1 -> Yes.

## Processor Control Instructions

Processor control instructions include flag operation instructions and CPU control instructions.

### Flag Operation Instructions

*   **stc & clc & cmc**
    *   `stc`: Set CF to 1.
    *   `clc`: Set CF to 0.
    *   `cmc`: Complement (Negate) CF (If CF was 0, make it 1; if CF was 1, make it 0).
    `CF`: Carry flag.

*   **std & cld**
    *   `std`: Set DF to 1.
    *   `cld`: Set DF to 0.
    `DF`: Direction flag. In string processing instructions (`movs`, `cmps`, etc.), determines whether the index registers (SI/RSI, DI/RDI) auto-increment (DF=0, forward) or auto-decrement (DF=1, backward) after each operation.

*   **sti & cli**
    *   `sti`: Set IF to 1 (Enable Interrupts).
    *   `cli`: Set IF to 0 (Disable Interrupts).
    `IF`: Interrupt allow flag. Controls whether the CPU can respond to external maskable interrupt requests.

