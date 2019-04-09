x1 = factorial(15)
A = [16 3 2 13; 5 10 11 8; 9 6 7 12; 4 15 14 1]
x2B = eye(4)
x3 = sum(A(:,3))
x4 =  A(:,[1,3])
x5 = A(:,randi([1,4],1,2))
x6sumA = sum(A)
x6sumATrans = sum(A')
x6sortTrans = (sort(A'))'
Bident = eye(4)
x7a = A*Bident
x7b = A.*Bident
x8 = sum((sum(A>10))')
x9x = 1:1:100;
x9y = log(x9x);
x9 = plot(x9x,x9y)
B = eye(4);
for i=1:4
    for j=1:4
        B(i,j)=1/A(i,j);
    end;
end;
x10sumsB = sum(B(:,:))
x10shortB = sum(1./A)