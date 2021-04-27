#include <stdio.h>
#include <inttypes.h>

#define W 64
// Words and bytes.
#define WORD uint64_t
#define PF PRIx64
#define BYTE uint8_t

// SHA512 works on blocks of 1024 bits.
union Block {
    // 8 x 128 = 1024 - dealing with block as bytes.
    BYTE bytes[128];
    // 64 x 16 = 1024 - dealing with block as words.
    WORD words[16];
    // 64 x 16 = 1024 - dealing with the last 128 bits of last block.
    uint64_t sixf[16];
};

// For keeping track of where we are with the input message/padding.
enum Status {
    READ, PAD, END
};

// Returns 1 if it created a new block from original message or padding.
// Returns 0 if all padded message has already been consumed.
int next_block(FILE *f, union Block *M, enum Status *S, uint64_t *nobits) {

    // Number of bytes read.
    size_t nobytes;

    if (*S == END) {
        // Finish.
        return 0;
    } else if (*S == READ) {
        // Try to read 128 bytes from the input file.
        nobytes = fread(M->bytes, 1, 128, f);
        // Calculate the total bits read so far.
        *nobits = *nobits + (8 * nobytes);
        // Enough room for padding.
        if (nobytes == 128) {
            // This happens when we can read 128 bytes from f.
            return 1;
        } else if (nobytes < 112) {
            // This happens when we have enough roof for all the padding.
            // Append a 1 bit (and seven 0 bits to make a full byte).
            M->bytes[nobytes] = 0x80; // In bits: 10000000.
            // Append enough 0 bits, leaving 64 at the end.
            for (nobytes++; nobytes < 112; nobytes++) {
                M->bytes[nobytes] = 0x00; // In bits: 00000000
            }
            // Append nobits as a big endian integer.
            M->sixf[15] = (islilend() ? bswap_64(*nobits) : *nobits);
            // Say this is the last block.
            *S = END;
        } else {
            // Got to the end of the input message and not enough room
            // in this block for all padding.
            // Append a 1 bit (and seven 0 bits to make a full byte.)
            M->bytes[nobytes] = 0x80;
            // Append 0 bits.
            for (nobytes++; nobytes < 128; nobytes++) {
                M->bytes[nobytes] = 0x00; // In bits: 00000000
            }
            // Change the status to PAD.
            *S = PAD;
        }
    } else if (*S == PAD) {
        // Append 0 bits.
        for (nobytes = 0; nobytes < 112; nobytes++) {
            M->bytes[nobytes] = 0x00; // In bits: 00000000
        }
        // Append nobits as a big endian integer.
        M->sixf[15] = (islilend() ? bswap_64(*nobits) : *nobits);
        // Change the status to END.
        *S = END;
    }

    // Swap the byte order of the words if we're little endian.
    if (islilend())
        for (int i = 0; i < 16; i++)
            M->words[i] = bswap_64(M->words[i]);

    return 1;
}


int main(int argc, char *argv[]) {

    // Iterator.
    int i;

    // The current block.
    union Block B;

    // Total number of bits read.
    uint64_t nobits = 0;

    // Current status of reading input.
    enum Status S = READ;

    // File pointer for reading.
    FILE *f;
    // Open file from command line for reading.
    f = fopen(argv[1], "r");
    
    // Loop through (preprocessed) the blocks.
    while (next_block(f, &B, &S, &nobits)) {
        // Print the 16 32-bit words.
        for (i = 0; i < 16; i++) {
            printf("%016" PF " ", B.words[i]);
        }
        printf("\n");
    }

    // Close the file.
    fclose(f);

    // Print total number of bits read.
    printf("Total bits read: %d.\n", nobits);

    return 0;
}