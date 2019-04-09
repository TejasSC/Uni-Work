function [pClasses, featureStdDevs, featureMeans] = CNBTrain(AttributeSet, LabelSet)
  %define constants
  numLabels = size(LabelSet, 1);
  numFeatures = size(AttributeSet, 2);
  numClasses = max(LabelSet) + 1;
  pClasses = ones(1, numClasses);
  quantityOfClass = zeros(1, numClasses);

  %calculate means and std deviations for each feature given its class
  featureMeans = zeros(numFeatures, numClasses);
  featureSumsMeans = zeros(numFeatures, numClasses);
  featureStdDevs = zeros(numFeatures, numClasses);
  featureSumsVariances = zeros(numFeatures, numClasses);
  for label=1:numLabels
    %increment number of samples of certain class
    quantityOfClass(1,  LabelSet(label)+1) = quantityOfClass(1,  LabelSet(label)+1) + 1;
  end
  %assign initial probabilities of classes
  for class=1:numClasses
    pClasses(1, class) = quantityOfClass(1, class)/numLabels;
  end
  for feature = 1:numFeatures
    for label=1:numLabels
      %increment sum of feature quantity for a class
      featureSumsMeans(feature, LabelSet(label)+1) = featureSumsMeans(feature, LabelSet(label)+1) + AttributeSet(label, feature);
    end
    for class=1:numClasses
      featureMeans(feature, class) = featureSumsMeans(feature, class)/quantityOfClass(1, class);
    end
    for label=1:numLabels
      %Sum up the squares of differences between attribute set value (for a feature)
      square = (AttributeSet(label, feature) - featureMeans(feature, LabelSet(label)+1)).^2;
      featureSumsVariances(feature, LabelSet(label)+1) = featureSumsVariances(feature, LabelSet(label)+1) + square;
    end
    for class=1:numClasses
      featureStdDevs(feature, class) = sqrt(featureSumsVariances(feature, class)/quantityOfClass(1, class));
    end
  end
end
