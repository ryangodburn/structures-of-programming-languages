\ ===== circles.fs =====
\ Ryan Godburn & Matthew Williams
\ Integer-only circle tables
\ You can run either:
\   11 12 run              \ no sentinel; processes all items on stack
\ or
\   0 200 11 10 -3 run     \ sentinel-first; stops at the 0

\ --- math words (each takes diameter d and returns a value) ---

: radius      ( d -- r )    \ Calculate radius from diameter.
  2 / ;                     \ r = d / 2

: circumference ( d -- c )  \ Calculate circumference from diameter.
  22 7 */ ;                 \ c = floor(d * 22 / 7), using the approximation π ≈ 22/7.
                            \ */ is a scaled integer multiply-divide word.

: area        ( d -- a )    \ Calculate area from diameter.
                            \ a = floor((circumference * radius)/2)
  dup >r                    \ ( d ) -> ( )  | Save a copy of the diameter 'd' on the return stack. R: ( d )
  22 7 */                   \ ( d ) -> ( c ) | Calculate circumference 'c'.
  r> 2 /                    \ ( c ) -> ( c r ) | Retrieve 'd' from return stack, calculate radius 'r'. R: ( )
  * 2 /                     \ ( c r ) -> ( a ) | Calculate (c*r)/2 to get the area 'a'.
;

\ --- output words ---

: show-one ( d -- )         \ Display all calculated properties for a single diameter.
  cr                        \ Start on a new line.
  dup ." Diameter = " . cr
  dup 2 /           ." Radius = " . cr
  dup 22 7 */       ." Circumference = " . cr
  dup area          ." Area = " . cr
  cr                        \ Add a blank line for spacing.
  drop                      \ Remove the original diameter from the stack.
  ;

: run ( ... [0] -- )         \ Main loop to process diameters from the stack.
  cr ." Lab 2-Forth: Circle" cr    \ Program Title 
 cr ." By: Ryan Godburn & Matthew Williams" cr 
  begin                      \ Start an indefinite loop.
    depth 0= if exit then    \ If stack is empty, exit the loop (for non-sentinel case).
    dup 0= if drop 	     \ If the next input is 0 then...
	cr ." Terminating Program..." cr  \ Print once at end
	exit then \ If top item is a 0 (sentinel), drop it and exit.
    dup 0< if               \ Check if the diameter is negative.
      cr ." Diameter " dup . ." is negative; skipping." cr drop \ If so, print error and drop it.
    else
      show-one              \ Otherwise, process and show the circle's properties.
    then
  again                     \ Loop back to the beginning.
  ;
  
 0 200 11 10 -3 run 		\ Test Case