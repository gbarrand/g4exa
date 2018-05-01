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
// $Id: A01HadronPhysics.cc,v 1.1 2012/06/07 18:28:29 barrand Exp $
// --------------------------------------------------------------
//
// 09-Oct-2003 Hadron Physics List with Parameterization Model by T. Koi
// 12-Oct-2003 Bug Fixed (KaonMinus) by T. Koi

#include "A01HadronPhysics.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>   

#include "G4Version.hh"

A01HadronPhysics::A01HadronPhysics(const G4String& name)
                   :  G4VPhysicsConstructor(name)
{
}

A01HadronPhysics::~A01HadronPhysics()
{
}

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4ProcessManager.hh"

void A01HadronPhysics::ConstructProcess()
{
   G4ProcessManager * pManager = 0;

   // Pi+ Physics
   pManager = G4PionPlus::PionPlus()->GetProcessManager();

   // add processes
   G4HadronElasticProcess* theppElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theppElasticModel = new G4LElastic();
   theppElasticProcess->RegisterMe(theppElasticModel);
   pManager->AddDiscreteProcess(theppElasticProcess);
#endif 
   G4PionPlusInelasticProcess* thePionPlusInelasticProcess 
                         = new G4PionPlusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEPionPlusInelastic* thePionPlusLEPModel = new G4LEPionPlusInelastic();
   G4HEPionPlusInelastic* thePionPlusHEPModel = new G4HEPionPlusInelastic();
   thePionPlusInelasticProcess->RegisterMe(thePionPlusLEPModel);
   thePionPlusInelasticProcess->RegisterMe(thePionPlusHEPModel);
   pManager->AddDiscreteProcess(thePionPlusInelasticProcess);
#endif
   G4VProcess* theppMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theppIonisation        = new G4hIonisation();
   // 
   pManager->AddProcess(theppIonisation);
   pManager->AddProcess(theppMultipleScattering);
   // 
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theppMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theppIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theppMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theppIonisation,        idxPostStep,2);


   // Pi- Physics
   pManager = G4PionMinus::PionMinus()->GetProcessManager();

   G4HadronElasticProcess* thepmElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thepmElasticModel = new G4LElastic();
   thepmElasticProcess->RegisterMe(thepmElasticModel);
   pManager->AddDiscreteProcess(thepmElasticProcess);
#endif
   G4PionMinusInelasticProcess* thePionMinusInelasticProcess 
                         = new G4PionMinusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEPionMinusInelastic* thePionMinusLEPModel = new G4LEPionMinusInelastic();
   G4HEPionMinusInelastic* thePionMinusHEPModel = new G4HEPionMinusInelastic();
   thePionMinusInelasticProcess->RegisterMe(thePionMinusLEPModel);
   thePionMinusInelasticProcess->RegisterMe(thePionMinusHEPModel);
   pManager->AddDiscreteProcess(thePionMinusInelasticProcess);
#endif
   G4VProcess* thepmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thepmIonisation        = new G4hIonisation();
   // 
   // add processes
   pManager->AddProcess(thepmIonisation);
   pManager->AddProcess(thepmMultipleScattering);
   // 
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thepmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thepmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thepmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thepmIonisation,        idxPostStep,2);


   // K+ Physics
   pManager = G4KaonPlus::KaonPlus()->GetProcessManager();

   G4HadronElasticProcess* thekpElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thekpElasticModel = new G4LElastic();
   thekpElasticProcess->RegisterMe(thekpElasticModel);
   pManager->AddDiscreteProcess(thekpElasticProcess);
#endif
   G4KaonPlusInelasticProcess* theKaonPlusInelasticProcess 
                         = new G4KaonPlusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEKaonPlusInelastic* theKaonPlusLEPModel = new G4LEKaonPlusInelastic();
   G4HEKaonPlusInelastic* theKaonPlusHEPModel = new G4HEKaonPlusInelastic();
   theKaonPlusInelasticProcess->RegisterMe(theKaonPlusLEPModel);
   theKaonPlusInelasticProcess->RegisterMe(theKaonPlusHEPModel);
   pManager->AddDiscreteProcess(theKaonPlusInelasticProcess);
