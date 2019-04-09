function result = diagonalSum(m)
% returns 1 if sum from left top bottom right = left bottom to right top 


[height width] = size(m);
if (width ~=height)
    error('Only for square matricies');
end
lr = sum(diag(m));
rl = sum(diag(m(:,width:-1:1))); % go ACROSS but IN OPPOSITE direction
% both method still go down though 
result = (lr==rl)
