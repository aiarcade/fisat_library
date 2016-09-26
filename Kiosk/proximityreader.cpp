#include "proximityreader.h"

ProximityReader::ProximityReader()
{


}

int ProximityReader::readFile()
{
     datafile.open("/tmp/proximity",ios::in);
     int count=0;
     std::string _line;

     if (datafile.is_open())
    {
         while (std::getline(datafile, _line))
                 ++count;
             std::cout << "Number of lines in text file: " << count;

    }
     datafile.close();
     return count;
}

int ProximityReader::isPerson()
{
    if(readFile()>1)
        return 1;
    else
        return 0;
}



