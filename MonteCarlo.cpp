#include "MonteCarlo.hpp"

MonteCarlo::MonteCarlo(int Nscenarios, function<void(double,double*)> RandomVector)
	: generator(time(0)) {
	// Nscenarios is the dimension of the random vector X
	// The function RandomVector(N,CurrVal) saves f(N) on the array CurrVal(current value)
	// generator is used to generate random numbers: N(generator) is a Gaussian r.v.
	// Nsims is the number of random samplings that will be used in the Monte Carlo method
	this->Nscenarios = Nscenarios;
	this->RandomVector = RandomVector;
	CurrVal = new double[Nscenarios];
	Results = new double[Nscenarios];
}
//~~~~~~~~~~~~~~~~~~~~sample()~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MonteCarlo::sample() {
	// This function gives a sampling of the random vector X = f(N)
	// and saves it on the array CurrVal
	RandomVector(N(generator),CurrVal);
}
//~~~~~~~~~~~~~~~~~~~run()~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MonteCarlo::run(long unsigned int Nsims) {
	// This function takes the arithmetic mean of Nsims samplings of X
	// to approximate its vector of expectations, and saves it on the array Results
	for (int i=0; i<Nscenarios; i++) {
		Results[i] = 0;
	}
	for (long unsigned int k=0; k<Nsims; k++) {
		sample();
		for (int i=0; i<Nscenarios; i++) {
			Results[i] += CurrVal[i];
		}
	}
	for (int i=0; i<Nscenarios; i++) {
		Results[i] /= Nsims;
	}
}
//~~~~~~~~~~~~~~~~~~~show()~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

void MonteCarlo::show() {
	// This function prints the vector Results
	for (int i=0; i<Nscenarios; i++) {
		cout << "Scenario " << i+1 << ": " << Results[i] << "\n";
	}
}
	
double* MonteCarlo::getCurrVal() {
	return CurrVal;
}
	
double* MonteCarlo::getResults() {
	return Results;
}