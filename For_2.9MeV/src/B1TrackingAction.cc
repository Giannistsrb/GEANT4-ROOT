/// \file B1TrackingAction.cc
/// \brief Implementation of the TrackingAction class

#include "B1TrackingAction.hh"

// #include "Run.hh"
// #include "HistoManager.hh"

#include "G4RunManager.hh"
#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "B1RunAction.hh"
#include "B1EventAction.hh"
#include "G4PhysicsTable.hh"
#include "B1DetectorConstruction.hh"

#include "G4VPhysicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4INCLThreeVector.hh"
#include "G4ThreeVector.hh"

#include "G4Run.hh"
#include "G4WrapperProcess.hh"
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1TrackingAction::B1TrackingAction(B1EventAction *eventAction)
    : G4UserTrackingAction(),
      feventAction(eventAction),
      fNbStep1(0), fNbStep2(0), fTrackLen1(0.), fTrackLen2(0.), fTime1(0.), fTime2(0.),
      fTargetVolume(0), fScoringVolume(0), frunID(0)
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void B1TrackingAction::PreUserTrackingAction(const G4Track *track)
{
  fNbStep1 = fNbStep2 = 0;
  fTrackLen1 = fTrackLen2 = 0.;
  fTime1 = fTime2 = 0.;
}

void B1TrackingAction::PostUserTrackingAction(const G4Track *track)
{}