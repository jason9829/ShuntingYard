# Shunting Yard 
An algorithm that parse mathematical expressions into infix notation. This is one of the methods to solve the operator precedence problems in calculation (machine will read and calculate the mathematical expression without considering which operator should operated first).  

<br/>

## Table of Contents
1. [Requirements](#req)
2. [Explaination of the algorithm](#exAlgo)
   * [Example without brackets](#ex1) 
   * [Example with brackets](#ex2)
   * [Example with prefix](#ex3)
   * [Complex expression example](#ex4)
2. [Reference](#ref) 

<br/> 

## <a name="req"></a>Requirements
- Ruby
- mingw32/64
- ceedling 
- Tokenizer (forked from https://github.com/chaosAD/TokenizerSkeleton).

<br/>    
  
## <a name="exAlgo"></a> Explatination of the algorithm
### <a name="ex1"></a> 1. Example without brackets
Expression : 1 + 2 * 3

**Step 0**
```md
Expression : 1 + 2 * 3

*-----*    *-----*              X -Operator Stack
|     |    |     |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 1**
```md
Expression : 1 + 2 * 3
 current-----^
 
Push the first operand '1' into Operand Stack(Y).

*-----*    *-----*              X -Operator Stack
|     |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 2**
```md
Expression :  + 2 * 3
 current------^
 
Push the first operator '+' into Operator Stack(X).

*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 3**
```md
Expression : 2 * 3
 current-----^
Push the second operand '2' into Operand Stack(Y).
          
           *-----*
           |  2  |
*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 4**
```md
Expression :  * 3
 current------^
 
Since there are operator in the Operator Stack(X), there are comparison of precedence between two operators
'+'(in X) and '*' (before push). For this example, precedence of '*' > '+', thus '*' will be push into 
X. If the precedence of operator in X is larger than the operator of expression, then the operator of 
that operator(higher precedence).
          
*-----*    *-----*
|  *  |    |  2  |
*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 5**
```md
Expression :  3
 current------^
 
If there's no operation need to be done. Then the operand '3' will just push into Operand Stack(Y).
          
           *-----*
           |  3  |
*-----*    *-----*
|  *  |    |  2  |
*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 6**
```md
Expression :  END

Since the expression is END. The operation can be started. For basic operation(plus, minus, multiply and divisoin), 
two operands and one operator is required. So '*' will be pop out from X and '3' and '2'. And the multiplication of
'3' and '2' will be done. The results of that operation will be push back to Y.
     
           *-----*
           |  6  | <------- 3 * 2 = 6
*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 7**
```md
Expression :  END

Then operator '+' and operands '6' and '1' popped from respective stacks. And the operation on plus will be 
performed. The final answer '7' will be pushed back to Y.
                   
*-----*    *-----*              X -Operator Stack
|     |    |  7  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
  1 = 6 = 7----^
```

<br/> 

### <a name="ex2"></a> 2. Example with brackets
Expression : (1 + 2) * 3

**Step 0**
```md
Expression : (1 + 2) * 3

*-----*    *-----*              X -Operator Stack
|     |    |     |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 1**
```md
Expression : (1 + 2) * 3
 current-----^
For brackets, '(' will be push into Operator Stack no matter the precedence of previous operator.
Thus, the first operand '(' pushed into Operator Stack(X).

*-----*    *-----*              X -Operator Stack
|  (  |    |     |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 2**
```md
Expression :  1 + 2) * 3
 current------^
 
If there are no operation then the operand will be push into Operand Stack(Y).

*-----*    *-----*              X -Operator Stack
|  (  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 3**
```md
Expression : + 2) * 3
 current-----^
 
Since there are no operator after '(' so '+' will pushed into X. If there are operator after '('
Then, the comparison of predence between the operator after '(' and current operator at expression.
If the precedence of operator in the stack(operator after '(') is higher then current operator. 
Then the operation of operation in the stack will be performed first before pushing in the current
operator.
On the otherhand, if the operation in the stack has lower precedencce then the current operator at
the expression will be pushed into X.

*-----*
|  +  |
*-----*    *-----*              X -Operator Stack
|  (  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 4**
```md
Expression :  2) * 3
 current------^
 
Since there are not enough operand for operation. '2' is pushed into Y

*-----*    *-----*
|  +  |    |  2  |
*-----*    *-----*              X -Operator Stack
|  (  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```  

**Step 4**
```md
Expression :  ) * 3
 current------^
 
Since '(' are in X and ')' is met. When ')' met, the operation in the bracket will be done
(plus in this case). Thus '+' will be pop from X and '2' and '1' pop from Y stack. After the 
plus operation(1 + 2). The '(' will be pop out and ')' will be remove(both discarded). Then answer
will be pushed back into Y.

           *-----*
           |     |
*-----*    *-----*              X -Operator Stack
|     |    |  3  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
 1 + 2 = 3 ---^  
   
```


**Step 5**
```md
Expression :  * 3
 current------^
 
Since there are not operator in X. '*' will be pushed into X.

           *-----*
           |     |
*-----*    *-----*              X -Operator Stack
|  *  |    |  3  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 6**
```md
Expression :   3
 current-------^
 
Since there are not enough operannds for multiplication. '3' Was pushed into X.

           *-----*
           |  3  |
*-----*    *-----*              X -Operator Stack
|  *  |    |  3  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 7**
```md
Expression :   END

The expression reached the END. Thus the last operation(multiplication of '3' and '3')
will be performed. The final answer will be push back into Y.

*-----*    *-----*              X -Operator Stack
|     |    |  9  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
 3 * 3 = 9 ---^
```  


<br/> 

### <a name="ex3"></a> 3. Example with prefix
Expression : 9 + -1

**Step 0**
```md
Expression : 9 + -1

*-----*    *-----*              X -Operator Stack
|     |    |     |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 1**
```md
Expression : 9 + -1
 current-----^
Since the operand stack are empty, '9' will pushed into Y.

*-----*    *-----*              X -Operator Stack
|     |    |  9  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 2**
```md
Expression : + -1
 current-----^
 
Since the operator stack are empty, '+' will pushed into X.

*-----*    *-----*              X -Operator Stack
|  X  |    |  9  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 3**
```md
Expression : -1
 current-----^
 
Since there are '+' operator in X, there are a comparison of precedence between
operator in the stack('+') and operator at expression('-'). '-' are binded with 1
(there are already an addition operator) so this '-' mean unary minus of 1. So,
the operator '-' will combine with '1' to become '-1'. And '-1' then pushed into Y.

           *-----*
           | -1  |
*-----*    *-----*              X -Operator Stack
|  +  |    |  9  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 4**
```md
Expression : END

Since the expression is ENDed. The operation of '+' between '-1' and '9' is performed.
The final answer '8' pushed back into Y.

*-----*    *-----*              X -Operator Stack
|     |    |  8  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```  

<br/> 

### <a name="ex4"></a> 4. Complex expression example
Expression : 100 *(8 --2 *4) / 5

**Step 0**
```md
Expression : 100 *(8 --2 *4) / 5

*-----*    *-----*              X -Operator Stack
|     |    |     |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 1**
```md
Expression : 100 *(8 --2*4) / 5
 current-------^
 
Since the operand stack are empty, '100' will pushed into Y.

*-----*    *-----*              X -Operator Stack
|     |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 2**
```md
Expression :  *(8 --2*4) / 5
 current------^
 
Since the operator stack are empty, '*' will pushed into X.

*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 3**
```md
Expression :  (8 --2*4) / 5
 current------^
 
Since '(' is at the expression, it will be push directly into X.

*-----*
|  (  |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 3**
```md
Expression :  8 --2*4) / 5
 current------^
 
'8' is pushed directly into Y.

*-----*    *-----*
|  (  |    |  8  |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 4**
```md
Expression :  --2*4) / 5
 current------^
 
Since there are no operator after '(', '-' will pushed into X.

*-----*      
|  -  |      
*-----*    *-----*
|  (  |    |  8  |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 5**
```md
Expression :  -2*4) / 5
 current------^
 
The next '-' is prefix(because there are only an binary operator '-'). 

*-----* 
|  -  | 
*-----*      
|  -  |      
*-----*    *-----*
|  (  |    |  8  |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 5**
```md
Expression :  [-2]*4) / 5
 current--------^
 
The prefix '-' then combined with '2' to become '-2' then pushed into Y.

*-----*    *-----*  
|  -  |    | -2  |  
*-----*    *-----*
|  (  |    |  8  |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 6**
```md
Expression :   *4) / 5
 current-------^
 
Since there are already a binary operator('-'), there are a needed to compare the
precedencce between '-' and '*'. '*' has higher precedence so it will pushed into X.
if current operator at expression has lower precedence then the operation before it 
will be performed.

*-----*
|  *  |
*-----*    *-----*  
|  -  |    | -2  |  
*-----*    *-----*
|  (  |    |  8  |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 7**
```md
Expression :  4) / 5
 current------^
 
'4' is pushed into Y

*-----*    *-----*
|  *  |    |  4  |
*-----*    *-----*  
|  -  |    | -2  |  
*-----*    *-----*
|  (  |    |  8  |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 8**
```md
Expression :  ) / 5
 current------^
 
')' is met so the operation so the operation within the bracket will be done.
First '4' and '-2' will be popped out from Y.
Then '*' pop from X and the multiplication of '4' and '-2' will be performed.
The answer '-8' will then push into Y.

*-----*    *-----*  
|  -  |    | -8  |  
*-----*    *-----*
|  (  |    |  8  |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y  
```

**Step 9**
```md
Expression :  ) / 5
 current------^
      
Since '(' is not yet meet, the operation within bracket continued.
'-' , '-8' amd '8' pop out from respective stacks.
Subtraction of 8 and -8 performed. 
The answer 8 --8 = 16 push into Y.
Then both '(' and ')' are discarded.

           *-----*
           |  16 |
*-----*    *-----*              X -Operator Stack
|  *  |    | 100 |              Y -Operand  Stack
*-----*    *-----*
   X          Y  
```

**Step 10**
```md
Expression :  / 5
 current------^
 
Since precedence of '*' and '/' are the same, we can determine which operation to do first
by associativity of '*' and '/' is Left-to-right which mean that, the left side of the
expression will be performed first. In this case, the multiplication of 100 and 16 will be
performed first before '/' push into X. Then, the answer of multiplication is push into Y.
      
*-----*    *-----*              X -Operator Stack
|  /  |    | 1600|              Y -Operand  Stack
*-----*    *-----*
   X          Y  
```

**Step 11**
```md
Expression :   5
 current-------^
 
'5' is push into Y

           *-----*
           |  5  |
*-----*    *-----*              X -Operator Stack
|  /  |    | 1600|              Y -Operand  Stack
*-----*    *-----*
   X          Y  
```

**Step 12**
```md
Expression :   END

Since it reach the END of the expression, so the division between 1600 and 5
is performed then the final answer 320 is push into Y. 

*-----*    *-----*              X -Operator Stack
|     |    | 320 |              Y -Operand  Stack
*-----*    *-----*
   X          Y  
```

<br/> 


## <a name="ref"></a> Reference
1. [C Operator Precedence](https://en.cppreference.com/w/c/language/operator_precedence)
2. [Operator Precedence Description](https://github.com/jason9829/ShuntingYard/blob/master/src/Readme_Precedence.md)
