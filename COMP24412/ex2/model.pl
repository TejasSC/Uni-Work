:- use_module(library(clpfd)).

% Modelling a jazz big band
%Horns
%subset of Horns: saxophone
saxophone(alto_sax_1). saxophone(alto_sax_2).
saxophone(tenor_sax_1). saxophone(tenor_sax_2).
saxophone(baritone_sax).
%subset of Horns:
trumpet(trumpet_1). trumpet(trumpet_2). trumpet(trumpet_3). trumpet(trumpet_4).
trombone(tenor_trombone_1).
trombone(tenor_trombone_2).
trombone(tenor_trombone_3).
trombone(bass_trombone).

%Rhythm section
rhythm(piano).
rhythm(bass).
rhythm(drums).
rhythm(guitar).

% Rule 1
nonmem_of(X,[]).
nonmem_of(X, [H|T]) :-
  X \== H, nonmem_of(X, T).
% Rule 2
allDiff([]).
allDiff([X|Xs]) :-
  nonmem_of(X, Xs), allDiff(Xs).
% Rule 3
allRhythm([]).
allRhythm([X|Xs]) :-
  rhythm(X), allDiff([X|Xs]), allRhythm(Xs).
% Rule 4
brass(X) :-
  trumpet(X); trombone(X).
% Rule 5
horn(X) :-
  saxophone(X); brass(X).
% Rule 6
allHorns([], _).
allHorns([X|Xs], 0) :-
  saxophone(X), allDiff([X|Xs]), allHorns(Xs, 0).
allHorns([X|Xs], 1) :-
  trumpet(X), allDiff([X|Xs]), allHorns(Xs, 1).
allHorns([X|Xs], 2) :-
  trombone(X), allDiff([X|Xs]), allHorns(Xs, 2).
allHorns([X|_], _) :- false.
% Rule 7
rhythmSection(X) :-
  length(X, 4), allRhythm(X).
% Rule 8
hornsSection(S, T, B) :-
  length(S, 5), allHorns(S, 0),
  length(T, 4), allHorns(T, 1),
  length(B, 4), allHorns(B, 2).
% Rule 9
fullBand(X, S, T, B) :-
  rhythmSection(X), hornsSection(S,T,B).
% Rule 10
isLowPitched(X) :-
  trombone(X); X==baritone_sax; X==tenor_sax_1; X==tenor_sax_2.
