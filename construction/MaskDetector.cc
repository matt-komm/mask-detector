#include "MaskDetector.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4GeometryTolerance.hh"
#include "G4GeometryManager.hh"
#include "G4SDManager.hh"

#include "G4UserLimits.hh"

#include "G4Colour.hh"

#include "G4SystemOfUnits.hh"

#include <cmath>

//#include "G4ios.hh"
 
MaskDetector::MaskDetector():
    _worldLength(5.0*m),
    _checkOverlaps(true),
    _worldVolume(0)
{ 
    DefineMaterials();
    _tracker1VisAtt= new G4VisAttributes(G4Colour(1.0,1.0,0.0));
    _tracker2VisAtt= new G4VisAttributes(G4Colour(1.0,0.0,1.0));

    
}

MaskDetector::~MaskDetector()
{
}
 
G4VPhysicalVolume* MaskDetector::Construct()
{
    
    return DefineVolumes();
}

void MaskDetector::DefineMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();
    G4bool fromIsotopes = false;
    nistManager->FindOrBuildMaterial("G4_AIR", fromIsotopes);
    _pixelMaterial  = nistManager->FindOrBuildMaterial("G4_Si", fromIsotopes);
    _absorberMaterial = nistManager->FindOrBuildMaterial("G4_Al", fromIsotopes);
    G4cout << *(G4Material::GetMaterialTable()) << G4endl;
}   

G4LogicalVolume* MaskDetector::CreateStrip(G4double width, G4double length, G4double thickness, G4Material* material, SensitiveDetector* sd)
{
    G4Box* box = new G4Box("stripSolid",0.5*width,0.5*thickness,0.5*length);
    G4LogicalVolume* logicalVolume = new G4LogicalVolume(
        box,        //its solid
        material,   //its material
        "stripLV"   //its name
    ); 
    logicalVolume->SetSensitiveDetector(sd);
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    return logicalVolume;
}

G4LogicalVolume* MaskDetector::CreateTubs(G4double innerRadius, G4double outerRadius, G4double thickness, G4double angle, G4Material* material, SensitiveDetector* sd)
{
    G4Tubs* tube = new G4Tubs("capSolid",innerRadius,outerRadius,0.5*thickness,0*deg,angle);
    G4LogicalVolume* logicalVolume = new G4LogicalVolume(
        tube,        //its solid
        material,   //its material
        "capLV"   //its name
    ); 
    logicalVolume->SetSensitiveDetector(sd);
    G4SDManager::GetSDMpointer()->AddNewDetector(sd);
    return logicalVolume;
}

void MaskDetector::CreateBarrel(unsigned int layer, G4Material* material, G4double radius, G4double length, unsigned int amount, G4double tilted, G4double thickness)
{
    G4double width = std::sqrt(2*std::pow(radius,2)*(1-std::cos(360.0*deg/rad/amount+tilted/rad)));
    //width=100*mm;
    for (unsigned int i = 0; i < amount; ++i)
    {
        G4double angleRad = 360.0*deg/rad/amount*i;
        G4double xpos = std::sin(angleRad)*(radius+thickness*0.5);
        G4double ypos = std::cos(angleRad)*(radius+thickness*0.5);
        SensitiveDetector* sd = new SensitiveDetector(DetId::barrelId(layer,i));
        G4LogicalVolume* stripLV = CreateStrip(width,length, thickness, material,sd);
        if (i%2==0)
        {
            stripLV->SetVisAttributes(_tracker1VisAtt);
        }
        else
        {
            stripLV->SetVisAttributes(_tracker2VisAtt);
        }
        G4RotationMatrix* rotation = new G4RotationMatrix();
        rotation->set(G4ThreeVector(0,0,1),angleRad*rad+tilted);

        
        G4VPhysicalVolume* stripPV = new G4PVPlacement(
            rotation,               // no rotation
            G4ThreeVector(xpos,ypos,0.0), // position
            stripLV,         // its logical volume
            "stripPV",         // its name
            _worldVolume,               // its mother  volume
            false,           // no boolean operations
            0,               // copy number
            _checkOverlaps   // checking overlaps 
        ); 
    }
}

void MaskDetector::CreateEndcap(unsigned int layer, G4Material* material, G4double innerRadius, G4double outerRadius, G4double spacing, unsigned int amount, G4double tilted, G4double thickness)
{
    for (unsigned int i = 0; i < amount; ++i)
    {
        G4double angleRad = 360.0*deg/rad/amount*i;
        SensitiveDetector* sd = new SensitiveDetector(DetId::endcapId(layer,i));
        G4LogicalVolume* capLV = CreateTubs(innerRadius, outerRadius, thickness, 360*deg/rad/amount, material,sd);
        if (i%2==0)
        {
            capLV->SetVisAttributes(_tracker1VisAtt);
        }
        else
        {
            capLV->SetVisAttributes(_tracker2VisAtt);
        }
        G4RotationMatrix* rotationX = new G4RotationMatrix();
        rotationX->set(G4ThreeVector(std::cos(angleRad),std::sin(angleRad),0),tilted);
        
        G4RotationMatrix* rotationZ = new G4RotationMatrix();
        rotationZ->set(G4ThreeVector(0,0,1),angleRad*rad);
        (*rotationZ)*=(*rotationX);
        
        
        G4VPhysicalVolume* stripPV = new G4PVPlacement(
            rotationZ,               // no rotation
            G4ThreeVector(0.0,0.0,spacing), // position
            capLV,         // its logical volume
            "capPV",         // its name
            _worldVolume,               // its mother  volume
            false,           // no boolean operations
            0,               // copy number
            _checkOverlaps   // checking overlaps 
        ); 
    }
}

G4VPhysicalVolume* MaskDetector::DefineVolumes()
{
    G4GeometryManager::GetInstance()->SetWorldMaximumExtent(_worldLength);
    G4Material* air  = G4Material::GetMaterial("G4_AIR");
    
    G4Box* worldS = new G4Box("world",
        _worldLength/2,
        _worldLength/2,
        _worldLength/2
    );
    _worldVolume = new G4LogicalVolume(
        worldS,   //its solid
        air,      //its material
        "World"   //its name
    ); 
    G4VPhysicalVolume* world = new G4PVPlacement(
        0,               // no rotation
        G4ThreeVector(), // at (0,0,0)
        _worldVolume,         // its logical volume
        "World",         // its name
        0,               // its mother  volume
        false,           // no boolean operations
        0,               // copy number
        _checkOverlaps   // checking overlaps 
    );
    
    for (unsigned int i = 0; i < 5; ++i)
    {
        CreateBarrel(i,_pixelMaterial,25*cm+i*20*cm,1.0*m+i*0.2*m, 12, 0.0*deg);
        
    }
    //createEndcap(_pixelMaterial, 25*cm, 65*cm, 1.2*m, 16, 10.0*deg);
    //createEndcap(_pixelMaterial, 25*cm, 65*cm, 1.2*m, 16, 0.0*deg);
    
    //createBarrel(_absorberMaterial,130*cm,2.5*m, 16, 20.0*deg,20*cm);
    //static G4UserLimits stepLimit(_maxStep);
    //trackerLV->SetUserLimits(&stepLimit);
    
    return world;
}
