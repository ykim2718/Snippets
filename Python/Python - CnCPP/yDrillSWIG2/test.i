%module yDrillSWIG2
%{
#include "test.h"
%}

%include "std_vector.i"

namespace std {
%template(Line) vector <int>;
%template(Array) vector <vector<int>>;
}

%include "test.h"