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

#ifndef A01_Hodoscope_hh
#define A01_Hodoscope_hh

#include "HodoscopeHit.hh"

#include <G4VSensitiveDetector.hh>
#include <G4SDManager.hh>

namespace A01 {

class Hodoscope : public G4VSensitiveDetector {
public:
  Hodoscope(G4String name):G4VSensitiveDetector(name) {
    G4String HCname;
    collectionName.insert(HCname="hodoscopeColl");
    HCID = -1;
  }
  virtual ~Hodoscope() {}
public:
  virtual void Initialize(G4HCofThisEvent*HCE) {
    hitsCollection = new A01::HodoscopeHitsCollection(SensitiveDetectorName,collectionName[0]);
    if(HCID<0) { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection); }
    HCE->AddHitsCollection(HCID,hitsCollection);
  }

  virtual G4bool ProcessHits(G4Step* aStep,G4TouchableHistory* ROhist) {
    G4double edep = aStep->GetTotalEnergyDeposit();
    if(edep==0.) return true;

    G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
    G4TouchableHistory* theTouchable = (G4TouchableHistory*)(preStepPoint->GetTouchable());
    G4int copyNo = theTouchable->GetVolume()->GetCopyNo();
    G4double hitTime = preStepPoint->GetGlobalTime();

    // check if this finger already has a hit
    G4int ix = -1;
    for(G4int i=0;i<hitsCollection->entries();i++) {
      if((*hitsCollection)[i]->GetID()==copyNo) {
        ix = i;
        break;
      }
    }
    // if it has, then take the earlier time
    if(ix>=0) {
      if((*hitsCollection)[ix]->GetTime()>hitTime)
      { (*hitsCollection)[ix]->SetTime(hitTime); }
    } else {
      // if not, create a new hit and set it to the collection
      A01::HodoscopeHit* aHit = new A01::HodoscopeHit(copyNo,hitTime);
      G4VPhysicalVolume* thePhysical = theTouchable->GetVolume();
      aHit->SetLogV(thePhysical->GetLogicalVolume());
      G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
      aTrans.Invert();
      aHit->SetRot(aTrans.NetRotation());
      aHit->SetPos(aTrans.NetTranslation());
      hitsCollection->insert( aHit );
    }

    return true;
  }

  virtual void EndOfEvent(G4HCofThisEvent* /*HCE*/) {}
private:
  HodoscopeHitsCollection* hitsCollection;
  G4int HCID;
};

}

#endif

