# ft_containers

## Project's brief

This project is a 42 school project. The goal was to recode from scratch some 
C++98 containers from the standard library:
- vector
- queue
- list
- stack
- map

and as bonuses:
- deque
- set
- multiset
- multimap

## Key Concepts:
This project uses MetaProgramming, through the usage of template arguments, and
the usage of SFINAE technique. (see file ft\_utils.hpp for some SFINAE
implementations).

The underlying goal was to discover metaprogramming. Using template arguments
to force the compiler to produce the necessary functions, with the variable
types set in place of those template arguments.

The template arguments allow us to write the code once, it is very generic.

## Iterator traits:
The iterator traits class has been reimplemented, it allows us to make sure,
all iterators inherit of some basic typedef (ex: _value\_type_,
_difference\_type_, ...)

## Shortcuts:

# Coding deque class (bonus):
Deque was coded first, in order to reuse it as a base class for the classes
Stack, and queue.

# Coding rb\_tree class (extra bonus):

This class was coded in an attempt to give a base class to map, multimap, set
and set. It is a reimplementation of a red black tree. Coded in C at the
core of balancing functions of the tree, with tripple ref pointers usage.
See README.md in Red\_black\_tree folder.
