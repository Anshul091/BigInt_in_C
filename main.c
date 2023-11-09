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
            // {
            //     mid = (low + high) / 2;
            //     if (Compare(r, table[mid]) >= 0)
            //     {
            //         quo = mid;
            //         low = mid + 1;
            //     }
            //     else
            //     {
            //         high = mid - 1;
            //     }
            // }

            // Using linear search to find the quotient
            quo = 0;
            while (Compare(r, table[quo]) >= 0)
            {
                quo++;
            }
            quo--;

            temp = q;
            q = Multiply(q, ten);
            free_BigInt(temp);
            q->d[0] += quo;
            temp = r;
            r = Subtract(r, table[quo]);
            free_BigInt(temp);
        }
    }
    remove_preceding_zeroes(r);
    *remainder = r;

    for (int i = 0; i <= 10; i++)
    {
        free_BigInt(table[i]);
    }
    free_BigInt(ten);

    remove_preceding_zeroes(q);
    return q;
}

char *Decimal_Division(BigInt a, BigInt b)
{
    BigInt remainder;
    BigInt temp = new_BigInt(1);
    BigInt quotient = Divide(a, b, &remainder);
    llu mod;
    llu cur;
    int flag = 1;
    unsigned int ind = 0;
    unsigned int sz = quotient->len * 18 + decimal_precision + 2;

    char *result = (char *)malloc(sizeof(char) * sz);
    for (int i = quotient->len - 1; i >= 0; i--)
    {
        mod = BASE;
        mod /= 10;
        while (mod)
        {
            cur = quotient->d[i] / mod;
            cur %= 10;
            mod /= 10;
            if (flag)
            {
                if (cur == 0)
                {
                    sz--;
                    continue;
                }
                else
                {
                    flag = 0;
                }
            }
            // printf("%d\n", cur);
            result[ind++] = cur + '0';
        }
    }
    // print_BigInt(remainder);

    result[ind++] = '.';
    // return result;
    // free_BigInt(quotient);
    Left_Shift(remainder, (decimal_precision + 17) / 18);
    // BigInt ten = new_BigInt(1);
    // ten->d[0] = 10;
    // remainder = Multiply(remainder, Power(ten, decimal_precision));
    quotient = Divide(remainder, b, &temp);

    // printf("Quotient: ");
    // print_BigInt(quotient);
    // printf("%d\n", quotient->len);

    // printf("sz = %d\n", sz);
    // printf("ind = %d\n", ind);

    for (int i = quotient->len - 1; i >= 0; i--)
    {
        mod = BASE;
        mod /= 10;
        while (mod)
        {
            cur = quotient->d[i] / mod;
            cur %= 10;
            mod /= 10;
            result[ind++] = cur + '0';
            // printf("%d\n", cur);

            if (ind == sz - 1)
            {
                break;
            }
        }
        if (ind == sz - 1)
        {
            break;
        }
    }
    result[ind] = '\0';

    // free_BigInt(remainder);
    // free_BigInt(temp);
    // free_BigInt(quotient);

    return result;
}

BigInt Remainder(BigInt a, BigInt b)
{
    BigInt r;
    Divide(a, b, &r);
    return r;
}

BigInt Power(BigInt num, llu p)
{
    BigInt ans = new_BigInt(1);
    ans->d[0] = 1;

    BigInt temp;
    while (p > 0)
    {
        if (p & 1)
        {
            temp = ans;
            ans = Multiply(ans, num);
            free_BigInt(temp);
        }
        p >>= 1;
        temp = num;
        num = Multiply(num, num);
        free_BigInt(temp);
    }
    return ans;
}

BigInt GCD(BigInt a, BigInt b)
{
    BigInt temp;
    BigInt zero = new_BigInt(1);
    set_zero(zero);
    while (Compare(b, zero) != 0)
    {
        // printf("%d\n", Compare(b, zero));
        temp = Remainder(a, b);
        a = b;
        b = temp;
    }
    return a;
}

BigInt Factorial(llu n)
{
    BigInt ans = new_BigInt(1);
    // setzero(ans);
    ans->d[0] = 1;
    // set_zero(temp);
    for (int i = 1; i <= n; i++)
    {
        BigInt temp = new_BigInt(1);
        temp->d[0] = i;
        ans = Multiply(ans, temp);
    }
    return ans;
}

