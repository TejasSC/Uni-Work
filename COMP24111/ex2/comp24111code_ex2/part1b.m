load ORLfacedata;
%Getting all subjects data

X = data(:, :);
Y = labels(:, :);

for dataSet = 1:50
    [Xtr(:,:,dataSet), Xte(:,:,dataSet), Ytr(:,dataSet), Yte(:,dataSet)] = PartitionData(X,Y,5);
end

%LOOCV implementation here
maxAccK = 0;
kValOpt = 1;
for k = 1:40
    trainsRight = 0;
    for l = 1:200
        A = knearest(k, Xtr(l, :, 1), Xtr([1:l-1, l+1:200], :, 1), Ytr([1:l-1, l+1:200], 1));
        if (A == Ytr(l))
            trainsRight = trainsRight + 1;
        end
    end
    trainAccK = trainsRight / 200;
    if (trainAccK > maxAccK)
        maxAccK = trainAccK;
        kValOpt = k;
    end
end

%whatever optimum k is, compute training accuracy
testsRight = 0;
for testNum = 1:200
    if (knearest(kValOpt, Xte(testNum,:,1), Xtr(:,:,1), Ytr) == Yte(testNum))
        testsRight = testsRight + 1;
    end
end
testAcc = testsRight/200;

accuracies = ones(1,50);
subjects = ones(1,200);
minAcc = 1;
for dataSet = 1:50
  kNNtestsRight = 0;
  for testNum = 1:200
      if (knearest(kValOpt, Xte(testNum,:,dataSet), Xtr(:,:,dataSet), Ytr) == Yte(testNum))
          kNNtestsRight = kNNtestsRight + 1;
      end
  end
  accuracies(1,dataSet) = kNNtestsRight/200;
  if (accuracies(1,dataSet) < minAcc)
    minAcc = accuracies(1,dataSet);
  end
end
accuracyStDev = std(accuracies);
avgAccuracy = mean(accuracies);
