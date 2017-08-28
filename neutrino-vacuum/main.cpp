/*
 * We will solve the vacuum neutrino oscillations in this case with a simple 1D model.
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

// Record probability for every rstep in spatial z
const int rstep = 100;

// Number of steps in between before saving the array
const int sstep = 200;

// Number of iterations
const int Ntop = 1000;

// Setup Parameters

// delta z
const double dz = 0.01;

// Length of z direction
const double L = 1.0;


// Define lambda and omega

const double s2theta = 0.92; // sin^2 2theta;theta_{12}
const double c2theta = sqrt( 1 - pow( s2theta, 2.0) );
const double energy = 1.0; //in unit of MeV
//const double deltam2 = 2.5e-15; // delta m _{23} in unit of MeV^2
const double deltam2 = 7.5e-17; // delta m _{12} in unit of MeV^2
//const double omega = deltam2/(2*energy); // omega vacuum
const double omega = 1.0; // scale all quantities using omega, now distance is x omega


// Define the state type for odeint
typedef boost::array< double , 3 > state_type;


state_type hvac = { -c2theta * omega/2, s2theta * omega/2, 0 * omega/2 };


void neutrino( const state_type &rho , state_type &drhodz, double t )
{
    drhodz[0] = 2 * ( hvac[2] * rho[1] - hvac[1] * rho[2] );
    drhodz[1] = 2 * ( hvac[0] * rho[2] - hvac[2] * rho[0] );
    drhodz[2] = 2 * ( hvac[1] * rho[0] - hvac[0] * rho[1] );
}


ofstream data("vac_osc.txt");

void write_neutrino( const state_type &rho , const double t )
{
    cout << t << " , " << rho[0] << " , " << rho[1] << " , " << rho[2] << endl;
    data << t << " , " << rho[0] << " , " << rho[1] << " , " << rho[2] << endl;
}

int main(int argc, char **argv)
{
    state_type rho = { 1.0 , 0.0 , 0.0 }; // initial conditions
    integrate( neutrino , rho , 0.0 , 25.0 , 0.1 , write_neutrino );
}

// gnuplot -e "set terminal png; set datafile separator ','; plot 'cmake-build-debug/vac_osc.txt' using 1:2 with points" | imgcat
