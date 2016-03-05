function p = predict(Theta1, Theta2, X)
%PREDICT Predict the label of an input given a trained neural network
%   (Feedforward Propagation)
%   p = PREDICT(Theta1, Theta2, X) outputs the predicted label of X given the
%   trained weights of a neural network (Theta1, Theta2)

% Input layer (a_1) : 401 * 5000
% Hidden layer (a_2) : 26 * 5000
% Output layer (a_3) : 10 * 5000

m = size(X, 1);

% Add bias unit
X = [ones(m, 1) X];

a_1 = X';

z_2 = Theta1 * a_1;
a_2 = sigmoid(z_2);
% Add bias unit
a_2 = [ones(1, m); a_2];

z_3 = Theta2 * a_2;
a_3 = sigmoid(z_3);
[~, p] = max(a_3, [], 1);
p = p';

end
