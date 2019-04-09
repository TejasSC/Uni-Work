mem_of(X, [X|T]). %base case here, step case below
mem_of(X, [H|T]) :-
  mem_of(X, T).

isa_list([]).
isa_list([Head | Tail]) :-
  isa_list(Tail).

nonmem_of(_X,[]).
nonmem_of(X, [H|T]) :-
  X \== H, %X is different from head
  nonmem_of(X, T). %X is not in tail

bigger_than_two([_,_,_|_]).
%doesn't produce true if heads are [X] and X
same_head([X|_],[X|_]).

same_second([_,X|_],[_,X|_]).

%prefix - is one list a prefix of another
prefix([],[]).
prefix([],X).
prefix(X,[]).
prefix([HA|TA],[HB|TB]) :-
  HA == HB,
  prefix(TA,TB).

%define a predicate for all elements in a list being different
allDiff([]).
allDiff([X|XS]) :-
  nonmem_of(X, XS),
  allDiff(XS).
