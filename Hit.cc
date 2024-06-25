#include "Hit.hh"

G4ThreadLocal G4Allocator<Hit>* HitAllocator = nullptr;

Hit::Hit() : G4VHit(), fEdep(0.), fPos(G4ThreeVector()), fTime(0.), fTrackID(-1)
{}

Hit::~Hit()
{}

Hit::Hit(const Hit& hit) : G4VHit()
{
    fEdep = hit.fEdep;
    fPos = hit.fPos;
    fTime = hit.fTime;
    fTrackID = hit.fTrackID;
}

const Hit& Hit::operator=(const Hit& hit)
{
    fEdep = hit.fEdep;
    fPos = hit.fPos;
    fTime = hit.fTime;
    fTrackID = hit.fTrackID;
    return *this;
}

int Hit::operator==(const Hit& hit) const
{
    return (this == &hit) ? 1 : 0;
}