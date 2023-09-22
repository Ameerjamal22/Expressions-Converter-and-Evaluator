# Expressions-Converter-and-Evaluator
This C program is designed to work with mathematical expressions. It offers several functionalities, including reading expressions from a file, validating them, converting valid infix expressions to prefix notation, evaluating expressions, and more.

## Table of Contents
- [Overview](#overview)
- [Usage](#usage)
- [Code Structure](#code-structure)
- [How to Run](#how-to-run)


## Overview

- **IntegersStack**: Defines a stack data structure for integers and provides functions for pushing, popping, checking if the stack is empty, disposing of the stack, and more.

- **power**: Calculates x raised to the power of y.

- **EvaluateExpression**: Evaluates a given prefix expression and returns the result.

- **ReadInputFile**: Reads expressions from a user-specified file and stores them in a list.

- **PrintTextMessage**: Displays a menu of options to the user.

- **Menu**: The primary control flow of the program, allowing users to read expressions, validate them, convert to prefix notation, evaluate, and more.

- **PopInteger**: Removes the top integer from the integer stack.

- **TopInteger**: Retrieves the top integer from the integer stack.

- **isEmptyIntegersStack**: Checks if the integer stack is empty.

- **DisposeIntegersStack**: Removes all nodes from the integer stack and frees memory.

- **printIntegersStack**: Prints the values in the integer stack from top to bottom.

- **Print invalid equations**: Lists and prints the invalid equations.

- **Print all the results to the output file**: Saves the results of equations, both valid and invalid, to an output file named "output.txt".

## Usage

1. **Read Expressions from a File**: Select option 1 in the menu to read expressions from a file. Enter the filename when prompted.

2. **Check Validity of Equations**: Choose option 2 to check the validity of the equations. The program will display whether each equation is valid or not.

3. **Convert Equations to Prefix Notation**: Opt for option 3 to convert valid infix equations to prefix notation. The program will show the resulting prefix expressions.

4. **Evaluate Equations**: Select option 4 to evaluate the results of the equations. The program will display the results.

5. **Print Invalid Equations**: Use option 5 to print and list all invalid equations.

6. **Print All Results to Output File**: Choose option 6 to save all equation results, both valid and invalid, to an output file named "output.txt."

7. **Exit Program**: To exit the program, select option 7.

## Code Structure

The code is structured to provide modularity and organization.

## How to Run

To run the program, follow these steps:

1. Compile the code :
   ```bash
   gcc part1.c part2.c -o expression_program
Execute the resulting executable:
bash
Copy code
./expression_program
The program will display a menu-based interface for interacting with expressions read from a file.
