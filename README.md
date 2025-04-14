# C_guides: Learning C Programming In-Depth
This repo is specially for learning to program in a low-level langauage and fully understand the concepts , this repo might not be well structured for reading because all the things i keep learning is for fun and is altered in some  ways like somethings are not covered while others might be covered to the depths of hell


## Project Structure

- **src/**: Source code organized by topic:
  - **basics/**: Fundamentals like pointers, structs, bit operations, and macros.
  - **advanced/**: Memory allocation, threading, and atomic operations.
  - **dsa/**: Data structures (linked lists, hashmaps, stacks, queues).
  - **networking/**: Network programming, including adapter info and a basic web server.
- **notes/**: Detailed explanations of concepts (e.g., allocation, structs).
- **scripts/**: Utility scripts for building and debugging (`build.sh`, `debug.sh`).

## Data Structures and Algorithms

The `/dsa/` directory contains implementations of common data structures:
- **LinkedList/**: Singly and chained linked lists (`linked_list.c`, `chained_ll.c`).
- **HashMap/**: Basic key-value store (`hashmap.c`, `hashmap.h`).
- **Set/**: Unique element collection (`set.c`).
- **Stack_Queue/**: Stack (`stack.c`) and queue (`queue.c`, `generic_queue.c`) implementations.

More data structures are planned for future updates.

## Progress

- [x] **Memory Allocation**: Dynamic memory management with `malloc`, `free`, etc. (`/advanced/allocation/`, `notes/allocation.md`).
- [x] **Structs**: Pointers, packing, and alignment (`/basics/structs/`, `notes/structs.md`).
- [ ] **System Calls**: Kernel-level interactions (work in progress).

## Currently writing

- Developing a **network frame sniffer** in `/networking/` to capture and analyze packets in a CLI, inspired by tools like Wireshark.
- Exploring low-level programming concepts, such as bit manipulation and memory optimization.

## Getting Started

1. Clone the repository:
   ```bash
   git clone <repository-url>
