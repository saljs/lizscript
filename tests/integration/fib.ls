(func fib
  (switch 0
    (((= 1) #x) 1)
    (((> 1) #x)
      ((+ (fib ((- 1) #x))) (fib  ((- 2) #x)))
    )
  )
  (fib 10)
)

Fibonacci Sequence:
The function `fib` recursively calculates the nth Fibonacci number.
