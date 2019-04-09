load ORLfacedata;
%Getting all subjects data

X = data(:, :);
Y = labels(:, :);
accuracies = ones(40,50);
newYtr = ident(40);

for subject = 1:40
  for dataSet = 1:50
    [Xtr(:,:,dataSet), Xte(:,:,dataSet), Ytr(:,dataSet), Yte(:,dataSet)] = PartitionData(X,Y,5);
    %Xtr -> Xtr with ones as first
    exfTrain = [ones(size(Xtr(:,:,dataSet),1),1),Xtr(:,:,dataSet)];
    %Ytr -> change to matrix instead of vector
    %for val = 1:size(Ytr,1)
    %  for subject=1:40
    %    if (subject == Ytr(val,1))
    %      newYtr(subject,:) = 
    %    end
    %  end

    %end
    weightMatrix = pinv(exfTrain)*;

    exfTest = [ones(size(Xte(:,:,dataSet),1),1),Xte(:,:,dataSet)];
    predictions = exfTest * weightMatrix;
  end

end

%for dataSet = 1:50
    %

    %%Xtr -> Xtr with ones as first
    %exfTrain = [ones(size(Xtr(:,:,dataSet),1),1),Xtr(:,:,dataSet)];
    %%Ytr -> change to matrix instead of vector
    %weightMatrix = pinv(exfTrain)*diag(Ytr);

    %exfTest = [ones(size(Xte(:,:,dataSet),1),1),Xte(:,:,dataSet)];
    %predictions = exfTest * weightMatrix;
%end