#endif
   G4VProcess* thekpMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thekpIonisation        = new G4hIonisation();
   // 
   // add processes
   pManager->AddProcess(thekpIonisation);
   pManager->AddProcess(thekpMultipleScattering);
   // 
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thekpMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thekpIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thekpMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thekpIonisation,        idxPostStep,2);


   // K- Physics
   pManager = G4KaonMinus::KaonMinus()->GetProcessManager();

   // add processes
   G4HadronElasticProcess* thekmElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thekmElasticModel = new G4LElastic();
   thekmElasticProcess->RegisterMe(thekmElasticModel);
   pManager->AddDiscreteProcess(thekmElasticProcess);
#endif
   G4KaonMinusInelasticProcess* theKaonMinusInelasticProcess 
                         = new G4KaonMinusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEKaonMinusInelastic* theKaonMinusLEPModel = new G4LEKaonMinusInelastic();
   G4HEKaonMinusInelastic* theKaonMinusHEPModel = new G4HEKaonMinusInelastic();
   theKaonMinusInelasticProcess->RegisterMe(theKaonMinusLEPModel);
   theKaonMinusInelasticProcess->RegisterMe(theKaonMinusHEPModel);
   pManager->AddDiscreteProcess(theKaonMinusInelasticProcess);
#endif
   G4VProcess* thekmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thekmIonisation        = new G4hIonisation();

   pManager->AddProcess(thekmIonisation);
   pManager->AddProcess(thekmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thekmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thekmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thekmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thekmIonisation,        idxPostStep,2);


   // Kaon0L Phsics
   pManager = G4KaonZeroLong::KaonZeroLong()->GetProcessManager();

   G4HadronElasticProcess* thek0lElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thek0lElasticModel = new G4LElastic();
   thek0lElasticProcess->RegisterMe(thek0lElasticModel);
   pManager->AddDiscreteProcess(thek0lElasticProcess);
#endif
   G4KaonZeroLInelasticProcess* theKaonZeroLInelasticProcess 
                         = new G4KaonZeroLInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEKaonZeroLInelastic* theKaonZeroLLEPModel = new G4LEKaonZeroLInelastic();
   G4HEKaonZeroInelastic* theKaonZerolHEPModel = new G4HEKaonZeroInelastic();
   theKaonZeroLInelasticProcess->RegisterMe(theKaonZeroLLEPModel);
   theKaonZeroLInelasticProcess->RegisterMe(theKaonZerolHEPModel);
   pManager->AddDiscreteProcess(theKaonZeroLInelasticProcess);
#endif

   // Kaon0S Phsics
   pManager = G4KaonZeroShort::KaonZeroShort()->GetProcessManager();

   G4HadronElasticProcess* thek0sElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thek0sElasticModel = new G4LElastic();
   thek0sElasticProcess->RegisterMe(thek0sElasticModel);
   pManager->AddDiscreteProcess(thek0sElasticProcess);
#endif
   
   G4KaonZeroSInelasticProcess* theKaonZeroSInelasticProcess 
                         = new G4KaonZeroSInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEKaonZeroSInelastic* theKaonZeroSLEPModel = new G4LEKaonZeroSInelastic();
   G4HEKaonZeroInelastic* theKaonZerosHEPModel = new G4HEKaonZeroInelastic();
   theKaonZeroSInelasticProcess->RegisterMe(theKaonZeroSLEPModel);
   theKaonZeroSInelasticProcess->RegisterMe(theKaonZerosHEPModel);
   pManager->AddDiscreteProcess(theKaonZeroSInelasticProcess);
#endif

   // Proton Physics
   pManager = G4Proton::Proton()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thepElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thepElasticModel = new G4LElastic();
   thepElasticProcess->RegisterMe(thepElasticModel);
   pManager->AddDiscreteProcess(thepElasticProcess);
#endif
   
   G4ProtonInelasticProcess* theProtonInelasticProcess 
                         = new G4ProtonInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEProtonInelastic* theProtonLEPModel = new G4LEProtonInelastic();
   G4HEProtonInelastic* theProtonHEPModel = new G4HEProtonInelastic();
   theProtonInelasticProcess->RegisterMe(theProtonLEPModel);
   theProtonInelasticProcess->RegisterMe(theProtonHEPModel);
   pManager->AddDiscreteProcess(theProtonInelasticProcess);
#endif
   
   G4VProcess* thepMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thepIonisation        = new G4hIonisation();

   pManager->AddProcess(thepIonisation);
   pManager->AddProcess(thepMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thepMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thepIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thepMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thepIonisation,        idxPostStep,2);


   // anti-proton Physics
   pManager = G4AntiProton::AntiProton()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theapElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theapElasticModel = new G4LElastic();
   theapElasticProcess->RegisterMe(theapElasticModel);
   pManager->AddDiscreteProcess(theapElasticProcess);
