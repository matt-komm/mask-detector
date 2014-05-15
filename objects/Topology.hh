#ifndef TOPOLOGY_H
#define TOPOLOGY_H

#include "DetId.hh"
#include "G4RotationMatrix.hh"
#include "G4ThreeVector.hh"

class Surface
{
    protected:
        G4double _length;
        G4double _width;
        G4ThreeVector _position;
        G4RotationMatrix _rotation;
        
    public:
        Surface(G4double length, G4double width, G4ThreeVector position, G4RotationMatrix rotation):
            _length(length),
            _width(width),
            _position(position),
            _rotation(rotation)
        {
        
        }
        ~Surface()
        {
        }
};


template<unsigned int sides=12>
class BarrelLayer
{
    public:
        BarrelLayer()
        {
        }
        
        ~BarrelLayer()
        {
        }
};

class Topology
{
    protected:
        Topology();
    public:
        
        ~Topology();
};

#endif

