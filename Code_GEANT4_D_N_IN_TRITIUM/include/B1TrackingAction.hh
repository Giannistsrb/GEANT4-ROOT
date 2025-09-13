/// \file B1TrackingAction.hh
/// \brief Definition of the TrackingAction class
//
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#ifndef B1TrackingAction_h
#define B1TrackingAction_h 1

#include "G4UserTrackingAction.hh"
#include "globals.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
class B1EventAction;
class G4BestUnit;
class G4LogicalVolume;
class B1TrackingAction : public G4UserTrackingAction {

  public:  
    B1TrackingAction(B1EventAction* eventAction);
   ~B1TrackingAction() {};
   
    virtual void  PreUserTrackingAction(const G4Track*);   
    virtual void PostUserTrackingAction(const G4Track*);
    
    // void UpdateTrackInfo(G4double, G4double, G4double);    
   //  void UpdateTrackInfo(const G4Track*);

  private:
    B1EventAction* feventAction;
    G4int fNbStep1, fNbStep2;
    G4double fTrackLen1, fTrackLen2;
    G4double fTime1, fTime2;
    G4LogicalVolume* fTargetVolume;
     G4LogicalVolume* fScoringVolume;
    G4int frunID;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
