//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

#ifndef A01_DriftChamberHit_hh
#define A01_DriftChamberHit_hh

#include <G4VHit.hh>
#include <G4THitsCollection.hh>
#include <G4Allocator.hh>
#include <G4ThreeVector.hh>

namespace A01 {

class DriftChamberHit : public G4VHit {
public:

      DriftChamberHit();
      DriftChamberHit(G4int z);
      virtual ~DriftChamberHit();
      DriftChamberHit(const DriftChamberHit &right);
      const DriftChamberHit& operator=(const DriftChamberHit &right);
      int operator==(const DriftChamberHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

	  inline float x();
	  inline float y();

      virtual void Draw();
      virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
      virtual std::vector<G4AttValue>* CreateAttValues() const;
      virtual void Print();

  private:
      G4int layerID;
      G4double time;
      G4ThreeVector localPos;
      G4ThreeVector worldPos;

  public:
      inline void SetLayerID(G4int z) { layerID = z; }
      inline G4int GetLayerID() const { return layerID; }
      inline void SetTime(G4double t) { time = t; }
      inline G4double GetTime() const { return time; }
      inline void SetLocalPos(G4ThreeVector xyz) { localPos = xyz; }
      inline G4ThreeVector GetLocalPos() const { return localPos; }
      inline void SetWorldPos(G4ThreeVector xyz) { worldPos = xyz; }
      inline G4ThreeVector GetWorldPos() const { return worldPos; }
};

typedef G4THitsCollection<DriftChamberHit> DriftChamberHitsCollection;

extern G4Allocator<DriftChamberHit> DriftChamberHitAllocator;

inline void* DriftChamberHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)DriftChamberHitAllocator.MallocSingle();
  return aHit;
}

inline void DriftChamberHit::operator delete(void* aHit)
{
  DriftChamberHitAllocator.FreeSingle((DriftChamberHit*) aHit);
}

}

#endif


