load ORLfacedata;
%Getting subjects 1 and 30s data
X = data([1:10, 291:300],:);
Y = labels([1:10, 291:300],:);

testResults = ones(50,6);
trainResults = ones(50,6);
avgTests = ones(1, 6);
avgTrains = ones(1, 6);
%Testing different values of k
for k = 1:6
    %Must partition dataset for each value of k
    for i = 1:50
        [Xtr, Xte, Ytr, Yte] = PartitionData(X,Y,3);

        %calculating the correct number of correct classifications
        testsRight = 0;
        for testNum = 1:14
            if (knearest(k, Xte(testNum,:), Xtr, Ytr) == Yte(testNum))
                testsRight = testsRight + 1;
            end
        end
        testResults(i,k) = testsRight/14;

        trainsRight = 0;
        for trainNum = 1:6
            if (knearest(k, Xtr(trainNum,:), Xtr, Ytr) == Ytr(trainNum))
                trainsRight = trainsRight + 1;
            end
        end
        trainResults(i,k) = trainsRight/6;
    end
    avgTests(1, k) = mean(testResults(:,k));
    avgTrains(1, k) = mean(trainResults(:,k));
end
x = 1:1:6;
figure(1); errorbar(x, avgTests, std(testResults));
%ShowResult(X,Y,testResults,6);
figure(2); errorbar(x, avgTrains, std(trainResults));
%ShowResult(X,Y,trainResults,6);
