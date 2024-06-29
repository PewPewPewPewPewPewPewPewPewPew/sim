#ifndef HIT_HH
#define HIT_HH

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4String.hh"

class Hit : public G4VHit
{
public:
    Hit();
    virtual ~Hit();
    Hit(const Hit&);
    const Hit& operator=(const Hit&);

    void SetEdep(G4double de) { edep = de; }
    G4double GetEdep() const { return edep; }

    void SetPos(const G4ThreeVector& pos) { position = pos; }
    G4ThreeVector GetPos() const { return position; }

    void SetTime(G4double time) { globalTime = time; }
    G4double GetTime() const { return globalTime; }

    void SetTrackID(G4int id) { trackID = id; }
    G4int GetTrackID() const { return trackID; }

    void SetParticleName(G4String name) { particleName = name; }
    G4String GetParticleName() const { return particleName; }

    void SetKineticEnergy(G4double ke) { kineticEnergy = ke; }
    G4double GetKineticEnergy() const { return kineticEnergy; }

    void SetMomentum(const G4ThreeVector& mom) { momentum = mom; }
    G4ThreeVector GetMomentum() const { return momentum; }

    void SetNextVolumeName(const G4String& name) { nextVolumeName = name; }
    G4String GetNextVolumeName() const { return nextVolumeName; }

    void Print() const;

private:
    G4double edep;
    G4ThreeVector position;
    G4double globalTime;
    G4int trackID;
    G4String particleName;
    G4double kineticEnergy;
    G4ThreeVector momentum;
    G4String nextVolumeName;
};

typedef G4THitsCollection<Hit> HitCollection;
extern G4ThreadLocal G4Allocator<Hit>* HitAllocator;

#endif
