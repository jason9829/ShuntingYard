# Sections
i) Description
1. [Introdution of operator precedence](#IntrOfOpPre)
2. [Working of operator precedence](#WorkOfOpPre) 

ii) [Reference](#ref) 

# <a name="IntrOfOpPre"></a> Introducction
## What is operator precedence?
Operator precedence is an order of operations which reflects the convention of 
which operation should be done first for any given mathematical expression.

## Why used operator precedence in Shunting Yard
Since computer will read the expression from left to right, it will operate the
expression based on what operator read first not based on precedence. This may
cause error in some mathemtical expression. For exaxmple,
'''md
Expression = 5 - 2 * 10
'''
By right, the multiplication of 2 and 10 should be done first but without any
precedence, the computer will calculate ("5 - 2") first then multiply by 10
which results 30 but the correct answer is -15.

# <a name="WorkOfOpPre"></a> Working of operator precedence
## Binding energy
Binding energy is the strength of bond between the operator and operand. If the
binding energy is high mean the operation of that operator will be performed first
or vice versa.

# How to know the precedence of an operator
## Low precedence in term of binding energy
If there are operand on the left hand side of the operator exclude brackets and
there are operands after the operand. Then, the operator is considered binary
(weakest precedence).
'''md
Expression = 1 + 10
  Binary-------^
'''

## High precedence in term of binding energy
If there are already an binary operator or the previous operator is an unary then 
current operator is consider unary (higher precedence than binary) 
'''md
Expression = 1 + - 10
  Unary----------^
  
  OR
  
 Expression = 1 + + - 10
  Unary-------------^ 
'''
# <a name="ref"></a> Reference
1. [Operator precedence wiki](https://en.wikipedia.org/wiki/Order_of_operations)
