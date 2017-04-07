/*
 * We will solve the damped oscillators equation.
 * d^2 x/dt^2 + lambda d x/d t + omega x = 0
 * We have to make it systems of first order ode.
 * d (x, y) /d t = ( y, - omega x - lambda y )
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <boost/numeric/odeint.hpp>
using namespace boost::numeric::odeint;

/* The type of container used to hold the state vector */
typedef std::vector< double > sv;
//typedef std::vector< double > state_vector;
// Define a state vector type of data, sv for short;



// Define lambda and omega

const double omega = 1.0;
const double lambda = 0.1;


// harmonic oscillator system prepared for use in odeint
void ho( const sv & s, sv & dsdt , const double /* t */ ) {

    dsdt[0] = s[1];
    dsdt[1] = - omega * s[0] - lambda * s[1];

}

//int write_data () {

//}




int main() {



// initial condition

    sv s(2);

    s[0] = 1.0;
    s[1] = 0.0;
    int STEPS = 1000;
    double STEP_SIZE = 0.01 ;

    std::ofstream data;

//    data.open("assets/ho-damped.txt");
    data.open("ho-damped.txt");


    for(int i = 0; i < STEPS; i ++ ) {
        integrate(ho, s, (i) * 10.0/STEPS, (i+1) * 10.0/STEPS , STEP_SIZE);
        std::cout << s[0] << " , " << s[1] <<std::endl;

        data << s[0] << "\n";
//        std::copy(s.begin(), s.end(), std::ostream_iterator<sv>( data, "1 \n" ) );

    }


    data.close();

    std::cout << "END OF PROGRAM INDICATOR!" << std::endl;

    return 0;

}