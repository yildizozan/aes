#include <cstdio>
#include <cstdlib>
#include <ctime>

#include <aes.h>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */


int main(int argc, char *argv[]) {

    printf("Hello, World!\n");

    {
        uint8_t flag = 1;

        state_t input = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0xfe};
        state_t expected = {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0xbb};

        printf("%s%s Test%s\n", BLUE, "SubstitutionBytes", RESET);

        Debug("State:", input, 16);
        SubstitutionBytes(&input);
        Debug("Result:", input, 16);

        for (int i = 0; i < 16; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        Debug("Expect:", expected, 16);
        if (flag) {
            printf("%s%s equal! %s\n", GREEN, "SubstitutionBytes", RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, "SubstitutionBytesWord", RESET);
        }

        printf("-----------------------------------\n");
    }
    {
        uint8_t flag = 1;
        // This is major-column order matrix
        state_t input = {
                0x63, 0x2F, 0xAF, 0xA2, 0xEB, 0x93, 0xC7, 0x20, 0x9F, 0x92, 0xAB, 0xCB, 0xA0, 0xC0, 0x30, 0x2B
        };
        state_t expected = {
                0xBA, 0x75, 0xF4, 0x7A, 0x84, 0xA4, 0x8D, 0x32, 0xE8, 0x8D, 0x06, 0x0E, 0x1B, 0x40, 0x7D, 0x5D
        };

        printf("%s%s Test%s\n", BLUE, "MixColumnsNew", RESET);

        Debug("State:", input, 16);
        MixColumnsNew(&input);
        Debug("Result:", input, 16);

        for (int i = 0; i < 16; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        Debug("Expect:", expected, 16);
        if (flag) {
            printf("%s%s equal! %s\n", GREEN, "MixColumnsNew", RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, "MixColumnsNew", RESET);
        }

        printf("-----------------------------------\n");
    }
    {
        uint8_t flag = 1;
        // This is major-column order matrix
        state_t input = {
                0x63, 0x2F, 0xAF, 0xA2, 0xEB, 0x93, 0xC7, 0x20, 0x9F, 0x92, 0xAB, 0xCB, 0xA0, 0xC0, 0x30, 0x2B
        };
        state_t expected = {
                0xBA, 0x75, 0xF4, 0x7A, 0x84, 0xA4, 0x8D, 0x32, 0xE8, 0x8D, 0x06, 0x0E, 0x1B, 0x40, 0x7D, 0x5D
        };

        printf("%s%s Test%s\n", BLUE, "MixColumnsLookupTable", RESET);

        Debug("State:", input, 16);
        MixColumnsLookupTable(&input);
        Debug("Result:", input, 16);

        for (int i = 0; i < 16; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        Debug("Expect:", expected, 16);
        if (flag) {
            printf("%s%s equal! %s\n", GREEN, "MixColumnsLookupTable", RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, "MixColumnsLookupTable", RESET);
        }

        printf("-----------------------------------\n");
    }
    {
        uint8_t flag = 1;
        // This is major-column order matrix
        state_t expected = {
                0x63, 0x2F, 0xAF, 0xA2, 0xEB, 0x93, 0xC7, 0x20, 0x9F, 0x92, 0xAB, 0xCB, 0xA0, 0xC0, 0x30, 0x2B
        };
        state_t input = {
                0xBA, 0x75, 0xF4, 0x7A, 0x84, 0xA4, 0x8D, 0x32, 0xE8, 0x8D, 0x06, 0x0E, 0x1B, 0x40, 0x7D, 0x5D
        };

        printf("%s%s Test%s\n", BLUE, "MixRColumnsLookupTable", RESET);

        Debug("State:", input, 16);
        MixRColumnsLookupTable(&input);
        Debug("Result:", input, 16);

        for (int i = 0; i < 16; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        Debug("Expect:", expected, 16);
        if (flag) {
            printf("%s%s equal! %s\n", GREEN, "MixRColumnsLookupTable", RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, "MixRColumnsLookupTable", RESET);
        }

        printf("-----------------------------------\n");
    }
    {
        uint8_t flag = 1;
        // This is major-column order matrix
        uint8_t input[16] = {0x54, 0x68, 0x61, 0x74, 0x73, 0x20, 0x6D, 0x79, 0x20, 0x4B, 0x75, 0x6e, 0x67, 0x20, 0x46, 0x75};
        uint8_t expected[16] = {0xE2, 0x32, 0xFC, 0xF1, 0x91, 0x12, 0x91, 0x88, 0xB1, 0x59, 0xE4, 0xE6, 0xD6, 0x79, 0xA2, 0x93};
        printf("%s%s Test%s\n", BLUE, "key_expansion", RESET);

        Debug("State:", input, 16);
        key_expansion(0, input);
        Debug("Result:", input, 16);

        for (int i = 0; i < 16; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        Debug("Expect:", expected, 16);
        if (flag) {
            printf("%s%s equal! %s\n", GREEN, "key_expansion", RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, "key_expansion", RESET);
        }

        printf("-----------------------------------\n");
    }
    {
        uint8_t flag = 1;
        // This is major-column order matrix
        state_t input = {0x04, 0x66, 0x81, 0xE5, 0xE0, 0xCB, 0x19, 0x9A, 0x48, 0xF8, 0xD3, 0x7A, 0x28, 0x06, 0x26, 0x4C};
        uint8_t key[16] = {0xA0, 0xFA, 0xFE, 0x17, 0x88, 0x54, 0x2C, 0xB1, 0x23, 0xA3, 0x39, 0x39, 0x2A, 0x6C, 0x76, 0x05};
        state_t expected = {0xA4, 0x9C, 0x7F, 0xF2, 0x68, 0x9F, 0x35, 0x2B, 0x6B, 0x5B, 0xEA, 0x43, 0x02, 0x6A, 0x50, 0x49};

        printf("%s%s Test%s\n", BLUE, "AddRoundKey", RESET);

        Debug("State:", input, 16);
        Debug("RndKey:", key, 16);
        AddRoundKey(&input, key);
        Debug("Result:", input, 16);

        for (int i = 0; i < 16; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        Debug("Expect:", expected, 16);
        if (flag) {
            printf("%s%s equal! %s\n", GREEN, "AddRoundKey", RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, "AddRoundKey", RESET);
        }

        printf("-----------------------------------\n");
    }

    return 0;
}
