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

#include "../A01/EmCalorimeterHit.hh"

#include <G4VisAttributes.hh>
#include <G4LogicalVolume.hh>
#include <G4UnitsTable.hh>
#include <G4AttDef.hh>
#include <G4AttValue.hh>
#include <G4UIcommand.hh>
#include <G4AttDefStore.hh>
#include <G4VVisManager.hh>

G4Allocator<A01::EmCalorimeterHit> A01::EmCalorimeterHitAllocator;

A01::EmCalorimeterHit::EmCalorimeterHit()
{
  cellID = -1;
  edep = 0.;
  pLogV = 0;
}

A01::EmCalorimeterHit::EmCalorimeterHit(G4int z)
{
  cellID = z;
  edep = 0.;
  pLogV = 0;
}

A01::EmCalorimeterHit::~EmCalorimeterHit()
{;}

A01::EmCalorimeterHit::EmCalorimeterHit(const A01::EmCalorimeterHit &right)
    : G4VHit() {
  cellID = right.cellID;
  edep = right.edep;
  pos = right.pos;
  rot = right.rot;
  pLogV = right.pLogV;
}

const A01::EmCalorimeterHit& A01::EmCalorimeterHit::operator=(const A01::EmCalorimeterHit &right)
{
  cellID = right.cellID;
  edep = right.edep;
  pos = right.pos;
  rot = right.rot;
  pLogV = right.pLogV;
  return *this;
}

int A01::EmCalorimeterHit::operator==(const A01::EmCalorimeterHit &right) const
{
  return (cellID==right.cellID);
}

void A01::EmCalorimeterHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager&&(edep>0.))
  {
    // Draw a calorimeter cell with a color corresponding to its energy deposit
    G4Transform3D trans(rot.inverse(),pos);
    G4VisAttributes attribs;
    const G4VisAttributes* pVA = pLogV->GetVisAttributes();
    if(pVA) attribs = *pVA;
    G4double rcol = edep/(0.7*CLHEP::GeV);
    if(rcol>1.) rcol = 1.;
    if(rcol<0.4) rcol = 0.4;
    G4Colour colour(rcol,0.,0.);
    attribs.SetColour(colour);
    attribs.SetForceSolid(true);
    pVVisManager->Draw(*pLogV,attribs,trans);
  }
}

const std::map<G4String,G4AttDef>* A01::EmCalorimeterHit::GetAttDefs() const
{
  G4bool isNew;
  std::map<G4String,G4AttDef>* store
    = G4AttDefStore::GetInstance("A01::EmCalorimeterHit",isNew);
  if (isNew) {
    G4String HitType("HitType");
    (*store)[HitType] = G4AttDef(HitType,"Hit Type","Physics","","G4String");

    G4String ID("ID");
    (*store)[ID] = G4AttDef(ID,"ID","Physics","","G4int");

    G4String Energy("Energy");
    (*store)[Energy] = G4AttDef(Energy,"Energy Deposited","Physics","G4BestUnit","G4double");

    G4String Pos("Pos");
    (*store)[Pos] = G4AttDef(Pos, "Position",
		      "Physics","G4BestUnit","G4ThreeVector");

    G4String LVol("LVol");
    (*store)[LVol] = G4AttDef(LVol,"Logical Volume","Physics","","G4String");
  }
  return store;
}

std::vector<G4AttValue>* A01::EmCalorimeterHit::CreateAttValues() const
{
  std::vector<G4AttValue>* values = new std::vector<G4AttValue>;

  values->push_back(G4AttValue("HitType","EmCalorimeterHit",""));

  values->push_back
    (G4AttValue("ID",G4UIcommand::ConvertToString(cellID),""));

  values->push_back
    (G4AttValue("Energy",G4BestUnit(edep,"Energy"),""));

  values->push_back
    (G4AttValue("Pos",G4BestUnit(pos,"Length"),""));

  if (pLogV)
    values->push_back
      (G4AttValue("LVol",pLogV->GetName(),""));
  else
    values->push_back
      (G4AttValue("LVol"," ",""));

   return values;
}

void A01::EmCalorimeterHit::Print()
{
  G4cout << "  Cell[" << cellID << "] " << edep/CLHEP::MeV << " (MeV)" << G4endl;
}


