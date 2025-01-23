#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Implement the given function (see the wiki) in the sysv_abi.S file
int isPrime(int num) {
    int result;
    __asm__ __volatile__ (
        "movl $0, %%eax\n\t"           // Default to not prime
        "cmpl $2, %1\n\t"               // Compare input with 2
        "jl .end\n\t"                   // Less than 2 is not prime
        "je .prime\n\t"                 // 2 is prime
        "testl $1, %1\n\t"              // Check if even
        "jz .end\n\t"                   // Even numbers (except 2) are not prime

        "movl $3, %%ecx\n\t"            // Start divisor at 3
        "movl %1, %%eax\n\t"            // Copy input 
        "sqrtl %%eax\n\t"               // Get square root

        ".divisibility_loop:\n\t"
        "cmpl %%ecx, %%eax\n\t"         // Compare divisor with sqrt(num)
        "jl .prime\n\t"                 // If divisor > sqrt(num), it's prime

        "movl %1, %%edx\n\t"            // Dividend
        "movl %%ecx, %%eax\n\t"         // Divisor
        "xorl %%edx, %%edx\n\t"         // Clear remainder
        "divl %%ecx\n\t"                // Divide input by current divisor

        "testl %%edx, %%edx\n\t"        // Check remainder
        "jz .end\n\t"                   // If remainder is 0, not prime

        "addl $2, %%ecx\n\t"            // Next odd divisor
        "jmp .divisibility_loop\n\t"

        ".prime:\n\t"
        "movl $1, %%eax\n\t"            // Return 1 (true)

        ".end:\n\t"
        : "=a" (result)                 // Output operand
        : "r" (num)                     // Input operand
        : "%ecx", "%edx"                // Clobbered registers
    );
    return result;
}

int main(int argc, char **argv)
{
    setbuf(stdout, NULL); // Disable buffering

    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <number>\n", argv[0]);
        return 1;
    }

    int number = atoi(argv[1]);
    printf("%d %s\n", number, isPrime(number) ? "is a prime number" : "is not a prime number");

    return 0;
}
