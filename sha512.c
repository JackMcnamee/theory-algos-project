#include <stdio.h>
#include <inttypes.h>

// Words and bytes.
#define WORD uint32_t
#define PF PRIX32
#define BYTE uint8_t

// Page 5 of the secure hash standard.
#define ROTL(x,n) (x<<n) | (x>>(W-n))
#define ROTR(x,n) (x>>n) | (x<<(W-n))
#define SHR(x,n) x>>n

// Page 10 of the secure hash standard.
#define CH(x,y,z) (x&y)^(~x&z)
#define MAJ(x,y,z) (x&y)^(x&z)^(y&z)

#define SIG0(x) ROTR(x,2)^ROTR(x,13)^ROTR(x,22)
#define SIG1(x) ROTR(x,6)^ROTR(x,11)^ROTR(x,25)
#define SiG0(x) ROTR(x,7)^ROTR(x,18)^SHR(x,3)
#define SiG1(x) ROTR(x,17)^ROTR(x,19)^SHR(x,10)

// SHA256 works on blocks of 512 bits.
union Block {
    // 8 x 64 = 512 - dealing with block as bytes.
    BYTE bytes[64];
    // 32 x 16 = 512 - dealing with block as words.
    WORD words[16];
    // 64 x 8 = 512 - dealing with the last 64 bits of last block.
    uint64_t sixf[8];
};

// For keeping track of where we are with the input message/padding.
enum Status {
    READ, PAD, END
};

// To-Do: SHA-512 Constants
// Page 11 of the secure hash standard. SHA-224 and SHA-256 Constants
const WORD K[] = {
    0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
    0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
    0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
    0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
    0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
    0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
    0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
    0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
    0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
    0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
    0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
    0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
    0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
    0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
    0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
    0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
};

// Returns 1 if it created a new block from original message or padding.
// Returns 0 if all padded message has already been consumed.
int next_block(FILE *f, union Block *B, enum Status *S, uint64_t *nobits) {

    // Number of bytes read.
    size_t nobytes;

    if (*S == END) {
        return 0;
    } else if (*S == READ) {
        // Try to read 64 bytes from the input file.
        nobytes = fread(B->bytes, 1, 64, f);
        // Calculate the total bits read so far.
        *nobits = *nobits + (8 * nobytes);
        // Enough room for padding.
        if (nobytes == 64) {
            // This happens when we can read 64 bytes from f.
            return 1;
        } else if (nobytes < 56) {
            // This happens when we have enough roof for all the padding.
            // Append a 1 bit (and seven 0 bits to make a full byte).
            B->bytes[nobytes] = 0x80; // In bits: 10000000.
            // Append enough 0 bits, leaving 64 at the end.
            for (nobytes++; nobytes < 56; nobytes++) {
                B->bytes[nobytes] = 0x00; // In bits: 00000000
            }
            // Append length of original input (CHECK ENDIANESS).
            B->sixf[7] = *nobits;
            // Say this is the last block.
            *S = END;
        } else {
            // Got to the end of the input message and not enough room
            // in this block for all padding.
            // Append a 1 bit (and seven 0 bits to make a full byte.)
            B->bytes[nobytes] = 0x80;
            // Append 0 bits.
            for (nobytes++; nobytes < 64; nobytes++) {
                 // Error: trying to write to 
                B->bytes[nobytes] = 0x00; // In bits: 00000000
            }
            // Change the status to PAD.
            *S = PAD;
        }
    } else if (*S == PAD) {
        // Append 0 bits.
        for (nobytes = 0; nobytes < 56; nobytes++) {
            B->bytes[nobytes] = 0x00; // In bits: 00000000
        }
        // Append nobits as an integer. CHECK ENDIAN!
        B->sixf[7] = *nobits;
        // Change the status to END.
        *S = END;
    }
    
    return 1;
}

// To-Do: Start SHA-512 functions

int main(int argc, char *argv[]) {
    // Section 5.3.4
    WORD H[] = {
        0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a,
        0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19
    };

    // File pointer for reading.
    FILE *f;
    // Open file from command line for reading.
    f = fopen(argv[1], "r");

    // Calculate the SHA512 of f.

    // Print the final SHA512 hash.

    // Close the file.
    fclose(f);

    return 0;
}