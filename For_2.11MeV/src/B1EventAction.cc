/// \file B1EventAction.cc
/// \brief Implementation of the B1EventAction class

#include "B1EventAction.hh"
#include "B1RunAction.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"

#include "G4SDManager.hh"
#include "G4AnalysisManager.hh" 
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

void B1EventAction::NeutronEnergy(G4double NeutronKin)
{
   fRunAction->NeutronEnergy(NeutronKin);
}

void B1EventAction::DeuteronEnergy(G4double DeuteronKin)
{
   fRunAction->DeuteronEnergy(DeuteronKin);
}

void B1EventAction::molyNeutronEnergy(G4double NeutronKin)
{
  fRunAction->molyNeutronEnergy(NeutronKin);
}

void B1EventAction::tiTNeutronEnergy(G4double NeutronKin)
{
  fRunAction->tiTNeutronEnergy(NeutronKin);
}

void B1EventAction::copperNeutronEnergy(G4double NeutronKin)
{
  fRunAction->copperNeutronEnergy(NeutronKin);
}

//======================================================
//Z-Position of each neutron generated in the foils:
void B1EventAction::zPosMolyNeutronGenerated(G4double zPos)
{
  fRunAction->zPosMolyNeutronGenerated(zPos);
}

void B1EventAction::zPosTiTNeutronGenerated(G4double zPos)
{
  fRunAction->zPosTiTNeutronGenerated(zPos);
}

void B1EventAction::zPosCopperNeutronGenerated(G4double zPos)
{
  fRunAction->zPosCopperNeutronGenerated(zPos);
}
//========================================================

//Part 2 (5 extra foils):
//----------------------------------------------------------------------
//For the Au11 extra foil:
void B1EventAction::Au11NeutronEnergy(G4double NeutronKin) 
{ 
  fRunAction->Au11NeutronEnergy(NeutronKin); 
}

void B1EventAction::Au11NeutronEnergyfromMoly(G4double NeutronKin)
{
  fRunAction->Au11NeutronEnergyfromMoly(NeutronKin);
}

void B1EventAction::Au11NeutronEnergyfromTiT(G4double NeutronKin)
{
  fRunAction->Au11NeutronEnergyfromTiT(NeutronKin);
}

void B1EventAction::Au11NeutronEnergyfromCopper(G4double NeutronKin)
{
  fRunAction->Au11NeutronEnergyfromCopper(NeutronKin);
}

void B1EventAction::Au11NeutronEnergyNotFromMoAndCu(G4double NeutronKin)
{
  fRunAction->Au11NeutronEnergyNotFromMoAndCu(NeutronKin);
}

//----------------------------------------------------------------------
//For the Tl1 extra foil:
void B1EventAction::Tl1NeutronEnergy(G4double NeutronKin) 
{ 
  fRunAction->Tl1NeutronEnergy(NeutronKin); 
}

void B1EventAction::Tl1NeutronEnergyfromMoly(G4double NeutronKin)
{
  fRunAction->Tl1NeutronEnergyfromMoly(NeutronKin);
}

void B1EventAction::Tl1NeutronEnergyfromTiT(G4double NeutronKin)
{
  fRunAction->Tl1NeutronEnergyfromTiT(NeutronKin);
}

void B1EventAction::Tl1NeutronEnergyfromCopper(G4double NeutronKin)
{
  fRunAction->Tl1NeutronEnergyfromCopper(NeutronKin);
}

void B1EventAction::Tl1NeutronEnergyNotFromMoAndCu(G4double NeutronKin)
{
  fRunAction->Tl1NeutronEnergyNotFromMoAndCu(NeutronKin);
}

//----------------------------------------------------------------------
//For the Al6 extra foil:
void B1EventAction::Al6NeutronEnergy(G4double NeutronKin) 
{ 
  fRunAction->Al6NeutronEnergy(NeutronKin); 
}

void B1EventAction::Al6NeutronEnergyfromMoly(G4double NeutronKin)
{
  fRunAction->Al6NeutronEnergyfromMoly(NeutronKin);
}

void B1EventAction::Al6NeutronEnergyfromTiT(G4double NeutronKin)
{
  fRunAction->Al6NeutronEnergyfromTiT(NeutronKin);
}

void B1EventAction::Al6NeutronEnergyfromCopper(G4double NeutronKin)
{
  fRunAction->Al6NeutronEnergyfromCopper(NeutronKin);
}

void B1EventAction::Al6NeutronEnergyNotFromMoAndCu(G4double NeutronKin)
{
  fRunAction->Al6NeutronEnergyNotFromMoAndCu(NeutronKin);
}

//----------------------------------------------------------------------
//For the Ge76 extra foil:
void B1EventAction::Ge76NeutronEnergy(G4double NeutronKin) 
{ 
  fRunAction->Ge76NeutronEnergy(NeutronKin); 
}

void B1EventAction::Ge76NeutronEnergyfromMoly(G4double NeutronKin)
{
  fRunAction->Ge76NeutronEnergyfromMoly(NeutronKin);
}

void B1EventAction::Ge76NeutronEnergyfromTiT(G4double NeutronKin)
{
  fRunAction->Ge76NeutronEnergyfromTiT(NeutronKin);
}

void B1EventAction::Ge76NeutronEnergyfromCopper(G4double NeutronKin)
{
  fRunAction->Ge76NeutronEnergyfromCopper(NeutronKin);
}

void B1EventAction::Ge76NeutronEnergyNotFromMoAndCu(G4double NeutronKin)
{
  fRunAction->Ge76NeutronEnergyNotFromMoAndCu(NeutronKin);
}

//----------------------------------------------------------------------
//For the Al7 extra foil:
void B1EventAction::Al7NeutronEnergy(G4double NeutronKin) 
{ 
  fRunAction->Al7NeutronEnergy(NeutronKin); 
}

void B1EventAction::Al7NeutronEnergyfromMoly(G4double NeutronKin)
{
  fRunAction->Al7NeutronEnergyfromMoly(NeutronKin);
}

void B1EventAction::Al7NeutronEnergyfromTiT(G4double NeutronKin)
{
  fRunAction->Al7NeutronEnergyfromTiT(NeutronKin);
}

void B1EventAction::Al7NeutronEnergyfromCopper(G4double NeutronKin)
{
  fRunAction->Al7NeutronEnergyfromCopper(NeutronKin);
}

void B1EventAction::Al7NeutronEnergyNotFromMoAndCu(G4double NeutronKin)
{
  fRunAction->Al7NeutronEnergyNotFromMoAndCu(NeutronKin);
}

//----------------------------------------------------------------------
//For the AuX extra foil:
void B1EventAction::AuXNeutronEnergy(G4double NeutronKin) 
{ 
  fRunAction->AuXNeutronEnergy(NeutronKin); 
}

void B1EventAction::AuXNeutronEnergyfromMoly(G4double NeutronKin)
{
  fRunAction->AuXNeutronEnergyfromMoly(NeutronKin);
}

void B1EventAction::AuXNeutronEnergyfromTiT(G4double NeutronKin)
{
  fRunAction->AuXNeutronEnergyfromTiT(NeutronKin);
}

void B1EventAction::AuXNeutronEnergyfromCopper(G4double NeutronKin)
{
  fRunAction->AuXNeutronEnergyfromCopper(NeutronKin);
}

void B1EventAction::AuXNeutronEnergyNotFromMoAndCu(G4double NeutronKin)
{
  fRunAction->AuXNeutronEnergyNotFromMoAndCu(NeutronKin);
}







