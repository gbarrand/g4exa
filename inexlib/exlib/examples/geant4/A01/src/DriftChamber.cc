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
// --------------------------------------------------------------
//
#include "../A01/DriftChamber.hh"
#include "../A01/DriftChamberHit.hh"

#include <G4SDManager.hh>

A01::DriftChamber::DriftChamber(G4String name):G4VSensitiveDetector(name) {
  G4String HCname;
  collectionName.insert(HCname="driftChamberColl");
  HCID = -1;
}

A01::DriftChamber::~DriftChamber() {}

void A01::DriftChamber::Initialize(G4HCofThisEvent*HCE)
{
  hitsCollection = new A01::DriftChamberHitsCollection
                   (SensitiveDetectorName,collectionName[0]);
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection); }
  HCE->AddHitsCollection(HCID,hitsCollection);
}

G4bool A01::DriftChamber::ProcessHits(G4Step*aStep,G4TouchableHistory* /*ROhist*/)
{
  G4double charge = aStep->GetTrack()->GetDefinition()->GetPDGCharge();
  if(charge==0.) return true;

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume* theMotherPhysical = theTouchable->GetVolume(1); // mother
  G4int copyNo = theMotherPhysical->GetCopyNo();
  G4ThreeVector worldPos = preStepPoint->GetPosition();
  G4ThreeVector localPos
    = theTouchable->GetHistory()->GetTopTransform().TransformPoint(worldPos);

  A01::DriftChamberHit* aHit = new A01::DriftChamberHit(copyNo);
  aHit->SetWorldPos(worldPos);
  aHit->SetLocalPos(localPos);
  aHit->SetTime(preStepPoint->GetGlobalTime());

  hitsCollection->insert(aHit);

  return true;
}

void A01::DriftChamber::EndOfEvent(G4HCofThisEvent* /*HCE*/) {}

