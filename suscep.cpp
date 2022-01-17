#include <iostream>
#include <cmath>
#include <vector>
#include <cassert>
using std::scientific;
using namespace std;

// lattice size
const int dim = 3;
const int L = 3;
// needs to be known at compile time
const int vol = pow(L,dim);
const long numberOfConfigs = pow(2,vol);
// array which stores the dim 
int nbrAr[vol][dim];

// data of a single configuration
struct configData {
    int energy;
    double susc;
    double suscEnergy;
};

// output data for a given beta, to be plotted
struct outData {
    double tanhBeta;
    double beta;
    double energy;
    double susc;
    double suscEnergy;
};

void printConfigData(configData);

// print the entries of an integer vector
void printVector(const vector <int>);
void printBoolAr(const bool[], const int);

// configuration of spins, which is labeled by an integer in the range 1 ... 2^vol.
// a spin \pm 1 is set to be a bool {0,1} - for Potts or O(n) this would be different
class SpinConfig {
private:
public:
    SpinConfig(int);
    int m_label;
    bool m_spins[vol];
    
    void computeAll();

    double m_susc;
    double m_energy;
    double m_suscEnergy;
        
    void showConfig();
    // void printObs();

    configData fetchData();
};

// np.loadtxt(filename, dtype = float)



////////////////////
// general functions
////////////////////



////////////////////
// functions specific to the Ising model
////////////////////

// we label vectors of coordinates (x1, ..., xd) by an integer
vector <int> intToCoordinates(int);
int coordinatesToInt(vector <int>);
// spins are booleans, so need to explain how to multiply them
int multiplySpins(const bool, const bool);
    
int main () {

    
    // number of steps in tanh(beta)
    int betaSteps = 100;
 
    cout << "Lattice dimensions: " << L << "^" << dim << " = " << vol << ", "
         << numberOfConfigs << " configurations.\n";
    cout << "Number of bonds is " << vol*dim << ".\n";
    cout << endl;
    
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
        double Z=0, energy = 0, susc = 0, suscEn = 0;
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
        cout << tanhBeta << " " << beta << " " << energy << " " << susc << " " << od.suscEnergy << endl;
    }
    cout << "\nDone.\n\n";
}

SpinConfig::SpinConfig(int n)
{
    assert(n >= 0 && n < numberOfConfigs);
    
    m_label = n; // set label
    for(int ct = 0; ct<vol; ct++) {
        int rem = n % 2;
        if(rem == 0) m_spins[ct] = false;
        else m_spins[ct] = true;
        n = (n-rem)/2;
    }                              
};

void SpinConfig::computeAll() {
    int tp = 0;
    for(int i=0; i<vol; i++) {
        for(int j = 0; j<vol; j++) {
            tp += multiplySpins(m_spins[i], m_spins[j]);
        }
    }
    m_susc = tp/pow(vol,2);
   
    tp = 0;
    for(int i=0; i<vol; i++) {
        for(int d=0; d<dim; d++) {
            int nb = nbrAr[i][d];
            tp -= multiplySpins(m_spins[i], m_spins[nb]);
        }
    }
    m_energy = tp;
    m_suscEnergy = m_susc*m_energy;
}

void SpinConfig::showConfig() {
    printBoolAr(m_spins, vol);
}

configData SpinConfig::fetchData() {
    computeAll();
    
    configData dataAr;
    dataAr.energy = m_energy;
    dataAr.susc = m_susc;
    dataAr.suscEnergy = m_suscEnergy;
    return dataAr;
}

void printConfigData(configData cd) {
    cout << "[Energy, susceptibiltiy, mixed] = [" <<  cd.energy << ", " << cd.susc << ", " << cd.suscEnergy << "]\n";
}

void printVector(const vector <int>& v) {
    for(int p : v) std::cout << p << " ";
    std::cout << std::endl;
}

void printBoolAr(const bool b[], int size) {
    for(int i = 0; i<size; i++ ) std::cout << b[i] << " ";
    std::cout << std::endl;
}

vector <int> intToCoordinates(int n)
{
    assert(n >= 0 && n < vol);
    vector <int> out = {};
    while( n > 0 ) {
        int tp = n % L;
        out.push_back(tp);
        n = (n-tp)/L;
    }
    while( out.size() < dim ) out.push_back(0);
    return out;
}

int coordinatesToInt(vector <int> v)
{
    int out = 0;
    int mult = 1;
    while(v.size() > 0) {
        out += v.front()*mult;
        v.erase(v.begin());
        mult *= L;
    }
    return out;
}

int multiplySpins(bool b1, bool b2) {
    if(b1 == b2) return 1;
    else return -1;
}
            
      
