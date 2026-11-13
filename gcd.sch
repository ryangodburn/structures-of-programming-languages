;; ------------------------------------------------- Top-level
(define (run)
  (display "Greatest Common Divisor")
  (newline)
  (display "Enter two integers (0 0 to end): ")
  (newline)
  (let ((n1 (read)) ; bind name to meaning.
        (n2 (read))) ; ends the list of local symbols.
    (cond ((and (= n1 0) (= n2 0))
           (display "Exiting.") ; Assuming this is what happens on 0 0
           (newline))
          (else
           (gcdprint n1 n2)
           (run))) ; recursive call for loop.
    ) ; ends the let.
  ) ; ends the define.

;;; ---------------------------------------------- Calling gcd
(define (gcdprint a b)
  (let ((f (list "The gcd of " a " and " b " is " (mygcd a b))))
    ; ends the list of local symbols.
    (for-each display f)
    (newline)
    ) ; ends the let.
  ) ; ends the define.

;;; -------------------------------- The gcd function in Scheme
(define (mygcd x y)
  (cond ((or (< x 0) (< y 0)) (mygcd (abs x) (abs y)))
        ((< x y) (mygcd y x))
        ((= y 0) x)
        (else (mygcd y (remainder x y)))
        )
  )
