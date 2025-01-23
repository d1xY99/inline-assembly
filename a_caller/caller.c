#include <stdio.h>
#include <string.h>
#include <memory.h>
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
// Implement the function call in assembly in the TODO section below.
// Do not change the functionality or the signature of the function to be called.
// Do not modify this file outside the TODO section.

// Function to be called:
int32_t replaceChars(char* string, size_t string_len, const char* find, const char* replace);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL); // Disable buffering

    if (argc != 4)
    {
        fprintf(stderr, "Usage: %s <string> <char>\n", argv[0]);
        return 1;
    }

    char *string = argv[1];
    size_t string_len = strlen(string);
    char find = *(argv[2]);
    char replace = *(argv[3]);
    int32_t replaced = 0;

    printf("Calling function with parameters: string=%p, string_len=%zu, find=%p, replace=%p\n",
           string, string_len, &find, &replace);

    // Use (only!) GCC inline assembly to call `replaceChar`. Always consider the expected data types.
    // Parameters: string, string_len, find, replace
    // Store the return value in replaced

    // ########## TODO START ##########
    // System V AMD64 ABI implementation (64-bit)
    asm volatile (
        "pushq %%rbx\n"
        "pushq %%rcx\n"
        "pushq %%rdi\n"
        "pushq %%rsi\n"
        "pushq %%r8\n"
        "pushq %%r9\n"
        
        "movq %[str], %%rdi\n"
        "movq %[len], %%rsi\n"
        "movq %[f], %%rdx\n"
        "movq %[r], %%rcx\n"
        "call replaceChars\n"
        
        "movl %%eax, %[replaced]\n"

        "popq %%r9\n"
        "popq %%r8\n"
        "popq %%rsi\n"
        "popq %%rdi\n"
        "popq %%rcx\n"
        "popq %%rbx\n"
        : [replaced] "=r"(replaced)
        : [str] "r"(string), [len] "r"(string_len), [f] "r"(&find), [r] "r"(&replace)
        : "rdi", "rsi", "rdx", "rcx", "r8", "r9", "memory"
);
    // ########## TODO END ##########

    printf("Function returned: Replaced %d characters\n", replaced);
    printf("Resulting string: %s\n", string);

    return 0;
}