void precompute_factorial()
{
    FACT[0] = Factorial(1);
    BigInt n = new_BigInt(1);
    n->d[0] = 1;

    for (int i = 1; i < MAX_FACT; i++)
    {
        FACT[i] = Multiply(FACT[i - 1], n);
        n->d[0]++;
    }
    free_BigInt(n);
}

void Increment(const BigInt a, const BigInt delta)
{
    if (a->len <= delta->len)
    {
        increase_size(a, delta->len - a->len + 1);
    }
    llu carry = 0;
    for (unsigned int i = 0; i < delta->len; i++)
    {
        a->d[i] += delta->d[i] + carry;
        carry = a->d[i] / BASE;
        a->d[i] %= BASE;
    }
    for (unsigned int i = delta->len; i < a->len; i++)
    {
        a->d[i] += carry;
        carry = a->d[i] / BASE;
        a->d[i] %= BASE;
    }
}

void increase_size(BigInt b, const unsigned int delta_len)
{
    b->d = (llu *)realloc(b->d, sizeof(llu) * (b->len + delta_len));
    b->len += delta_len;
    for (int i = b->len - delta_len; i < b->len; i++)
        b->d[i] = 0;
}

void remove_preceding_zeroes(BigInt a)
{
    while (a->len > 1 && a->d[a->len - 1] == 0)
    {
        a->len--;
    }
}

