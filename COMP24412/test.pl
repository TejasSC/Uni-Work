:- use_module(library(clpfd)).

rows_sum([A1,A2,A3,B1,B2,B3,C1,C2,C3], Sum):-
  A1+A2+A3 #= Sum,
  B1+B2+B3 #= Sum,
  C1+C2+C3 #= Sum.
cols_sum([A1,A2,A3,B1,B2,B3,C1,C2,C3], Sum):-
  A1+B1+C1 #= Sum,
  A2+B2+C2 #= Sum,
  A3+B3+C3 #= Sum.

evenA([]).
evenA(X) :-
  X = [_|T1], T1 = [_|T2], evenA(T2).

evenB([]).
evenB([List1|List2]) :- evenB(List1), evenB(List2).

evenC([]).
evenC([X,Y]) :- evenC(Z).

evenD([]).
evenD([_,_|Tail]) :- evenD(Tail).

%heavier(concrete,wood).
heavier(metal,wood).
%heavier(metal,feather).
heavier(wood,paper).
%heavier(X,Z) :- heavier(X,Y), heavier(Y,Z).
is_heavier(X,Y) :- heavier(X,Y).
is_heavier(X,Z) :- heavier(X,Y), is_heavier(Y,Z).

child_throwsto(anne, peter).
child_throwsto(peter, iana).
child_throwsto(iana, anne).
child_throwsto(jackie, fang).
child_throwsto(fang, paolo).
child_throwsto(paolo, jackie).


ballfrom_reaches_lvia(From, To, [To]) :-
  child_throwsto(From, To).
ballfrom_reaches_lvia(From, To, [Neighbour|Path]) :-
  child_throwsto(From, Neighbour),
  ballfrom_reaches_lvia(Neighbour,To,Path).

p([],X,X).
p([X|Xs], Ys, [X|Zs]) :-
  p(Xs, Ys, Zs).

tasklist([]).
tasklist([X|Xs]) :-
  tasklist(Xs).

tasklist2([X|Xs]) :-
  tasklist2(Xs).
tasklist2([]).

task(A).
task(R).
task(S).
task(T).
task(B).
task(C).
task(L).
task(M).
task(N).

abs_moved([],[]).
abs_moved([X],[X]) :-
    task(X).
abs_moved([a, X | Xs], [Y, a | Ys]) :-
    task(X),
    task(Y),
    abs_moved([X|Xs],[Y|Ys]).
abs_moved([E, X | Xs], [E, Y | Ys]) :-
    task(X),
    task(Y),
    dif(E,a),
    task(E),
    abs_moved([X|Xs],[Y|Ys]).