#endif

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4AntiProtonInelasticProcess* theAntiProtonInelasticProcess 
                         = new G4AntiProtonInelasticProcess();
   
   G4LEAntiProtonInelastic* theAntiProtonLEPModel = new G4LEAntiProtonInelastic();
   G4HEAntiProtonInelastic* theAntiProtonHEPModel = new G4HEAntiProtonInelastic();
   theAntiProtonInelasticProcess->RegisterMe(theAntiProtonLEPModel);
   theAntiProtonInelasticProcess->RegisterMe(theAntiProtonHEPModel);
   pManager->AddDiscreteProcess(theAntiProtonInelasticProcess);
   
   G4AntiProtonAnnihilationAtRest* theAntiProtonAnnihilation
                            =  new G4AntiProtonAnnihilationAtRest();
   pManager->AddRestProcess(theAntiProtonAnnihilation);
#endif

   G4VProcess* theapMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theapIonisation        = new G4hIonisation();

   pManager->AddProcess(theapIonisation);
   pManager->AddProcess(theapMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theapMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theapIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theapMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theapIonisation,        idxPostStep,2);


   // neutron Physics
   pManager = G4Neutron::Neutron()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thenElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thenElasticModel = new G4LElastic();
   thenElasticProcess->RegisterMe(thenElasticModel);
   pManager->AddDiscreteProcess(thenElasticProcess);
#endif
   G4NeutronInelasticProcess* theNeutronInelasticProcess 
                         = new G4NeutronInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LENeutronInelastic* theNeutronLEPModel = new G4LENeutronInelastic();
   G4HENeutronInelastic* theNeutronHEPModel = new G4HENeutronInelastic();
   theNeutronInelasticProcess->RegisterMe(theNeutronLEPModel);
   theNeutronInelasticProcess->RegisterMe(theNeutronHEPModel);
   pManager->AddDiscreteProcess(theNeutronInelasticProcess);
#endif
   
   G4HadronFissionProcess* thenFission
                         = new G4HadronFissionProcess();
   G4LFission* thenFissionModel = new G4LFission();
   thenFission->RegisterMe(thenFissionModel);
   pManager->AddDiscreteProcess(thenFission);


   G4HadronCaptureProcess* thenCapture
                         = new G4HadronCaptureProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LCapture* thenCaptureModel = new G4LCapture();
   thenCapture->RegisterMe(thenCaptureModel);
   pManager->AddDiscreteProcess(thenCapture);
#endif

   // anti-neutron Physics
   pManager = G4AntiNeutron::AntiNeutron()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theanElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theanElasticModel = new G4LElastic();
   theanElasticProcess->RegisterMe(theanElasticModel);
   pManager->AddDiscreteProcess(theanElasticProcess);
#endif
   
   G4AntiNeutronInelasticProcess* theAntiNeutronInelasticProcess 
                         = new G4AntiNeutronInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEAntiNeutronInelastic* theAntiNeutronLEPModel = new G4LEAntiNeutronInelastic();
   G4HEAntiNeutronInelastic* theAntiNeutronHEPModel = new G4HEAntiNeutronInelastic();
   theAntiNeutronInelasticProcess->RegisterMe(theAntiNeutronLEPModel);
   theAntiNeutronInelasticProcess->RegisterMe(theAntiNeutronHEPModel);
   pManager->AddDiscreteProcess(theAntiNeutronInelasticProcess);
   
   G4AntiNeutronAnnihilationAtRest* theAntiNeutronAnnihilation
                            =  new G4AntiNeutronAnnihilationAtRest();
   pManager->AddRestProcess(theAntiNeutronAnnihilation);
#endif


   // Lambda Physics
   pManager = G4Lambda::Lambda()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thel0ElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thel0ElasticModel = new G4LElastic();
   thel0ElasticProcess->RegisterMe(thel0ElasticModel);
   pManager->AddDiscreteProcess(thel0ElasticProcess);
#endif
   
   G4LambdaInelasticProcess* theLambdaInelasticProcess 
                         = new G4LambdaInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LELambdaInelastic* theLambdaLEPModel = new G4LELambdaInelastic();
   G4HELambdaInelastic* theLambdaHEPModel = new G4HELambdaInelastic();
   theLambdaInelasticProcess->RegisterMe(theLambdaLEPModel);
   theLambdaInelasticProcess->RegisterMe(theLambdaHEPModel);
   pManager->AddDiscreteProcess(theLambdaInelasticProcess);
