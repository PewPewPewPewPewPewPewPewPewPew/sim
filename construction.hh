#ifndef MY_PROJECT_CONSTRUCTION_HH // Updated include guard
#define MY_PROJECT_CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Tubs.hh"
#include "G4ThreeVector.hh"
#include "SensitiveDetector.hh"
#include "globals.hh"



class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
    DetectorConstruction();
    virtual ~DetectorConstruction();

    virtual G4VPhysicalVolume* Construct() override; // Explicitly mark as override
    virtual void ConstructSDandField() override;


private:
    G4LogicalVolume *fLogicDetectorFront;
    G4LogicalVolume *fLogicDetectorBack;

};

#endif // MY_PROJECT_CONSTRUCTION_HH
