;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;; Your solution goes in this file ;;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;
;PART 1
;


; part 1.1 - cycle
(defun cycle (n  l)
    ; if the first element is null
    (if (null (first l))
        ;then we will get the nil;
        (car l)
        ;else we will take the list and set the head to be the tail n times
        (dotimes (x n)
        (setq l (append (cdr l) (list (car l))))))
    l
)

; part 1.2 - split-list
(defun split-list (d l)
    (setq returnList '() temp '())
    (dolist (x l)
        (cond
            ; if delim
            ( (equalp x d)
                ;add temp to ret IF temp is not nil.
                (cond
                    ;if temp is nil, do nothing
                    ( (null temp) nil)
                    ( (null returnList) (setq returnList (list temp) temp '() ))
                    ;otherwise, add list
                    (t (setq returnList (append returnList (list temp))
                          temp '() )  ;clear temp
                        ;(print "adding to retlist: ") (write returnlist)
                    )
                ) ;end cond
            )
            ;else add x to temp
            (t 
                (setq temp (append temp (list x)))
                ;(print "temp: ") (write temp)
            )
        ) ;end cond
    ) ;end dolist
    
    ;append temp one last time, if applicable
    (cond ( (not (null temp)) (setq returnList (append returnList (list temp)))))
    
    ;return the list
    (cond
        ( (and (null returnList) (null temp)) nil)
        (t returnList)
    )
) ;end defun

; part 1.3 - range
(defun range (l)
    ;define 4 variables, least, mean, and greatest for values in the list, and count to keep track of how many there are.
    (setq least nil mean 0 greatest nil count 0)
    
    (dolist (x l)
        ;if we have not seen any values yet
        (if (= count 0)
            ;set least and greatest to be x
            (setq least x greatest x))
        ;if x < least, set least to be x
        (if (< x least)
            (setq least x))
        ;if x > greatest, set greatest to x
        (if (> x greatest)
            (setq greatest x))
        ;increment count and add x to the mean
        (setq count (+ count 1) mean (+ mean x)))
    ;if the list is null
    (if ( null l)
        ;then return the null list
        l
        ;else return a list with the desired values
        (list least (/ mean count) greatest))
)

; part 1.4 - search-count
(defun search-count (a l)
    ;count will keep track of how many times we see the atom a
    (setq count 0)
    ;iterate through the list l
    (dolist (x l)
        ; if a is in the list
        (if (equal x a)
            ;we will increment count by 1
            (setq count (+ count 1))))
    ;returning the count
    count
)

; part 1.5 - pivot
(defun pivot (n l)
    (setq ltl '() gtl '()) ; less-than / greater-than lists
    (dolist (element l)
        ; if element > n, add to gtl
        (cond ((>= element n)
            (setq gtl (append gtl (list element))))
        ; else add to ltl
            (t (setq ltl (append ltl (list element))))
        )
    ) ;end of dolist
    (list ltl gtl)
)

; part 1.6 - quicksort
(defun quicksort (l)
    (cond
        ((null l) nil)
        ((sorted? l) l)
        (t (progn
            ;set pivot to first element
            (let* ((piv (car l)) (lo-hi (pivot piv l))) ;local variables piv, lo-hi = results from pivot call
                (cond
                    ;both null - do nothing
                    ((and (null (car lo-hi)) (null (cadr lo-hi))) nil)
                    ;lo list null - sort high list -- strip the pivot
                    ((null (car lo-hi)) (append (list piv) (quicksort (cdadr lo-hi)))) ;cdadr => high list w/o first element
                    ;hi list null - sort low list -- append piv after
                    ((null (cadr lo-hi)) (append (quicksort (car lo-hi)) (list piv)))
                    ;both lists fine - qsort lo, insert piv, qsort hi
                    (t (append (quicksort (car lo-hi)) (list piv) (quicksort (cdadr lo-hi))))
                )
            )
        ))
    )
)

;small helper func for quicksort to check if list is sorted (ascending)
(defun sorted? (l)
    (cond
        ( (= (list-length l) 1) t)
        ((< (car l) (car (cdr l))) (sorted? (cdr l)))
        (nil nil)
    )
)

;
;PART 2
;

(defun match (L1 L2)
    (cond
        ((equal L1 L2) t)
        ((and (null L1) (null L2)) t)
        ( (> (list-length L1) (list-length L2)) nil) ;L1 should always have equal or less tokens
        (t (progn
            (setq iter 0)
            (cond
                ( (equal (car L1) '? )
                    ; . . .
                    ;check if there is a token to match ?
                    (if (> (list-length L2) 0)
                    ;true
                        ;check if at end of expressions
                        (if (and (null (rest L1)) (null (rest L2)))
                        ;true
                            ;end - return true
                            t
                        ;false
                            ;continue onwards
                            (match (rest L1) (rest L2))
                        )
                    ;false
                        ;no token matching ?
                        nil
                    )
                ) ;end ?
                
                ( (equal (car L1) '! )
                    ; . . .
                    ;if we get a !, call match again
                    ;if we get a ?, check char and match
                    ;if we get a token, increment L2 until we find it
                    
                    ;make sure we have a token at L2
                    (if (> 0 (list-length L2) )
                    ;true
                        nil
                    ;false
                        ;check the value of (car L1)
                        (cond
                            ;check if at end of expressions
                            ( (null (rest L1))
                                t
                            )
                            
                            ;if next in L1 is ! or ?
                            ( (or (equal (cadr L1) '!) (equal (cadr L1) '?))
                                (match (rest L1) (rest L2))
                            )
                            
                            ;if next in L1 is a token
                            ( (not (null (cadr L1)))
                                ;iterate through L2 until we find it
                                (loop for i from 1 to (- (list-length L2) 1) do
                                    (if (equal (cadr L1) (nth i L2))
                                    ;true
                                        ;found matching token at i
                                        (return (match (rest L1) (nthcdr i L2)))
                                    ;false
                                        nil
                                    )
                                ) ;end loop
                            )
                        ) ;end cond
                    ) ;end if
                ) ;end !
                
                ;else, check if tokens are equivalent
                ( (equal (car L1) (car L2))
                    ; . . .
                    (if (and (null (rest L1)) (null (rest L2)))
                    ;true
                        ;end - return true
                        (if (equal (list-length L1) (list-length L2))
                        ;true
                            t
                        ;false
                            nil
                        )
                    ;false
                        ;continue onwards
                        (match (rest L1) (rest L2))
                    )
                )
                
                ;otherwise, mismatch - return false
                (t nil)
                
                
                
            ) ;end cond
            
        ))
    ) ;end cond
) ;end match

;
;PART 3
;

; part 3.1
(defun matrix-add (l1 l2)

    (cond
        ;if the lists are null, we return null
        ( (or (null l1) (null l2)) nil)
        ;if the lists are not the same length, return an error
        ( (not (eq (list-length l1) (list-length l2))) (print "Err: L1 != L2") )
        
        (t (progn 
            ;set our temp and return value to nil
            (setq result '() temp '())

            (dolist (row l1)
                ;curL2 will cycle through the L2 list 
                (setq curl2 (car l2))
                ;for the size of each list in l1, we will cycle through
                (loop for i from 0 to (- (list-length row) 1) do
                    ;add the sum of the items from the two lists in l1 and l2 into temp
                    (setq temp (append temp (list (+ (nth i row) (nth i curl2)))))
                )
                ;We will then set l2 to point to the next value in the list
                (setq l2 (cdr l2)
                      ;result make a list with the itself and temp
                      result (append result (cons temp ()))
                      ;set temp to be null again
                      temp '())
            )
            ;return the result
            result
        ))
    )
)

; part 3.2
(defun matrix-multiply (L1 L2)
    ;for row in L1
        ;for column in L2
            ;for element length, result[row][column] = sum of products
    (cond
        ( (or (null L1) (null L2)) nil) ;return nil if we get nil input
        ;check row/column lengths
        ( (not (eq (list-length (car L1)) (list-length L2))) (print "Err: L1 row length != L2 column length!")) ; row length of L1 must equal column length of L2
        (t (progn ; progn for multiple statements
             ; do the multiplication
             (setq result '() temp '()
                   sum 0
                   length (list-length (car L1))) ; length = # row ct in L1 = column ct in L2
             ;for each row in L1
             (dolist (row L1)
                (loop for i from 0 to (- (list-length (car L2)) 1) do ;for each column in L2
                    (loop for j from 0 to (- length 1) do
                        ;multiply (nth j row) (nth i (nth j L2))
                        ;(print "multiplying ") (write (nth j row)) (write " ") (write (nth i (nth j L2)))
                        (setq sum (+ sum (* (nth j row) (nth i (nth j L2)))))
                    ) ;end summing
                    ;(print sum)
                    (setq temp (append temp (list sum))
                          sum 0) ;clear sum
                ) ;end column
                (cond ((null result) (setq result (list temp) temp '() )) ;first time - set result directly to temp
                (t (setq result (append result (list temp))       ;else - append temp to result
                      temp '())))
            )
            result
        ))
    ) ;end cond
) ;end func

; part 3.3
(defun matrix-transpose (L)
    (cond ((null L) nil)
        (t (progn
            (setq length (list-length (car L))
                  result '() temp '())
            ;
            (loop for i from 0 to (- length 1) do
                (loop for j from 0 to (- (list-length L) 1) do
                    (setq temp (append temp (list (nth i (nth j L)))))
                )
                (cond ((null result) (setq result (list temp) temp '())) ;first time
                (t (setq result (append result (list temp)) temp '())))  ;subsequent
            )
            result
        ))
    ) ;end cond
) ;end func