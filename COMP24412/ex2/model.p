fof(one, axiom, ![X] : (horn(X) => (sax(X) | brass(X)) & ~(sax(X) & brass(X)))).
fof(two, axiom, ![X] : (brass(X) => (trumpet(X) | trombone(X)) & ~(trumpet(X) & trombone(X)))).
fof(three, axiom, ![X, L] : (cons(X, L) != empty)).
fof(four, axiom, ![X0, X1, L0, L1] : ((cons(X0, L0) = cons(X1, L1)) => (X0=X1 & L0=L1))).
fof(five, axiom, ![X, L] : (sublist(L, cons(X,L)))).
fof(six, axiom, ![X,Y,Z] : ((sublist(X,Y) & sublist(Y,Z)) => sublist(X,Z))).
fof(seven, axiom, ![X] : ~sublist(X,X)).
