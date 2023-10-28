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
    BigInt c = new_BigInt(a->len + b->len);
    c->sign = 1 - a->sign ^ b->sign;
    llu carry;
    set_zero(c);
    for (unsigned int i = 0; i < a->len; i++)
    {
        carry = 0;
        for (unsigned int j = 0; j < b->len; j++)
        {
            _MUL_(a->d[i], b->d[j], &carry, &(c->d[i + j]));
            // _MUL_ exactly does the below 3 operations without overflow
            // c->d[i + j] += a->d[i] * b->d[j] + carry;
            // carry = c->d[i + j] / BASE;
            // c->d[i + j] %= BASE;
        }
        c->d[i + b->len] = carry;
    }

    remove_preceding_zeroes(c);
    return c;
}

void Left_Shift(BigInt num, unsigned int shift)
{
    if (shift == 0)
    {
        return;
    }
    if (num->len == 1 && num->d[0] == 0)
    {
        return;
    }

    llu *temp = (llu *)malloc(sizeof(llu) * (num->len + shift));
    if (temp == NULL)
    {
        printf("Fatal Error: Memory allocation failed!");
        exit(1);
    }
    for (unsigned int i = 0; i < shift; i++)
    {
        temp[i] = 0;
    }

    for (unsigned int i = 0; i < num->len; i++)
    {
        temp[i + shift] = num->d[i];
    }
    free(num->d);
    num->d = temp;
    num->len += shift;
}

int Compare(const BigInt a, const BigInt b)
{
    BigInt diff = Subtract(a, b);
    int flag = 0;
    for (int i = 0; i < diff->len; i++)
    {
        if (diff->d[i] != 0)
        {
            flag = 1;
        }
    }
    if (diff->sign == 0) // diff is negative
    {
        free_BigInt(diff);
        return -1;
    }
    else if (diff->sign == 1)
    {
        free_BigInt(diff);
        return flag;
    }
}

BigInt Divide(const BigInt a, const BigInt b, BigInt *remainder)
{
    BigInt q = new_BigInt(1);
    set_zero(q);
    q->sign = 1 - a->sign ^ b->sign;

    BigInt r = new_BigInt(1);
    set_zero(r);

    BigInt ten = new_BigInt(1);
    ten->d[0] = 10;

    BigInt table[11];
    table[0] = new_BigInt(1);
    set_zero(table[0]);

    for (int i = 1; i <= 10; i++)
    {
        table[i] = Add(table[i - 1], b);
    }

    llu mod;
    llu cur;
    int quo;
    BigInt temp;

    for (int i = a->len - 1; i >= 0; i--)
    {
        mod = BASE;
        mod /= 10;
        while (mod)
        {
            cur = a->d[i] / mod;
            cur %= 10;
            // printf("%d\n", cur);
            mod /= 10;
            temp = r;
            r = Multiply(r, ten);
            free_BigInt(temp);
            r->d[0] += cur;

            // I thought binary search would be faster,
            // but ended up being slower as there are only 10 values to search

            // // Using binary search to find the quotient
            // int low = 0, high = 10, mid;
            // quo = 0;
            // while (low <= high)
