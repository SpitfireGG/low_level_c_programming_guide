# Pointers

Pointers are C’s superpower—direct memory control. Master them, and you own the machine.

## 1. What’s a Pointer?
- **Definition**: Variable holding a memory address.
- **Syntax**: `int *p;`—`p` points to an `int`.
- **Read**: Right-to-left—`p` is a pointer to an `int`.
- **Size**: 8 bytes (64-bit)—e.g., `0x7fff5fbff8c0`.

**Example**:
```c
int x = 10;
int *p = &x; // &x = address of x
*p = 20;     // x now 20
