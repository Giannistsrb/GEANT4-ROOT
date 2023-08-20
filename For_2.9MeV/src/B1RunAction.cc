/// \file B1RunAction.cc
/// \brief Implementation of the B1RunAction class

#include "B1RunAction.hh"
#include "B1PrimaryGeneratorAction.hh"
#include "B1DetectorConstruction.hh"
#include "G4AnalysisManager.hh"
#include <stdlib.h>
#include "G4RunManager.hh"
#include "G4Run.hh"
#include "G4AccumulableManager.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4LogicalVolume.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GenericAnalysisManager.hh"
#include "G4Timer.hh"

using G4AnalysisManager = G4GenericAnalysisManager;

B1RunAction::B1RunAction()
    : G4UserRunAction(),
      Nofneutrons(0.),
      time(0),
      fRunID(10),
      neu(0.),
      moly(0.),
      tit(0.),
      cop(0.)

{

  G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetVerboseLevel(1);

  //All neutrons generated:
  analysisManager->CreateH1("All_Neutrons_Generated", "All Neutrons", 2001, 0.* MeV, 20. * MeV, "MeV"); 
  
  //All deuterons peaks:
  analysisManager->CreateH1("Deuteron_Peaks", "Deuterons", 2001, 0.* MeV, 20. * MeV, "MeV");

  //==================================================================================
  //FIRST PART - FLANGE: 
  //==================================================================================

  // Counts for neutrons for each foil in the flange:
  analysisManager->CreateH1("Mo_1stFoil_Neutrons", "Molybdenum Neutrons", 2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("TiT_2ndFoil",         "TiT Neutrons",        2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Copper_3rdFoil",      "Copper Neutrons",     2001, 0.* MeV, 20. * MeV, "MeV");

  //==================================================================================
  // The Z-position of each neutron generated into the Molybdenum, TiT and Copper (to check biasing in general):
  analysisManager->CreateH1("Mo_1stFoil_Z_Pos_Neutrons_Generated" ,  "Z position for Neutrons Generated in Molybdenum", 2001, 18.1933  * cm, 18.3  * cm, "cm");
  analysisManager->CreateH1("TiT_2ndFoil_Z_Pos_Neutrons_Generated",  "Z position for Neutrons Generated in TiT",        2001, 18.1933  * cm, 18.3  * cm, "cm");
  analysisManager->CreateH1("Cu_3rdFoil_Z_Pos_Neutrons_Generated" ,  "Z position for Neutrons Generated in Copper",     2001, 18.1933  * cm, 18.3  * cm, "cm");

  //==================================================================================
  //SECOND PART - 5 FOILS:
  //==================================================================================

  //==================================================================================
  //Neutrons energy for Al7:
  analysisManager->CreateH1("Al7_1stFoil_NeutronsAll",      "Al7(1st foil). All neutrons",               2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Al7_1stFoil_TargetMoly",       "Al7(1st foil). Neutrons from Molybdenum",   2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Al7_1stFoil_TargetTiT",        "Al7(1st foil). Neutrons from TiT",          2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Al7_1stFoil_TargetCopper",     "Al7(1st foil). Neutrons from Copper",       2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Al7_1stFoil_TargetNotMoAndCu", "Al7(1st foil). Neutrons not from Mo or Cu", 2001, 0.* MeV, 20. * MeV, "MeV"); //Neutrons from everywhere except for Mo and Cu

  //==================================================================================
  //Neutrons energy for Ge76:
  analysisManager->CreateH1("Ge76_2ndFoil_NeutronsAll",      "Ge76(2nd foil). All neutrons",               2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Ge76_2ndFoil_TargetMoly",       "Ge76(2nd foil). Neutrons from Molybdenum",   2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Ge76_2ndFoil_TargetTiT",        "Ge76(2nd foil). Neutrons from TiT",          2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Ge76_2ndFoil_TargetCopper",     "Ge76(2nd foil). Neutrons from Copper",       2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Ge76_2ndFoil_TargetNotMoAndCu", "Ge76(2nd foil). Neutrons not from Mo or Cu", 2001, 0.* MeV, 20. * MeV, "MeV"); //Neutrons from everywhere except for Mo and Cu


  //==================================================================================
  //Neutrons energy for GeNat:
  analysisManager->CreateH1("GeNat_3rdFoil_NeutronsAll",      "GeNat(3rd foil). All neutrons",               2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("GeNat_3rdFoil_TargetMoly",       "GeNat(3rd foil). Neutrons from Molybdenum",   2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("GeNat_3rdFoil_TargetTiT",        "GeNat(3rd foil). Neutrons from TiT",          2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("GeNat_3rdFoil_TargetCopper",     "GeNat(3rd foil). Neutrons from Copper",       2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("GeNat_3rdFoil_TargetNotMoAndCu", "GeNat(3rd foil). Neutrons not from Mo or Cu", 2001, 0.* MeV, 20. * MeV, "MeV"); //Neutrons from everywhere except for Mo and Cu

  
  //==================================================================================
  //Neutrons energy for Al8:
  analysisManager->CreateH1("Al8_4thFoil_NeutronsAll",      "Al8(4th foil). All neutrons",               2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Al8_4thFoil_TargetMoly",       "Al8(4th foil). Neutrons from Molybdenum",   2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Al8_4thFoil_TargetTiT",        "Al8(4th foil). Neutrons from TiT",          2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Al8_4thFoil_TargetCopper",     "Al8(4th foil). Neutrons from Copper",       2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("Al8_4thFoil_TargetNotMoAndCu", "Al8(4th foil). Neutrons not from Mo or Cu", 2001, 0.* MeV, 20. * MeV, "MeV"); //Neutrons from everywhere except for Mo and Cu


  //==================================================================================
  //Neutrons energy for AuLight:
  analysisManager->CreateH1("AuLight_5thFoil_NeutronsAll",      "AuLight(5th foil). All neutrons",               2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("AuLight_5thFoil_TargetMoly",       "AuLight(5th foil). Neutrons from Molybdenum",   2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("AuLight_5thFoil_TargetTiT",        "AuLight(5th foil). Neutrons from TiT",          2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("AuLight_5thFoil_TargetCopper",     "AuLight(5th foil). Neutrons from Copper",       2001, 0.* MeV, 20. * MeV, "MeV");
  analysisManager->CreateH1("AuLight_5thFoil_TargetNotMoAndCu", "AuLight(5th foil). Neutrons not from Mo or Cu", 2001, 0.* MeV, 20. * MeV, "MeV"); //Neutrons from everywhere except for Mo and Cu
  
}

//==========================================================================================

B1RunAction::~B1RunAction() {}

//==========================================================================================

void B1RunAction::BeginOfRunAction(const G4Run *run)
{

  // TIMER:
  G4Timer *time = new G4Timer();
  time->Start();

  //==============================

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->SetNtupleMerging(true);

  fRunID = run->GetRunID();

  analysisManager->SetFileName("2.9MeV_10^7_biasTargets=HeTiT_f=2000_fnInteractions>1_YesWeight.root");

  analysisManager->OpenFile();

  // Inform the runManager to save random number seed:
  G4RunManager::GetRunManager()->SetRandomNumberStore(false);

  // Reset accumulables to their initial values:
  G4AccumulableManager *accumulableManager = G4AccumulableManager::Instance();
  accumulableManager->Reset();
}

//================================================================================================

void B1RunAction::EndOfRunAction(const G4Run *run)
{
  G4int nofEvents = run->GetNumberOfEvent();
  if (nofEvents == 0)
  {
    return;
  }

  // Run conditions
  //  note: There is no primary generator action object for "master"
  //        run manager for multi-threaded mode.
  const B1PrimaryGeneratorAction *generatorAction = static_cast<const B1PrimaryGeneratorAction *>(G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
  G4String runCondition;
  if (generatorAction)
  {
    const G4ParticleGun *particleGun = generatorAction->GetParticleGun();
    runCondition += particleGun->GetParticleDefinition()->GetParticleName();
    runCondition += " of ";
    G4double particleEnergy = particleGun->GetParticleEnergy();
    runCondition += G4BestUnit(particleEnergy, "Energy");
  }

  //==============================================================================
  // Print

  if (IsMaster())
  {
    G4cout
        << G4endl
        << "--------------------End of Global Run-----------------------";
  }
  else
  {
    G4cout
        << G4endl
        << "--------------------End of Local Run------------------------";
  }

  G4cout
      << G4endl
      << " The run consists of " << nofEvents << " " << runCondition
      << G4endl
      << "------------------------------------------------------------"
      << G4endl;

  if (IsMaster())
  {
    G4cout << "NUMBEROF_MASTEr NEUTRONS" << Nofneutrons << G4endl;
  }

  auto analysisManager = G4AnalysisManager::Instance();

  analysisManager->Write();

  if (IsMaster())
    WriteToASCII();
  {
    analysisManager->CloseFile();
  }

  G4Timer *time = new G4Timer();

  time->Stop();

  G4cout << "RunTime = " << time->GetRealElapsed() << G4endl;
}

//==========================================================================================

void B1RunAction::FillDetected(G4double energy, G4int Z, G4int A, G4int particleID, 
                               G4double pos_x, G4double pos_y, G4double pos_z,  G4int trackID, 
                               G4int parentID)

{}

//==========================================================================================

void B1RunAction::neutronKinEn(G4double neutronKinEn)
{
  auto analysisManager = G4AnalysisManager::Instance();
}

void B1RunAction::NeutronEnergy(G4double neutronKinEn)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(0, neutronKinEn);

  neu = neutronKinEn;
}
void B1RunAction::DeuteronEnergy(G4double deuteronKinEn)
{

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(1, deuteronKinEn);
}

//First part (flange):
void B1RunAction::molyNeutronEnergy(G4double neutronKinEn)
{

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(2, neutronKinEn);

  moly = neutronKinEn;
}

void B1RunAction::tiTNeutronEnergy(G4double neutronKinEn)
{

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(3, neutronKinEn);

  tit = neutronKinEn;
}

void B1RunAction::copperNeutronEnergy(G4double neutronKinEn)
{

  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(4, neutronKinEn);

  cop = neutronKinEn;
}

void B1RunAction::zPosMolyNeutronGenerated(G4double z)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(5, z);
}

void B1RunAction::zPosTiTNeutronGenerated(G4double z)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(6, z);
}

void B1RunAction::zPosCopperNeutronGenerated(G4double z)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(7, z);
}

//Second part (5 extra foils):
//-------------------------------------------------------------
//For Al7 (1st Foil):
void B1RunAction::Al7NeutronEnergy(G4double neutronKinEn)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(8, neutronKinEn);
}

void B1RunAction::Al7NeutronEnergyfromMoly(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(9, neutronKin);
}

void B1RunAction::Al7NeutronEnergyfromTiT(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(10, neutronKin);
}

void B1RunAction::Al7NeutronEnergyfromCopper(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(11, neutronKin);
}

void B1RunAction::Al7NeutronEnergyNotFromMoAndCu(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(12, neutronKin);
}



//-------------------------------------------------------------
//For Ge76 (2nd Foil):
void B1RunAction::Ge76NeutronEnergy(G4double neutronKinEn)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(13, neutronKinEn);
}

void B1RunAction::Ge76NeutronEnergyfromMoly(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(14, neutronKin);
}

void B1RunAction::Ge76NeutronEnergyfromTiT(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(15, neutronKin);
}

void B1RunAction::Ge76NeutronEnergyfromCopper(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(16, neutronKin);
}


void B1RunAction::Ge76NeutronEnergyNotFromMoAndCu(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(17, neutronKin);
}
//-------------------------------------------------------------
//For GeNat (3rd Foil):
void B1RunAction::GeNatNeutronEnergy(G4double neutronKinEn)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(18, neutronKinEn);
}

void B1RunAction::GeNatNeutronEnergyfromMoly(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(19, neutronKin);
}

void B1RunAction::GeNatNeutronEnergyfromTiT(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(20, neutronKin);
}

void B1RunAction::GeNatNeutronEnergyfromCopper(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(21, neutronKin);
}

void B1RunAction::GeNatNeutronEnergyNotFromMoAndCu(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(22, neutronKin);
}
//-------------------------------------------------------------
//For Al8 (4th Foil):
void B1RunAction::Al8NeutronEnergy(G4double neutronKinEn)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(23, neutronKinEn);
}

void B1RunAction::Al8NeutronEnergyfromMoly(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(24, neutronKin);
}

void B1RunAction::Al8NeutronEnergyfromTiT(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(25, neutronKin);
}

void B1RunAction::Al8NeutronEnergyfromCopper(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(26, neutronKin);
}

void B1RunAction::Al8NeutronEnergyNotFromMoAndCu(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(27, neutronKin);
}

//-------------------------------------------------------------
//For AuLight (5th Foil):
void B1RunAction::AuLightNeutronEnergy(G4double neutronKinEn)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(28, neutronKinEn);
}

void B1RunAction::AuLightNeutronEnergyfromMoly(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(29, neutronKin);
}

void B1RunAction::AuLightNeutronEnergyfromTiT(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(30, neutronKin);
}

void B1RunAction::AuLightNeutronEnergyfromCopper(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(31, neutronKin);
}

void B1RunAction::AuLightNeutronEnergyNotFromMoAndCu(G4double neutronKin)
{
  auto analysisManager = G4AnalysisManager::Instance();
  analysisManager->FillH1(32, neutronKin);
}


//================================================================================

#include <iostream>
#include <fstream>
void B1RunAction::WriteToASCII() {}
