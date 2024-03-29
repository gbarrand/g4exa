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

#include "../A01/DriftChamberHit.hh"

#include <G4VVisManager.hh>
#include <G4Circle.hh>
#include <G4VisAttributes.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>
#include <G4UIcommand.hh>
#include <G4AttDefStore.hh>
#include <G4UnitsTable.hh>

G4Allocator<A01::DriftChamberHit> A01::DriftChamberHitAllocator;

A01::DriftChamberHit::DriftChamberHit() {
  layerID = -1;
  time = 0.;
}

A01::DriftChamberHit::DriftChamberHit(G4int z) {
  layerID = z;
  time = 0.;
}

A01::DriftChamberHit::~DriftChamberHit() {}

A01::DriftChamberHit::DriftChamberHit(const A01::DriftChamberHit &right): G4VHit() {
  layerID = right.layerID;
  worldPos = right.worldPos;
  localPos = right.localPos;
  time = right.time;
}

const A01::DriftChamberHit& A01::DriftChamberHit::operator=(const A01::DriftChamberHit &right)
{
  layerID = right.layerID;
  worldPos = right.worldPos;
  localPos = right.localPos;
  time = right.time;
  return *this;
}

int A01::DriftChamberHit::operator==(const A01::DriftChamberHit &/*right*/) const
{
  return 0;
}

void A01::DriftChamberHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(worldPos);
    circle.SetScreenSize(2);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,1.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}

const std::map<G4String,G4AttDef>* A01::DriftChamberHit::GetAttDefs() const
{
  G4bool isNew;
  std::map<G4String,G4AttDef>* store
    = G4AttDefStore::GetInstance("A01::DriftChamberHit",isNew);
  if (isNew) {
    G4String HitType("HitType");
    (*store)[HitType] = G4AttDef(HitType,"Hit Type","Physics","","G4String");

    G4String ID("ID");
    (*store)[ID] = G4AttDef(ID,"ID","Physics","","G4int");

    G4String Time("Time");
    (*store)[Time] = G4AttDef(Time,"Time","Physics","G4BestUnit","G4double");

    G4String Pos("Pos");
    (*store)[Pos] = G4AttDef(Pos, "Position",
		      "Physics","G4BestUnit","G4ThreeVector");
  }
  return store;
}

std::vector<G4AttValue>* A01::DriftChamberHit::CreateAttValues() const
{
  std::vector<G4AttValue>* values = new std::vector<G4AttValue>;

  values->push_back(G4AttValue("HitType","DriftChamberHit",""));

  values->push_back
    (G4AttValue("ID",G4UIcommand::ConvertToString(layerID),""));

  values->push_back
    (G4AttValue("Time",G4BestUnit(time,"Time"),""));

  values->push_back
    (G4AttValue("Pos",G4BestUnit(worldPos,"Length"),""));

  return values;
}

void A01::DriftChamberHit::Print()
{
  G4cout << "  Layer[" << layerID << "] : time " << time/CLHEP::ns
         << " (nsec) --- local (x,y) " << localPos.x()
         << ", " << localPos.y() << G4endl;
}


