# Chudnovsky Algorithm for Computing Pi

This project implements the Chudnovsky algorithm to compute the value of Pi (`π`). The algorithm is known for its high precision and efficiency in calculating Pi using infinite series. Additionally, the program includes operations on big integers, fractions, and complex numbers.

## Features

- **Big Integer Operations:** Addition, subtraction, multiplication, division, modulo, GCD, power, and factorial.
- **Complex Number Operations:** Addition, subtraction, multiplication, division, and conjugate.
- **Fraction Operations:** Addition, subtraction, multiplication, division, and reduction to simplest form.
- **Chudnovsky Algorithm:** Computes the value of Pi using the Chudnovsky formula with a specified number of terms.
- **Newton-Raphson Algorithm:** Computes the square root of 10005, a critical component of the Chudnovsky formula.

## Getting Started

### Prerequisites

Ensure you have a C/C++ compiler installed. The program uses standard C libraries, so no additional dependencies are required.

### Compilation

To compile the program, use the following command:

```sh
gcc main.c -o main
```
### Running the Program
After compiling, you can run the program with:
```
./a.out
```
### Menu Options

Upon running, the program presents a menu with the following options:

1. **Basic Operations on Big Integers:**
   - Addition
   - Subtraction
   - Multiplication
   - Division
   - Decimal Division
   - Remainder (Modulo)
   - GCD
   - Power
   - Factorial

2. **Operations on Complex Numbers:**
   - Addition
   - Subtraction
   - Multiplication
   - Division
   - Conjugate

3. **Operations on Fractions:**
   - Addition
   - Subtraction
   - Multiplication
   - Division
   - Reduce to Simplest Form

4. **Computation of Pi:**
   - Compute the square root of 10005 using the Newton-Raphson algorithm
   - Compute the value of Pi using the Chudnovsky algorithm

5. **Miscellaneous:**
   - Set decimal precision
   - Exit the program

## Chudnovsky Algorithm

The Chudnovsky algorithm is a fast method for calculating the digits of Pi. The implementation calculates Pi as a fraction, which can then be converted to its decimal representation.

### Using the Chudnovsky Algorithm

1. Select the option to compute Pi from the menu.
2. Enter the number of terms you wish to use for the computation. More terms yield higher precision but increase computation time.
3. Optionally, you can write the computed value of Pi in decimal form to a file.

## Performance Considerations

- Computations involving large numbers and high precision can be computationally intensive.
- The program uses arbitrary-precision arithmetic to handle large integers and fractions.

## Contributing

Contributions are welcome! Feel free to fork the repository and submit pull requests with improvements or additional features.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- The Chudnovsky algorithm for its efficient and precise calculation of Pi.
- Big integer and fraction arithmetic support for handling large calculations.
