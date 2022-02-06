#include<stdio.h>
#include<math.h>
float initial_force(float w,float l,float f,float h,float L,float u,double o1,float k);
float initial_power(float Fi,float vi);
float acceleration(float vf,float vi);
float roll_res(float f,float m,float g);
float grade_res(float m,float g,double o2,float k);
float relative_speed(float vw,float vf);
float aero_res(float rho,float C,float A,float vr);
float dynamic_force(float w,float a,float g,float Rr,float Rg,float Ra);
float dynamic_power(float Fd,float vf);
float max_power(float Pi,float Pd);
float initial_current(float Pi,float Vm);
float dynamic_current(float Pd,float Vm);
float battery_cap(float P,float Vm);
void battery_design(float v,float c);
void SOC_estimation(float t1,float t2,float Ii,float Bq,float Id);
int main()
{
    float Fi,Pi,Fd,Pd,Ii,Id,Vm;
/*Fi=Initial force;Pi=Initial power;Fd=Dynamic force;Pd=Dynamic power
Ii=Initial current;Id=Dynamic current;Vm=motor rating voltage*/
float m,w,l,f,h,L,u,k,P1,P2,Bp,P,Bq;
/*m=Vehicle mass;w=vehicle weight;l=Distance of front wheel from CG
f=coefficient of rolling motion resistance;h=CG height;L=Wheel base
u=adhesion coefficient;P1,P2,k=intermediate parameter;
Bp,Bq=Battery capacity;P=Maximum propulsion power*/
double o1,o2;
//o1,o2=slope angle with respect to horizon
float g,A,rho,C,vf,a,Rr,Rg,Ra,vi,vw,vr;
/*g=gravitational acceleration;A=frontal area of the vehicle;rho=Air density
C=Drag coefficient;vf=final velocity;a=acceleration;Rr=Rolling resistance;
Rg=Grade resistance;Ra=Aerodynamic resistance;vi=Initial velocity;
vw=Average wind speed;vr=Relative speed of vehicle with respect to wind;*/
float v,Vt,Vt1,Ct,c;
float t1,t2,T1,T2,SOC;
/*v=nominal cell voltage,Vt=,Vt1=,Ct=,c=rated cell capacity,
t1=time duration of initial mode,t2=time duration of dynamic mode,SOC=SOC of battery
*/
printf("Calculation of initial force\n");
printf("Enter the value of weight of the vehicle in newton\nw=");
scanf("%f",&w);
printf("Enter the value of distance of front wheel from CG in metres\nl=");
scanf("%f",&l);
printf("Enter the value of coefficient of rolling motion resistance\nf=");
scanf("%f",&f);
printf("Enter the value of CG height in metres\nh=");
scanf("%f",&h);
printf("Enter the value of wheel base in metres\nL=");
scanf("%f",&L);
printf("Enter the value of adhesion coefficient\nu=");
scanf("%f",&u);
printf("Enter the value of slope angle with respect to horizon in degrees\no1=");
scanf("%lf",&o1);
k=3.14/180;
Fi=initial_force(w,l,f,h,L,u,o1,k);
printf("\n\n\nCalculation of initial power");
printf("\nEnter the initial speed of the vehicle in m/s\nvi=");
scanf("%f",&vi);
Pi=initial_power(Fi,vi);
printf("\n\n\nCalculation of dynamic force");
printf("\nEnter the final speed of the vehicle in m/s\nvf=");
scanf("%f",&vf);
a=acceleration(vf,vi);
printf("\n\nCalculation of Rolling resistance");
printf("\nEnter the value of mass of the vehicle in Kg\nm=");
scanf("%f",&m);
printf("\nEnter the value of gravitational acceleration\ng=");
scanf("%f",&g);
Rr=roll_res(f,m,g);
printf("\n\nCalculation of Grade resistance");
printf("\nEnter the value of slope angle with respect to horizon in degrees\no2=");
scanf("%lf",&o2);
Rg=grade_res(m,g,o2,k);
printf("\n\nCalculation of Aerodynamic resistance");
printf("\nEnter the value of average wind speed\nvw=");
scanf("%f",&vw);
vr=relative_speed(vw,vf);
printf("\nEnter the value of air density in Kg/m^3\n");
scanf("%f",&rho);
printf("\nEnter the value of drag coefficient\nC=");
scanf("%f",&C);
printf("\nEnter the value of frontal area of the vehicle in m^2\nA=");
scanf("%f",&A);
Ra=aero_res(rho,C,A,vr);
Fd=dynamic_force(w,a,g,Rr,Rg,Ra);
printf("\n\nCalculation of dynamic power");
Pd=dynamic_power(Fd,vf);
P=max_power(Pi,Pd);
printf("\nEnter the value of motor rating voltage\nVm=");
scanf("%f",&Vm);
Ii=initial_current(Pi,Vm);
Id=dynamic_current(Pd,Vm);
printf("\n\nCalculation of battery capacity in order to run the motor for 1 hour \nat the required power rating");
Bq=battery_cap(P,Vm);
printf("\n\nEnter the value of nominal voltage of the cell in volts\nv=");
scanf("%f",&v);
printf("\nEnter the value of rated cell capacity in Ah\nc=");
scanf("%f",&c);
battery_design(v,c);


}

