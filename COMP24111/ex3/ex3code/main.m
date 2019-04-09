close all;
clear all;
fname = input('Enter a filename to load data for training/testing: ','s');
if strcmp(fname, 'spambase.data') == 1
  load(fname);
  accuracyMatrix = zeros(10,1);
  labelSet = spambase(:,58);%Both this and attribute set have to be indexed properly
  attributeSet = spambase(:, 1:57);
  labels = size(attributeSet, 1);
  for k = 1:10
    % Put your CNB training function below
    [pClasses, featureStdDevs, featureMeans] = CNBTrain(attributeSet([1:(460)*(k-1), (460)*k+1:labels],:), labelSet([1:(460)*(k-1), (460)*k+1:labels],:)); % CNB training
    % Put your CNB test function below
    [predictLabelVector, accuracy] = CNBTest(pClasses, featureStdDevs, featureMeans, attributeSet((460)*(k-1) + 1 : 460*k,:), labelSet((460)*(k-1) + 1 : 460*k,:)); % CNB test
    accuracyMatrix(k, 1) = accuracy;
  end
  fprintf('********************************************** \n');
  fprintf('Avg Accuracy on Continuous Dataset %s: %f \n', fname, mean(accuracyMatrix(:,1)));
  fprintf('Stdev Accuracy on Continuous Dataset %s: %f \n', fname, std(accuracyMatrix(:,1)));
  fprintf('********************************************** \n');

elseif strcmp(fname, 'avc_c2.mat') == 1
  load(fname);
  % Put your CNB training function below
  [pClasses, featureStdDevs, featureMeans] = CNBTrain(AttributeSet, LabelSet);
  [predictLabelVector, accuracy] = CNBTest(pClasses, featureStdDevs, featureMeans, testAttributeSet, validLabel) % CNB test
  fprintf('********************************************** \n');
  fprintf('Accuracy on Continuous Dataset %s: %f \n', fname, accuracy);
  fprintf('********************************************** \n');
else
  load(fname);
  % Put your NB training function below
  [lookUpTables, matrixProbs] = NBTrain(AttributeSet, LabelSet) % NB training
  % Put your NB test function below
  [predictLabelVector, accuracy] = NBTest(lookUpTables, matrixProbs, testAttributeSet, validLabel) % NB test
  fprintf('********************************************** \n');
  fprintf('Accuracy on Discrete Dataset %s: %f \n', fname, accuracy);
  fprintf('********************************************** \n');
end
