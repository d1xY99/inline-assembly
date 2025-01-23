# x86-64 Inline Assembly

## Overview
Exploration of inline assembly and System V AMD64 ABI calling conventions.

### CPUID Instruction
- Read CPU information using `cpuid` instruction
- Retrieve:
  - Manufacturer ID string
  - Processor brand string
- Check CPU feature support flags:
  - SSE
  - MSR
  - CMOV
  - AVX
  - AVX2
  - VMX
  - FMA
  - HYBRID

### Calling Conventions
#### Part A: Function Call in Assembly
- Implemented function call using inline assembly
- Follow System V AMD64 ABI
- Manage register clobbering

#### Part B: Prime Function in Assembly
- Implemented Prime calculation function
- Follow System V AMD64 calling convention

## Build Instructions
```bash
mkdir build
cd build
cmake ..
make
```

## Debugging
- Use GDB with PEDA plugin
- Inspect register contents

## Resources
- CPUID instruction documentation
- System V AMD64 ABI specification
- GCC inline assembly documentation

## Requirements
- x86-64 Linux environment
- GCC compiler
- CMake
