/// \file B1ActionInitialization.cc
/// \brief Implementation of the B1ActionInitialization class

#include "B1ActionInitialization.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "B1SteppingAction.hh"
#include "B1TrackingAction.hh"
#include "B1OptrMultiParticleChangeCrossSection.hh"
#include "B1OptrChangeCrossSection.hh"
//#include "SensitiveDetector.hh"
//#include "SensitiveDetectorHit.hh"
#include "B1DetectorConstruction.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1ActionInitialization::B1ActionInitialization()
 : G4VUserActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1ActionInitialization::~B1ActionInitialization()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1ActionInitialization::BuildForMaster() const
{
  B1RunAction* runAction = new B1RunAction;
  SetUserAction(runAction);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1ActionInitialization::Build() const
{
  SetUserAction(new B1PrimaryGeneratorAction);
  // SetUserAction(new B1DetectorConstruction);
  
  B1RunAction* runAction = new B1RunAction;
  SetUserAction(runAction);

  // SetUserAction(new SensitiveDetector(runAction));
  
  B1EventAction* eventAction = new B1EventAction(runAction);
  SetUserAction(eventAction);
  
  SetUserAction(new B1SteppingAction(eventAction));
  SetUserAction(new B1TrackingAction(eventAction));
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
