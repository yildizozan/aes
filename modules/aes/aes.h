//
// Created by yildizozan on 2.01.2021.
//

#ifndef AES_AES_H
#define AES_AES_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>


/* 32-bit words in the block */
#define Nb 4

/* 32-bit words in key */
#define Nk 4

/*
 * Number of transformation rounds
 * Rounds Nr = 6 + max{Nb,Nk}
 *
 * AES-128 : 10
 * AES-192 : 12
 * AES-256 : 14
*/
#define Nr 10

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

typedef uint8_t state_t[Nb * Nk];

/**
 *
 * @param round
 * @param state
 * @param subKey
 */
void AddRoundKey(state_t *state, const uint8_t *subKey);

/**
 * 0000 1111 (8-bit) -> sbox[0,15]
 * @param round
 * @param state
 */
void SubstitutionBytes(state_t *state);

/**
 * 0000 1111 (8-bit) -> sbox[0,15]
 * @param round
 * @param values
 */
void SubstitutionBytesWord(const uint8_t *values, uint8_t *output);

/**
 * 1 2 3 4 -> 1 2 3 4
 * 1 2 3 4 -> 2 3 4 1
 * 1 2 3 4 -> 3 4 1 2
 * 1 2 3 4 -> 4 1 2 3
 *
 * @param round
 * @param state
 */
void ShiftRows(state_t *state);

/**
 * GF(8)
 * P(X) = X^3 + X + 1
 *
 * @param state
 */
void MixColumns(state_t *state);

void MixColumnsNew(state_t *state);

/**
 *
 * @param a
 * @param b
 * @param c
 * @param d
 */
void MixCol(state_t *state);

/**
 *        w[4]     ->   [shift]   ->  subsbytes  -> round constrait(rcon) ->
 *  E8	C0	FC	56 -> C0 FC	56 E8 -> BA XX XX XX ->
 */


//uint8_t state[Nb][Nk];

/**
 *
 * @param key
 */
void LeftCircularShift(const uint8_t *key, uint8_t *output);

/**
 * Need to be same size two array
 *
 * @param arr1
 * @param arr2
 * @param result
 */
void XOR(const uint8_t *arr1, const uint8_t *arr2, uint8_t *result);

/**
 *
 * @param key
 * @param output
 * @param round
 */
void AddingRoundConstant(const uint8_t *key, uint8_t *output, unsigned int round);

/**
 *
 * @param word
 */
void Print1DArray(const uint8_t *word, const uint8_t size);

/**
 *
 * @param msg
 * @param data
 * @param size
 */
void Debug(const char *msg, const uint8_t *data, const uint8_t size);

/**
 * a
 * b
 * c
 *
 *
 * 1 2 3 4
 * 5 6 7 8 -> 4 8 2 6 -> 8 2 6 4
 * 9 0 1 2
 * 3 4 5 6
 *   n-4      n-1  n
 * [ 00	12	75	BB XX YY ... ]
 * [ 89	44	E6	BB XX YY ... ]
 * [ D8	DD	4D	3B XX YY ... ]
 * [ D5	40	E8	06 XX YY ... ]
 *
 *        k[0]            k[0]            k[0]           k[0]
 *   -------------  --------------  --------------  --------------
 * [ 05	DC	2B	3E	55	78	98	8C	A7	B7	79	B5	67	0A	55	70 ] input
 *
 *        w[0]            w[0]            w[0]           w[0]
 *   -------------  --------------  --------------  --------------
 * [ EF	4D	F9	3C	AA	33	02	9F	FB	85	7F	A8	43	45	50	51 ] output
 *
 * @param state
 */
void KeyExpand(uint8_t round, uint8_t *state);

/**
 *
 * @param state
 * @param key
 */
void Cipher(state_t *state, uint8_t *key);

/**
 *
 * @param state
 */
void PrintState(const char *msg, state_t *state);

/**
 * @link https://en.wikipedia.org/wiki/Rijndael_MixColumns
 *
 * @param a
 * @param b
 * @param r
 */
void gmix_columns(uint8_t *r);

#endif //AES_AES_H
