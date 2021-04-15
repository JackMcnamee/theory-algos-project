# Theory of Algorithms Project 2021

### Description
This programme, written in the C programming language, calculates the [SHA512](https://www.nist.gov/publications/secure-hash-standard) value of a file entered by the user via a command line argument.

#### Project Structure
- The [funcs.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/funcs.c) file contains the operations, functions, and constants used in SHA512. 
- The [preprocessing.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/preprocessing.c) file consists of the 3 steps involved in preprocessing the input file:
  - padding the file contents
  - parsing the file contents into blocks 
  - setting the initial hash value
- The [sha512.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/sha512.c) file includes the methods in both of the files above, the methods needed to perform the hash computation and the SHA512 algorithm on the file entered by the user, and also runs the programme.

### Instructions on how to run project
Enter in the following commands into your command prompt:
1) `git clone https://github.com/JackMcnamee/theory-algos-project`
2) `cd theory-algos-project`
3) `make sha512`
4) `./sha512 path/to/your/file/input.txt`

### SHA512
SHA512 is a cryptographic algorithm that performs a hashing function on data. The algorithm is very similar to SHA256, used in the Bitcoin blockchain, except it operates on a 1024-bit message block and a 512-bit intermediate hash value.

The steps involved in SHA512 include:
1) Formatting the input
2) Preprocessing
3) Output

### Resources
- [Secure Hash Standard Publication](https://www.nist.gov/publications/secure-hash-standard)
- [Cryptography: Explaining SHA-512](https://medium.com/@zaid960928/cryptography-explaining-sha-512-ad896365a0c1)
- [Descriptions of SHA-256, SHA-384, and SHA-512](http://www.iwar.org.uk/comsec/resources/cipher/sha256-384-512.pdf)
