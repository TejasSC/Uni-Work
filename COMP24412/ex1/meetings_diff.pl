% Explicity state the six students
student(student1).
student(student2).
student(student3).
student(student4).
student(student5).
student(student6).

mem_of(X, [X|T]). %base case here, step case below
mem_of(X, [H|T]) :-
  mem_of(X, T).

%constraint 3
nonmem_of(_X,[]).
nonmem_of(X, [H|T]) :-
  X \== H, %X is different from head
  nonmem_of(X, T). %X is not in tail

allDiff([]).
allDiff([X|XS]) :-
  nonmem_of(X, XS),
  allDiff(XS).

areStudents([]).
areStudents([X|XS]) :-
  student(X),
  areStudents(XS).

%constraint 1,4
isStudent(X-Y, S) :-
  X == S;
  Y == S.

%constraint 2
is_pair_there([],_) :- false.
is_pair_there([X-Y|XS], A-B) :-
  (X == A, Y == B);
  (X == B, Y == A);
  is_pair_there(XS, A-B).

%swapped constraints at bottom 
meetings_one_two_three(A-B, C-D, E-F) :-
  allDiff([A-B, C-D, E-F]),
  areStudents([A, B, C, D, E, F]),
  isStudent(C-D, student6),
  isStudent(A-B, student1),
  nonmem_of(student1-student4, [A-B, C-D, E-F]),
  is_pair_there([A-B, C-D, E-F], student2-student3).
