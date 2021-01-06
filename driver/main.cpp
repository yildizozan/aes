#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <aes.h>

int main(int argc, char *argv[]) {

    printf("Hello, World!\n");

    {
        uint8_t flag = 1;
        // This is major-column order matrix
        state_t input = {
                0x63, 0x2F, 0xAF, 0xA2, 0xEB, 0x93, 0xC7, 0x20, 0x9F, 0x92, 0xAB, 0xCB, 0xA0, 0xC0, 0x30, 0x2B
        };
        state_t expected = {
                0xBA, 0x75, 0xF4, 0x7A, 0x84, 0xA4, 0x8D, 0x32, 0xE8, 0x8D, 0x06, 0x0E, 0x1B, 0x40, 0x7D, 0x5D
        };

        printf("%s%s Test%s\n", BLUE, "MixColumns", RESET);

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
        uint8_t input[] = {
                0x2B, 0x7E, 0x15, 0x16, 0x28, 0xAE, 0xD2, 0xA6, 0xAB, 0xF7, 0x15, 0x88, 0x09, 0xCF, 0x4F, 0x3C
        };
        state_t expected = {
                0xA0, 0xFA, 0xFE, 0x17, 0x88, 0x54, 0x2C, 0xB1, 0x23, 0xA3, 0x39, 0x39, 0x2A, 0x6C, 0x76, 0x05
        };

        printf("%s%s Test%s\n", BLUE, "KeyExpand", RESET);

        Debug("State:", input, 16);
        KeyExpand(0, input);
        Debug("Result:", input, 16);

        for (int i = 0; i < 16; ++i) {
            if (input[i] != expected[i]) {
                flag = 0;
                break;
            }
        }

        Debug("Expect:", expected, 16);
        if (flag) {
            printf("%s%s equal! %s\n", GREEN, "KeyExpand", RESET);
        } else {
            printf("%s%s not equal!%s\n", RED, "KeyExpand", RESET);
        }

        printf("-----------------------------------\n");
    }
    {
        uint8_t flag = 1;
        // This is major-column order matrix
        state_t input = {
                0x04, 0x66, 0x81, 0xE5, 0xE0, 0xCB, 0x19, 0x9A, 0x48, 0xF8, 0xD3, 0x7A, 0x28, 0x06, 0x26, 0x4C
        };
        uint8_t key[16] = {
                //0xE2, 0x32, 0xFC, 0xF1, 0x91, 0x12, 0x91, 0x88, 0xB1, 0x59, 0xE4, 0xE6, 0x07, 0x03, 0x79, 0x63
                0xA0, 0xFA, 0xFE, 0x17, 0x88, 0x54, 0x2C, 0xB1, 0x23, 0xA3, 0x39, 0x39, 0x2A, 0x6C, 0x76, 0x05
        };
        state_t expected = {
                0xA4, 0x9C, 0x7F, 0xF2, 0x68, 0x9F, 0x35, 0x2B, 0x6B, 0x5B, 0xEA, 0x43, 0x02, 0x6A, 0x50, 0x49
        };

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
