.global isPrime
isPrime:

    pushq %rbx
    pushq %rbp
    pushq %r12
    pushq %r13
    pushq %r14
    pushq %r15
    
//    movq $0, %rdi
//  movl %ecx, %edi
    

    cmp $1, %rdi
    jbe 0f

    cmp $4, %rdi
    je 0f
    
    cmp $5, %rdi
    jbe 1f

    // Check if num is divisible by 2, 3, or 5
    
    movq $0, %rdx
    movq %rdi, %rax
    movl $2, %ebx
    movl %edx, %ecx         
    idivl %ebx              
    testl %edx, %edx
    je 0f                  

    movq $0, %rdx
    movq %rdi, %rax
    movl $3, %ebx
    movl %edx, %ecx         
    idivl %ebx              
    testl %edx, %edx
    je 0f                   
    movq $0, %rdx
    movq %rdi, %rax
    movl $5, %ebx
    movl %edx, %ecx         
    idivl %ebx              
    testl %edx, %edx
    je 0f                   // If the remainder is 0, set result to 0 and exit
    
    movq $5, %rcx
    
    2:
    movq $0, %rbx
	movl %ecx, %ebx
    imul %ebx, %ebx
    cmp %ebx, %edi
    jb 1f
    
    
    // rdi % ecx == 0 || rdi % (ecx + 2) == 0 -> return 0
    
    movq $0, %rdx
    movq %rdi, %rax
    movl %ecx, %ebx
    idivl %ebx
    testl %edx, %edx
    je 0f
    
    movq $0, %rdx
    movq %rdi, %rax
    movl %ecx, %ebx
    addl $2, %ebx
    idivl %ebx
    testl %edx, %edx
    je 0f
    
    addl $6, %ecx
    
    jmp 2b
    
    
    0:
    movl $0, %eax
    jmp 4f

    1:
    movl $1, %eax
    jmp 4f

    
    4:
    // Restore callee-saved registers
    popq %r15
    popq %r14
    popq %r13
    popq %r12
    popq %rbp
    popq %rbx

    ret