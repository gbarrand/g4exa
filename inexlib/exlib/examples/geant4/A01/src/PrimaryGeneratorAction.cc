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

#include "../A01/PrimaryGeneratorAction.hh"

#include <G4ParticleGun.hh>
#include <G4ParticleTable.hh>
#include <Randomize.hh>

///////////////////////////////////////////////////////////////////////////
/// messenger : ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
#include <G4UImessenger.hh>
#include <G4UIcmdWithADoubleAndUnit.hh>
#include <G4UIcmdWithABool.hh>
namespace A01 {
class PrimaryGeneratorMessenger: public G4UImessenger {
public:
  PrimaryGeneratorMessenger(PrimaryGeneratorAction * mpga):target(mpga) {
    momentumCmd = new G4UIcmdWithADoubleAndUnit("/mydet/momentum",this);
    momentumCmd->SetGuidance("Mean momentum of primaries");
    momentumCmd->SetParameterName("p",true);
    momentumCmd->SetRange("p>=0.");
    momentumCmd->SetDefaultValue(1.);
    momentumCmd->SetDefaultUnit("GeV");

    sigmaMomCmd = new G4UIcmdWithADoubleAndUnit("/mydet/sigmaMomentum",this);
    sigmaMomCmd->SetGuidance("Sigma momentum of primaries");
    sigmaMomCmd->SetParameterName("p",true);
    sigmaMomCmd->SetRange("p>=0.");
    sigmaMomCmd->SetDefaultValue(1.);
    sigmaMomCmd->SetDefaultUnit("GeV");

    sigmaAngCmd = new G4UIcmdWithADoubleAndUnit("/mydet/sigmaAngle",this);
    sigmaAngCmd->SetGuidance("sigma angle divergence of primaries");
    sigmaAngCmd->SetParameterName("t",true);
    sigmaAngCmd->SetRange("t>=0.");
    sigmaAngCmd->SetDefaultValue(1.);
    sigmaAngCmd->SetDefaultUnit("deg");

    randomCmd = new G4UIcmdWithABool("/mydet/randomizePrimary",this);
    randomCmd->SetGuidance("Boolean flag for randomizing primary particle types.");
    randomCmd->SetGuidance("In case this flag is false, you can select the primary particle");
    randomCmd->SetGuidance("  with /gun/particle command.");
    randomCmd->SetParameterName("flg",true);
    randomCmd->SetDefaultValue(true);
  }
  ~PrimaryGeneratorMessenger() {
    delete momentumCmd;
    delete sigmaMomCmd;
    delete sigmaAngCmd;
    delete randomCmd;
  }
public:
  virtual void SetNewValue(G4UIcommand * command,G4String newValues);
  virtual G4String GetCurrentValue(G4UIcommand * command);
private:
  PrimaryGeneratorAction * target;
private: //commands
  G4UIcmdWithADoubleAndUnit*  momentumCmd;
  G4UIcmdWithADoubleAndUnit*  sigmaMomCmd;
  G4UIcmdWithADoubleAndUnit*  sigmaAngCmd;
  G4UIcmdWithABool*           randomCmd;
};
}
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////

A01::PrimaryGeneratorAction::PrimaryGeneratorAction() {
  momentum = 1000.*CLHEP::MeV;
  sigmaMomentum = 50.*CLHEP::MeV;
  sigmaAngle = 2.*CLHEP::deg;
  randomizePrimary = true;

  G4int n_particle = 1;
  particleGun  = new G4ParticleGun(n_particle);

  //create a messenger for this class
  gunMessenger = new A01::PrimaryGeneratorMessenger(this);

  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  positron = particleTable->FindParticle(particleName="e+");
  muon = particleTable->FindParticle(particleName="mu+");
  pion = particleTable->FindParticle(particleName="pi+");
  kaon = particleTable->FindParticle(particleName="kaon+");
  proton = particleTable->FindParticle(particleName="proton");

  // default particle kinematics
  particleGun->SetParticlePosition(G4ThreeVector(0.,0.,-8.*CLHEP::m));
  particleGun->SetParticleDefinition(positron);
}

A01::PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
  delete particleGun;
  delete gunMessenger;
}

void A01::PrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  G4ParticleDefinition* particle;

  if(randomizePrimary)
  {
    /////////////////////////////////////////////G4int i = (int)(5.*G4UniformRand());
    G4int i = (int)(2.*G4UniformRand());
    switch(i)
    {
      case 0:
        particle = positron;
        break;
      case 1:
        particle = muon;
        break;
      case 2:
        particle = pion;
        break;
      case 3:
        particle = kaon;
        break;
      default:
        particle = proton;
        break;
    }
    particleGun->SetParticleDefinition(particle);
  }
  else
  {
    particle = particleGun->GetParticleDefinition();
  }

  G4double pp = momentum + (G4UniformRand()-0.5)*sigmaMomentum;
  G4double mass = particle->GetPDGMass();
  G4double Ekin = std::sqrt(pp*pp+mass*mass)-mass;
  particleGun->SetParticleEnergy(Ekin);

  G4double angle = (G4UniformRand()-0.5)*sigmaAngle;
  particleGun->SetParticleMomentumDirection(G4ThreeVector(std::sin(angle),0.,std::cos(angle)));

  particleGun->GeneratePrimaryVertex(anEvent);
}

///////////////////////////////////////////////////////////////////////////
/// messenger : ///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////
void A01::PrimaryGeneratorMessenger::SetNewValue(G4UIcommand * command,G4String newValue)
{
  if( command==momentumCmd )
  { target->SetMomentum(momentumCmd->GetNewDoubleValue(newValue)); }
  if( command==sigmaMomCmd )
  { target->SetSigmaMomentum(sigmaMomCmd->GetNewDoubleValue(newValue)); }
  if( command==sigmaAngCmd )
  { target->SetSigmaAngle(sigmaAngCmd->GetNewDoubleValue(newValue)); }
  if( command==randomCmd )
  { target->SetRandomize(randomCmd->GetNewBoolValue(newValue)); }
}

G4String A01::PrimaryGeneratorMessenger::GetCurrentValue(G4UIcommand * command)
{
  G4String cv;
  if( command==momentumCmd )
  { cv = momentumCmd->ConvertToString(target->GetMomentum(),"GeV"); }
  if( command==sigmaMomCmd )
  { cv = sigmaMomCmd->ConvertToString(target->GetSigmaMomentum(),"GeV"); }
  if( command==sigmaAngCmd )
  { cv = sigmaAngCmd->ConvertToString(target->GetSigmaAngle(),"deg"); }
  if( command==randomCmd )
  { cv = randomCmd->ConvertToString(target->GetRandomize()); }

  return cv;
}

