/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "B1RunAction.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4GenericAnalysisManager.hh" 
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "Randomize.hh"
#include "G4RunManager.hh"
#include "G4GenericAnalysisManager.hh"
#include <iomanip>

using G4AnalysisManager = G4GenericAnalysisManager;

void B1EventAction::BeginOfEventAction(const G4Event *)
{}
void B1EventAction::EndOfEventAction(const G4Event *event)
{}
B1EventAction::B1EventAction(B1RunAction *runAction)
    : G4UserEventAction(),
      fRunAction(runAction)
{}
B1EventAction::~B1EventAction() 
{}

void B1EventAction::oxygenNeutronEnergy             (G4double NeutronKin) { fRunAction->oxygenNeutronEnergy(NeutronKin); }
void B1EventAction::carbonNeutronEnergy             (G4double NeutronKin) { fRunAction->carbonNeutronEnergy(NeutronKin); }
void B1EventAction::molyNeutronEnergy               (G4double NeutronKin) { fRunAction->molyNeutronEnergy(NeutronKin); }
void B1EventAction::TiTNeutronEnergy                (G4double NeutronKin) { fRunAction->TiTNeutronEnergy(NeutronKin);}
void B1EventAction::copperNeutronEnergy             (G4double NeutronKin) { fRunAction->copperNeutronEnergy(NeutronKin);}
void B1EventAction::Al7NeutronEnergy                (G4double NeutronKin) { fRunAction->Al7NeutronEnergy(NeutronKin); }
void B1EventAction::Al7NeutronEnergyfromOxygen      (G4double NeutronKin) { fRunAction->Al7NeutronEnergyfromOxygen(NeutronKin);}
void B1EventAction::Al7NeutronEnergyfromCarbon      (G4double NeutronKin) { fRunAction->Al7NeutronEnergyfromCarbon(NeutronKin);}
void B1EventAction::Al7NeutronEnergyfromMoly        (G4double NeutronKin) { fRunAction->Al7NeutronEnergyfromMoly(NeutronKin);}
void B1EventAction::Al7NeutronEnergyfromTiT         (G4double NeutronKin) { fRunAction->Al7NeutronEnergyfromTiT(NeutronKin);}
void B1EventAction::Al7NeutronEnergyfromCopper      (G4double NeutronKin) { fRunAction->Al7NeutronEnergyfromCopper(NeutronKin);}
void B1EventAction::Al7NeutronEnergyNotFromMoAndCu  (G4double NeutronKin) { fRunAction->Al7NeutronEnergyNotFromMoAndCu(NeutronKin);}
void B1EventAction::Ge76NeutronEnergy               (G4double NeutronKin) { fRunAction->Ge76NeutronEnergy(NeutronKin); }
void B1EventAction::GeNatNeutronEnergy              (G4double NeutronKin) { fRunAction->GeNatNeutronEnergy(NeutronKin); }
void B1EventAction::Al8NeutronEnergy                (G4double NeutronKin) { fRunAction->Al8NeutronEnergy(NeutronKin); }
void B1EventAction::AuLightNeutronEnergy            (G4double NeutronKin) { fRunAction->AuLightNeutronEnergy(NeutronKin);}









