/*******************************************/
/**    Your solution goes in this file    **/ 
/*******************************************/

/* PART 1 */

/*year_1953_1996_novels*/
year_1953_1996_novels(P) :-
    novel(P,1953) ; novel(P,1996).


/*period_1800_1900_novels*/
period_1800_1900_novels(P) :-
    novel(P,Z),
    Z >= 1800,
    Z =< 1900.

/*lotr_fans*/
lotr_fans(P) :-
    fan(P, B),
    member(the_lord_of_the_rings, B).


/*author_names*/
author_names(P) :-
    author(P, A_Books),
    fan(chandler, C_Books),
    author_check(A_Books, C_Books).

author_check(Author_Books, Fan_Books) :-
    nth(_, Author_Books, Common),
    nth(_, Fan_Books, Common),!.


/*fans_names*/
% find fans of brandon sanderson
fans_names(P) :-
    fan(P, Fan_Books),
    author(brandon_sanderson, BS_Books),
    author_check(Fan_Books, BS_Books).
    
% book_check(X, Y) :-
%     nth(_, X, C),
%     nth(_, Y, C),!.

/*mutual_novels*/
mutual_novels(P) :-
    fan(phoebe, P_Books),
    fan(ross, R_Books),
    novel_check(P, P_Books, R_Books).
    
mutual_novels(P) :-
    fan(phoebe, P_Books),
    fan(monica, M_Books),
    novel_check(P, P_Books, M_Books).
    
mutual_novels(P) :-
    fan(ross, R_Books),
    fan(monica, M_Books),
    novel_check(P, R_Books, M_Books).
    
novel_check(P, [HX|TX], List2) :-
    P = HX,
    isMember(HX,List2).
    
novel_check(P, [_|TX], List2) :-
    novel_check(P, TX, List2).

/* END OF PART 1 */


/* PART 2 */

/*isMember*/
% true when we find equal head
%\isMember([], Y).
isMember(X, [X|_]).

% recurse to next head
isMember(X, [_|T]) :-
    isMember(X, T).
   
/*isUnion*/
isUnion([], List, List).

isUnion([H|List1], List2, List3) :-
    isMember(H, List2),!,
    isUnion(List1, List2, List3).
    
isUnion([H|List1], List2, [H|List3]) :-
    isUnion(List1, List2, List3).
    
/*isIntersection*/
isIntersection([],X,[]).

isIntersection([X|R], Y, [X|Z]) :-
    isMember(X, Y), !,
    isIntersection(R, Y, Z).

isIntersection([X|R], Y, Z) :-
    isIntersection(R, Y, Z).

/*powerSet*/
powerSet(X, Y) :-
    findall(Z, powerset_generator(X, Z), Y).
    
powerset_generator([], []).

powerset_generator([_|T], Set) :-
    powerset_generator(T, Set).

powerset_generator([H|T], [H|T_Set]) :-
    powerset_generator(T, T_Set).

/*isEqual*/
isEqual(X, Y) :-
    isIntersection(X, Y, Z),
    Z = X,
    check_length(X, Y).
    
check_length([], []).
check_length([_|X], [_|Y]) :-
    check_length(X, Y).
    
/* END OF PART 2 */

/*PART 3 */

solve. % :(

/*
/* farmer wolf goat cabbage
initial_state(a,a,a,a).
final_state(b,b,b,b).

state(a,a,a,a).

unsafe(state(b, a, a, X)).
unsafe(state(a, b, b, X)).
unsafe(state(b, X, a, a)).
unsafe(state(a, X, b, b)).

take(w



opposite(A, B) :-
    A = (a,a,a,a),
    B = (a,a,a,b).
    
*/