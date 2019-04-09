:- use_module(library(clpfd)).

%Equations for Cows and chikens
cows_chicken_eqs(Cows, Chicken) :-
  65 #= Cows + Chicken,
  CowsFeet #= Cows * 4,
  ChickenFeet #= Chicken * 2,
  226 #= CowsFeet + ChickenFeet.

%Result should be 48 cows, 17 chickens
cows_chicken(Cows, Chicken) :-
  Cows in 0..65,
  Chicken in 0..65,
  cows_chicken_eqs(Cows, Chicken).
