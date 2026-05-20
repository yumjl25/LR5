#ifndef PLANES_H
#define PLANES_H

#include <string>
#include <vector>
#include <map>
#include <set>

using namespace std;

enum class Type { 
    CREATE_PLANE,
    PLANES_FOR_TOWN,
    TOWNS_FOR_PLANE,
    PLANES,
    UNKNOWN
};

class PlaneSystem {
private:
    map<string, vector<string>> planes;
    
    bool planeExists(const string& name) const;
    vector<string> getPlanesForTown(const string& town) const;
    
public:
    void createPlane(const string& name, const vector<string>& towns);
    void planesForTown(const string& town) const;
    void townsForPlane(const string& name) const;
    void printAllPlanes() const;
    
    static Type getCommandType(const string& cmd); 
};

#endif