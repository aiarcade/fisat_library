#ifndef PROXIMITYREADER_H
#define PROXIMITYREADER_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


class ProximityReader
{
public:
    ProximityReader();
    int readFile();
    int isPerson();
private:

    string line;
    ifstream datafile;
};

#endif // PROXIMITYREADER_H
