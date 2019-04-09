function result = SortDist(p,M);

% calculate 10 distance values away from a new point x 
% sort them in ascending order
% return top 3 values
stuff = eye(10);
distances = stuff(1,:);
[rows columns]=size(M);
[x columns]=size(p);
%if (columns ~=2 | x~=1)
    %error('Only works for two dimensional data points');
%end

for i = 1:rows
    squarex = (p(1,1) - M(i,1)).^2;
    squarey = (p(1,2) - M(i,2)).^2;
    distance = sqrt(squarex + squarey);
    distances(1,i) = distance;
end
sortedDists = sort(distances);
result = sortedDists(:,1:3)
    
        