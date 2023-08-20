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
//
/// \file exampleB1.cc
/// \brief Main program of the B1 example

#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"

#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"

#include "G4UImanager.hh"
#include "QBBC.hh"

#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "Randomize.hh"
#include "B1RunAction.hh"

#include "G4TScoreNtupleWriter.hh"
#include "G4GenericAnalysisManager.hh"

#include "time.h"
#include "G4Timer.hh"
#include "QGSP_INCLXX.hh"

#include "QGSP_BIC_AllHP.hh"

#include "G4GenericBiasingPhysics.hh"
// #include "QBBC_HP.hh"

using G4AnalysisManager = G4GenericAnalysisManager;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{
// //Instantiate the G4Timer object, to monitor the CPU time spent for the entire execution
// G4Timer* theTimer = new G4Timer();
// theTimer->Start();
  // Detect interactive mode (if no arguments) and define UI session
  //
  // G4Random::setTheEngine(new CLHEP::RanecuEngine);
  //  G4double seed;
  //     if(argc > 2) {seed = atol(argv[2]);}
  //          else{seed = time(NULL);}
  //  G4Random::setTheSeed(seed);
  // #ifdef G4MULTITHREADED
  // G4MTRunManager* runManager = new G4MTRunManager;
  // runManager->SetNumberOfThreads(2); // Is equal to 2 by default
  // #else
  // G4RunManager* pRunManager = new G4RunManager;
  // #endif



  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

  // Optionally: choose a different Random engine...
  // G4Random::setTheEngine(new CLHEP::MTwistEngine);
  
  // Construct the default run manager
  //
   auto* runManager =
     G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

 // Set mandatory initialization classes
  //
 // Detector construction
 B1DetectorConstruction* det = new B1DetectorConstruction();
runManager->SetUserInitialization(det);

// Physics list
G4VModularPhysicsList* physicsList = new QGSP_BIC_AllHP;
 G4GenericBiasingPhysics* biasingPhysics = new G4GenericBiasingPhysics();
   
     
      //biasingPhysics->PhysicsBias("deuteron", {"dInelastic"}); 
      //biasingPhysics->PhysicsBias("neutron", {"neutronInelastic"});
      //physicsList->RegisterPhysics(biasingPhysics); 
      biasingPhysics->Bias("deuteron");
      physicsList->RegisterPhysics(biasingPhysics);
      //G4cout << "      ********************************************************* " << G4endl;
      //G4cout << "      ********** processes are wrapped for biasing ************ " << G4endl;
      //G4cout << "      ********************************************************* " << G4endl;
     
  runManager->SetUserInitialization(physicsList);
  physicsList->SetVerboseLevel(1);
  runManager->SetUserInitialization(physicsList);

  // User action initialization
  runManager->SetUserInitialization(new B1ActionInitialization());

  // Initialize visualization
  //
  G4VisManager* visManager = new G4VisExecutive;
  // G4VisExecutive can take a verbosity argument - see /vis/verbose guidance.
  // G4VisManager* visManager = new G4VisExecutive("Quiet");
  visManager->Initialize();

  // Get the pointer to the User Interface manager
  G4UImanager* UImanager = G4UImanager::GetUIpointer();



// G4TScoreNtupleWriter<G4AnalysisManager> scoreNtupleWriter;
  // Process macro or start UI session
  //
  if ( ! ui ) { 
    // batch mode
    G4String command = "/control/execute ";
    G4String fileName = argv[1];
    UImanager->ApplyCommand(command+fileName);
  }
  else { 
    // interactive mode
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
  }

  // Job termination
  // Free the store: user actions, physics_list and detector_description are
  // owned and deleted by the run manager, so they should not be deleted 
  // in the main() program !
  // delete run;
  delete visManager;
  delete runManager;

  // theTimer->Stop();
  // G4cout<<"The simulation took: "<<theTimer->GetRealElapsed()<<"s to finish (real time)"<<G4endl;

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo.....
