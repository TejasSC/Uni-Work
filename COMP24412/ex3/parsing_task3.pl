%Following in (consumed, left behind) format, i.e.
%This asks what values we can give to W, such that we get an s by
%consuming the symbols in W, leaving nothing behind.
%Uses definite clause grammars
noun([alloy]).
noun([carbon]).
noun([steel]).
noun([woman]).
noun([man]).
verb([shoots]).
verb([is]).
verb([contains]).
det([the]).
det([an]).
det([a]).

noun_phrase(A) :- (det(A,B), noun(B,C));noun(A,C).
verb_phrase(A) :- (verb(B),noun_phrase(B,C));verb(A,C).
sentence(A) :- noun_phrase(B), verb_phrase(C).
