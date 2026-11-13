;;; Lab 7: Circle Statistics
;;; Csci 6636 / 4536 Fall 2025
;;; Made by Ryan Godburn and Matthew Williams
;;; This program calculates circle statistics given a diameter

;; Calculate radius from diameter
(define (calc-radius diameter)
  (/ diameter 2.0))

;; Calculate circumference from diameter
(define (calc-circumference diameter)
  (* 3.14159265358979323846 diameter))

;; Calculate area from radius
(define (calc-area radius)
  (* 3.14159265358979323846 radius radius))

;; Print the results table for a given diameter
(define (print-results diameter)
  (let* ((radius (calc-radius diameter))
         (circumference (calc-circumference diameter))
         (area (calc-area radius)))
    (display "Diameter = ")
    (display (exact->inexact diameter))
    (newline)
    (display "Radius = ")
    (display radius)
    (newline)
    (display "Circumference = ")
    (display circumference)
    (newline)
    (display "Area = ")
    (display area)
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
(define (circle-stats)
  (display "Circle Statistics Calculator")
  (newline)
  (display "==============================")
  (newline)
  (newline)
  (main-loop))

;; Run the program
(circle-stats)
