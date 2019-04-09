function [lookUpTables, matrixProbs] = NBTrain(AttributeSet, LabelSet)
  %define constants
  numLabels = size(LabelSet, 1);
  numFeatures = size(AttributeSet, 2);
  numClasses = max(max(LabelSet)) + 1;
  numAttrValues = max(max(AttributeSet)) + 1;

  matrixProbs = zeros(numClasses, 1);
  labelCount = zeros(numClasses, 1);%
  for i=1:numLabels
    %Adding one because matlab indexes from 1, and values will be (0,1) -> (1,2)
    labelCount(LabelSet(i) + 1) = labelCount(LabelSet(i) + 1) + 1;
  end
  %Dimensions of lookUpTable for av2_c2 are 2x2x57, for example
  lookUpTables = zeros(numAttrValues, numClasses, numFeatures);

  %Populate lookup tables with conditional probabilities for each feature
  %               P(AttrValue|Class = 0, for fx)  P(AttrValue|Class = 1, for fx)
  %AttrValue = 0  xxxxxxxxxxxxxxxxxxxxxxxxxxxxx   xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  %AttrValue = 1  xxxxxxxxxxxxxxxxxxxxxxxxxxxxx   xxxxxxxxxxxxxxxxxxxxxxxxxxxxx
  %
  for f = 1:numFeatures %57
    for j = 1:numLabels %2300
      lookUpTables(AttributeSet(j,f)+1, LabelSet(j)+1, f) = lookUpTables(AttributeSet(j,f)+1, LabelSet(j)+1, f) + 1;
    end
    for class=1:numClasses
      lookUpTables(:,class,f) = lookUpTables(:,class,f) / labelCount(class);
    end
  end
  %Returning the general probabilities of spam and not spam
  matrixProbs = labelCount / numLabels
end
