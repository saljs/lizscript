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

An implementation of least common multiple finder.
