#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

/*
* Gustav Gränsbo
* https://open.kattis.com/problems/airlinehub
*/

#define PI 3.14159265

using namespace std;

// Ignore squareroot as we just want to compare
double chord_length(double x, double y, double z)
{
	return x*x + y*y + z*z;
}

struct node
{
	double x, y, z;
	double phi_deg {};
	double gamma_deg {};
	double max_distance {};
	
};

int main()
{
	unsigned n;
	// Solve cases until standard input is empty.
	while(scanf("%u", &n) == 1)
	{
		vector<node> hub(n);
		for(unsigned i = 0; i < n; ++i)
		{
			// Read input
			double phi, gamma;
			scanf("%lf %lf", &phi, &gamma);
			
			hub[i].phi_deg = phi;
			hub[i].gamma_deg = gamma;
			
			// Convert to radians
			phi *= PI/180;
			gamma *= PI/180;
			
			// Calculate x, y and z coordinates based on longitude and latitude
			hub[i].x = cos(phi) * cos(gamma);
			hub[i].y = cos(phi) * sin(gamma);
			hub[i].z = sin(phi);
			
			// Update the max distance of all existing nodes
			for(unsigned j = 0; j < i; ++j)
			{
				double d = chord_length(abs(hub[i].x - hub[j].x), abs(hub[i].y - hub[j].y), abs(hub[i].z - hub[j].z));
				if(d > hub[i].max_distance) hub[i].max_distance = d;
				if(d > hub[j].max_distance) hub[j].max_distance = d;
			}
		}
		
		// Find the node with the lowest max distance.
		double min_distance = 1e9;
		unsigned best_choice;
		for(unsigned i = 0; i < n; ++i)
		{
			if(hub[i].max_distance <= min_distance)
			{
				min_distance = hub[i].max_distance;
				best_choice = i;
			}
		}
		printf("%.2lf %.2lf\n", hub[best_choice].phi_deg, hub[best_choice].gamma_deg);
	}
}