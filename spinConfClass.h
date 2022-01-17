// data format of a single configuration
struct configData {
    int energy;
    double susc;
    double suscEnergy;
};

// spins are booleans, so need to explain how to multiply them
int multiplySpins(bool b1, bool b2) {
    if(b1 == b2) return 1;
    else return -1;
}

void printBoolAr(const bool b[], int size) {
    for(int i = 0; i<size; i++ ) std::cout << b[i] << " ";
    std::cout << std::endl;
}

//////////////////////
/// the class itself
//////////////////////
// configuration of spins, which is labeled by an integer in the range 1 ... 2^vol.
// a spin \pm 1 is set to be a bool {0,1} - for Potts or O(n) this would be different
//////////////////////
class SpinConfig {
private:
    int m_label;
    bool m_spins[vol];
    double m_susc;
    double m_energy;
    double m_suscEnergy;
public:
    SpinConfig(int);
    void computeAll();
    void showConfig();
    configData fetchData(); // compute and output the data of the configuration
};

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
