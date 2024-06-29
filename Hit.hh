#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4ThreeVector.hh"
#include "G4Allocator.hh"
#include "G4THitsCollection.hh"

class Hit : public G4VHit
{
public:
    Hit();
    virtual ~Hit();
    Hit(const Hit& right);
    const Hit& operator=(const Hit& right);
    int operator==(const Hit& right) const;

    inline void* operator new(size_t);
    inline void operator delete(void* hit);

    void SetEdep(G4double de) { edep = de; }
    void SetPos(G4ThreeVector xyz) { pos = xyz; }
    void SetTime(G4double t) { time = t; }
    void SetTrackID(G4int id) { trackID = id; }
    void SetParticleName(const G4String& name) { particleName = name; }
    void SetKineticEnergy(G4double ke) { kineticEnergy = ke; }
    void SetMomentum(G4ThreeVector mom) { momentum = mom; }

    G4double GetEdep() const { return edep; }
    G4ThreeVector GetPos() const { return pos; }
    G4double GetTime() const { return time; }
    G4int GetTrackID() const { return trackID; }
    G4String GetParticleName() const { return particleName; }
    G4double GetKineticEnergy() const { return kineticEnergy; }
    G4ThreeVector GetMomentum() const { return momentum; }

private:
    G4double edep;
    G4ThreeVector pos;
    G4double time;
    G4int trackID;
    G4String particleName;
    G4double kineticEnergy;
    G4ThreeVector momentum;
};

typedef G4THitsCollection<Hit> HitCollection;

extern G4ThreadLocal G4Allocator<Hit>* HitAllocator;

inline void* Hit::operator new(size_t)
{
    if (!HitAllocator)
        HitAllocator = new G4Allocator<Hit>;
    return (void*)HitAllocator->MallocSingle();
}

inline void Hit::operator delete(void* hit)
{
    HitAllocator->FreeSingle((Hit*)hit);
}

#endif
