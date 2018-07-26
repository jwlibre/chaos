#include <stdio.h>
#include <stdlib.h>
#include <math.h>


FILE * fptr; //defines a file pointer named 'fptr'

int main ()
{
	
	
	int k;
	int n; //counting variable for the number of steps
	int N; //will be used to obtain the number of desired steps from scanf
	double dt=0.05; //specifies 0.05 second time intervals between Runge-Kutta iterations.
	double t; //time variable to keep track of the dt increments, goes from 0 to N*dt
	double a=10.0; //specifies the a (Prandtl number) value
	double b=(8.0)/(3.0); //specifies the b value
	double r; //declares the Rayleigh number, whose value will be chosen by the user.
	double y1, y2, y3; //this is the starting point - y1,0/y2,0/y,3/0
	
	double f[1000][1000]; //sets an array of arbitrary (sufficiently large) size
	
	printf("Select parameter values\n"); //scanf functions allow user to select values of N, r, and the initial starting values of the three variables.
	printf("type in an integer number of steps, N: ");
	scanf("%d", &N);
	printf("\n N=%d \n", N);
	printf("type in a value for r: ");
	scanf("%lf", &r);
	printf("\n r=%lf \n", r);
	printf("type in a value for y1: ");
	scanf("%lf", &y1);
	printf("\n y1=%lf \n", y1);
	printf("type in a value for y2: ");
	scanf("%lf", &y2);
	printf("\n y2=%lf \n", y2);
	printf("type in a value for y3: ");
	scanf("%lf", &y3);
	printf("\n y3=%lf \n", y3);
	
	printf("initial conditions: at time t=0, y1=%lf, y2=%lf, y3=%lf\n", y1, y2, y3); //confirmation that user input has been received
	
	fptr = fopen("chaos1.txt", "w");  //opens chaos1.data for output. Switch to chaos.txt for laptop.
	
	if (fptr==0)
	{
		printf("Error opening file\n"); //tells the user if there is a problem opening the file for output, and quits the program smoothly
		exit(1);
	}
	
	fprintf(fptr, "#t\t\t #y1\t\t #y2\t\t #y3\t\t\n"); //prints headers to the columns of data in the output file to make the data easier to read.
	fprintf(fptr, "%lf\t %lf\t %lf \t %lf\t\n",t, y1, y2, y3); //prints the initial values of t, y1, y2 and y3 to the output file.
	
	for (n=1; n<=N; n++) //this for loop controls the number of iterations the Runge-Kutta process runs for, as specified by the user input, and hence the amount of time elapsed.
	{
		/*FIRST RUNGE-KUTTA STEP*/
		f[0][0]=a*(y2-y1);
		f[1][0]=r*y1-y2-(y1*y3);
		f[2][0]=(y1*y2)-(b*y3);
		
		/*SECOND AND THIRD RUNGE-KUTTA STEPS*/
		for(k=1; k<=2; k++)
		{
			f[0][k]=a*(y2+(f[1][k-1])*(0.5*(dt))) - a*(y1+(f[0][k-1])*(0.5*(dt)));
			f[1][k]=r*(y1+(f[0][k-1])*(0.5*(dt))) - (y2+(f[1][k-1])*(0.5*(dt))) - (y1+(f[0][k-1])*(0.5*(dt)))*(y3+(f[2][k-1])*(0.5*(dt)));
			f[2][k]=(y1+(f[0][k-1])*(0.5*(dt)))*(y2+(f[1][k-1])*(0.5*(dt))) - b*(y3+(f[2][k-1])*(0.5*(dt)));
		}
		
		/*FOURTH RUNGE-KUTTA STEP*/
		f[0][3]=a*(y2+(f[1][2])*(dt))-a*(y1+(f[0][2])*(dt));
		f[1][3]=r*(y1+(f[0][2])*(dt))-(y2+(f[1][2])*(dt))-(y1+(f[0][2])*(dt))*(y3+(f[2][2])*(dt));
		f[2][3]=(y1+(f[0][2])*(dt))*(y2+(f[1][2])*(dt))-b*(y3+(f[2][2])*(dt));
		
		//then calculates the yi,4 values. Since the yi,4 become the yi,0 values (i.e. to be plugged in to the next Runge-Kutta iteration), you see we reset the values here.
		y1=y1+(f[0][0]+2*f[0][1]+2*f[0][2]+f[0][3])*dt/6.0;
		y2=y2+(f[1][0]+2*f[1][1]+2*f[1][2]+f[1][3])*dt/6.0;
		y3=y3+(f[2][0]+2*f[2][1]+2*f[2][2]+f[2][3])*dt/6.0;
		
		t=n*dt;
		 /*Optional printf functions to ease de-bugging show the values after each Runge-Kutta iteration*/
		//printf("at time %lf, y1=%lf, y2=%lf, y3=%lf\n", t, y1, y2, y3);
		//printf("%lf\n", y2);
		//printf("%lf\n", y3);
		
		fprintf(fptr, "%lf\t %lf\t %lf \t %lf\t\n", t, y1, y2, y3); //prints the values to the output file after a complete iteration
		
		
		f[0][0]=0; //just to ensure the array spaces are all reset after each iteration
		f[0][1]=0;
		f[0][2]=0;
		f[0][3]=0;
		f[1][0]=0;
		f[1][1]=0;
		f[1][2]=0;
		f[1][3]=0;
		f[2][0]=0;
		f[2][1]=0;
		f[2][2]=0;
		f[2][3]=0;
	}
	printf ("y1=%lf\n y2=%lf\n y3=%lf\n", y1, y2, y3); //Prints the final values to the console to indicate successful completion.
	
	fclose(fptr); //CLOSES THE FILE AFTER DATA INPUT
	
	return 0;
	
}