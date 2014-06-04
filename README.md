#Calculate
##Commandline based calculator

No variables, no functions, just basic calculator functions.
###Supported operators:
* +
* -
* *
* /
* %
* ^

### Grammar:
```EBNF
start: expression;
expression: expression, operator, expression | number;
number: "\d+";
operator: "[+-/*^%]|**|//";
```

### How To Use:

```BASH
calculate 20 + 5 * 2
```

```BASH
calculate
> 30 - 5
    25
> help
-helptext-
> quit
```

### To-do:
* Add support for garbage collection
* Make better use of C++0x features?
