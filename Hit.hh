#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"

class Hit : public G4VHit
{
public:
    Hit();
    virtual ~Hit();
    Hit(const Hit& hit);
    const Hit& operator=(const Hit& hit);
    int operator==(const Hit& hit) const;

    inline void* operator new(size_t);
    inline void operator delete(void*);

    void SetEdep(G4double edep) { fEdep = edep; }
    G4double GetEdep() const { return fEdep; }

    void SetPos(const G4ThreeVector& pos) { fPos = pos; }
    G4ThreeVector GetPos() const { return fPos; }

    void SetTime(G4double time) { fTime = time; }
    G4double GetTime() const { return fTime; }

    void SetTrackID(G4int trackID) { fTrackID = trackID; }
    G4int GetTrackID() const { return fTrackID; }

private:
    G4double fEdep;
    G4ThreeVector fPos;
    G4double fTime;
    G4int fTrackID;
};

typedef G4THitsCollection<Hit> HitsCollection;

extern G4ThreadLocal G4Allocator<Hit>* HitAllocator;

inline void* Hit::operator new(size_t)
{
    if (!HitAllocator) HitAllocator = new G4Allocator<Hit>;
    return (void*)(HitAllocator->MallocSingle());
}

inline void Hit::operator delete(void* hit)
{
    HitAllocator->FreeSingle((Hit*)hit);
}

#endif