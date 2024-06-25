#include "construction.hh"
#include "SensitiveDetector.hh"
#include "G4NistManager.hh"
#include "G4Material.hh"
#include "G4Element.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4ThreeVector.hh"
#include "G4VisAttributes.hh"
#include "G4UserLimits.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"


MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    G4NistManager* nist = G4NistManager::Instance();

    // Define elements
    G4Element* Ga = nist->FindOrBuildElement("Ga");
    G4Element* N = nist->FindOrBuildElement("N");
    G4Element* Zn = nist->FindOrBuildElement("Zn");
    G4Element* O = nist->FindOrBuildElement("O");

    // Define materials
    G4Material* GaN = new G4Material("GaN", 6.15 * g/cm3, 2);
    GaN->AddElement(Ga, 1);
    GaN->AddElement(N, 1);

    G4Material* ZnO = new G4Material("ZnO", 5.610 * g/cm3, 2);
    ZnO->AddElement(Zn, 1);
    ZnO->AddElement(O, 1);

    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");

    // Define silicon material
    G4Material* Si = nist->FindOrBuildMaterial("G4_Si");

    // World volume
    G4Box* solidWorld = new G4Box("solidWorld", 50 * um, 50 * um, 50 * um);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicWorld");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", nullptr, false, 0, true);

    // Nanorod dimensions
    G4double radius = 500 * nm;
    G4double length = 5 * um;
    G4double distance = 3 * um;
    G4double coverThickness =  40 * nm; // Thickness of GaN layer

    // Solid for ZnO nanorod
    G4Tubs* solidNanorod = new G4Tubs("solidNanorod", 0, radius, length / 2, 0. * deg, 360. * deg);
    G4LogicalVolume* logicNanorod = new G4LogicalVolume(solidNanorod, ZnO, "logicNanorod");

    // Visualization attributes for ZnO nanorod
    G4VisAttributes* nanorodVisAttr = new G4VisAttributes(G4Colour(0.0, 0.0, 1.0)); // Blue
    nanorodVisAttr->SetVisibility(true);
    logicNanorod->SetVisAttributes(nanorodVisAttr);

    // Solid for GaN cover tube (sides)
    G4Tubs* solidCoverTube = new G4Tubs("solidCoverTube", radius, radius + coverThickness, length / 2, 0. * deg, 360. * deg);
    G4LogicalVolume* logicCoverTube = new G4LogicalVolume(solidCoverTube, GaN, "logicCoverTube");

    // Visualization attributes for GaN cover tube
    G4VisAttributes* coverTubeVisAttr = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Red
    coverTubeVisAttr->SetVisibility(true);
    logicCoverTube->SetVisAttributes(coverTubeVisAttr);

    // Solid for GaN cover cap (top)
    G4Tubs* solidCoverCap = new G4Tubs("solidCoverCap", 0, radius + coverThickness, coverThickness / 2, 0. * deg, 360. * deg);
    G4LogicalVolume* logicCoverCap = new G4LogicalVolume(solidCoverCap, GaN, "logicCoverCap");

    // Visualization attributes for GaN cover cap
    G4VisAttributes* coverCapVisAttr = new G4VisAttributes(G4Colour(1.0, 0.0, 0.0)); // Red
    coverCapVisAttr->SetVisibility(true);
    logicCoverCap->SetVisAttributes(coverCapVisAttr);

    // Set user limits
    G4double maxStep = 0.2 * um;
    G4UserLimits* userLimits = new G4UserLimits(maxStep);
    logicNanorod->SetUserLimits(userLimits);
    logicCoverCap->SetUserLimits(userLimits);
    logicCoverTube->SetUserLimits(userLimits);

    // Array dimensions
    G4double arrayWidth = 10 * distance; // width of the array
    G4double arrayHeight = 10 * distance; // height of the array
    G4double arrayDepth = length + coverThickness; // depth of the array (length of nanorod + thickness of cover cap)

    // Silicone box dimensions (5% larger than the array dimensions)
    G4double boxWidth = 1.0 * arrayWidth;
    G4double boxHeight = 1.0 * arrayHeight;
    G4double boxThickness = 1 * um;

    // Solid for Silicone box
    G4Box* solidBox = new G4Box("solidBox", boxWidth / 2, boxHeight / 2, boxThickness / 2);
    G4LogicalVolume* logicBox = new G4LogicalVolume(solidBox, Si, "logicBox");

    // Visualization attributes for Silicone box
    G4VisAttributes* boxVisAttr = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); // Yellow
    boxVisAttr->SetVisibility(true);
    logicBox->SetVisAttributes(boxVisAttr);

    // Center the nanorod array within the world volume
    G4double arrayOffsetZ = -boxThickness / 2;

    // Loop to place nanorods and their covers
    for (G4int i = 0; i < 10; ++i)
    {
        for (G4int j = 0; j < 10; ++j)
        {
            G4double xPos = (i - 5) * distance; // Center the array in the world volume
            G4double yPos = (j - 5) * distance; // Center the array in the world volume
            G4double zPosNanorod = length / 2 + arrayOffsetZ; // Adjust for centering

            // Place ZnO nanorod
            G4ThreeVector nanorodPosition = G4ThreeVector(xPos, yPos, zPosNanorod);
            new G4PVPlacement(0, nanorodPosition, logicNanorod, "physNanorod", logicWorld, false, i * 10 + j, true);

            // Place GaN cover tube (adjust z position accordingly)
            G4ThreeVector coverTubePosition = G4ThreeVector(xPos, yPos, zPosNanorod);
            new G4PVPlacement(0, coverTubePosition, logicCoverTube, "physCoverTube", logicWorld, false, i * 10 + j, true);

            // Place GaN cover cap (adjust z position accordingly)
            G4double zPosCoverCap = zPosNanorod + length / 2 + coverThickness / 2; // Place at the top of the nanorod
            G4ThreeVector coverCapPosition = G4ThreeVector(xPos, yPos, zPosCoverCap);
            new G4PVPlacement(0, coverCapPosition, logicCoverCap, "physCoverCap", logicWorld, false, i * 10 + j, true);
        }
    }

    // Position for the silicone box (centered in the world volume)
    G4ThreeVector boxPosition = G4ThreeVector(-1.5 * um, -1.5 * um, arrayOffsetZ);
    new G4PVPlacement(0, boxPosition, logicBox, "physBox", logicWorld, false, 0, true);

    G4Material* detectorMat = worldMat;

    // Size of the detector box (same size as the side of the world)
    G4double detectorThickness = 1 * nm; // Very thin
    G4double detectorSizeXY = 50 * um;   // Same as world size

    // Positions for the detectors
    G4double zPositionFront = -24 * um; // Just outside the world on the front
    G4double zPositionBack = 24 * um;   // Just outside the world on the back

    // Create front detector volume
    G4Box* solidDetectorFront = new G4Box("solidDetectorFront", detectorSizeXY / 2, detectorSizeXY / 2, detectorThickness / 2);
    logicDetectorFront = new G4LogicalVolume(solidDetectorFront, detectorMat, "logicDetectorFront");
    new G4PVPlacement(0, G4ThreeVector(0., 0., zPositionFront), logicDetectorFront, "physDetectorFront", logicWorld, false, 0, true);

    // Create back detector volume
    G4Box* solidDetectorBack = new G4Box("solidDetectorBack", detectorSizeXY / 2, detectorSizeXY / 2, detectorThickness / 2);
    logicDetectorBack = new G4LogicalVolume(solidDetectorBack, detectorMat, "logicDetectorBack");
    new G4PVPlacement(0, G4ThreeVector(0., 0., zPositionBack), logicDetectorBack, "physDetectorBack", logicWorld, false, 0, true);

    // Visualization attributes for detectors
    G4VisAttributes* detectorVisAttr = new G4VisAttributes(G4Colour(0.0, 1.0, 0.0)); // Green
    detectorVisAttr->SetVisibility(true);
    logicDetectorFront->SetVisAttributes(detectorVisAttr);
    logicDetectorBack->SetVisAttributes(detectorVisAttr);
// Create and register sensitive detectors
    G4SDManager* sdManager = G4SDManager::GetSDMpointer();
    SensitiveDetector* detector = new SensitiveDetector("SensitiveDetector");
    sdManager->AddNewDetector(detector);

    // Attach the sensitive detector to the logical volumes
    logicDetectorFront->SetSensitiveDetector(detector);
    logicDetectorBack->SetSensitiveDetector(detector);

    return physWorld;
}
