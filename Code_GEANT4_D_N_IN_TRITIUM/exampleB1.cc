
#include "B1DetectorConstruction.hh"
#include "B1ActionInitialization.hh"
#include "G4RunManagerFactory.hh"
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "Randomize.hh"
#include "B1RunAction.hh"
#include "G4TScoreNtupleWriter.hh"
#include "G4GenericAnalysisManager.hh"
#include "time.h"
#include "G4Timer.hh"
#include "QGSP_BIC_AllHP.hh"
#include "G4GenericBiasingPhysics.hh"
#include "G4HadronElasticPhysicsHP.hh"
#include "globals.hh"

using G4AnalysisManager = G4GenericAnalysisManager;
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

int main(int argc,char** argv)
{

 G4Timer* theTimer = new G4Timer();
 theTimer->Start();

  G4UIExecutive* ui = 0;
  if ( argc == 1 ) {
    ui = new G4UIExecutive(argc, argv);
  }

   auto* runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

  B1DetectorConstruction* det = new B1DetectorConstruction();
  runManager->SetUserInitialization(det);

  G4VModularPhysicsList* physicsList = new QGSP_BIC_AllHP;
  physicsList->ReplacePhysics(new G4HadronElasticPhysicsHP());

  G4GenericBiasingPhysics* biasingPhysics = new G4GenericBiasingPhysics();
 
  biasingPhysics->Bias("deuteron");
  physicsList->RegisterPhysics(biasingPhysics);
     
  runManager->SetUserInitialization(physicsList);
  physicsList->SetVerboseLevel(1);
  

  runManager->SetUserInitialization(new B1ActionInitialization());

  G4VisManager* visManager = new G4VisExecutive;

  visManager->Initialize();

  G4UImanager* UImanager = G4UImanager::GetUIpointer();

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

  delete visManager;
  delete runManager;

    theTimer->Stop();
     G4cout<<"The simulation took: "<<theTimer->GetRealElapsed()<<"s to finish (real time)"<<G4endl;

}


