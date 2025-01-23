#include <stdio.h>
#include <stdint.h>
// There is nothing to do in this file.
// Changes in this file will not be considered in the test system.

// This function has to be called.
/**
 * @brief Replaces all occurrences of the character 'find' in the string 'string' with the character 'replace'.
 *
 * @param string      Pointer to the input string where replacements will be performed.
 * @param string_len  The length of the input string.
 * @param find        The character to be replaced in the string.
 * @param replace     The character that will replace 'find' in the string.
 *
 * @return             The number of replacements made in the string
 */
int32_t replaceChars(char* string, size_t string_len, const char* find, const char* replace) 
{
    printf("Function called with parameters: string=%p, string_len=%zu, find=%p, replace=%p\n",
           string, string_len, find, replace);

    if (string == NULL || find == NULL || replace == NULL)
        return 0;

    int32_t replacements = 0;

    for (size_t i = 0; i < string_len; i++) {
        if (string[i] == *find) 
        {
            string[i] = *replace;
            replacements++;
        }
    }

    return replacements;
}