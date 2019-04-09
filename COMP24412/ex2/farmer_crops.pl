:- use_module(library(clpfd)).

crops_eqs([A, B, C, D, E, F]) :-
  A #\= B, A #\= C, A #\= D, A #\= F,
  B #\= C, B #\= D,
  C #\= D, C #\= E,
  D #\= E, D #\= F,
  E #\= F.

crops3([A, B, C, D, E, F]) :-
  crops_eqs([A, B, C, D, E, F]),
  [A, B, C, D, E, F] ins 1..3,
  label([A, B, C, D, E, F]).

crops4([A, B, C, D, E, F]) :-
  crops_eqs([A, B, C, D, E, F]),
  [A, B, C, D, E, F] ins 1..4,
  label([A, B, C, D, E, F]).
