cl = 1.0;
boxdim = 1.0;
nsp = 5;  //numero de sub particoes

Point(1) = {0, 0, 0, cl};
Point(2) = {boxdim, 0, 0, cl};
Point(3) = {boxdim, boxdim/10, 0, cl};
Point(4) = {0, boxdim/10, 0, cl};

Line(1) = {1, 2};
Line(2) = {2, 3};
Line(3) = {3, 4};
Line(4) = {4, 1};

Line Loop(6) = {1, 2, 3, 4};
Plane Surface(6) = {6};

// Put nsp points with a refinement toward the extremities on curve 2

//Para malha não estruturada comentar a linha abaixo
 Transfinite Line{1,2,3,4} = nsp ;

// Define the Surface as transfinite, by specifying the four corners of the
// transfinite interpolation

//Para malha não estruturada comentar a linha abaixo
 Transfinite Surface{6} = {1,2,3,4}  Alternate;  //Left;  //Right;

// (Note that the list on the right hand side refers to points, not curves. When
// the surface has only 3 or 4 points on its boundary the list can be
// omitted. The way triangles are generated can be controlled by appending
// "Left", "Right" or "Alternate" after the list.)

// Recombine the triangles into quads
Recombine Surface{1}; 

// Apply an elliptic smoother to the grid
Mesh.Smoothing = 100;

Color Black{Surface{6}};
Color Black{Line{1}};
//Color Black{Line{2}};
//Color Black{Line{3}};
//Color Black{Line{4}};


