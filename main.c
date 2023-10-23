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
typedef struct ComplexStruct ComplexObj;

typedef struct FractionStruct *Fraction;
typedef struct FractionStruct FractionObj;

typedef unsigned long long llu;
typedef long long ll;

BigInt FACT[MAX_FACT];
Fraction sqrt_10005 = NULL;
Fraction PI;
char *PI_str;

// Function prototypes

int Max(int x, int y);
int Min(int x, int y);

// ---- BigInt functions ----
BigInt new_BigInt(const unsigned int length);
void set_zero(BigInt b);
void free_BigInt(BigInt b);
void print_BigInt(BigInt b);
BigInt Add(const BigInt a, const BigInt b);
BigInt Subtract(const BigInt a, const BigInt b);
void _MUL_(llu x, llu y, llu *carry, llu *result);
BigInt Multiply(const BigInt a, const BigInt b);
void Left_Shift(BigInt num, unsigned int shift);
int Compare(const BigInt a, const BigInt b);
BigInt Divide(const BigInt a, const BigInt b, BigInt *remainder);
char *Decimal_Division(BigInt a, BigInt b);
BigInt Remainder(BigInt a, BigInt b);
BigInt Power(BigInt num, llu p);
BigInt GCD(BigInt a, BigInt b);
BigInt Factorial(llu n);
void precompute_factorial();
void Increment(const BigInt a, const BigInt delta);
void increase_size(BigInt b, const unsigned int delta_len);
void remove_preceding_zeroes(BigInt a);
int isPrime(int n);
int gcd(int a, int b);

// ---- Complex functions ----
Complex new_Complex();
void print_Complex(Complex a);
void free_Complex(Complex a);
long long int real_part(Complex a);
long long int imag_part(Complex a);
long long int modulus(Complex a);
Complex conjugate(Complex a);
Complex add_Complex(Complex a, Complex b);
Complex subtract_Complex(Complex a, Complex b);
Complex multiply_Complex(Complex a, Complex b);
Complex divide_Complex(Complex a, Complex b);

// ---- Fraction functions ----
Fraction new_Fraction();
Fraction input_Fraction();
void print_Fraction(Fraction a);
void reduce_Fraction(Fraction a);
Fraction add_Fraction(Fraction a, Fraction b);
Fraction subtract_Fraction(Fraction a, Fraction b);
Fraction multiply_Fraction(Fraction a, Fraction b);
Fraction divide_Fraction(Fraction a, Fraction b);
void reciprocal_Fraction(Fraction a);
void free_Fraction(Fraction a);
void cancel_zeroes(Fraction a);

// Calculate the square root of a BigInt using Newton Rapson method
Fraction Square_Root(BigInt k, int n);

// Computes value of PI using Chudnovsky algorithm
void PI_Chudnovsky(int n);

int Max(int x, int y)
{
    return x > y ? x : y;
}

int Min(int x, int y)
{
    return x < y ? x : y;
}

// -------------- BigInt functions ----------------

BigInt new_BigInt(const unsigned int length)
{
    BigInt b = (BigInt)malloc(sizeof(BigIntObj));
    if (b == NULL)
    {
        printf("Fatal error: Memory allocation failed!");
        exit(1);
    }
    b->sign = 1;
    b->len = length;
    b->d = (llu *)malloc(length * sizeof(llu));
    if (b->d == NULL)
    {
        printf("Fatal error: Memory allocation failed!");
        exit(1);
    }
    return b;
}

void set_zero(BigInt b)
{
    for (unsigned int i = 0; i < b->len; i++)
        b->d[i] = 0;
}

void free_BigInt(BigInt b)
{
    free(b->d);
    free(b);
}

void print_BigInt(BigInt b)
{
    printf("%c", b->sign == 1 ? '+' : '-');

    int i = b->len;
    while (--i > 0 && b->d[i] == 0)
        ;

    printf("%llu", b->d[i--]);

    while (i >= 0)
        printf("%018llu", b->d[i--]);

    printf("\n");
}

