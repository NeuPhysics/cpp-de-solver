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
#include <boost/numeric/ublas/blas.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/assignment.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/odeint.hpp>
using namespace std;
using namespace boost::numeric::odeint;

/* The type of container used to hold the state vector */
typedef complex<double> wave_amp;
typedef array< complex<double> , 2> wave_fun;
typedef controlled_runge_kutta< runge_kutta_cash_karp54<wave_fun> > stepper_type;
//typedef runge_kutta4< wave_fun > stepper_type;
//typedef runge_kutta4< wave_fun , double ,
//        wave_fun , double ,
//        vector_space_algebra > stepper_type;
// Define wave function

// Define lambda and omega

const double s2theta = 0.92; // sin^2 2theta;theta_{12}
const double c2theta = sqrt( 1 - pow( s2theta, 2.0) );
const double energy = 1.0; //in unit of MeV
//const double deltam2 = 2.5e-15; // delta m _{23} in unit of MeV^2
const double deltam2 = 7.5e-17; // delta m _{12} in unit of MeV^2
//const double omega = deltam2/(2*energy); // omega vacuum
const double omega = 1.0; // scale all quantities using omega, now distance is x omega

const complex<double> I(0.0,1.0);


// harmonic oscillator system prepared for use in odeint
void schrodinger( const wave_fun & psi, wave_fun & dpsidt , const double /* t */ ) {

    dpsidt[0] = - I * (omega / 2) * ( -c2theta * psi[0] + s2theta * psi[1] );
    dpsidt[1] = - I * ( omega / 2) * ( s2theta * psi[0] + c2theta * psi[1] );

}

double vac_osc( double x ) {
    return 1 - pow(s2theta,2.0) * pow( sin ( omega * x/ 2 ) , 2.0 ) ;
}

double xhat2x (double xhat) {
    return (xhat / 0.190 ) * ( 7.5e-17 / deltam2 ) * ( energy / 1.0 ) ; //return x in km
}




int main() {

    wave_fun psi;

    psi[0] = 1.0;
    psi[1] = 0.0;

    int STEPS = 2000;
    double STEP_SIZE = 0.1;
    double END_POINT = 100;

    ofstream data;

    data.open("vac_osc.txt");


    for (int i = 0; i < STEPS; i++) {

        cout << integrate_adaptive( stepper_type() , schrodinger, psi, (i) * END_POINT / STEPS, (i + 1) * END_POINT / STEPS, STEP_SIZE ) << endl;

        data << (i + 1) * END_POINT / STEPS << " , " << xhat2x((i + 1) * END_POINT / STEPS ) << " , " << psi[0].real() << " , " << psi[0].imag() << " , " << psi[1].real() << " , " << psi[1].imag() << " , " << norm(psi[0]) << " , " << vac_osc( (i + 1) * END_POINT / STEPS ) << "\n";
        cout << psi[0] << " , " << psi[1] << endl;
        cout << norm(psi[0]) << endl;
        cout << vac_osc( (i + 1) * END_POINT / STEPS ) << endl;
    }

    data.close();

    cout << "END OF PROGRAM INDICATOR!" << endl;

    return 0;

} // To plot data using gnuplot: gnuplot -e "set terminal png; set datafile separator ','; plot 'vac_osc.txt' using 2:7 with points, 'vac_osc.txt' using 2:8 smooth csplines" | imgcat