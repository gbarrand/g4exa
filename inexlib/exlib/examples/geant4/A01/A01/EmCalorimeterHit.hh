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

#ifndef A01_EmCalorimeterHit_hh
#define A01_EmCalorimeterHit_hh

#include <G4VHit.hh>

#include <G4ThreeVector.hh>
#include <G4RotationMatrix.hh>

#include <G4THitsCollection.hh>

class G4LogicalVolume;

namespace A01 {
class EmCalorimeterHit : public G4VHit
{
  public:

      EmCalorimeterHit();
      EmCalorimeterHit(G4int z);
      virtual ~EmCalorimeterHit();
      EmCalorimeterHit(const EmCalorimeterHit &right);
      const EmCalorimeterHit& operator=(const EmCalorimeterHit &right);
      int operator==(const EmCalorimeterHit &right) const;

      inline void *operator new(size_t);
      inline void operator delete(void *aHit);

      virtual void Draw();
      virtual const std::map<G4String,G4AttDef>* GetAttDefs() const;
      virtual std::vector<G4AttValue>* CreateAttValues() const;
      virtual void Print();

  private:
      G4int cellID;
      G4double edep;
      G4ThreeVector pos;
      G4RotationMatrix rot;
      const G4LogicalVolume* pLogV;

  public:
      inline void SetCellID(G4int z) { cellID = z; }
      inline G4int GetCellID() const { return cellID; }
      inline void SetEdep(G4double de) { edep = de; }
      inline void AddEdep(G4double de) { edep += de; }
      inline G4double GetEdep() const { return edep; }
      inline void SetPos(G4ThreeVector xyz) { pos = xyz; }
      inline G4ThreeVector GetPos() const { return pos; }
      inline void SetRot(G4RotationMatrix rmat) { rot = rmat; }
      inline G4RotationMatrix GetRot() const { return rot; }
      inline void SetLogV(G4LogicalVolume* val) { pLogV = val; }
      inline const G4LogicalVolume* GetLogV() const { return pLogV; }
};

typedef G4THitsCollection<EmCalorimeterHit> EmCalorimeterHitsCollection;

extern G4Allocator<EmCalorimeterHit> EmCalorimeterHitAllocator;

inline void* EmCalorimeterHit::operator new(size_t)
{
  void* aHit;
  aHit = (void*)EmCalorimeterHitAllocator.MallocSingle();
  return aHit;
}

inline void EmCalorimeterHit::operator delete(void* aHit)
{
  EmCalorimeterHitAllocator.FreeSingle((EmCalorimeterHit*) aHit);
}

}

#endif


