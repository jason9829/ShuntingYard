
# Sections
Explanation of the algorithm with examples:
1. [Example without brackets](#ex1) 
2. [Example with brackets](#ex2)
3. [Example with prefix](#ex3)

# <a name="ex1"></a> Example without brackets
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
Push the first operand '1' into Operand Stack(Y).

Expression :  + 2 * 3

*-----*    *-----*              X -Operator Stack
|     |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 2**
```md
Push the first operator '+' into Operator Stack(X).

Expression :  2 * 3

*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 3**
```md
Push the second operand '2' into Operand Stack(Y).

Expression :  * 3
          
           *-----*
           |  2  |
*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 4**
```md
Since there are operator in the Operator Stack(X), there are comparison of precedence between two operators
'+'(in X) and '*' (before push). For this example, precedence of '*' > '+', thus '*' will be push into 
X. If the precedence of operator in X is larger than the operator of expression, then the operator of 
that operator(higher precedence).

Expression :  3
          
*-----*    *-----*
|  *  |    |  2  |
*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 5**
```md
If there's no operation need to be done. Then the operand will just push into Operand Stack(Y).

Expression :  END
          
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
Since the expression is END. The operation can be started. For basic operation(plus, minus, multiply and divisoin), 
two operands and one operator is required. So '*' will be pop out from X and '3' and '2'. And the multiplication of
'3' and '2' will be done. The results of that operation will be push back to Y.

Expression :  END
          
           *-----*
           |  6  | <------- 3 * 2 = 6
*-----*    *-----*              X -Operator Stack
|  +  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 7**
```md
Then operator '+' and operands '6' and '1' popped from respective stacks. And the operation on plus will be 
performed. The final answer '7' will be pushed back to Y.

Expression :  END
                   

*-----*    *-----*              X -Operator Stack
|     |    |  7  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
  1 = 6 = 7----^
```

# <a name="ex2"></a> Example with brackets
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
For brackets, '(' will be push into Operator Stack no matter the precedence of previous operator.
Thus, the first operand '(' pushed into Operator Stack(X).

Expression : 1 + 2) * 3

*-----*    *-----*              X -Operator Stack
|  (  |    |     |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 2**
```md
If there are no operation then the operand will be push into Operand Stack(Y).

Expression :  + 2) * 3

*-----*    *-----*              X -Operator Stack
|  (  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 3**
```md
Since there are no operator after '(' so '+' will pushed into X. If there are operator after '('
Then, the comparison of predence between the operator after '(' and current operator at expression.
If the precedence of operator in the stack(operator after '(') is higher then current operator. 
Then the operation of operation in the stack will be performed first before pushing in the current
operator.
On the otherhand, if the operation in the stack has lower precedencce then the current operator at
the expression will be pushed into X.

Expression :  2) * 3

*-----*
|  +  |
*-----*    *-----*              X -Operator Stack
|  (  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 4**
```md
Since there are not enough operand for operation. '2' is pushed into Y

Expression :  ) * 3

*-----*    *-----*
|  +  |    |  2  |
*-----*    *-----*              X -Operator Stack
|  (  |    |  1  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```  

**Step 4**
```md
Since '(' are in X and ')' is met. When ')' met, the operation in the bracket will be done
(plus in this case). Thus '+' will be pop from X and '2' and '1' pop from Y stack. After the 
plus operation(1 + 2). The '(' will be pop out and ')' will be remove(both discarded). Then answer
will be pushed back into Y.

Expression :  * 3

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
Since there are not operator in X. '*' will be pushed into X.
Expression :   3

           *-----*
           |     |
*-----*    *-----*              X -Operator Stack
|  *  |    |  3  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 6**
```md
Since there are not enough operannds for multiplication. '3' Was pushed into X.
Expression :   END

           *-----*
           |  3  |
*-----*    *-----*              X -Operator Stack
|  *  |    |  3  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 7**
```md
The expression reached the END. Thus the last operation(multiplication of '3' and '3')
will be performed. The final answer will be push back into Y.
Expression :   END

*-----*    *-----*              X -Operator Stack
|     |    |  9  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
 3 * 3 = 9 ---^
```

# <a name="ex3"></a> Example with prefix
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
Since the operand stack are empty, '9' will pushed into Y.
Expression : + -1

*-----*    *-----*              X -Operator Stack
|     |    |  9  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 2**
```md
Since the operator stack are empty, '+' will pushed into X.
Expression : -1

*-----*    *-----*              X -Operator Stack
|  X  |    |  9  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 3**
```md
Since there are '+' operator in X, there are a comparison of precedence between
operator in the stack('+') and operator at expression('-'). '-' are binded with 1
(there are already an addition operator) so this '-' mean unary minus of 1. So,
the operator '-' will combine with '1' to become '-1'. And '-1' then pushed into Y.
Expression : END

           *-----*
           | -1  |
*-----*    *-----*              X -Operator Stack
|  +  |    |  9  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```

**Step 4**
```md
Since the expression is ENDed. The operation of '+' between '-1' and '9' is performed.
The final answer '8' pushed back into Y.
Expression : END

*-----*    *-----*              X -Operator Stack
|     |    |  8  |              Y -Operand  Stack
*-----*    *-----*
   X          Y
```
