# LizScript

LizScript is an interpreted functional language made for specifying policies in
applications that need guarantees of memory safety and eventual completion. The
LizScript interpreter only uses static and stack memory, with no heap
allocations, making it safe for use in long running applications on embedded
devices. All recursion is bounded, ensuring that the interpreter will never get
stuck in an infinite loop or overflow the stack.

LizScript is a strongly-typed language with type inference. As a functional
language, functions in LizScript are first-class. In addition to functions,
LizScript has 4 basic types: integers, floating point numbers, characters,
and booleans. As a purely functional language, functions in LizScript take
one input and produce one output. The language has no support for collections,
such as lists or tuples. 

## Building

A simple LizScript interpreter can be built by running `make` in this directory.
The binary produced is `./build/liz`. 

To compile and run all tests, simply invoke `make test`.

## Example LizScript programs:

Calculate the 10th Fibonacci number:
```
(func fib
  (switch 0
    (((= 1) #x) 1)
    (((> 1) #x)
      ((+ (fib ((- 1) #x))) (fib  ((- 2) #x)))
    )
  )
  (fib 10)
)
```

Find the least common multiple of 3 and 8:
```
(func lcm
  (let b #x
    (func lcm_in
      (switch #x
        (((> 0) ((% mult) #x)) (lcm_in ((+ b) #x)))
      )
      (lcm_in b)
    )
  )
  (let mult 3 (lcm 8))
)
```
