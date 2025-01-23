#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Implement the given function (see the wiki) in the sysv_abi.S file
int isPrime(int num);

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
