# Theory of Algorithms Project 2021

### Description
This programme, written in the C programming language, calculates the [SHA512](https://www.nist.gov/publications/secure-hash-standard) value of a file entered by the user via a command line argument. The programme compiles using `gcc` and a `Makefile` is compiled when `make` is called in the project folder.

#### Project Structure
- The [funcs.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/funcs.c) file contains the operations, functions, and constants used in SHA512. 
- The [preprocessing.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/preprocessing.c) file consists of the 3 steps involved in preprocessing the input file:
  - padding the file contents
  - parsing the file contents into blocks 
  - setting the initial hash value
- The [sha512.c](https://github.com/JackMcnamee/theory-algos-project/blob/main/sha512.c) file includes the methods needed to perform the hash computation, the SHA512 algorithm on the file entered by the user, and run the programme.

### Instructions on how to run project
1) `git clone https://github.com/JackMcnamee/theory-algos-project`
2) `cd theory-algos-project`
3) `make sha512`
4) `./sha512 path/to/your/file/input.txt`

### Resources
- [Secure Hash Standard Publication](https://www.nist.gov/publications/secure-hash-standard)
