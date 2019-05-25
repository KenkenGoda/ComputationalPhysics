/*single.c*/
#include<stdio.h>
#include<string.h>
#include<math.h>

float f();
float fl();

int main(void){
    float h,err,x,dfdh;
    int i;
    FILE *fp;

    fp=fopen("err_single.dat","w");

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

float f(double x){
    float a;

    a=sin(x);

    return a;
}

float fl(double x){
    float a;

    a=cos(x);

    return a;
}