float initial_force(float w,float l,float f,float h,float L,float u,double o1,float k)
{
    float Fi;
    Fi=w*(((l+f*h)/L)/(1+(u*h/L))*u+(sin(o1*k)));
    printf("\nThe initial force in newton is %f",Fi);
    return(Fi);
}

float initial_power(float Fi,float vi)
{
    float Pi;
    Pi=Fi*vi;
    printf("\nThe initial power in watts is %f",Pi);
    return(Pi);
}

float acceleration(float vf,float vi)
{
    float a;
    a=(vf-vi)/60;
    printf("\nThe acceleration of the vehicle in m/s^2 is a=%f",a);
    return(a);
}

float roll_res(float f,float m,float g)
{
    float Rr;
    Rr=f*m*g;
    printf("\nThe rolling resistance is %f",Rr);
    return(Rr);
}
float grade_res(float m,float g,double o2,float k)
{
    float Rg;
    Rg=m*g*sin(o2*k);
    printf("\nThe grade resistance is %f",Rg);
    return(Rg);
}

float relative_speed(float vw,float vf)
{
    float vr;
    vr=vw+vf;
    printf("\nRelative speed of vehicle with respect to wind is %f",vr);
    return(vr);
}

float aero_res(float rho,float C,float A,float vr)
{
    float Ra;
    Ra=0.5*rho*C*A*vr*vr;
    printf("\nThe aerodynamic resistance is %f",Ra);
    return(Ra);
}

float dynamic_force(float w,float a,float g,float Rr,float Rg,float Ra)
{
    float Fd;
    Fd=((w*a)/g)+Rr+Rg+Ra;
    printf("\n\nThe value of dynamic force in newton is %f",Fd);
    return(Fd);
}

float dynamic_power(float Fd,float vf)
{
    float Pd;
    Pd=Fd*vf;
    printf("\nThe value of dynamic power in watts is %f\n\n",Pd);
    return(Pd);
}

float max_power(float Pi,float Pd)
{
    float P1,P2,P;
    if(Pi>Pd)
{
    P1=Pi+2000;
    P=P1;
    printf("\nThe maximum propulsion power in watts is %f\n\n",P);
}
else
{
    P2=Pd+2000;
    P=P2;
    printf("\nThe maximum propulsion power in watts is %f\n\n",P);
}
return (P);
}

float initial_current(float Pi,float Vm)
{
    float Ii;
    Ii=Pi/Vm;
    printf("\nThe initial value of current in ampere is %f",Ii);
    return(Ii);
}
float dynamic_current(float Pd,float Vm)
{
    float Id;
    Id=Pd/Vm;
    printf("\nThe dynamic value of current in ampere is %f",Id);
    return(Id);
}

float battery_cap(float P,float Vm)
{
    float Bp,Bq;
    Bp=P*1;
    printf("\nThe required battery capacity in Wh is %f",Bp);
    Bq=Bp/Vm;
    printf("\n\nThe required battery capacity in Ah is %f\n",Bq);
    return(Bq);
}

void battery_design(float v,float c)
{
    float Vt,Ct,Vt1;
    Vt=v+v;
    Ct=c*3;
    printf("\nThe terminal voltage of 1 module is %f",Vt);
    printf("\nThe capacity in Ah of 1 module is %f",Ct);
    printf("\n\n\nSuch 10 modules are connected in series");
    Vt1=Vt*10;
    printf("\nThe terminal voltage of the battery in volts is %f",Vt1);
    printf("\nThe battery capacity in Ah is %f\n",Ct);
}

