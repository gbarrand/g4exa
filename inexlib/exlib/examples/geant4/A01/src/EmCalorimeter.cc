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
#include "../A01/EmCalorimeter.hh"
#include "../A01/EmCalorimeterHit.hh"

#include <G4SDManager.hh>

A01::EmCalorimeter::EmCalorimeter(G4String name)
:G4VSensitiveDetector(name)
{
  G4String HCname;
  collectionName.insert(HCname="EMcalorimeterColl");
  HCID = -1;
}

A01::EmCalorimeter::~EmCalorimeter(){;}

void A01::EmCalorimeter::Initialize(G4HCofThisEvent*HCE)
{
  hitsCollection = new A01::EmCalorimeterHitsCollection
                   (SensitiveDetectorName,collectionName[0]);
  if(HCID<0)
  { HCID = G4SDManager::GetSDMpointer()->GetCollectionID(hitsCollection); }
  HCE->AddHitsCollection(HCID,hitsCollection);

  // fill calorimeter hits with zero energy deposition
  for(int i=0;i<80;i++)
  {
    A01::EmCalorimeterHit* aHit = new A01::EmCalorimeterHit(i);
    hitsCollection->insert( aHit );
  }
}

G4bool A01::EmCalorimeter::ProcessHits(G4Step*aStep,G4TouchableHistory* /*ROhist*/)
{
  G4double edep = aStep->GetTotalEnergyDeposit();
  if(edep==0.) return true;

  G4StepPoint* preStepPoint = aStep->GetPreStepPoint();
  G4TouchableHistory* theTouchable
    = (G4TouchableHistory*)(preStepPoint->GetTouchable());
  G4VPhysicalVolume* thePhysical = theTouchable->GetVolume();
  G4int copyNo = thePhysical->GetCopyNo();

  A01::EmCalorimeterHit* aHit = (*hitsCollection)[copyNo];
  // check if it is first touch
  if(!(aHit->GetLogV()))
  {
    // fill volume information
    aHit->SetLogV(thePhysical->GetLogicalVolume());
    G4AffineTransform aTrans = theTouchable->GetHistory()->GetTopTransform();
    aTrans.Invert();
    aHit->SetRot(aTrans.NetRotation());
    aHit->SetPos(aTrans.NetTranslation());
  }
  // add energy deposition
  aHit->AddEdep(edep);

  return true;
}

void A01::EmCalorimeter::EndOfEvent(G4HCofThisEvent* /*HCE*/)
{}