BigInt input_BigInt() // function to take input from user by string
{
    char *arr;
    arr = (char *)malloc(2 * sizeof(char));
    int count = 0;
    int szalloc = 2;
    char c = ' ';
    int sgn = 1;
    // Removing whitespaces from the input buffer
    while (c == ' ' || c == '\n') {
        c = getchar();
    }
    ungetc(c, stdin);

    while (c != '\n')
    {
        if (count == szalloc - 1)
        {

            arr = (char *)realloc(arr, 2 * szalloc * sizeof(char));
            szalloc *= 2;
        }

        scanf("%c", &c);
        if (count == 0)
        {
            if (c == '+' || c == '-')
            {
                if (c == '-')
                {
                    sgn = 0;
                }
                continue;
            }
        }
        arr[count] = c;

        count++;
    }
    // printf("count :%d\n",count);
    int lenreq = count / 18;
    if (count % 18 != 0)
    {
        lenreq++;
    }
    BigInt x = new_BigInt(lenreq);
    set_zero(x);
    int j = 0;
    while (count != 0)
    {
        llu tmp = 0;
        if (count <= 18)
        {
            for (int i = 0; i < count - 1; i++)
            {
                tmp = 10 * tmp + (arr[i] - '0');
                // printf("%d ",arr[i]-'0');
            }
            x->d[j] = tmp;
            j++;
            count = 0;
            // printf("\ntmp %d \n",arr[3]-'0');
        }
        else
        {
            for (int i = count - 19; i < count - 1; i++)
            {
                tmp = 10 * tmp + (arr[i] - '0');
            }
            count -= 18;
            x->d[j] = tmp;
            j++;
        }
    }
    x->sign = sgn;
    return x;
}

BigInt Add(const BigInt a, const BigInt b)
{
    if (a->sign == 1 && b->sign == 0)
    {
        return Subtract(a, b);
    }
    if (a->sign == 0 && b->sign == 1)
    {
        return Subtract(b, a);
    }

    BigInt c = new_BigInt(1 + Max(a->len, b->len));
    set_zero(c);
    llu carry = 0;
    for (unsigned int i = 0; i < c->len - 1; i++)
    {
        c->d[i] = carry +
                  (i < a->len ? a->d[i] : 0) +
                  (i < b->len ? b->d[i] : 0);
        carry = c->d[i] / BASE;
        c->d[i] %= BASE;
    }
    if (carry > 0)
    {
        c->d[c->len - 1] = carry;
    }

    if (a->sign == 0 && b->sign == 0)
    {
        c->sign = 0;
    }

    remove_preceding_zeroes(c);
    return c;
}

BigInt Subtract(const BigInt a, const BigInt b)
{
    BigInt c = new_BigInt(1 + Max(a->len, b->len));
    set_zero(c);
    ll carry = 0;
    ll temp;
    for (unsigned int i = 0; i < c->len - 1; i++)
    {
        temp = carry +
               (i < a->len ? a->d[i] : 0) -
               (i < b->len ? b->d[i] : 0);

        if (temp < 0)
        {
            carry = -1;
            c->d[i] = temp + BASE;
        }
        else
        {
            carry = 0;
            c->d[i] = temp;
        }
    }

    if (carry > 0)
    {
        c->d[c->len - 1] = carry;
    }
    else if (carry < 0)
    {
        c->sign = 0;
        carry = 0;
        for (unsigned int i = 0; i < c->len - 1; i++)
        {
            temp = carry +
                   (i < b->len ? b->d[i] : 0) -
                   (i < a->len ? a->d[i] : 0);

            if (temp < 0)
            {
                carry = -1;
                c->d[i] = temp + BASE;
            }
            else
            {
                carry = 0;
                c->d[i] = temp;
            }
        }
    }

    remove_preceding_zeroes(c);
    return c;
}

void _MUL_(llu x, llu y, llu *carry, llu *result)
{
    /*
    Multiplies x and y, and stores the product in result, and excess value in carry.
    The value stored in carry is added to result before multiplication.
    The value stored in result is incremented, not overwritten.
    */

    llu x0 = x % HALFBASE,
        x1 = x / HALFBASE,
        y0 = y % HALFBASE,
        y1 = y / HALFBASE,
        excess = x1 * y0 + x0 * y1;

    // Note the += here, to add to the previous value; Also note that the previous carry is added to this because carry will be reset to new carry
    *result += x0 * y0 + (excess % HALFBASE) * HALFBASE + (*carry);

    // No += here because carry will be recalculated
    *carry = x1 * y1 + excess / HALFBASE + (*result) / BASE;

    *result %= BASE;
}

BigInt Multiply(const BigInt a, const BigInt b)
{