int isPrime(int n)
{
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;

    for (int i = 5; i * i <= n; i = i + 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    return 1;
}

int gcd(int a, int b)
{
    while (b)
    {
        a %= b;
        // swap(a, b);
    }
    return a;
}

// ---------------- Complex Functions ----------------

Complex new_Complex()
{
    Complex temp;
    temp = (Complex)malloc(sizeof(ComplexObj));
    return temp;
}

void print_Complex(Complex a)
{
    if (a->imag >= 0)
        printf("%lld + %lldi\n", (a->real), (a->imag));
    else
        printf("%lld - %lldi\n", (a->real), -(a->imag));
}

void free_Complex(Complex a)
{
    free(a);
}

long long int real_part(Complex a)
{
    return a->real;
}

long long int imag_part(Complex a)
{
    return a->imag;
}

Complex conjugate(Complex a)
{
    Complex c = new_Complex();
    c->real = a->real;
    if (a->imag == 0)
    {
        c->imag = a->imag;
    }
    else
        c->imag = (-1) * (a->imag);
    return c;
}

long long int modulus(Complex a)
{
    return pow(a->real, 2) + pow(a->imag, 2);
}

Complex add_Complex(Complex a, Complex b)
{
    Complex c;
    c = new_Complex();
    c->real = ((a->real) + (b->real));
    c->imag = (a->imag) + (b->imag);
    return c;
}

Complex subtract_Complex(Complex a, Complex b)
{
    Complex c;
    c = new_Complex();
    c->real = a->real - b->real;
    c->imag = a->imag - (b->imag);

    return c;
}

Complex multiply_Complex(Complex a, Complex b)
{
    Complex c = new_Complex();
    c->real = (a->real * b->real) - (a->imag * b->imag);
    c->imag = (a->real * b->imag) + (a->imag * b->real);

    return c;
}

Complex divide_Complex(Complex a, Complex b)
{
    Complex c = new_Complex();

    c->real = real_part(multiply_Complex(a, conjugate(b))) / modulus(b);
    c->imag = imag_part(multiply_Complex(a, conjugate(b))) / modulus(b);

    return c;
}

// ------------ Fraction Functions ------------

Fraction new_Fraction()
{
    Fraction c;
    c = (Fraction)malloc(sizeof(FractionObj));
    // c->num=new_BigInt(1);
    // c->den=new_BigInt(1);
    return c;
}

Fraction input_Fraction()
{
    Fraction c;
    printf("Enter Numerator: ");
    BigInt a = input_BigInt();
    printf("Enter Denominator: ");
    BigInt b = input_BigInt();

    c = (Fraction)malloc(sizeof(FractionObj));

    c->num = a;
    c->den = b;

    return c;
}

void print_Fraction(Fraction a)
{
    printf("Numerator :  ");
    print_BigInt(a->num);
    printf("Denominator : ");
    print_BigInt(a->den);
}

void reduce_Fraction(Fraction a)
{
    BigInt g = GCD(a->num, a->den);
    remove_preceding_zeroes(g);
    if (g->d[0] == 1)
    {
        return;
    }
    BigInt rem;
    a->num = Divide(a->num, g, &rem);
    a->den = Divide(a->den, g, &rem);
}

Fraction add_Fraction(Fraction a, Fraction b)
{
    Fraction c = new_Fraction();
    c->num = Add(Multiply(a->num, b->den), Multiply(a->den, b->num));
    c->den = Multiply(a->den, b->den);

    // BigInt rem;
    // BigInt g = GCD(a->den, b->den);
    // BigInt a1 = Multiply(a->num, g);
    // BigInt b1 = Multiply(b->num, g);
    // c->num = Add(a1, b1);

    // BigInt d = Divide(a->den, g, &rem);
    // c->den = Multiply(b->den, d);

    // free_BigInt(a1);
    // free_BigInt(b1);
    // free_BigInt(d);
    // free_BigInt(g);
    // free_BigInt(rem);

    // reduce_Fraction(c);

    return c;
}

Fraction subtract_Fraction(Fraction a, Fraction b)
{
    Fraction c = new_Fraction();
    c->num = Subtract(Multiply(a->num, b->den), Multiply(a->den, b->num));
    c->den = Multiply(a->den, b->den);

    // BigInt rem;
    // BigInt g = GCD(a->den, b->den);
    // BigInt a1 = Multiply(a->num, g);
    // BigInt b1 = Multiply(b->num, g);
    // c->num = Subtract(a1, b1);

    // BigInt d = Divide(a->den, g, &rem);
    // c->den = Multiply(b->den, d);

    // free_BigInt(a1);
    // free_BigInt(b1);
    // free_BigInt(d);
    // free_BigInt(g);
    // free_BigInt(rem);

    // reduce_Fraction(c);

    return c;
}

Fraction multiply_Fraction(Fraction a, Fraction b)
{
    Fraction c = new_Fraction();
    c->num = Multiply(a->num, b->num);
    c->den = Multiply(a->den, b->den);

    // reduce_Fraction(c);

    return c;
}

Fraction divide_Fraction(Fraction a, Fraction b)
{
    Fraction c = new_Fraction();
    c->num = Multiply(a->num, b->den);
    c->den = Multiply(a->den, b->num);

    // reduce_Fraction(c);

    return c;
}

void reciprocal_Fraction(Fraction a)
{
    BigInt temp = a->num;
    a->num = a->den;
    a->den = temp;
}

void free_Fraction(Fraction a)
{
    free_BigInt(a->num);
    free_BigInt(a->den);
    free(a);
}

void cancel_zeroes(Fraction a)
{
    int cnt = 0;
    for (int i = 0; i < Min(a->num->len, a->den->len); i++)
    {
        if (a->num->d[i] == 0 && a->den->d[i] == 0)
        {
            cnt++;
        }
        else
        {
            break;
        }
    }
    a->num->d += cnt;
    a->den->d += cnt;
    a->num->len -= cnt;
    a->den->len -= cnt;
}

Fraction Square_Root(BigInt k, int n)
{
    // Calculate the square root of a BigInt using Newton Rapson method

    Fraction x = new_Fraction();
    // free_BigInt(x->num);
    int flag = 0;

    if (k->len == 1 && k->d[0] == 10005)
    {
        flag = 1;
        // x->num = new_BigInt(1);
        // x->num->d[0] = 2050048640064001ULL;
        // x->den = new_BigInt(1);
        // x->den->d[0] = 20495363200160ULL;

        x->num = new_BigInt(4);
        x->num->d[0] = 38194350081024001ULL;
        x->num->d[1] = 947199942084943826ULL;
        x->num->d[2] = 764652037898659122ULL;
        x->num->d[3] = 141301459ULL;

        x->den = new_BigInt(4);
        x->den->d[0] = 118368174297600640ULL;
        x->den->d[1] = 1550394278198635ULL;
        x->den->d[2] = 476412055532869542ULL;
        x->den->d[3] = 1412661ULL;
    }
    else
    {
        x->num = new_BigInt(1);
        x->num->d[0] = 2;
        x->den = new_BigInt(1);
        x->den->d[0] = 1;
    }

    Fraction temp, temp1, f, df;
    Fraction two = new_Fraction();
    two->num = new_BigInt(1);
    two->den = new_BigInt(1);
    two->num->d[0] = 2;
    two->den->d[0] = 1;

    Fraction nn = new_Fraction();
    nn->den = new_BigInt(1);
    nn->num = k;
    nn->den->d[0] = 1;

