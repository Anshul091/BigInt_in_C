/*    
 CS201- DSA Project 
 Project Title : BIGINT & Calculation of PI
 Instructor : Dr. Anil Shukla
 Mentor : Avadhesh Gaur

 Anant Prakash Singh -2021CSB1066  
 Kartik Yadav -2021CSB1101  
 Aditya Kumar Sahu -2021MCB1228

*/




#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define BASE 1000000000000000000ULL; // 1e18
#define HALFBASE 1000000000ULL
#define MAX_FACT 10000

unsigned int decimal_precision = 3000;

#define OUTPUT_SQRT_FILENAME "./output_sqrt_10005.txt"
#define OUTPUT_PI_FILENAME "./output_pi.txt"

struct BigIntStruct
{
    short int sign;
    unsigned int len;
    unsigned long long *d;
};

struct FractionStruct
{
    struct BigIntStruct *num;
    struct BigIntStruct *den;
};

struct ComplexStruct
{
    long long int real;
    long long int imag;
};

typedef struct BigIntStruct *BigInt;
typedef struct BigIntStruct BigIntObj;

typedef struct ComplexStruct *Complex;
