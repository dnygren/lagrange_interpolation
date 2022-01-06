%
% Code for modified Lagrange formula
% From https://www.math.umd.edu/~petersd/666/BarycentricLagrange1.pdf
%
% Note that evaluating equation (5) in the above PDF when x equals one of the
% nodes xj yields 0=0 which gives NaN in machine arithmetic.
%
% The Matlab code evaluates the p(x) for a vector of x-values. We first compute
% the vector of y-values using (5) which will give NaN for x-values which
% coincide with one of the nodes. We therefore fix the y-vector by using the
% given function values at the nodes.
%

function ye = modlagr(x,y,xe)
% ye = modlagr(x,y,xe)
% find interpolating polynomial for data x,y and evaluate at points xe
% input:
% vectors x,y: given data points
% vector xe: evaluation points
% output:
% vector ye: values of interpolating polynomial at points xe
% compute w_j
w = zeros(size(x)); % Return an array the same size as x but all zeros
for j=1:length(x);
    w(j) = 1;
    for k=1:j-1
        w(k) = w(k)/(x(k)-x(j));
        w(j) = w(j)/(x(j)-x(k));
    end
end

w % Print out weights

% Evaluate modified Lagrange formula
s = zeros(size(xe));    % Return an array the same size as xe but all zeros
P = ones(size(xe));     % ... the same size as P but all ones
equalnode = zeros(size(xe)); % ... the same size as xe but all zeros
%for j=1:n % <--- Typo in original?
for j=1:length(x)
    d = xe - x(j);
    equalnode(d==0) = j;  % where xe coincides with node: store node number
    s = s + y(j)*w(j)./d; % division by zero where xe coincides with node
    P = P.*d;
end
ye = P.*s;

% fix ye for xe-values which coincide with nodes
ind = (equalnode>0); % indices where we had division by zero
ye(ind) = y(equalnode(ind)); % replace with nodal values
