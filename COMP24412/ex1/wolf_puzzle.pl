is_pos(south).
is_pos(north).
is_pos(_) :- false.

isa_list([]).
isa_list([Head | Tail]) :-
  isa_list(Tail).

%true iff both arguments are opposite sides of the river
side_opposite(X,Y) :-
  X \== Y.

%states that are allowed
fwgc(Farmer, Wolf, Goat, Cabbage) :-
  (Farmer == north; Farmer = south),
  (Wolf == north; Wolf = south),
  (Goat == north; Goat = south),
  (Cabbage == north; Cabbage = south).

is_state(fwgc(north, north, north, north)).%safe
is_state(fwgc(north, north, north, south)).%safe
is_state(fwgc(north, north, south, north)).%safe
is_state(fwgc(north, north, south, south)).
is_state(fwgc(north, south, north, north)).
is_state(fwgc(north, south, north, south)).%safe
is_state(fwgc(north, south, south, north)).
is_state(fwgc(north, south, south, south)).
is_state(fwgc(south, north, north, north)).
is_state(fwgc(south, north, north, south)).
is_state(fwgc(south, north, south, north)).%safe
is_state(fwgc(south, north, south, south)).
is_state(fwgc(south, south, north, north)).
is_state(fwgc(south, south, north, south)).%safe
is_state(fwgc(south, south, south, north)).%safe
is_state(fwgc(south, south, south, south)).%safe

safestate(fwgc(north, north, north, north)).
safestate(fwgc(north, north, north, south)).
safestate(fwgc(north, north, south, north)).
safestate(fwgc(north, south, north, south)).
safestate(fwgc(south, north, south, north)).
safestate(fwgc(south, south, north, south)).
safestate(fwgc(south, south, south, north)).
safestate(fwgc(south, south, south, south)).

%initial setup of game
puzzlestate_moves(fwgc(south, south, south, south), []).
