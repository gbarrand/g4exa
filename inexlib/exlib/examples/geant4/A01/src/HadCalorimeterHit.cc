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

#include "../A01/HadCalorimeterHit.hh"

#include <G4AttDef.hh>
#include <G4AttValue.hh>
#include <G4UIcommand.hh>
#include <G4AttDefStore.hh>
#include <G4UnitsTable.hh>
#include <G4Box.hh>
#include <G4VVisManager.hh>
#include <G4Colour.hh>
#include <G4VisAttributes.hh>

G4Allocator<A01::HadCalorimeterHit> A01::HadCalorimeterHitAllocator;

A01::HadCalorimeterHit::HadCalorimeterHit()
{
  columnID = -1;
  rowID = -1;
  edep = 0.;
}

A01::HadCalorimeterHit::HadCalorimeterHit(G4int iCol,G4int iRow)
{
  columnID = iCol;
  rowID = iRow;
  edep = 0.;
}

A01::HadCalorimeterHit::~HadCalorimeterHit() {}

A01::HadCalorimeterHit::HadCalorimeterHit(const A01::HadCalorimeterHit &right)
    : G4VHit() {
  columnID = right.columnID;
  rowID = right.rowID;
  edep = right.edep;
  pos = right.pos;
  rot = right.rot;
}

const A01::HadCalorimeterHit& A01::HadCalorimeterHit::operator=(const A01::HadCalorimeterHit &right)
{
  columnID = right.columnID;
  rowID = right.rowID;
  edep = right.edep;
  pos = right.pos;
  rot = right.rot;
  return *this;
}

int A01::HadCalorimeterHit::operator==(const A01::HadCalorimeterHit &right) const
{
  return (columnID==right.columnID&&rowID==right.rowID);
}

void A01::HadCalorimeterHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager&&(edep>0.))
  {
    // Draw a calorimeter cell with depth propotional to the energy deposition
    G4Transform3D trans(rot.inverse(),pos);
    G4VisAttributes attribs;
    G4Colour colour(1.,0.,0.);
    attribs.SetColour(colour);
    attribs.SetForceSolid(true);
    G4Box box("dummy",15.*CLHEP::cm,15.*CLHEP::cm,1.*CLHEP::m*edep/(0.1*CLHEP::GeV));
    pVVisManager->Draw(box,attribs,trans);
  }
}

const std::map<G4String,G4AttDef>* A01::HadCalorimeterHit::GetAttDefs() const
{
  G4bool isNew;
  std::map<G4String,G4AttDef>* store
    = G4AttDefStore::GetInstance("A01::HadCalorimeterHit",isNew);
  if (isNew) {
    G4String HitType("HitType");
    (*store)[HitType] = G4AttDef(HitType,"Hit Type","Physics","","G4String");

    G4String Column("Column");
    (*store)[Column] = G4AttDef(Column,"Column ID","Physics","","G4int");

    G4String Row("Row");
    (*store)[Row] = G4AttDef(Row,"Row ID","Physics","","G4int");

    G4String Energy("Energy");
    (*store)[Energy] = G4AttDef(Energy,"Energy Deposited","Physics","G4BestUnit","G4double");

    G4String Pos("Pos");
    (*store)[Pos] = G4AttDef(Pos, "Position",
		      "Physics","G4BestUnit","G4ThreeVector");
  }
  return store;
}

std::vector<G4AttValue>* A01::HadCalorimeterHit::CreateAttValues() const
{
  std::vector<G4AttValue>* values = new std::vector<G4AttValue>;

  values->push_back(G4AttValue("HitType","HadCalorimeterHit",""));

  values->push_back
    (G4AttValue("Column",G4UIcommand::ConvertToString(columnID),""));

  values->push_back
    (G4AttValue("Row",G4UIcommand::ConvertToString(rowID),""));

  values->push_back
    (G4AttValue("Energy",G4BestUnit(edep,"Energy"),""));

  values->push_back
    (G4AttValue("Pos",G4BestUnit(pos,"Length"),""));

  return values;
}

void A01::HadCalorimeterHit::Print()
{
  G4cout << "  Cell[" << rowID << ", " << columnID << "] " << edep/CLHEP::MeV << " (MeV) " << pos << G4endl;
}