#endif

   // Anti-Labda Physics
   pManager = G4AntiLambda::AntiLambda()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theal0ElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theal0ElasticModel = new G4LElastic();
   theal0ElasticProcess->RegisterMe(theal0ElasticModel);
   pManager->AddDiscreteProcess(theal0ElasticProcess);
#endif
   
   G4AntiLambdaInelasticProcess* theAntiLambdaInelasticProcess 
                         = new G4AntiLambdaInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEAntiLambdaInelastic* theAntiLambdaLEPModel = new G4LEAntiLambdaInelastic();
   G4HEAntiLambdaInelastic* theAntiLambdaHEPModel = new G4HEAntiLambdaInelastic();
   theAntiLambdaInelasticProcess->RegisterMe(theAntiLambdaLEPModel);
   theAntiLambdaInelasticProcess->RegisterMe(theAntiLambdaHEPModel);
   pManager->AddDiscreteProcess(theAntiLambdaInelasticProcess);
#endif

   // Sigma+ Physics
   pManager = G4SigmaPlus::SigmaPlus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thespElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thespElasticModel = new G4LElastic();
   thespElasticProcess->RegisterMe(thespElasticModel);
   pManager->AddDiscreteProcess(thespElasticProcess);
#endif
   G4SigmaPlusInelasticProcess* theSigmaPlusInelasticProcess 
                         = new G4SigmaPlusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LESigmaPlusInelastic* theSigmaPlusLEPModel = new G4LESigmaPlusInelastic();
   G4HESigmaPlusInelastic* theSigmaPlusHEPModel = new G4HESigmaPlusInelastic();
   theSigmaPlusInelasticProcess->RegisterMe(theSigmaPlusLEPModel);
   theSigmaPlusInelasticProcess->RegisterMe(theSigmaPlusHEPModel);
   pManager->AddDiscreteProcess(theSigmaPlusInelasticProcess);
#endif
   
   G4VProcess* thespMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thespIonisation        = new G4hIonisation();

   pManager->AddProcess(thespIonisation);
   pManager->AddProcess(thespMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thespMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thespIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thespMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thespIonisation,        idxPostStep,2);


   // anti-Sigma+ Physics
   pManager = G4AntiSigmaPlus::AntiSigmaPlus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theaspElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theaspElasticModel = new G4LElastic();
   theaspElasticProcess->RegisterMe(theaspElasticModel);
   pManager->AddDiscreteProcess(theaspElasticProcess);
#endif
   G4AntiSigmaPlusInelasticProcess* theAntiSigmaPlusInelasticProcess 
                         = new G4AntiSigmaPlusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEAntiSigmaPlusInelastic* theAntiSigmaPlusLEPModel = new G4LEAntiSigmaPlusInelastic();
   G4HEAntiSigmaPlusInelastic* theAntiSigmaPlusHEPModel = new G4HEAntiSigmaPlusInelastic();
   theAntiSigmaPlusInelasticProcess->RegisterMe(theAntiSigmaPlusLEPModel);
   theAntiSigmaPlusInelasticProcess->RegisterMe(theAntiSigmaPlusHEPModel);
   pManager->AddDiscreteProcess(theAntiSigmaPlusInelasticProcess);
#endif
   
   G4VProcess* theaspMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theaspIonisation        = new G4hIonisation();

   pManager->AddProcess(theaspIonisation);
   pManager->AddProcess(theaspMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theaspMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theaspIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theaspMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theaspIonisation,        idxPostStep,2);


   // Sigma- Physics
   pManager = G4SigmaMinus::SigmaMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thesmElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thesmElasticModel = new G4LElastic();
   thesmElasticProcess->RegisterMe(thesmElasticModel);
   pManager->AddDiscreteProcess(thesmElasticProcess);
#endif
   
   G4SigmaMinusInelasticProcess* theSigmaMinusInelasticProcess 
                         = new G4SigmaMinusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LESigmaMinusInelastic* theSigmaMinusLEPModel = new G4LESigmaMinusInelastic();
   G4HESigmaMinusInelastic* theSigmaMinusHEPModel = new G4HESigmaMinusInelastic();
   theSigmaMinusInelasticProcess->RegisterMe(theSigmaMinusLEPModel);
   theSigmaMinusInelasticProcess->RegisterMe(theSigmaMinusHEPModel);
   pManager->AddDiscreteProcess(theSigmaMinusInelasticProcess);
