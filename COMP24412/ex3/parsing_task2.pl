%Following in (consumed, left behind) format, i.e.
%This asks what values we can give to W, such that we get an s by
%consuming the symbols in W, leaving nothing behind.
noun([alloy|W],W).
noun([carbon|W],W).
noun([steel|W],W).
noun([woman|W],W).
noun([man|W],W).
verb([shoots|W],W).
verb([is|W],W).
verb([contains|W],W).
det([the|W],W).
det([an|W],W).
det([a|W],W).

noun_phrase(A,C) :- (det(A,B), noun(B,C));noun(A,C).
verb_phrase(A,C) :- (verb(A,B),noun_phrase(B,C));verb(A,C).
sentence(A,C) :- noun_phrase(A,B), verb_phrase(B,C).
