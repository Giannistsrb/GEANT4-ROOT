/// \file B1EventAction.hh
/// \brief Definition of the B1EventAction class

#ifndef B1EventAction_h
#define B1EventAction_h 1

#include "G4UserEventAction.hh"
#include "globals.hh"
#include "G4THitsMap.hh"
#include "G4AnalysisManager.hh" 
#include <map>

class B1RunAction;

/// Event action class
///

class B1EventAction : public G4UserEventAction
{
  public:
    B1EventAction(B1RunAction* runAction);
    virtual ~B1EventAction();

    virtual void BeginOfEventAction(const G4Event* event);
    virtual void EndOfEventAction(const G4Event* event);

    void NeutronEnergy(G4double);
    
    //First part (flange):
    //Neutron energies from the foils:
    void molyNeutronEnergy(G4double);
    void tiTNeutronEnergy(G4double);
    void copperNeutronEnergy(G4double);
    
    //Z-Position of Neutrons generated in each foil:
    void zPosMolyNeutronGenerated(G4double);
    void zPosTiTNeutronGenerated(G4double);
    void zPosCopperNeutronGenerated(G4double);

    //---------------------------------------------------------
    //Second part (5 extra foils):
    //For Au11-Tl1:
    void Au11NeutronEnergy(G4double);
    void Au11NeutronEnergyfromMoly(G4double);
    void Au11NeutronEnergyfromTiT(G4double);
    void Au11NeutronEnergyfromCopper(G4double);
    void Au11NeutronEnergyNotFromMoAndCu(G4double);    
    void Tl1NeutronEnergy(G4double);
    void Tl1NeutronEnergyfromMoly(G4double);
    void Tl1NeutronEnergyfromTiT(G4double);
    void Tl1NeutronEnergyfromCopper(G4double);
    void Tl1NeutronEnergyNotFromMoAndCu(G4double);
    //For Al6:
    void Al6NeutronEnergy(G4double);
    void Al6NeutronEnergyfromMoly(G4double);
    void Al6NeutronEnergyfromTiT(G4double);
    void Al6NeutronEnergyfromCopper(G4double);
    void Al6NeutronEnergyNotFromMoAndCu(G4double);

    //For Ge76:
    void Ge76NeutronEnergy(G4double);
    void Ge76NeutronEnergyfromMoly(G4double);
    void Ge76NeutronEnergyfromTiT(G4double);
    void Ge76NeutronEnergyfromCopper(G4double);
    void Ge76NeutronEnergyNotFromMoAndCu(G4double);

    //For Al7:
    void Al7NeutronEnergy(G4double);
    void Al7NeutronEnergyfromMoly(G4double);
    void Al7NeutronEnergyfromTiT(G4double);
    void Al7NeutronEnergyfromCopper(G4double);
    void Al7NeutronEnergyNotFromMoAndCu(G4double);
    //For AuX:
    void AuXNeutronEnergy(G4double);
    void AuXNeutronEnergyfromMoly(G4double);
    void AuXNeutronEnergyfromTiT(G4double);
    void AuXNeutronEnergyfromCopper(G4double);
    void AuXNeutronEnergyNotFromMoAndCu(G4double);
    //-----------------------------------------------------------
    
    //Get the deuteron energy function:
    void DeuteronEnergy(G4double);

    B1RunAction* fRunAction;

  };

#endif

    
