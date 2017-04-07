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
// Define a state vector type of data, sv for short;



// Define lambda and omega

const double omega = 1.0;
const double lambda = 0.1;

const complex<double> I(0.0,1.0);


// harmonic oscillator system prepared for use in odeint
void schrodinger( const wave_amp & psi, wave_amp & dpsidt , const double /* t */ ) {

    dpsidt = psi * I;

}




int main() {

    wave_amp psi;

    psi = 1.0 * I ;

    int STEPS = 1000;
    double STEP_SIZE = 0.1;

    ofstream data;

    data.open("complex.txt");

    for(int i = 0; i < STEPS; i++ ) {

        cout << integrate(schrodinger, psi, (i) * 10.0/STEPS, (i+1) * 10.0/STEPS , STEP_SIZE) << endl;

        data << psi.real() << " , " << psi.imag() << "\n";
        cout << psi << endl;
    }

    data.close();

    cout << "END OF PROGRAM INDICATOR!" << endl;

    return 0;

}