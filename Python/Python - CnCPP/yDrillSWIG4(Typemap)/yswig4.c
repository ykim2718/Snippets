double *f1() {
    static double output[]={0.,1.};
    return output;
}

double *f2() {
    static double out=2.0;
    return &out;
}

double f3() {
    return 3.0;
}