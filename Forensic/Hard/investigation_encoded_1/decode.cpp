#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_OUTPUT 65536
#define MAX_BITS (MAX_OUTPUT * 8)
#define MAX_FLAG 65536

/*
 * secret lấy trực tiếp từ mystery @ 0x2020
 */
unsigned char secret[] = {
    0xb8, 0xea, 0x8e, 0xba,
    0x3a, 0x88, 0xae, 0x8e,
    0xe8, 0xaa, 0x28, 0xbb,
    0xb8, 0xeb, 0x8b, 0xa8,
    0xee, 0x3a, 0x3b, 0xb8,
    0xbb, 0xa3, 0xba, 0xe2,
    0xe8, 0xa8, 0xe2, 0xb8,
    0xab, 0x8b, 0xb8, 0xea,
    0xe3, 0xae, 0xe3, 0xba,
    0x80
};


/*
 * matrix:
 *
 * matrix[i][0] = length
 * matrix[i][1] = start
 *
 * a = 0
 * b = 1
 * ...
 * z = 25
 * { = 26
 */
int matrix[27][2] = {
    { 8,   0 },   // a
    { 12,  8 },   // b
    { 14, 20 },   // c
    { 10, 34 },   // d
    { 4,  44 },   // e
    { 12, 48 },   // f
    { 12, 60 },   // g
    { 10, 72 },   // h
    { 6,  82 },   // i
    { 16, 88 },   // j
    { 12, 104 },  // k
    { 12, 116 },  // l
    { 10, 128 },  // m
    { 8,  138 },  // n
    { 14, 146 },  // o
    { 14, 160 },  // p
    { 16, 174 },  // q
    { 10, 190 },  // r
    { 8,  200 },  // s
    { 6,  208 },  // t
    { 10, 214 },  // u
    { 12, 224 },  // v
    { 12, 236 },  // w
    { 14, 248 },  // x
    { 16, 262 },  // y
    { 14, 278 },  // z
    { 4,  292 }   // {
};


/*
 * Lấy bit từ secret.
 *
 * mystery sử dụng:
 *
 * secret[index / 8]
 * shift = 7 - index % 8
 */
int getSecretBit(int index)
{
    int byteIndex = index / 8;
    int bitIndex = 7 - (index % 8);

    return (secret[byteIndex] >> bitIndex) & 1;
}


/*
 * Tạo bit pattern tương ứng với một ký tự.
 */
int getPattern(int index, char *pattern)
{
    int length = matrix[index][0];
    int start  = matrix[index][1];

    for (int i = 0; i < length; i++) {
        pattern[i] =
            getSecretBit(start + i) + '0';
    }

    pattern[length] = '\0';

    return length;
}


/*
 * Kiểm tra phần còn lại có phải padding 0 hay không.
 *
 * save() của mystery sẽ padding các bit cuối bằng 0
 * để đủ 1 byte.
 */
int isPadding(char *bits, int pos, int totalBits)
{
    int remaining = totalBits - pos;

    /*
     * Padding tối đa 7 bit.
     */
    if (remaining > 7)
        return 0;

    for (int i = pos; i < totalBits; i++) {
        if (bits[i] != '0')
            return 0;
    }

    return 1;
}


/*
 * Backtracking decode.
 */
int solve(
    char *bits,
    int pos,
    int totalBits,
    char *answer,
    int answerPos
)
{
    /*
     * Đã đi hết dữ liệu.
     */
    if (pos == totalBits) {
        answer[answerPos] = '\0';

        printf("[+] Decoded: %s\n", answer);

        return 1;
    }


    /*
     * Nếu phần cuối chỉ là padding 0.
     */
    if (isPadding(bits, pos, totalBits)) {

        answer[answerPos] = '\0';

        printf("[+] Decoded: %s\n", answer);

        return 1;
    }


    char pattern[512];


    /*
     * Thử các ký tự:
     *
     * b-z và {
     *
     * Không thử 'a' vì:
     *
     * matrix['a'].length = 0
     *
     * Nếu thử sẽ gây vòng lặp vô hạn.
     */
    for (int i = 1; i < 27; i++) {

        int length =
            getPattern(i, pattern);


        /*
         * Không đủ dữ liệu.
         */
        if (pos + length > totalBits)
            continue;


        /*
         * So sánh pattern với output.
         */
        if (strncmp(
                bits + pos,
                pattern,
                length
            ) == 0) {

            char c;

            if (i == 26)
                c = '{';
            else
                c = 'a' + i;


            answer[answerPos] = c;


            /*
             * Đệ quy.
             */
            if (solve(
                    bits,
                    pos + length,
                    totalBits,
                    answer,
                    answerPos + 1
                )) {

                return 1;
            }
        }
    }


    return 0;
}


int main()
{
    FILE *fp;

    unsigned char output[MAX_OUTPUT];

    char bits[MAX_BITS + 1];

    char answer[MAX_FLAG];


    /*
     * Mở output.
     */
    fp = fopen("output", "rb");

    if (fp == NULL) {

        printf("[-] Cannot open output\n");

        return 1;
    }


    /*
     * Đọc toàn bộ output.
     */
    int outputSize =
        fread(
            output,
            1,
            MAX_OUTPUT,
            fp
        );

    fclose(fp);


    printf("[+] Output size: %d bytes\n",
           outputSize);


    /*
     * Chuyển từng byte thành 8 bit.
     *
     * Ví dụ:
     *
     * 0x8e
     *
     * -> 10001110
     */
    int bitCount = 0;

    for (int i = 0;
         i < outputSize;
         i++) {

        for (int j = 7;
             j >= 0;
             j--) {

            bits[bitCount++] =
                ((output[i] >> j) & 1) + '0';
        }
    }

    bits[bitCount] = '\0';


    printf("[+] Bit length: %d\n",
           bitCount);


    /*
     * Decode.
     */
    if (!solve(
            bits,
            0,
            bitCount,
            answer,
            0
        )) {

        printf(
            "[-] Cannot decode output\n"
        );

        return 1;
    }


    return 0;
}