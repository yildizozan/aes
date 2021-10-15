#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>
#include <unistd.h>

#include <aes.h>


#define STRIP_FLAG_HELP 1

#include <gflags/gflags.h>

DEFINE_bool(verbose, false, "Display program name before message");

DEFINE_string(in, "", "Message or cipher data");
DEFINE_string(out, "out.txt", "Output file");
DEFINE_string(message, "", "Message to encrypt");
DEFINE_string(key, "", "Encryption key");

// Encryption or Decryption
DEFINE_bool(encrypt, false, "AES encryption");
DEFINE_bool(decrypt, false, "AES decryption");

// Modes
DEFINE_bool(ecb, false, "Electronic Cook Book");
DEFINE_bool(cbc, false, "Cipher-Block Crypto it will need to IV");
DEFINE_bool(ofb, false, "Cipher-Block Crypto it will need to IV");

DEFINE_string(iv, "", "Initialization Vector (16chars)");

/**
 *
 * @param flagname
 * @param value
 * @return
 */
static bool IsNonEmptyMessage(const char *flagname, const std::string &value) {
    return value[0] != '\0';
}

/**
 *
 * @param flagname
 * @param value
 * @return
 */
static bool KeyValidator(const char *flagname, const std::string &value) {
    return value[0] != '\0' && value.size() == 16;
}

//DEFINE_validator(in, &IsNonEmptyMessage);
//DEFINE_validator(message, &IsNonEmptyMessage);

DEFINE_validator(key, &KeyValidator);

int main(int argc, char *argv[]) {
    gflags::SetUsageMessage("Hello, World! Welcome AES Cipher");
    gflags::SetVersionString("0.1.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    if (FLAGS_verbose) std::cout << gflags::ProgramInvocationShortName() << ": ";
    gflags::ShutDownCommandLineFlags();

    std::ifstream infile(FLAGS_in, std::ifstream::binary);
    if (!infile.is_open()) {
        std::cout << "infile not opened!" << std::endl;
        std::cerr << "Error: " << strerror(errno);
        exit(1);
    }
    std::ofstream outfile(FLAGS_out, std::ofstream::binary);
    if (!outfile.is_open()) {
        std::cout << "outfile not opened!" << std::endl;
        std::cerr << "Error: " << strerror(errno);
        exit(2);
    }

    uint8_t iv[Nb * Nk];
    uint8_t key[Nb * Nk];
    for (int i = 0; i < Nb * Nk; ++i) {
        key[i] = FLAGS_key[i];
    }

    // Global nessage
    std::string message;

    int len = FLAGS_message.length();

    // Message chunk 128-bit
    std::vector<std::string> blocks;

    if (!FLAGS_in.empty()) {
        char c = 0;
        while (infile.get(c))
            message += (uint8_t) c;
        for (unsigned i = 0; i < message.length(); i += Nb * Nk) {
            blocks.push_back(message.substr(i, Nb * Nk));
        }
    }
    if (!FLAGS_message.empty()) {
        for (unsigned i = 0; i < len; i += Nb * Nk) {
            blocks.push_back(FLAGS_message.substr(i, Nb * Nk));
        }
    }

    // IV string to unit8_t *arr
    if (!FLAGS_iv.empty()) {
        for (int i = 0; i < Nb * Nk; ++i) {
            iv[i] = FLAGS_iv[i];
        }
    }

    // This variable needs to other modes
    // For example CBC
    state_t state_last = {0};
    state_t *state_table = (state_t *) malloc(blocks.size() * sizeof(state_t));

    // Core loop
    // All block starting to here for encrypt
    for (unsigned n = 0; n < blocks.size(); ++n) {
        std::string block = blocks[n];
        state_t state = {0};
        for (int j = 0; j < Nb * Nk; ++j) {
            if (j < block.length()) {
                state[j] = block[j];
            } else {
                state[j] = 0; // padding
            }
        }

        if (FLAGS_encrypt) {
            if (FLAGS_ecb) {
                Encryption(&state, key);
            }
            if (FLAGS_cbc) {
                if (n == 0) {
                    for (int i = 0; i < Nb * Nk; ++i) {
                        state[i] = state[i] ^ iv[i];
                    }
                } else {
                    for (int i = 0; i < Nb * Nk; ++i) {
                        state[i] ^= state_last[i];
                    }
                }
                Encryption(&state, key);
                for (int i = 0; i < Nb * Nk; ++i) {
                    state_last[i] = state[i];
                }
            }
            if (FLAGS_ofb) {
                if (n == 0) {
                    Encryption(&iv, key);
                    for (int i = 0; i < Nb * Nk; ++i) {
                        state_last[i] = iv[i];
                    }
                } else {
                    Encryption(&state, key);
                }
                for (int i = 0; i < Nb * Nk; ++i) {
                    state[i] ^= state_last[i];
                }
            }
        }
        if (FLAGS_decrypt) {
            if (FLAGS_ecb) {
                Decryption(&state, key);
            }
            if (FLAGS_cbc) {
                for (int i = 0; i < Nb * Nk; ++i) {
                    state_table[n][i] = state[i];
                }
                Decryption(&state, key);
                if (n == 0) {
                    for (int i = 0; i < Nb * Nk; ++i) {
                        state[i] ^= iv[i];
                    }
                } else {
                    for (int i = 0; i < Nb * Nk; ++i) {
                        state[i] = state[i] ^ state_table[n - 1][i];
                    }
                }
            }
            if (FLAGS_ofb) {
                if (n==0) {
                    Decryption(&iv, key);
                    for (int i = 0; i < Nb * Nk; ++i) {
                        state_last[i] = iv[i];
                    }
                } else {
                    Decryption(&state_last, key);
                }

                for (int i = 0; i < Nb * Nk; ++i) {
                    state[i] = state[i] ^ state_last[i];
                }
            }
        }
#ifdef DEBUG
        for (int i = 0; i < Nb * Nk; ++i) {
            printf("%02X ", state_table[n][i]);
        }
#endif
        // Write result file
        for (unsigned i = 0; i < Nb * Nk; ++i) {
            if (state[i] != 0) {
                outfile << state[i];
#ifdef DEBUG
                fprintf(stdout, "%02X", state[i]);
#endif
            }
        }
    }

    printf("\n");

    outfile.close();
    infile.close();

    return 0;
}