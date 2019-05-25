/*double.c*/
#include<stdio.h>
#include<string.h>
#include<math.h>

double f();
double fl();

int main(void){
    double h,err,x,dfdh;
    int i;
    FILE *fp;

    fp=fopen("err_double.dat","w");

    x=1.0;

    for(i=0;i<20;i++){
        h=pow(10.0,-i);
        dfdh=(f(x+h)-f(x))/h;
        err=fabs(fl(x)-dfdh);

        printf("%d %16.8e %16.8e\n",i,h,err);
        fprintf(fp,"%d %16.8e %16.8e\n",i,h,err);
    }

    fclose(fp);

    return 0;
}

double f(double x){
    double a;

    a=sin(x);

    return a;
}

double fl(double x){
    double a;

    a=cos(x);

    return a;
}
