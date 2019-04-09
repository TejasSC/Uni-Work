load ORLfacedata;
%Getting subjects 1 and 30s data
X = data([1:10, 291:300],:);
Y = labels([1:10, 291:300],:);
accuracies = ones(1,50);
for dataSet = 1:50
  [Xtr, Xte, Ytr, Yte] = PartitionData(X,Y,3);

  %Use training data to train model to optimise weights
  %Xtr -> Xtr with ones as first
  exfTrain = [ones(size(Xtr,1),1),Xtr];
  %Ytr -> 1, -1
  for i = 1:size(Ytr,1)
      if(Ytr(i,1) ~= 1)
          Ytr(i,1) = -1;
      end
  end
  weights = pinv(exfTrain)*Ytr;

  %Xte -> Xte with ones as first column
  exfTest = [ones(size(Xte,1),1),Xte];
  %multiplying expanded feature matrix and weights
  %now calculating list of predictions based on given weights
  predictions = exfTest*weights;
  %Mapping positive real predictions to 1, negatives to 30
  for i = 1:size(predictions,1)
    if(predictions(i,1) < 0)
      predictions(i,1) = 30;
    else
      predictions(i,1) = 1;
    end
  end
  %Calculating how many correct classifications there were
  numCorrect = 0;
  for i = 1:size(predictions,1)
    if(Yte(i,1)==predictions(i,1))
      numCorrect = numCorrect + 1;
    end
  end
  accuracies(1,dataSet) = numCorrect/14;
end
x = 1:1:50;
figure(1); plot(x,accuracies, 'x');
ShowResult(X,Y,accuracies,5);
