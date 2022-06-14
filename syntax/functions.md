---
description: Learn the syntax of Functions.
---

# Functions

Broks' function names must start with a capital letter.

$$
F \space (p \rightarrow T, ...) \space \rightarrow T'= B.
$$

​$$F$$represents the functions name. The syntax inside the parenthesis can be repeated to represent the parameters or the inputs to the function. $$p$$ represents the parameters name and $$T$$ represents the parameters type. $$T'$$(the ' at the of the $$T$$is pronounced as prime and is allowed in function and variable names) is the functions return type. The $$\rightarrow T'$$ is optional if the function has no return value.

A could example would be the following:

```
Add (x -> Int, y -> Int) -> Int = x + y;
```

If the function has no parameters, you would just put $$()$$ instead of listing parameters.&#x20;

### Monadic functions

A monad function (discussed in more detail later on) is a function that can have multiple body expressions and statements. The syntax is fairly similar to a normal function just with a extra piece of punctuation.

$$
F \space (p \rightarrow T, ...) \space \rightarrow T'= |>  \newline B.
$$
