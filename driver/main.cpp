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
                0xBA, 0x75, 0xF4, 0x7A, 0x84, 0xA4, 0x8D, 0x32, 0xE8, 0x8D, 0x06, 0x0E, 0x1B, 0x40, 0x7D, 0x5D
        };
        state_t input = {
                0xBA, 0x75, 0xF4, 0x7A, 0x84, 0xA4, 0x8D, 0x32, 0xE8, 0x8D, 0x06, 0x0E, 0x1B, 0x40, 0x7D, 0x5D
        };

        printf("%s%s Test%s\n", BLUE, "InverseMixColumnsLookupTable", RESET);

        Debug("State:", input, 16);
        MixColumnsLookupTable(&input);
        InverseMixColumnsLookupTable(&input);
        Debug("Result:", input, 16);

        for (int i = 0; i < 16; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        Debug("Expect:", expected, 16);
        if (flag) {
            printf("%s%s equal! %s\n", GREEN, "InverseMixColumnsLookupTable", RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, "InverseMixColumnsLookupTable", RESET);
        }

        printf("-----------------------------------\n");
    }
    {
        uint8_t flag = 1;
        // This is major-column order matrix
        uint8_t expected[4][44] = {
                0x2B, 0x28, 0xAB, 0x09, 0xA0, 0x88, 0x23, 0x2A, 0xF2, 0x7A, 0x59, 0x73, 0x3D, 0x47, 0x1E, 0x6D, 0xEF, 0xA8, 0xB6, 0xDB, 0xD4, 0x7C, 0xCA, 0x11, 0x6D, 0x11, 0xDB, 0xCA, 0x4E, 0x5F, 0x84, 0x4E, 0xEA, 0xB5, 0x31, 0x7F, 0xAC, 0x19, 0x28, 0x57, 0xD0, 0xC9, 0xE1, 0xB6,
                0x7E, 0xAE, 0xF7, 0xCF, 0xFA, 0x54, 0xA3, 0x6C, 0xC2, 0x96, 0x35, 0x59, 0x80, 0x16, 0x23, 0x7A, 0x44, 0x52, 0x71, 0x0B, 0xD1, 0x83, 0xF2, 0xF9, 0x88, 0x0B, 0xF9, 0x00, 0x54, 0x5F, 0xA6, 0xA6, 0xD2, 0x8D, 0x2B, 0x8D, 0x77, 0xFA, 0xD1, 0x5C, 0x14, 0xEE, 0x3F, 0x63,
                0x15, 0xD2, 0x15, 0x4F, 0xFE, 0x2C, 0x39, 0x76, 0x95, 0xB9, 0x80, 0xF6, 0x47, 0xFE, 0x7E, 0x88, 0xA5, 0x5B, 0x25, 0xAD, 0xC6, 0x9D, 0xB8, 0x15, 0xA3, 0x3E, 0x86, 0x93, 0xF7, 0xC9, 0x4F, 0xDC, 0x73, 0xBA, 0xF5, 0x29, 0x66, 0xDC, 0x29, 0x00, 0xF9, 0x25, 0x0C, 0x0C,
                0x16, 0xA6, 0x88, 0x3C, 0x17, 0xB1, 0x39, 0x05, 0xF2, 0x43, 0x7A, 0x7F, 0x7D, 0x3E, 0x44, 0x3B, 0x41, 0x7F, 0x3B, 0x00, 0xF8, 0x87, 0xBC, 0xBC, 0x7A, 0xFD, 0x41, 0xFD, 0x0E, 0xF3, 0xB2, 0x4F, 0x21, 0xD2, 0x60, 0x2F, 0xF3, 0x21, 0x41, 0x6E, 0xA8, 0x89, 0xC8, 0xA6,
        };
        uint8_t key[16] = {0x2B, 0x7E, 0x15 , 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C};
        uint8_t w[4][44] = {0};
        printf("%s%s Test%s\n", BLUE, "key_expansion", RESET);

        Debug("Key:", key, 16);
        key_expansion(key, w);
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 44; ++j) {
                printf("0x%02X, ", w[i][j]);
                if (w[i][j] != expected[i][j]) {
                    flag = 0;
                    break;
                }
            }
            printf("\n");
        }


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
    {
        char test_name[] = "ShiftRows";
        uint8_t flag = 1;
        // This is major-column order matrix
        state_t input = {
                0xD4, 0x27, 0x11, 0xAE,
                0xE0, 0xBF, 0x98, 0xF1,
                0xB8, 0xB4, 0x5D, 0xE5,
                0x1E, 0x41, 0x52, 0x30,
        };
        state_t expected = {
                0xD4, 0xBF, 0x5D, 0x30,
                0xE0, 0xB4, 0x52, 0xAE,
                0xB8, 0x41, 0x11, 0xF1,
                0x1E, 0x27, 0x98, 0xE5,
        };
        printf("%s%s Test%s\n", BLUE, test_name, RESET);

        ShiftRows(&input);
        Debug("Result:", input, 16);

        size_t index_input = 0, index_expected = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                printf("%02X\t", input[index_input++]);
            }
            printf("\t=>\t");
            for (int j = 0; j < 4; ++j) {
                printf("%02X\t", expected[index_expected++]);
            }
            printf("\n");
        }

        for (int i = 0; i < Nb * Nk; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            printf("%s%s equal! %s\n", GREEN, test_name, RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, test_name, RESET);
        }

        printf("-----------------------------------\n");
    }
    {
        char test_name[] = "InversveShiftRows";
        uint8_t flag = 1;
        // This is major-column order matrix
        state_t input = {
                0xD4, 0x27, 0x11, 0xAE,
                0xE0, 0xBF, 0x98, 0xF1,
                0xB8, 0xB4, 0x5D, 0xE5,
                0x1E, 0x41, 0x52, 0x30,
        };
        state_t expected = {
                0xD4, 0x27, 0x11, 0xAE,
                0xE0, 0xBF, 0x98, 0xF1,
                0xB8, 0xB4, 0x5D, 0xE5,
                0x1E, 0x41, 0x52, 0x30,
        };
        printf("%s%s Test%s\n", BLUE, test_name, RESET);

        ShiftRows(&input);
        InversveShiftRows(&input);
/*
        size_t index_input = 0, index_expected = 0;
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j) {
                printf("%02X\t", input[index_input++]);
            }
            printf("\t=>\t");
            for (int j = 0; j < 4; ++j) {
                printf("%02X\t", expected[index_expected++]);
            }
            printf("\n");
        }
*/
        for (int i = 0; i < Nb * Nk; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        if (flag) {
            printf("%s%s equal! %s\n", GREEN, test_name, RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, test_name, RESET);
        }

        printf("-----------------------------------\n");
    }

    return 0;
}
