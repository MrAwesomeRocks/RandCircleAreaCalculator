// RandCircleAreaCalculator.cpp : Defines the entry point for the console application.
//

//Include all include files needed
#define _USE_MATH_DEFINES
#include <omp.h>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
using namespace std; //get rid of having to write std::FUNCTION

//Define Variables
size_t NThrows = 100000; //NThrows = # of throws/random numbers


int main() {
	srand(time(NULL)); //Seed the random number generator
	for (int j = 1; j <= 40; j++) {
		size_t NHits = 0, NMisses = 0;
		NThrows *= 10;
#pragma omp parallel for reduction(+ : NHits) reduction(+ : NMisses)
		for (long long int i = 0; i < NThrows; i++) {
			long double xi = static_cast<long double>(rand()) / RAND_MAX; //Generate positive x-value range:[0,1]
			long double yi = static_cast<long double>(rand()) / RAND_MAX; //Generate positive y-value range:[0,1]
			long double x = 1 - 2 * xi; //50% chance negation
			long double y = 1 - 2 * yi; //50% chance negation
			long double r2 = x*x + y*y; //Determine radius squared from center
			if (r2 <= 1)  //Count number of hits
			{
				NHits++;
			}
			else if (r2 > 1) //Count number of misses
			{
				NMisses++;
			}
		}
		long double HitTotal = static_cast<long double>(NHits) / static_cast<long double>(NThrows); //Compute Hits/Total thrown
		long double approxPi = HitTotal * 4; //Determine area of circle by multiplying HitTotal by area of square
		printf(
			"Try %2d: %18.16f  error = %10.3e\%\n",
			j, approxPi, 100*abs((1 - approxPi / M_PI))
		);
	}
}
