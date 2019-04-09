function [predictLabelVector, accuracy] = CNBTest(pClasses, featureStdDevs, featureMeans, testAttrSet, validLabel)
  %define constants
  testsRight = 0;
  %Dimensions of the testing set, labels by attributes
  numLabels = size(testAttrSet, 1)
  numFeatures = size(testAttrSet, 2);
  s = size(validLabel, 1);%storing the size of the predictLabelVector, of validLabel
  numClasses = size(pClasses, 2);%acquiring number of actual classes from training

  predictLabelVector = zeros(s, 1);%size of predictLabelVector
  probFeatGivenC = ones(numFeatures, numClasses);
  probFVGivenC = ones(numLabels, numClasses);%initialise probabilities matrix
  for label=1:numLabels %2400
    featureVector = testAttrSet(label,:);
    for c=1:numClasses %2
      for attr = 1:numFeatures
        %obtaining feature value for a certain feature
        if featureStdDevs(attr,c) ~= 0
          probFeatGivenC(attr, c) = normpdf(featureVector(attr),featureMeans(attr, c),featureStdDevs(attr,c));
        else
          probFeatGivenC(attr, c) = (featureVector(attr) == featureMeans(attr, c));
        end 
        probFVGivenC(label, c) = probFVGivenC(label, c) * probFeatGivenC(attr, c);
      end
      probFVGivenC(label, c) = probFVGivenC(label, c) * pClasses(1, c);
    end
    %Finding the maximum probabilities out of the classes assessed, to determine which class a label is in
    currentProbBiggest = probFVGivenC(label, 1);
    for c=1:numClasses
      if probFVGivenC(label, c) > currentProbBiggest
        predictLabelVector(label) = c - 1;
        %Without this, does not work for more than 2 classes
        currentProbBiggest = probFVGivenC(label, c);
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