#endif

   G4VProcess* thesmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thesmIonisation        = new G4hIonisation();

   pManager->AddProcess(thesmIonisation);
   pManager->AddProcess(thesmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thesmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thesmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thesmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thesmIonisation,        idxPostStep,2);


   // anti-Sigma- Physics
   pManager = G4AntiSigmaMinus::AntiSigmaMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theasmElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theasmElasticModel = new G4LElastic();
   theasmElasticProcess->RegisterMe(theasmElasticModel);
   pManager->AddDiscreteProcess(theasmElasticProcess);
#endif
   
   G4AntiSigmaMinusInelasticProcess* theAntiSigmaMinusInelasticProcess 
                         = new G4AntiSigmaMinusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEAntiSigmaMinusInelastic* theAntiSigmaMinusLEPModel = new G4LEAntiSigmaMinusInelastic();
   G4HEAntiSigmaMinusInelastic* theAntiSigmaMinusHEPModel = new G4HEAntiSigmaMinusInelastic();
   theAntiSigmaMinusInelasticProcess->RegisterMe(theAntiSigmaMinusLEPModel);
   theAntiSigmaMinusInelasticProcess->RegisterMe(theAntiSigmaMinusHEPModel);
   pManager->AddDiscreteProcess(theAntiSigmaMinusInelasticProcess);
#endif
   
   G4VProcess* theasmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theasmIonisation        = new G4hIonisation();

   pManager->AddProcess(theasmIonisation);
   pManager->AddProcess(theasmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theasmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theasmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theasmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theasmIonisation,        idxPostStep,2);


   // Xi0 Physics
   pManager = G4XiZero::XiZero()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thex0ElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thex0ElasticModel = new G4LElastic();
   thex0ElasticProcess->RegisterMe(thex0ElasticModel);
   pManager->AddDiscreteProcess(thex0ElasticProcess);
#endif
   
   G4XiZeroInelasticProcess* theXiZeroInelasticProcess 
                         = new G4XiZeroInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEXiZeroInelastic* theXiZeroLEPModel = new G4LEXiZeroInelastic();
   G4HEXiZeroInelastic* theXiZeroHEPModel = new G4HEXiZeroInelastic();
   theXiZeroInelasticProcess->RegisterMe(theXiZeroLEPModel);
   theXiZeroInelasticProcess->RegisterMe(theXiZeroHEPModel);
   pManager->AddDiscreteProcess(theXiZeroInelasticProcess);
#endif

   // Anti-Xi0 Physics
   pManager = G4AntiXiZero::AntiXiZero()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theax0ElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theax0ElasticModel = new G4LElastic();
   theax0ElasticProcess->RegisterMe(theax0ElasticModel);
   pManager->AddDiscreteProcess(theax0ElasticProcess);
#endif
   
   G4AntiXiZeroInelasticProcess* theAntiXiZeroInelasticProcess 
                         = new G4AntiXiZeroInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEAntiXiZeroInelastic* theAntiXiZeroLEPModel = new G4LEAntiXiZeroInelastic();
   G4HEAntiXiZeroInelastic* theAntiXiZeroHEPModel = new G4HEAntiXiZeroInelastic();
   theAntiXiZeroInelasticProcess->RegisterMe(theAntiXiZeroLEPModel);
   theAntiXiZeroInelasticProcess->RegisterMe(theAntiXiZeroHEPModel);
   pManager->AddDiscreteProcess(theAntiXiZeroInelasticProcess);
#endif

   // Xi- Physics
   pManager = G4XiMinus::XiMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thexmElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* thexmElasticModel = new G4LElastic();
   thexmElasticProcess->RegisterMe(thexmElasticModel);
   pManager->AddDiscreteProcess(thexmElasticProcess);
#endif
   
   G4XiMinusInelasticProcess* theXiMinusInelasticProcess 
                         = new G4XiMinusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEXiMinusInelastic* theXiMinusLEPModel = new G4LEXiMinusInelastic();
   G4HEXiMinusInelastic* theXiMinusHEPModel = new G4HEXiMinusInelastic();
   theXiMinusInelasticProcess->RegisterMe(theXiMinusLEPModel);
   theXiMinusInelasticProcess->RegisterMe(theXiMinusHEPModel);
   pManager->AddDiscreteProcess(theXiMinusInelasticProcess);
