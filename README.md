# Theia
A new stack-based programming language I am designing written primarily in C.

This is not intended to be used in production. It is an experiment and research project into the process of creating a programming language.

## Components
Source code needs to go through several processes in order to be run.
I will need to code all of these.
### Lexer
First, it needs to be converted into a set of **tokens**. This is done by passing it through a *Lexer*, which tokenises each word in the source code into a specific item which can be used in later steps.
### Parser
After being tokenised, the tokens are passed through a parser, which is what enforces the "grammar" of the language by converting groups of tokens into a syntax tree.
### Interpreter
Finally, the syntax tree is passed into an interpreter, which evaluates the result.

## Designing the language
### Language Features
The language must be Turing Complete. This means it must have the following operations:
- Read memory
- Write memory
- Pointer movement
- Conditional jumps
- Loops
- Increment & Decrement
The first three can actually be done by allowing the creation of variables and lists.

On top of this, I will provide multiplication, division, modulus, and exponents, as well as a user input and and output.

#### Arithmetic Operators
|Symbol|Operation|Arity|
|-|-------------|-|
|+|Addition|2|
|-|Subtraction|2|
|*|Multiplication|2|
|/|Division|2|
|%|Modulus|2|
|^|Exponent|2|

#### List & String Operators
|Symbol|Operation|Arity|
|-|-------------|-|
|++|Concatenation|2|
|\|\||Length|1|

#### Variable Operators
|Symbol|Operation|Arity|
|-|-------------|-|
|=|Storage|3|
|$|Retrieval|1|

Storage takes three operands because we need to take a type, variable name, and the value.

#### Other Operators
|Symbol|Operation|Arity|
|-|-------------|-|
|:|Output|1|

### Language Structure
The language will work on multiple stacks, one for each data type. Stacks will contain values and pointers to data, on which operations will occur. Expressions will be written in Reverse Polish Notation (AKA PostFix Notation) to simplify the language. This also benefits the user as the order of operations for RPN is unambiguous.

### Libraries
I will make use of a linked list library we used in the First Year of my CS degree, as it is easily accessible and modifiable, and I have experience using it. I will also include the Stack extension to the library because it is useful.