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
// 13-Oct-2003 Add Comment for Ionisation of Generic Ion by T. Koi
// 05-Jan-2004 Change G. Ion Ionisation from G4hIonisation
//                                      to G4ionIonisation T. Koi

#include "../A01/IonPhysics.hh"

#include <G4Version.hh>
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031
#else
#include <G4LElastic.hh>
#include <G4LEDeuteronInelastic.hh>
#include <G4LETritonInelastic.hh>
#include <G4LEAlphaInelastic.hh>
#endif

#include <G4hIonisation.hh>
#include <G4HadronElasticProcess.hh>
#include <G4hMultipleScattering.hh>
#include <G4AlphaInelasticProcess.hh>
#include <G4TritonInelasticProcess.hh>
#include <G4DeuteronInelasticProcess.hh>
#include <G4ionIonisation.hh>
#include <G4ProcessManager.hh>

A01::IonPhysics::IonPhysics(const G4String& name):G4VPhysicsConstructor(name) {}

A01::IonPhysics::~IonPhysics() {}

void A01::IonPhysics::ConstructProcess()
{
   G4ProcessManager * pManager = 0;


   // Generic Ion
   pManager = G4GenericIon::GenericIon()->GetProcessManager();

   // add process
   G4VProcess* thegionMultipleScattering = new G4hMultipleScattering();
   //
   // G4hIonization may be not able to use for Geanric Ion in future
   // Please take care using this physics list after v5.2.p02
   // G4VProcess* thegionIonisation        = new G4hIonisation();
   //
   // From V6.0 hIonisation does not work for GenericIon
   G4VProcess* thegionIonisation        = new G4ionIonisation();
   //
   pManager->AddProcess(thegionIonisation);
   pManager->AddProcess(thegionMultipleScattering);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thegionMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thegionIonisation,        idxAlongStep,2);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thegionMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thegionIonisation,        idxPostStep,2);


   // Deuteron
   pManager = G4Deuteron::Deuteron()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thedueElasticProcess
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thedueElasticModel = new G4LElastic();
   thedueElasticProcess->RegisterMe(thedueElasticModel);
   pManager->AddDiscreteProcess(thedueElasticProcess);
#endif

   G4DeuteronInelasticProcess* theDeuteronInelasticProcess
                         = new G4DeuteronInelasticProcess();

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEDeuteronInelastic* theDeuteronLEPModel = new G4LEDeuteronInelastic();
   theDeuteronInelasticProcess->RegisterMe(theDeuteronLEPModel);
   pManager->AddDiscreteProcess(theDeuteronInelasticProcess);
#endif

   G4VProcess* thedueMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thedueIonisation        = new G4hIonisation();
   //
   pManager->AddProcess(thedueIonisation);
   pManager->AddProcess(thedueMultipleScattering);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thedueMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thedueIonisation,        idxAlongStep,2);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thedueMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thedueIonisation,        idxPostStep,2);


   // Triton
   pManager = G4Triton::Triton()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thetriElasticProcess
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thetriElasticModel = new G4LElastic();
   thetriElasticProcess->RegisterMe(thetriElasticModel);
   pManager->AddDiscreteProcess(thetriElasticProcess);
#endif

   G4TritonInelasticProcess* theTritonInelasticProcess
                         = new G4TritonInelasticProcess();

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LETritonInelastic* theTritonLEPModel = new G4LETritonInelastic();
   theTritonInelasticProcess->RegisterMe(theTritonLEPModel);
   pManager->AddDiscreteProcess(theTritonInelasticProcess);
#endif

   G4VProcess* thetriMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thetriIonisation        = new G4hIonisation();
   //
   pManager->AddProcess(thetriIonisation);
   pManager->AddProcess(thetriMultipleScattering);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thetriMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thetriIonisation,        idxAlongStep,2);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thetriMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thetriIonisation,        idxPostStep,2);


   // Alpha
   pManager = G4Alpha::Alpha()->GetProcessManager();

   // add processes
   G4HadronElasticProcess* thealElasticProcess
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thealElasticModel = new G4LElastic();
   thealElasticProcess->RegisterMe(thealElasticModel);
   pManager->AddDiscreteProcess(thealElasticProcess);
#endif

   G4AlphaInelasticProcess* theAlphaInelasticProcess
                         = new G4AlphaInelasticProcess();

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEAlphaInelastic* theAlphaLEPModel = new G4LEAlphaInelastic();
   theAlphaInelasticProcess->RegisterMe(theAlphaLEPModel);
   pManager->AddDiscreteProcess(theAlphaInelasticProcess);
#endif

   G4VProcess* thealpMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thealpIonisation        = new G4hIonisation();
   //
   pManager->AddProcess(thealpIonisation);
   pManager->AddProcess(thealpMultipleScattering);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thealpMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thealpIonisation,        idxAlongStep,2);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thealpMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thealpIonisation,        idxPostStep,2);


   // He3
   pManager = G4He3::He3()->GetProcessManager();

   // add processes
   G4HadronElasticProcess* thehe3ElasticProcess
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thehe3ElasticModel = new G4LElastic();
   thehe3ElasticProcess->RegisterMe(thehe3ElasticModel);
   pManager->AddDiscreteProcess(thehe3ElasticProcess);
#endif

   G4VProcess* thehe3MultipleScattering = new G4hMultipleScattering();
   G4VProcess* thehe3Ionisation        = new G4hIonisation();
   //
   pManager->AddProcess(thehe3Ionisation);
   pManager->AddProcess(thehe3MultipleScattering);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thehe3MultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thehe3Ionisation,        idxAlongStep,2);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thehe3MultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thehe3Ionisation,        idxPostStep,2);

}



