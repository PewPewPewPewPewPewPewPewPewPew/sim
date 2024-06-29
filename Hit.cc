#include "Hit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

G4ThreadLocal G4Allocator<Hit>* HitAllocator = 0;

Hit::Hit()
    : G4VHit(),
      edep(0.),
      position(G4ThreeVector()),
      globalTime(0.),
      trackID(-1),
      particleName(""),
      kineticEnergy(0.),
      momentum(G4ThreeVector()),
      nextVolumeName("")
{}

Hit::~Hit() {}

Hit::Hit(const Hit& right)
    : G4VHit()
{
    edep = right.edep;
    position = right.position;
    globalTime = right.globalTime;
    trackID = right.trackID;
    particleName = right.particleName;
    kineticEnergy = right.kineticEnergy;
    momentum = right.momentum;
    nextVolumeName = right.nextVolumeName;
}

const Hit& Hit::operator=(const Hit& right)
{
    if (this != &right) {
        edep = right.edep;
        position = right.position;
        globalTime = right.globalTime;
        trackID = right.trackID;
        particleName = right.particleName;
        kineticEnergy = right.kineticEnergy;
        momentum = right.momentum;
        nextVolumeName = right.nextVolumeName;
    }
    return *this;
}

void Hit::Print() const
{
    G4cout << "  trackID: " << trackID
           << "  particle: " << particleName
           << "  energy deposit: " << G4BestUnit(edep, "Energy")
           << "  position: " << G4BestUnit(position, "Length")
           << "  time: " << G4BestUnit(globalTime, "Time")
           << "  kinetic energy: " << G4BestUnit(kineticEnergy, "Energy")
           << "  momentum: " << G4BestUnit(momentum, "Energy")
           << "  next volume: " << nextVolumeName
           << G4endl;
}
