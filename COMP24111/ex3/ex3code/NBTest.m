function [predictLabelVector, accuracy] = NBTest(lookUpTables, matrixProbs, testAttrSet, validLabel)
  %define constants
  testsRight = 0;
  %Dimensions of the testing set, labels by attributes
  numLabels = size(testAttrSet, 1)
  numAttr = size(testAttrSet, 2);
  s = size(validLabel, 1);%storing the size of the predictLabelVector, of validLabel
  numClasses = size(matrixProbs, 1);%acquiring number of actual classes from training

  predictLabelVector = zeros(s, 1);%size of predictLabelVector
  probClassGivenFeature = ones(numLabels, numClasses);%initialise probabilities matrix
  for label=1:numLabels %2300
    for class=1:numClasses %2, 3 or 7
      for attr = 1:numAttr
        %
        probClassGivenFeature(label, class) = probClassGivenFeature(label, class)*lookUpTables(testAttrSet(label, attr)+1, class, attr);
      end
      %Using bayes' theorem to calculate p(class|feature)
      probClassGivenFeature(label, class) = probClassGivenFeature(label, class)* matrixProbs(class, 1);
    end
    %Finding the maximum probabilities out of the classes assessed
    currentProbBiggest = probClassGivenFeature(label, 1);
    for class=1:numClasses
      if probClassGivenFeature(label, class) > currentProbBiggest
        predictLabelVector(label) = class - 1;
        currentProbBiggest = probClassGivenFeature(label, class);%Without this, does not work for more than 2 classes possible
      end
    end
  end
  %calculating accuracy based on number of labels and matching valid and predicted
  for label=1:numLabels
    if predictLabelVector(label)==validLabel(label)
      testsRight = testsRight + 1;
    end
  end
  accuracy = testsRight/numLabels
end
