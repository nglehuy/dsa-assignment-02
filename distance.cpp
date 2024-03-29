#include <string.h>
#include <time.h>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#define __PI 3.14159265358979323846
#define earthRadiusKm 6371.0
using namespace std;
double deg2rad(double deg) { return (deg * __PI / 180); }
///  This function converts radians to decimal degrees
double rad2deg(double rad) { return (rad * 180 / __PI); }
/**
 * Returns the distance between two points on the Earth.
 * Direct translation from http://en.wikipedia.org/wiki/Haversine_formula
 * @param lat1d Latitude of the first point in degrees
 * @param lon1d Longitude of the first point in degrees
 * @param lat2d Latitude of the second point in degrees
 * @param lon2d Longitude of the second point in degrees
 * @return The distance between the two points in kilometers
 */
double distanceEarth(double lat1d, double lon1d, double lat2d, double lon2d) {
    double lat1r, lon1r, lat2r, lon2r, u, v;
    lat1r = deg2rad(lat1d);
    lon1r = deg2rad(lon1d);
    lat2r = deg2rad(lat2d);
    lon2r = deg2rad(lon2d);
    u     = sin((lat2r - lat1r) / 2);
    v     = sin((lon2r - lon1r) / 2);
    return 2.0 * earthRadiusKm * asin(sqrt(u * u + cos(lat1r) * cos(lat2r) * v * v));
}
int main(int narg, char **argv) {
    double lat1, lon1, lat2, lon2;
    string a(argv[2]);
    string b(argv[1]);
    string c(argv[4]);
    string d(argv[3]);
    stringstream(a) >> lat1;
    stringstream(b) >> lon1;
    stringstream(c) >> lat2;
    stringstream(d) >> lon2;
    cout << "Distance = " << fabs(distanceEarth(lat1, lon1, lat2, lon2)) << endl;
    return 0;
}
