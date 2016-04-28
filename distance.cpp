#include <iostream>
#include <cmath>
#include <utility>
#include <iomanip>      // std::setprecision


double hav(double dif) {
        return (1 - cos(dif))/2;
}

double Distance(std::pair<double, double>coord1, std::pair<double, double>coord2) {

        double r = 6371.0088;
        double pi = 3.14159265358979323846;

        double lat1 = coord1.first * pi / 180;
        double lng1 = coord1.second * pi / 180;

        double lat2 = coord2.first * pi / 180;
        double lng2 = coord2.second * pi / 180;

        double difLat = lat2 - lat1;
        double difLng = lng2 - lng1;

        double res = 2 * r * asin(
          sqrt(
            hav(difLat)
            + cos(lat1)
            * cos(lat2)
            * hav(difLng)
          )
        );

        return res * 1000;
}


int main()
{
        std::pair<double, double> coord1 = std::pair<double, double>(33, 1);
        std::pair<double, double> coord2 = std::pair<double, double>(-45, -9);
        double res = Distance(coord1, coord2);

        std::cout << std::setprecision(9) << res << std::endl;
        return 0;
}
