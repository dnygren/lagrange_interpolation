% Data to be interpolated using the modified Lagrange formula

% Don't split long rows
split_long_rows(0)

% From the Rosemount 0118MF data sheet
% Resistances
x = [ 25.90 34.54 59.69 67.89 92.06 100.00 107.87 131.21 138.90 146.55 ]
% Temperatures at those resistances
y = [ -180.0 -160.0 -100.0 -80.0 -20.0 0.0 20.0 80.0 100.0 120.0 ]

% Resistances at which that interpolated temperatures are required.
xe = [ 25.0 34.0 59.0 67.0 92.0 101.0 107.0 131.0 138.0 146.0 ]

ye = modlagr(x,y,xe) % Defined in modlagr.m file
