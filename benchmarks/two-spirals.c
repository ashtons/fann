/*       Two-Spirals Benchmark
	 Data Set Generator
	 
	 v1.0
	 By:  Matt White  (mwhite+@cmu.edu)
	 Based on code by Alexis Wieland of MITRE Corporation

	 Usage: a.out <density> <radius>
	   Density defaults to '1'. 
	   Radius defaults to '6.5'.
	   These are the values used in the original benchmark.
	   Changing the density changes the number of data points generated.
	   Changing the radius changes the range of numbers generated.
	 
	 Description
	 ~~~~~~~~~~~
	   This program generates two sets of points, each with 
         96 * density + 1 data points (3 revolutions of 32 times the density
	 plus one end point).  The output of this program is in the standard
	 CMU Neural Network Benchmark format.  For more information, see the 
	 accompanying database file, 'two-spirals'.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#ifndef PI						/* PI is defined on some systems, if it is not, define */
#define PI 3.1416				/*  it to four decimal places.  Good enough for our    */
#endif /*  purposes.                                          */


/*      Function Prototypes      */

void getCommandLine(int *, double *, int, char **);
void printHeader(int, double);
void printSet(int, double);


int main(int argc, char **argv)
{
	int density;				/* Density of the data set to generate */
	double maxRadius;			/* Maximum radius of the data set to generate */

	getCommandLine(&density, &maxRadius, argc, argv);
	printHeader(density, maxRadius);
	printSet(density, maxRadius);

	return 0;
}


/*      getCommandLine -  This function reads the values from the command line
	and interprets them.  The first argument is read as the density and the
	second as the radius.  If there is no value for radius, it defaults to
	6.5 while density defaults to 1.  Extra arguments are ignored.
*/

void getCommandLine(int *density, double *maxRadius, int argc, char **argv)
{
	if(argc < 2)
		*density = 1;
	else
		*density = atoi(*(argv + 1));
	if(argc < 3)
		*maxRadius = 6.5;
	else
		*maxRadius = atof(*(argv + 2));
}


/*      printHeader -  This function prints out the header information for the
	data set.  This includes generation time (local), density and radius.
	It also prints the $SETUP segment for the data set.
*/

void printHeader(int density, double maxRadius)
{
	time_t genTime;

	time(&genTime);

	/*
	 * printf  (";Two-Spirals Benchmark\n");
	 * printf  (";Generated: %s", asctime( localtime( &genTime ) ));
	 * printf  (";Density:   %d\n", density );
	 * printf  (";Radius:    %.2f\n\n", maxRadius );
	 * printf  (";Program by: Matt White  (mwhite+@cmu.edu)\n");
	 * printf  (";Benchmark by: Alexis Wieland of MITRE Corporation\n");
	 * printf  (";  Any questions should be directed to neural-bench@cs.cmu.edu.");
	 * printf  ("\n\n");
	 * 
	 * printf  ("$SETUP\n\n");
	 * printf  ("PROTOCOL: IO;\n");
	 * printf  ("OFFSET: 0;\n");
	 * printf  ("INPUTS: 2;\n");
	 * printf  ("OUTPUTS: 1;\n\n");
	 * printf  ("IN [1]: CONT {%.2f,-%.2f};\n", maxRadius, maxRadius );
	 * printf  ("IN [2]: CONT {%.2f,-%.2f};\n\n", maxRadius, maxRadius );
	 * printf  ("OUT [1]: BINARY;\n\n\n");
	 * 
	 * printf  ("$TRAIN\n\n");
	 */

	printf("%d 2 1\n", (density * 96 + 1) * 2);
}


/*      printSet -  Generates and prints out a data set having the specified
	density and radius.
*/

void printSet(int density, double maxRadius)
{
	int points,					/* Number of interior data points to generate */
	  i;						/* Indexing variable */
	double x,					/* x coordinate */
	  y,						/* y coordinate */
	  angle,					/* Angle to calculate */
	  radius;					/* Radius at current iteration */

	points = (96 * density);
	for(i = 0; i <= points; i++)
	{

		/* Angle is based on the iteration * PI/16, divided by point density */
		angle = (i * PI) / (16.0 * density);

		/* Radius is the maximum radius * the fraction of iterations left */
		radius = maxRadius * ((104 * density) - i) / (104 * density);

		/* x and y are based upon cos and sin of the current radius */
		x = radius * cos(angle);
		y = radius * sin(angle);

		/* printf ("%8.5f, %8.5f  =>  +;\n", x, y ); */
		/* printf ("%8.5f, %8.5f  =>  -;\n", -x, -y ); */
		if(i % 2 == 1)
		{
			printf("%8.5f %8.5f 1\n", x, y);
			printf("%8.5f %8.5f 0\n", -x, -y);
		}
	}
}
