# Theory of Algorithms Project 2021
### Description
This programme, written in the C programming language, calculates the [SHA512](https://www.nist.gov/publications/secure-hash-standard) value of a file entered by the user via a command line argument.

#### Project Structure
- The [funcs.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/funcs.c) file contains the operations, functions, and constants used in SHA512. These functions can be found in section [4.1.3](https://www.nist.gov/publications/secure-hash-standard) of the Secure Hash Standard Publication.
- The [preprocessing.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/preprocessing.c) file consists of the 3 steps involved in preprocessing the input file:
  - setting the initial hash value
  - padding the file contents
  - parsing the file contents into blocks 
- The [sha512.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/sha512.c) file includes the methods in both of the files above, the methods needed to perform the hash computation and the SHA512 algorithm on the file entered by the user, and also runs the programme.

### Instructions on how to run this project
Enter in the following commands into your command prompt:
1) `git clone https://github.com/JackMcnamee/theory-algos-project`
2) `cd theory-algos-project`
3) `make sha512`
4) `./sha512 path/to/your/file/input.txt`

### SHA512
SHA512 is a cryptographic algorithm that performs a hashing function on data. The algorithm is very similar to SHA256, used in the Bitcoin blockchain, except it operates on a 1024-bit message block and a 512-bit intermediate hash value.

The steps involved in SHA512 include:
1) Initial Hash Value
      - An initial hash value is needed for the first 1024 bit block. The hash values are obtained from the fractional parts of the square roots of the first 8 prime numbers. This 64 bit sequence can be found in section [5.3.5](https://www.nist.gov/publications/secure-hash-standard) of the Secure Hash Standard Publication.

2) Preprocessing
      - To get the message to its desired length, which is a multiple of 1024, the message is appended with bits. The bits that are used are 1 followed by 0's. Such as 100000. 
      - The size of the original message is also appended as it has to be represented in 128 bits. With this taken into consideration, the maximum size for the original message is: (2 to the power of 128) - 2.

3) Computation
      - The hash computation takes place in a for loop, from i = 1 to N = number of blocks in the padded message.
      - Initialize registers (a, b, c, ..., h) with the initial hash values. 
      - Apply the compression function to update registers in a for loop, j = 0 to 79. This can be seen in section [6.4.2.3](https://www.nist.gov/publications/secure-hash-standard) of the Secure Hash Standard Publication.
      - Compute the ith intermediate hash value H(i). This can be seen in section [6.4.2.4](https://www.nist.gov/publications/secure-hash-standard) of the Secure Hash Standard Publication.
      - Once the original for loop is completed, the hash of the message is obtained.
***
### Answers to Questions
1) Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?
      - SHA512 is part of the SHA-2 family, which also includes SHA-224, SHA-256, SHA-384, SHA-512/224, SHA-512/256. SHA-2 consists of a set of crytographic hash functions, designed by the US National Security Agency. A hash function is a mathematical function that converts an input into a compressed output string, called a hash value. The input to SHA512 can be a length of up to 2^128 bits but the output is always 512 bits. This fixed length adds to the security of SHA512 as some bits will be lost, if the input message is longer than 512 bits, and will result in the hash function being irreversible.
2) Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?
      - Designing such an algorithm would depend on many factors, such as the equipment and resources available, the size of the input message, and the time you have. The resources needed would probably include a quantum computer, however the likelihood of the algorithm outputting the correct input message in our lifetime would be very low. My reasoning for this is that there is no evidence of any members of the SHA-2 family having been cracked yet. Also the price of Bitcoin being as high as it is, is in part to the security of the cryptocurrency, which uses SHA-256 in the creation of Bitcoin addresses. 

***
### Resources
- [Secure Hash Standard Publication](https://www.nist.gov/publications/secure-hash-standard)
- [Cryptography: Explaining SHA-512](https://medium.com/@zaid960928/cryptography-explaining-sha-512-ad896365a0c1)
- [Descriptions of SHA-256, SHA-384, and SHA-512](http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf)
- [SHA-2](https://en.wikipedia.org/wiki/SHA-2)
- [SHA-256in Bitcoin](https://en.bitcoin.it/wiki/SHA-256)
