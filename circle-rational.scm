;;; Lab 7: Circle Statistics - Extra Credit Version
;;; Csci 6636 / 4536 Fall 2025
;;; Made by Ryan Godburn and Matthew Williams
;;; This program calculates circle statistics using rational arithmetic

;; Use a rational approximation of pi (22/7 or a better fraction)
;; For better accuracy, using 355/113 which is accurate to 6 decimal places
(define pi-rational 355/113)

;; Alternative: use 22/7 for simpler rational arithmetic
;; (define pi-rational 22/7)

;; Calculate radius from diameter (exact rational)
(define (calc-radius diameter)
  (/ diameter 2))

;; Calculate circumference from diameter (exact rational)
(define (calc-circumference diameter)
  (* pi-rational diameter))

;; Calculate area from radius (exact rational)
(define (calc-area radius)
  (* pi-rational radius radius))

;; Print the results table for a given diameter using rational arithmetic
(define (print-results diameter)
  (let* ((radius (calc-radius diameter))
         (circumference (calc-circumference diameter))
         (area (calc-area radius)))
    (display "Diameter = ")
    (display diameter)
    (if (not (integer? diameter))
        (begin
          (display " (exact: ")
          (display diameter)
          (display ")"))
        '())
    (newline)
    (display "Radius = ")
    (display radius)
    (newline)
    (display "Circumference = ")
    (display circumference)
    (display " (approx: ")
    (display (exact->inexact circumference))
    (display ")")
    (newline)
    (display "Area = ")
    (display area)
    (display " (approx: ")
    (display (exact->inexact area))
    (display ")")
    (newline)
    (newline)))

;; Process a single diameter input
(define (process-diameter diameter)
  (cond
    ((= diameter 0) #f)  ; return false to signal termination
    ((< diameter 0)
     (display "Error: Diameter cannot be negative.")
     (newline)
     (newline)
     #t)  ; return true to continue
    (else
     (print-results diameter)
     #t)))  ; return true to continue

;; Main loop - recursively read and process diameters
(define (main-loop)
  (display "Enter the diameter of a circle (0 to quit): ")
  (let ((diameter (read)))
    (if (process-diameter diameter)
        (main-loop)  ; recursive call to continue
        (display "Program terminated.\n"))))

;; Start the program
(define (circle-stats-rational)
  (display "Circle Statistics Calculator (Rational Arithmetic)")
  (newline)
  (display "===================================================")
  (newline)
  (display "Using pi = 355/113 for exact rational calculations")
  (newline)
  (newline)
  (main-loop))

;; Run the program
(circle-stats-rational)
