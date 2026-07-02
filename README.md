# Theia
A new stack-based programming language I am designing written primarily in C.

This is not intended to be used in production. It is an experiment and research project into the process of creating a programming language.

## Language Features
The language must be Turing Complete. This means it must have the following operations:
- Read memory
- Write memory
- Pointer movement
- Conditional jumps
- Loops
- Increment & Decrement
The first three can actually be done by allowing the creation of variables and lists.

On top of this, I will provide multiplication, division, and exponents, as well as a user input and and output.

## Language Structure
The language will work on a stack. This stack will contain values and pointers to data, on which operations will occur. Expressions will be written in Reverse Polish Notation (AKA PostFix Notation) to simplify the language. This also benefits the user as the order of operations for RPN is unambiguous.

## Libraries
I will make use of a linked list library we used in the First Year of my CS degree, as it is easily accessible and modifiable.