function [J grad] = cost_function(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

             
m = size(X, 1);
         
% X -> 5000 * 400
% y -> 5000 * 1
% y_label -> 10 * 5000
% a_3 (hypothesis) -> 10 * 5000

X = [ones(m, 1) X];

a_1 = X';
z_2 = Theta1 * a_1;
a_2 = sigmoid(z_2);
a_2 = [ones(1, m); a_2];
z_3 = Theta2 * a_2;
a_3 = sigmoid(z_3);

tmp = eye(num_labels);
y_label = tmp(y, :)';

left_member = -y_label .* log(a_3);
right_member = (1 - y_label) .* (log(1 - a_3));
% Sum over labels
first_sum = sum(left_member - right_member);
% Sum over training examples 
J = sum(first_sum) / m;

regularization = (lambda / (2 * m)) * (sum(sum(Theta1(:, 2:end) .^ 2)) + sum(sum(Theta2(:, 2:end) .^ 2)));
J = J + regularization;

% -------------------------------------------------------------

d3 = a_3 - y_label;
d2 = (Theta2(:, 2:end)' * d3) .* sigmoidGradient(z_2);

delta1 = d2 * a_1';
delta2 = d3 * a_2';

Theta1_grad = (1 / m) .* delta1;
Theta2_grad = (1 / m) .* delta2;

%big_delta_1 = 0;
%big_delta_2 = 0;
%for c=1:m
    
 %   a_1 = X(c, :)';
  % a_2 = [1; sigmoid(z_2)];
   % z_3 = Theta2 * a_2;
    %a_3 = sigmoid(z_3);
    
%    disp(size(a_3));
 %   delta_3 = a_3 - y_label(c);

  %  delta_2 = (Theta2(:, 2:end)' * delta_3) .* sigmoidGradient(z_2);
   % big_delta_1 = big_delta_1 + delta_2 * a_1';
    %big_delta_2 = big_delta_2 + delta_3 * a_2';
    
%end

%Theta1_grad = (1 / m) .* big_delta_1;
%Theta2_grad = (1 / m) .* big_delta_2;

% =========================================================================

Theta1_grad = Theta1_grad + [zeros(size(Theta1, 1), 1) ((lambda / m) .* Theta1(:, 2:end))];
Theta2_grad = Theta2_grad + [zeros(size(Theta2, 1), 1) ((lambda / m) .* Theta2(:, 2:end))];

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];

end