#endif
   
   G4VProcess* thexmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thexmIonisation        = new G4hIonisation();

   pManager->AddProcess(thexmIonisation);
   pManager->AddProcess(thexmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thexmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thexmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thexmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thexmIonisation,        idxPostStep,2);


   // anti-Xi- Physics
   pManager = G4AntiXiMinus::AntiXiMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theaxmElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theaxmElasticModel = new G4LElastic();
   theaxmElasticProcess->RegisterMe(theaxmElasticModel);
   pManager->AddDiscreteProcess(theaxmElasticProcess);
#endif
   
   G4AntiXiMinusInelasticProcess* theAntiXiMinusInelasticProcess 
                         = new G4AntiXiMinusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEAntiXiMinusInelastic* theAntiXiMinusLEPModel = new G4LEAntiXiMinusInelastic();
   G4HEAntiXiMinusInelastic* theAntiXiMinusHEPModel = new G4HEAntiXiMinusInelastic();
   theAntiXiMinusInelasticProcess->RegisterMe(theAntiXiMinusLEPModel);
   theAntiXiMinusInelasticProcess->RegisterMe(theAntiXiMinusHEPModel);
   pManager->AddDiscreteProcess(theAntiXiMinusInelasticProcess);
#endif
   
   G4VProcess* theaxmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theaxmIonisation        = new G4hIonisation();

   pManager->AddProcess(theaxmIonisation);
   pManager->AddProcess(theaxmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theaxmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theaxmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theaxmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theaxmIonisation,        idxPostStep,2);


   // Omega- Physics
   pManager = G4OmegaMinus::OmegaMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theomElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theomElasticModel = new G4LElastic();
   theomElasticProcess->RegisterMe(theomElasticModel);
   pManager->AddDiscreteProcess(theomElasticProcess);
#endif
   
   G4OmegaMinusInelasticProcess* theOmegaMinusInelasticProcess 
                         = new G4OmegaMinusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEOmegaMinusInelastic* theOmegaMinusLEPModel = new G4LEOmegaMinusInelastic();
   G4HEOmegaMinusInelastic* theOmegaMinusHEPModel = new G4HEOmegaMinusInelastic();
   theOmegaMinusInelasticProcess->RegisterMe(theOmegaMinusLEPModel);
   theOmegaMinusInelasticProcess->RegisterMe(theOmegaMinusHEPModel);
   pManager->AddDiscreteProcess(theOmegaMinusInelasticProcess);
#endif
   
   G4VProcess* theomMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theomIonisation        = new G4hIonisation();

   pManager->AddProcess(theomIonisation);
   pManager->AddProcess(theomMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theomMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theomIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theomMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theomIonisation,        idxPostStep,2);


   // anti-Omega- Physics
   pManager = G4AntiOmegaMinus::AntiOmegaMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theaomElasticProcess 
                         = new G4HadronElasticProcess();
#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LElastic* theaomElasticModel = new G4LElastic();
   theaomElasticProcess->RegisterMe(theaomElasticModel);
   pManager->AddDiscreteProcess(theaomElasticProcess);
#endif
   
   G4AntiOmegaMinusInelasticProcess* theAntiOmegaMinusInelasticProcess 
                         = new G4AntiOmegaMinusInelasticProcess(); 

#if defined(G4VERSION_NUMBER) && G4VERSION_NUMBER>=1031 //G.Barrand
#else
   G4LEAntiOmegaMinusInelastic* theAntiOmegaMinusLEPModel = new G4LEAntiOmegaMinusInelastic();
   G4HEAntiOmegaMinusInelastic* theAntiOmegaMinusHEPModel = new G4HEAntiOmegaMinusInelastic();
   theAntiOmegaMinusInelasticProcess->RegisterMe(theAntiOmegaMinusLEPModel);
   theAntiOmegaMinusInelasticProcess->RegisterMe(theAntiOmegaMinusHEPModel);
   pManager->AddDiscreteProcess(theAntiOmegaMinusInelasticProcess);
#endif
   
   G4VProcess* theaomMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theaomIonisation        = new G4hIonisation();

   pManager->AddProcess(theaomIonisation);
   pManager->AddProcess(theaomMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theaomMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theaomIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theaomMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theaomIonisation,        idxPostStep,2);

}
