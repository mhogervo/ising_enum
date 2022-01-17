#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
using namespace std;
using std::scientific;

// lattice size
const int dim = 2;
const int L = 3;
// needs to be known at compile time
const int vol = pow(L,dim);
const long numberOfConfigs = pow(2,vol);
// array which stores the neighbors of sites
int nbrAr[vol][dim];

// defines a class SpinConfig which stores and manipulates configurations;
// and some small functions
#include "spinConfClass.h"

// output data for a given beta, to be plotted
struct outData {
    double tanhBeta;
    double beta;
    double energy;
    double susc;
    double suscEnergy;
};

//void printConfigData(configData);
//void printVector(const vector <int>);
//void printBoolAr(const bool[], const int);

// we label vectors of coordinates (x1, ..., xd) by an integer
vector <int> intToCoordinates(int);
int coordinatesToInt(vector <int>);
    
int main () {    
    // number of steps in tanh(beta)
    int betaSteps = 100;
 
    cout << "\nLattice dimensions: " << L << "^" << dim << " = " << vol << ", "
         << numberOfConfigs << " configurations.\n";
    cout << "Number of bonds is " << vol*dim << ".\n\n";
    
    // populate the array of neighbors
    for(int x=0; x<vol; x++) {
        vector <int> xCoords = intToCoordinates(x);
        for(int d=0; d<dim; d++) {
            auto newCoords = xCoords;
            newCoords[d] = (newCoords[d]+1) % L;
            nbrAr[x][d] = coordinatesToInt(newCoords);
        }
    }

    cout << "Running through all configurations...\n";
    // go through all configurations and compute observables
    vector <configData> configDataAr;
    for(int n=0; n<numberOfConfigs; n++) {
        SpinConfig currentConfig(n);
        auto cd = currentConfig.fetchData();
        configDataAr.push_back(cd);
    }
    cout << endl;

    // list of values of tanh(beta) for which we'll compute
    double tanhBetaList[betaSteps];
    {
        double deltaTanhBeta = 1.0f/betaSteps;
        for(int i=0; i< betaSteps; i++) tanhBetaList[i] = deltaTanhBeta*i;
    }
      
    cout << "Computing observables for a range of values of tanh(beta)...\n\n";
    vector <outData> outputData;

    cout << scientific; // formatting output
   
    for(int i=0; i<betaSteps; i++) {
        double tanhBeta = tanhBetaList[i];
        double beta = atanh(tanhBeta);

        outData od;
        od.tanhBeta = tanhBeta, od.beta = beta;
        // running tally of observables as we go through
        // the list of configurations:
        double Z = 0, energy = 0, susc = 0, suscEn = 0;
        for(configData cd : configDataAr) {
            double wt = exp(-beta*cd.energy); // Boltzmann weight
            Z += wt;
            energy += cd.energy * wt;
            susc += cd.susc * wt;
            suscEn += cd.suscEnergy * wt;
        };
        energy /= Z;
        susc /= Z;
        suscEn /= Z;

        od.energy = energy;
        od.susc = susc;
        od.suscEnergy = susc*energy - suscEn;
        
        outputData.push_back(od);

        cout << od.tanhBeta << " " << od.beta << " " << od.energy << " " << od.susc << " " << od.suscEnergy << endl;
    }
    cout << "\nDone.\n\n";

    
}

// void printConfigData(configData cd) {
//     cout << "[Energy, susceptibiltiy, mixed] = [" <<  cd.energy << ", " << cd.susc << ", " << cd.suscEnergy << "]\n";
// }

// void printVector(const vector <int>& v) {
//     for(int p : v) std::cout << p << " ";
//     std::cout << std::endl;
// }

vector <int> intToCoordinates(int n) {
    assert(n >= 0 && n < vol);
    vector <int> out = {};
    while(n > 0) {
        int tp = n % L;
        out.push_back(tp);
        n = (n-tp)/L;
    }
    while(out.size() < dim) out.push_back(0);
    return out;
}

int coordinatesToInt(vector <int> v) {
    int out = 0, mult = 1;
    while(v.size() > 0) {
        out += v.front()*mult;
        v.erase(v.begin());
        mult *= L;
    }
    assert(out >= 0 && out < vol);
    return out;
}
      
