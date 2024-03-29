# Theory of Algorithms Project 2021
### Description
This program, written in the C programming language, calculates the [SHA512](https://www.nist.gov/publications/secure-hash-standard) hash value of a file entered by the user via a command line argument.

### Project Structure
- The [functions.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/funcs.c) file contains the operations, functions, and constants used in SHA512. These functions can be found in section [4.1.3](https://www.nist.gov/publications/secure-hash-standard) of the Secure Hash Standard Publication.
- The [preprocessing.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/preprocessing.c) file consists of the 3 steps involved in preprocessing the input file:
  - setting the initial hash value
  - padding the file contents
  - parsing the file contents into blocks 
- The [sha512.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/sha512.c) file includes the methods in both of the files above, the methods needed to perform the hash computation and the SHA512 algorithm on the file entered by the user, and also runs the program.
- The [tests.sh](https://github.com/JackMcnamee/theory-algos-project/blob/main/tests.sh) file is used to run tests on this program. It uses sha512sum on input.txt, which prints a SHA512 message digest, and compares this output to what this program ouputs when performing the sha512 encryption on input.txt. It also does the same to an empty.txt file, which contains no data. When ran, it lets the user know if the tests passed or failed.
- The [Makefile](https://github.com/JackMcnamee/theory-algos-project/blob/main/Makefile) defines the set of tasks to be excecuted. It contains instructions for making sha512, running tests, and cleaning created files.

### Instructions on how to run this project
Enter in the following commands into your Ubuntu or Debian terminal:
1) `git clone https://github.com/JackMcnamee/theory-algos-project`
2) `cd theory-algos-project`
3) To compile: `gcc sha512.c -o sha512`
4) To build the program: `make`
5) To get the SHA512 hash digest of your file: `./sha512 path/to/your/file.txt`
6) To test the program: `make test`
***
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
      - Once the original for loop is completed, the hash digest of the message is obtained.
***
### Answers to Questions
1) Why can't we reverse the SHA512 algorithm to retrieve the original message from a hash digest?
      - SHA512 is part of the SHA-2 family, which also includes SHA-224, SHA-256, SHA-384, SHA-512/224, SHA-512/256. SHA-2 consists of a set of crytographic hash functions, designed by the US National Security Agency. A hash function is a mathematical function that converts an input into a compressed output string, called a hash value. The input to SHA512 can be a length of up to 2^128 bits but the output or hash value is always 512 bits. This fixed length adds to the security of SHA512 as some bits will be lost which will result in the hash function being irreversible. 
2) Can you design an algorithm that, given enough time, will find input messages that give each of the possible 512-bit strings?
      - Designing such an algorithm would depend on many factors, such as the equipment and resources available, the size of the input message, and the time you have. The resources needed would probably include a quantum computer, however the likelihood of the algorithm outputting the correct input message in our lifetime would be very low. My reasoning for this is that there is no evidence of any members of the SHA-2 family having been cracked yet. Also the price of Bitcoin being as high as it is (currently at around 48,000 euro for 1 Bitcoin at the time of writing), is in part due to the security of the cryptocurrency, which uses SHA-256 in the creation of Bitcoin addresses. 
3) How difficult is it to find a hash digest beginning with at least twelve zeros?
      - The probability of generating a hash digest starting with twelve zeroes would be: 1/32^12 or 8.6736174e-19
          - The output from SHA512 is base 32 and we are looking for 12 zeros.  
      - To find the length of time it would take to generate this hash digest using a typical laptop:
          - Get the reciprocal of the possibility to find the average number of hashes to solve this: 1/(8.6736174e-19) = 1.1529215e+18
          - Divide this by the hashrate of your hardware to get the average number of seconds required to obtain this hash digest: 1.1529215e+18/3,000,000 = 384307166667 seconds or over 12,000 years.
              - A typical laptop does around 2-3 million hashes per second.
      - As you can see, it would be very difficult to generate a SHA512 hash digest beginning with twelve zeros due to the very low possibility of 1/32^12. It would also take over 12,000 years to do so, depending on the computers hash rate. 
***
### Resources
- [Secure Hash Standard Publication](https://www.nist.gov/publications/secure-hash-standard)
- [GCC Compiler](https://linuxize.com/post/how-to-install-gcc-compiler-on-ubuntu-18-04/)
- [sha512sum to generate SHA512 hash digest](https://manpages.ubuntu.com/manpages/xenial/man1/sha512sum.1.html)
- [SHA-2](https://en.wikipedia.org/wiki/SHA-2)
- [Cryptography: Explaining SHA-512](https://medium.com/@zaid960928/cryptography-explaining-sha-512-ad896365a0c1)
- [Descriptions of SHA-256, SHA-384, and SHA-512](http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf)
- [SHA-256 in Bitcoin](https://en.bitcoin.it/wiki/SHA-256)
- [Hash digest that starts with 9 zeros(SHA-256)](https://bitcoin.stackexchange.com/questions/81655/creating-a-hash-that-starts-wtih-9-zeros) 
