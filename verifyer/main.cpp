#include <iostream>
#include <cstdio>
#include <bits/stdc++.h>

#include <aes.h>

#include <gflags/gflags.h>

DEFINE_string(file, "", "Message or cipher data");
DEFINE_string(message, "", "Message to encrypt");
DEFINE_string(key, "", "Encryption key");
DEFINE_bool(verify, false, "Verify mode!");


/**
 *
 * @param flagname
 * @param value
 * @return
 */
static bool KeyValidator(const char *flagname, const std::string &value) {
    return value[0] != '\0' && value.size() == 16;
}

/**
 *
 * @param flagname
 * @param value
 * @return
 */
static bool IsNonEmptyMessage(const char *flagname, const std::string &value) {
    return value[0] != '\0';
}

DEFINE_validator(key, &KeyValidator);
DEFINE_validator(file, &IsNonEmptyMessage);


int main(int argc, char *argv[]) {
    gflags::SetUsageMessage("Hello, World! Welcome AES Cipher");
    gflags::SetVersionString("0.1.0");
    gflags::ParseCommandLineFlags(&argc, &argv, true);
    gflags::ShutDownCommandLineFlags();

    state_t state = {0};
    uint8_t key[Nb * Nk];

    std::ofstream outfile;
    std::ifstream infile(FLAGS_file, std::ifstream::binary);
    if (!infile.is_open()) {
        std::cout << "infile not opened!" << std::endl;
        std::cerr << "Error: " << strerror(errno);
        exit(1);
    }

    // Read from file
    std::string mac;
    std::string message;

    for (int i = 0; i < Nb * Nk; ++i) {
        key[i] = FLAGS_key[i];
    }

    // Message chunk 128-bit
    std::vector<std::string> chunks;

    // Read file
    char c = 0;
    while (infile.get(c))
        message += (uint8_t) c;

    if (FLAGS_verify) {
        mac = message.substr(message.size() - Nb * Nk);
        message = message.substr(0, message.length() - Nb * Nk);
    }

    for (unsigned i = 0; i < message.length(); i += Nb * Nk) {
        chunks.push_back(message.substr(i, Nb * Nk));
    }

    // This variable needs to other modes
    // For example CBC
    state_t result = {0};

    // Core loop
    // All block starting to here for encrypt
    for (unsigned n = 0; n < chunks.size(); ++n) {
        std::string block = chunks[n];

        for (int j = 0; j < Nb * Nk; ++j) {
            if (j < block.length()) {
                state[j] = block[j];
            } else {
                state[j] = 0; // padding
            }
        }

        Encryption(&state, key);

        for (int j = 0; j < Nb * Nk; ++j) {
            result[j] ^= state[j];
        }
    }

    // Close file
    infile.close();

    if (FLAGS_verify) {
        bool flag = false;
        for (int i = 0; i < mac.length(); ++i) {
            if (mac[i] == result[i]) {
                flag = true;
            }
        }
        if (flag) {
            printf("File verified!\n");
        } else {
            printf("File not verified!\n");
        }
    }


    // Write file MAC
    if (!FLAGS_verify) {
        outfile.open(FLAGS_file, std::ios::app);
        std::stringstream ss;

        // Write result file
        for (unsigned i = 0; i < Nb * Nk; ++i) {
            ss << result[i];
            fprintf(stdout, "%02X", result[i]);
        }
        outfile << ss.str();
        printf("\n");
        outfile.close();
    }

    return 0;
}