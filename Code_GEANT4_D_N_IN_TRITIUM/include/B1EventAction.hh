/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4THitsMap.hh"
#include "G4GenericAnalysisManager.hh" 
#include <map>

class B1RunAction;

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction(B1RunAction* runAction);
  
    virtual      ~B1EventAction();
    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void  EndOfEventAction  (const G4Event* event);
    
    void oxygenNeutronEnergy(G4double);
    void carbonNeutronEnergy(G4double);
    void molyNeutronEnergy(G4double);
    void TiTNeutronEnergy(G4double);
    void copperNeutronEnergy(G4double);
    
    

    void Al7NeutronEnergy(G4double);
    void Ge76NeutronEnergy(G4double);
    void GeNatNeutronEnergy(G4double);
    void Al8NeutronEnergy(G4double);
    void AuLightNeutronEnergy(G4double);
    
    void Al7NeutronEnergyfromOxygen(G4double);
    void Al7NeutronEnergyfromCarbon(G4double);
    void Al7NeutronEnergyfromMoly(G4double);
    void Al7NeutronEnergyfromTiT(G4double);
    void Al7NeutronEnergyfromCopper(G4double);
    void Al7NeutronEnergyNotFromMoAndCu(G4double);

    B1RunAction* fRunAction;

};

#endif

    
