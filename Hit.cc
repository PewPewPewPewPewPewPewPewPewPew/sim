#include "Hit.hh"

G4ThreadLocal G4Allocator<Hit>* HitAllocator = nullptr;

Hit::Hit() : G4VHit(), edep(0.), pos(G4ThreeVector()), time(0.), trackID(-1), kineticEnergy(0.), momentum(G4ThreeVector()) {}
Hit::~Hit() {}
Hit::Hit(const Hit& right) : G4VHit()
{
    edep = right.edep;
    pos = right.pos;
    time = right.time;
    trackID = right.trackID;
    particleName = right.particleName;
    kineticEnergy = right.kineticEnergy;
    momentum = right.momentum;
}
const Hit& Hit::operator=(const Hit& right)
{
    edep = right.edep;
    pos = right.pos;
    time = right.time;
    trackID = right.trackID;
    particleName = right.particleName;
    kineticEnergy = right.kineticEnergy;
    momentum = right.momentum;
    return *this;
}
int Hit::operator==(const Hit& right) const
{
    return (this == &right) ? 1 : 0;
}
