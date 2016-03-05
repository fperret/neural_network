%% Initialization
clear ; close all; clc

%% =========== Loading and Visualizing Data =============
%  We start the exercise by first loading and visualizing the dataset. 
%  You will be working with a dataset that contains handwritten digits.
%

% Load Training Data
fprintf('Loading and Visualizing Data ...\n')

load('data.mat');
m = size(X, 1);

% Randomly select 100 data points to display
sel = randperm(size(X, 1));
sel = sel(1:100);

displayData(X(sel, :));

fprintf('Program paused. Press enter to continue.\n');
pause;

%% ================= Training neural network =================

lambda = 1;
input_layer_size = 400;
hidden_layer_size = 25;
num_labels = 10;

% Create a function handle used by fmincg
costFunction = @(p) cost_function(p, input_layer_size, ...
                    hidden_layer_size, num_labels, X, y, lambda);

% Randomly initialize weights parameters and unroll them in vector
initial_theta1 = randInitializeWeights(input_layer_size, hidden_layer_size);
initial_theta2 = randInitializeWeights(hidden_layer_size, num_labels);
initial_thetas = [initial_theta1(:); initial_theta2(:)];

% Train neural network by finding values of thetas that minize the cost
% function
options = optimset('MaxIter', 200);
[thetas, cost] = fmincg(costFunction, initial_thetas, options);

% "Reshape" weights into matrices
Theta1 = reshape(thetas(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));
             
Theta2 = reshape(thetas((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

 %% ================ Prediction ================
% Predict the label of each input thanks to the trained parameters          
pred = predict(Theta1, Theta2, X);

fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred == y)) * 100);

fprintf('Program paused. Press enter to continue.\n');
pause;


%  Randomly permute examples
rp = randperm(m);

for i = 1:m
    % Display 
    fprintf('\nDisplaying Example Image\n');
    displayData(X(rp(i), :));

    pred = predict(Theta1, Theta2, X(rp(i),:));
    fprintf('\nNeural Network Prediction: %d (digit %d)\n', pred, mod(pred, 10));
    
    % Pause
    fprintf('Program paused. Press enter to continue.\n');
    pause;
end

