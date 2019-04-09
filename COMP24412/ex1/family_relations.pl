%Is X the father of Y?
father(X, Y) :-
  man(X),
  (parents(X,_,Y); parents(_,X,Y)).

%Is X the mother of Y?
mother(X, Y) :-
  woman(X),
  (parents(X,_,Y); parents(_,X,Y)).

%Are X and Y siblings?
sibling(X,Y) :-
  X \== Y,
  ((father(A,X),father(A,Y));
  (mother(A,X),mother(A,Y))).

%Is X a brother to Y?
brother(X, Y) :-
  man(X),
  sibling(X, Y).

%Is X a sister to Y?
sister(X, Y) :-
  woman(X),
  sibling(X, Y).

%Is X Y's first cousin?
% Parents of X and Y, who must be different people, must be siblings
first_cousin(X,Y) :-
  X \== Y,
  ((father(A,X),father(B,Y));
  (father(A,X),mother(B,Y));
  (mother(A,X),father(B,Y));
  (mother(A,X),mother(B,Y))),
  sibling(A,B).

ancestor(X,X) :- false.
ancestor(X,Y) :-
    mother(X,Y); father(X,Y);
    ((mother(X,Z); father(X,Z)),
    ancestor(Z,Y)).

cousin(X,X) :- false.
cousin(X,Y) :-
  ancestor(Z,X),
  ancestor(Z,Y).
