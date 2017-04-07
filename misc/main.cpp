#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <vector>

int main() {

    std::vector<int> my_vector(3);
    my_vector[0] = 1;
    my_vector[1] = 2;
    my_vector[2] = 3;

    std::ofstream assets;

    assets.open("test.txt");

    std::copy(my_vector.begin(), my_vector.end(), std::ostream_iterator<int>(std::cout, "\n"));

    assets << "test";

    assets.close();

    return 0;
}