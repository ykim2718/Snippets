integer*2 function addtwo(a ,b)
  !DEC$ ATTRIBUTES DLLEXPORT:: addtwo
  integer*2,intent(in)::a,b !Y160209,  pass by value
  !integer*2,intent(out)::a,b !Y160209, pass by reference
  !integer*2,intent(inout)::a,b !Y160209, by default
  addtwo=a+b
end function addtwo