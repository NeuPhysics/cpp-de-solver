/*
 * We will solve the vacuum oscillation equation.
 * i d / dx {psi1, psi2} = omega { { c, s }, { s , -c } } . { psi1, psi2 }
 * We have to make it systems of first order ode.
 * d (x, y) /d t = ( y, - omega x - lambda y )
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <complex>
#include <boost/numeric/odeint.hpp>
using namespace std;
using namespace boost::numeric::odeint;

/* The type of container used to hold the state vector */
typedef complex<double> wave_amp;
typedef vector<wave_amp> wave_fun;
// Define wave function

// Define lambda and omega

const double omega = 1.0;
const double lambda = 0.1;

const complex<double> I(0.0,1.0);


// harmonic oscillator system prepared for use in odeint
void schrodinger( const wave_fun & psi, wave_fun & dpsidt , const double /* t */ ) {

    dpsidt[0] = psi[0] * I;
    dpsidt[1] = psi[1] * I;

}




int main() {

    wave_fun psi;

    psi[0] = 1.0 * I;
    psi[1] = 1.0 * I;

    int STEPS = 1000;
    double STEP_SIZE = 0.1;

    ofstream data;

    data.open("complex.txt");

    for (int i = 0; i < STEPS; i++) {

        cout << integrate(schrodinger, psi, (i) * 10.0 / STEPS, (i + 1) * 10.0 / STEPS, STEP_SIZE) << endl;

        data << psi[0].real() << " , " << psi[0].imag() << " , " << psi[1].real() << " , " << psi[1].imag() << "\n";
        cout << psi[0] << " , " << psi[1] << endl;
    }

    data.close();

    cout << "END OF PROGRAM INDICATOR!" << endl;

    return 0;

}