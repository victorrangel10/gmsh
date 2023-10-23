// Gmsh project created on Tue Sep 01 14:04:51 2020
SetFactory("OpenCASCADE");

ndiv = 10;
// diagonal 10, 20, 30, 40, 50

//+

For i In {1: ndiv}
	offset = (i-1)/(2*ndiv);
	Point(4*i-3) = {0+offset, 0+offset, 0, 1.0};
	Point(4*i-2) = {0+offset, 1-offset, 0, 1.0};
	Point(4*i-1) = {1-offset, 1-offset, 0, 1.0};
	Point(4*i  ) = {1-offset, 0+offset, 0, 1.0};
	
	Line(4*i-3) = {4*i-3, 4*i-2};
	Line(4*i-2) = {4*i-2, 4*i-1};
	Line(4*i-1) = {4*i-1, 4*i  };
	Line(4*i-0) = {4*i  , 4*i-3};
	Transfinite Curve {4*i-3,4*i-2,4*i-1,4*i-0} = ndiv + 2 - i Using Progression 1;
	Curve Loop(i) = {4*i-3,4*i-2,4*i-1,4*i-0};

        Color Black{Line(4*i-3);}
	Color Black{Line(4*i-2);}
	Color Black{Line(4*i-1);}
	Color Black{Line(4*i-0);}
EndFor
//+

i = ndiv;

Curve Loop(i+1) = {4*i-3,4*i-2,4*i-1,4*i-0};

For i In {1: ndiv}
	Plane Surface(i) = {i,i+1};
        Color Black{Surface(i);}
EndFor