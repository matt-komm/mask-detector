#ifndef MASKDETECTOR_H
#define MASKDETECTOR_H

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "SensitiveDetector.hh"

#include <vector>

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class G4UserLimits;

class B2MagneticField;


class MaskDetector: 
    public G4VUserDetectorConstruction
{
    private:
        
        G4double _worldLength;

        G4UserLimits* _stepLimit;
        G4bool  _checkOverlaps;
        
        G4LogicalVolume* _worldVolume;
        G4Material* _pixelMaterial;
        G4Material* _absorberMaterial;
        
        G4VisAttributes* _tracker1VisAtt;
        G4VisAttributes* _tracker2VisAtt;
        
        SensitiveDetector* _sensitiveDetector;
        
        G4LogicalVolume* createStrip(G4double width, G4double length, G4double thickness, G4Material* material);
        void createBarrel(G4Material* material, G4double radius=15*mm, G4double length=2*m, G4int amount=10, G4double tilted=0.0, G4double thickness=2*mm);

        G4LogicalVolume* createTubs(G4double innerRadius, G4double outerRadius, G4double thickness, G4double angle, G4Material* material);
        void createEndcap(G4Material* material, G4double innerRadius, G4double outerRadius, G4double spacing, G4int amount, G4double tilted, G4double thickness=2*mm);

        void DefineMaterials();
        G4VPhysicalVolume* DefineVolumes();
    

    public:
        MaskDetector();
        virtual ~MaskDetector();

        virtual G4VPhysicalVolume* Construct();
};
#endif
