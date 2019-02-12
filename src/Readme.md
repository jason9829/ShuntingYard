## Explanation of the algorithm
# Sections
[Example without brackets](#ex1) Example without brackets

# <a name="ex1"></a> DETAIL SECTION
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
Since there are operator in the Operator Stack(X), the comparison of precedence between two operators
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
