/// \file B1SteppingAction.cc
/// \brief Implementation of the B1SteppingAction class

#include "B1SteppingAction.hh"
#include "B1EventAction.hh"
#include "B1DetectorConstruction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"
#include "G4ParticleDefinition.hh"

#include "G4TrackVector.hh"
#include "G4DynamicParticle.hh"
#include "G4VCrossSectionDataSet.hh"
#include "G4BiasingProcessInterface.hh"
#include "G4VProcess.hh"

#include "G4TrackingManager.hh"
#include "G4UserTrackingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
//---------------------------------------------------------------------------------------------------

B1SteppingAction::B1SteppingAction(B1EventAction *eventAction)
    : G4UserSteppingAction(),
      fEventAction(eventAction),
      fScoringVolume(0),
      fMolybdenum(0),
      fTiT(0),
      fCopper(0),
      fAuX(0),
      fAl8(0),
      fGe73(0),
      fGe76(0),
      fAl7(0)
{}

//---------------------------------------------------------------------------------------------------

B1SteppingAction::~B1SteppingAction()
{}

//----------------------------------------------------------------------------------------------------

void B1SteppingAction::UserSteppingAction(const G4Step *step)
{
  G4String particle = step->GetTrack()->GetParticleDefinition()->GetParticleName();
  const B1DetectorConstruction *detectorConstruction = static_cast<const B1DetectorConstruction *>(G4RunManager::GetRunManager()->GetUserDetectorConstruction());
  
  //----------------------------------------------------------------
  //First part (flange):
  //----------------------------------------------------------------

  if (!fScoringVolume)
  {
    fScoringVolume = detectorConstruction->GetScoringVolume();
  }

  if (!fMolybdenum)
  {
    fMolybdenum = detectorConstruction->GetMolyVolume();
  }

  if (!fTiT)
  {
    fTiT = detectorConstruction->GetTiTVolume();
  }

  if (!fCopper)
  {
    fCopper = detectorConstruction->GetCopperVolume();
  }

  //----------------------------------------------------------------
  //Second part (5 extra foils):
  //----------------------------------------------------------------
  if (!fAuX)
  {
    fAuX = detectorConstruction->GetAuXVolume();
  }
  if (!fAl8)
  {
    fAl8 = detectorConstruction->GetAl8Volume();
  } 
  if(!fGe73)
  {
    fGe73 = detectorConstruction->GetGe73Volume();
  }
  if(!fGe76)
  {
    fGe76 = detectorConstruction->GetGe76Volume();
  }
  if(!fAl7)
  {
    fAl7 = detectorConstruction->GetAl7Volume();
  }


  // get volume of the current step:
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  G4LogicalVolume *postvolume = 0;

  if (step->GetPostStepPoint()->GetTouchableHandle()->GetVolume())
  {
    postvolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  }

  // Watching for XS:
  G4int    parent   = step->GetTrack()->GetParentID();
  G4double weight   = step->GetTrack()->GetWeight();
 
  //---------------------------------------------------------------------------
  //We stop the deuterons when they reach the end of TiT.
  if (parent == 0 && volume != fCopper && postvolume == fCopper) { step->GetTrack()->SetTrackStatus(fStopAndKill); }
  
  //----------------------------------------------------------------------------
  //We kill in molybdenum the x secondary particles from (d,x) except for secondary neutrons:
  if (volume == fMolybdenum && parent == 0)
  {
    auto secondaries = step->GetSecondary();
    
    if (secondaries) //exist
    {
      size_t nSecondaries = secondaries->size();

      for (size_t i = 0; i < nSecondaries; i++)
      {
        G4Track *secTrack = secondaries->at(i);
        G4String secondariesName = secTrack->GetParticleDefinition()->GetParticleName();

        if (secondariesName != "deuteron")
        {
           secTrack->SetTrackStatus(fStopAndKill);
        }
    }
  }   
}

  //=======================================================
  // fTiT - Neutrons generated in the foil:
  //=======================================================
  if (volume == fTiT && parent == 0)
  {
    auto secondaries = step->GetSecondary();
    
    if (secondaries)
    {
      size_t nSecondaries = secondaries->size();

      for (size_t i = 0; i < nSecondaries; i++)
      {
        G4Track *secTrack = secondaries->at(i);
        G4String secondariesName = secTrack->GetParticleDefinition()->GetParticleName();

        auto process = secTrack->GetCreatorProcess()->GetProcessName();

        if (secondariesName == "neutron")
        {

          for (size_t j = 0; j < nSecondaries; j++)
          {
            G4Track *newTrack = secondaries->at(j);
            G4String compound = newTrack->GetParticleDefinition()->GetParticleName();
          }

          G4double NeutronEnergy = 0.;
          NeutronEnergy = secTrack->GetKineticEnergy();

          auto position = secTrack->GetPosition();
          G4double posX = position.getX();
          G4double posY = position.getY();
          G4double posZ = position.getZ();
          //Attaching to event action:
          fEventAction->zPosTiTNeutronGenerated(posZ);

//===================================================
#ifdef G4MULTITHREADED
          static G4Mutex stuffMutex = G4MUTEX_INITIALIZER;
          G4AutoLock al(&stuffMutex);
#endif
//===================================================

          static std::ofstream stuff("NeutronsGeneratedinTiT.txt");
          static bool first = true;

          if (first)
          {
            first = false;
            stuff << "positionX [cm]"     << std::setw(10) << ""
                  << "positionY [cm]"     << std::setw(10) << ""
                  << "positionZ [cm]"     << std::setw(10) << ""
                  << "NeutronKinEn [MeV]" << std::setw(10) << ""
                  << "processName"        << std::setw(10)         
                  << std::endl;
          }

          stuff << std::setw(12) << posX / cm
                << std::setw(12) << ""
                << std::setw(12) << posY / cm
                << std::setw(12) << ""
                << std::setw(12) << posZ / cm
                << std::setw(12) << ""
                << std::setw(12) << NeutronEnergy
                << std::setw(12) << ""
                << std::setw(12) << process << std::endl;
        

      
      }
    }
  }   
}

  //=========================================================================
  //Copper - Neutrons generated in the foil:
  //=========================================================================
  
  if(volume == fCopper && parent == 0)
  {
    auto secondaries = step->GetSecondary();

    if (secondaries)
    {
      size_t nSecondaries = secondaries->size();

      for (size_t i = 0; i < nSecondaries; i++)
      {
        G4Track* secTrack = secondaries->at(i);
        G4String secondariesName = secTrack->GetParticleDefinition()->GetParticleName();

        auto process = secTrack->GetCreatorProcess()->GetProcessName();


        if (secondariesName == "neutron")
        {
          G4double NeutronEnergy = 0.;
          NeutronEnergy = secTrack->GetKineticEnergy();

          auto position = secTrack->GetPosition();
          G4double posX = position.getX();
          G4double posY = position.getY();
          G4double posZ = position.getZ();
          //Attaching to event action:
          fEventAction->zPosCopperNeutronGenerated(posZ);

        //===================================================
        #ifdef G4MULTITHREADED
          static G4Mutex stuffMutex = G4MUTEX_INITIALIZER;
          G4AutoLock al(&stuffMutex);
        #endif
        //===================================================

          static std::ofstream stuff("NeutronsGeneratedinCopper.txt");
          static bool first = true;

          if (first)
          {
            first = false;
            stuff << "positionX [cm]"     << std::setw(10) << ""
                  << "positionY [cm]"     << std::setw(10) << ""
                  << "positionZ [cm]"     << std::setw(10) << ""
                  << "NeutronKinEn [MeV]" << std::setw(10) << ""
                  << "processName"        << std::setw(10)         
                  << std::endl;
          }
            
          stuff << std::setw(12) << posX / cm
                << std::setw(12) << ""
                << std::setw(12) << posY / cm
                << std::setw(12) << ""
                << std::setw(12) << posZ / cm
                << std::setw(12) << ""
                << std::setw(12) << NeutronEnergy
                << std::setw(12) << ""
                << std::setw(12) << process << std::endl;

        }
      }
    }
  }
  
  //============================================================================
  //For storing in root:
  //We get the energies of neutrons in each foil:
  if (particle == "neutron")
  {
    G4double NeutronEnergy = 0.;
    NeutronEnergy = step->GetPreStepPoint()->GetKineticEnergy();
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();

    //For general neutron energies:
    fEventAction->NeutronEnergy(NeutronEnergy);
    
    //Neutrons from Molybdenum:
    if (volume == fMolybdenum && vertexVolume == fMolybdenum) { fEventAction->molyNeutronEnergy(NeutronEnergy); } 
    //Neutrons from TiT:
    if (volume == fTiT && vertexVolume == fTiT) { fEventAction->tiTNeutronEnergy(NeutronEnergy); }
    //Neutrons from Copper:
    if (volume == fCopper && vertexVolume == fCopper) { fEventAction->copperNeutronEnergy(NeutronEnergy); }

    //All this information goes to event action and then to run action. 

  }
  
  //For deuteron implantation in Copper:
  if (particle == "deuteron" && volume == fCopper)
  {
    G4double DeuteronEnergy = 0.;
    DeuteronEnergy = step->GetPreStepPoint()->GetKineticEnergy();
    fEventAction->DeuteronEnergy(DeuteronEnergy);
  }


  //============================================================================================================
  //Second part (5 extra foils):
  if (particle == "neutron")
  {
  
  //--------------------------------------------------------------------------------
  //AuX Foil:
  // Check if the particle is a neutron and if it reaches fAuX:
  if (volume != fAuX && postvolume == fAuX)
  {
    //Get the energy of the neutrons which reach AuX foil:
    G4double Energy = 0.;
    Energy = step->GetPreStepPoint()->GetKineticEnergy(); 
    
    //Get the volumes neutrons came from & the name of each volume:
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();
    G4String volumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
    
    //Save the energy and mother volumes in text file:
    static std::ofstream stuff("NeutronsInsertAuX.txt");
    static bool first = true;

    if (first)
  {
            first = false;
            stuff << "NeutronKinEn [MeV]" << std::setw(10) << ""
                  << "MotherVolume"        << std::setw(10)         
                  << std::endl;
  }
            
          stuff << std::setw(12) << Energy
                << std::setw(12) << ""
                << std::setw(12) << volumeName << std::endl;


    //General energy:
    fEventAction->AuXNeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->AuXNeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT and flange:
    if (vertexVolume == fTiT) { fEventAction->AuXNeutronEnergyfromTiT(Energy); }
    
    //Energy comes from Copper:
    if (vertexVolume == fCopper){ fEventAction->AuXNeutronEnergyfromCopper(Energy); } 

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->AuXNeutronEnergyNotFromMoAndCu(Energy); }

  }

  //--------------------------------------------------------------------------------
  //Al8 Foil:
  // Check if the particle is a neutron and if it reaches fAl8:
  if (volume != fAl8 && postvolume == fAl8)
  {
    //Get the energy of the neutrons which reach Al8 foil:
    G4double Energy = 0.;
    Energy = step->GetPreStepPoint()->GetKineticEnergy(); 
    
    //Get the volumes neutrons came from & the name of each volume:
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();
    G4String volumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
    
    //Save the energy and mother volumes in text file:
    static std::ofstream stuff("NeutronsInsertAl8.txt");
    static bool first = true;

    if (first)
  {
            first = false;
            stuff << "NeutronKinEn [MeV]" << std::setw(10) << ""
                  << "MotherVolume"        << std::setw(10)         
                  << std::endl;
  }
            
          stuff << std::setw(12) << Energy
                << std::setw(12) << ""
                << std::setw(12) << volumeName << std::endl;


    //General energy (from everywhere):
    fEventAction->Al8NeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->Al8NeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT:
    if (vertexVolume == fTiT) { fEventAction->Al8NeutronEnergyfromTiT(Energy); }

    //Energy comes from Copper:
    if (vertexVolume == fCopper) { fEventAction->Al8NeutronEnergyfromCopper(Energy); }   

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->Al8NeutronEnergyNotFromMoAndCu(Energy); }

  }
  

  //--------------------------------------------------------------------------------
  //Ge73 Foil:
  // Check if the particle is a neutron and if it reaches fGe73:
  if (volume != fGe73 && postvolume == fGe73)
  {
    //Get the energy of the neutrons which reach Ge73 foil:
    G4double Energy = 0.;
    Energy = step->GetPreStepPoint()->GetKineticEnergy(); 
    
    //Get the volumes neutrons came from & the name of each volume:
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();
    G4String volumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
    
    //Save the energy and mother volumes in text file:
    static std::ofstream stuff("NeutronsInsertGe73.txt");
    static bool first = true;

    if (first)
  {
            first = false;
            stuff << "NeutronKinEn [MeV]" << std::setw(10) << ""
                  << "MotherVolume"        << std::setw(10)         
                  << std::endl;
  }
            
          stuff << std::setw(12) << Energy
                << std::setw(12) << ""
                << std::setw(12) << volumeName << std::endl;


    //General energy:
    fEventAction->Ge73NeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->Ge73NeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT:
    if (vertexVolume == fTiT){ fEventAction->Ge73NeutronEnergyfromTiT(Energy); }

    //Energy comes from Copper:
    if (vertexVolume == fCopper){ fEventAction->Ge73NeutronEnergyfromCopper(Energy); }   

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->Ge73NeutronEnergyNotFromMoAndCu(Energy); }

  }

  //--------------------------------------------------------------------------------
  //Ge76 Foil:
  // Check if the particle is a neutron and if it reaches fGe76:
  if (volume != fGe76 && postvolume == fGe76)
  {
    //Get the energy of the neutrons which reach Ge76 foil:
    G4double Energy = 0.;
    Energy = step->GetPreStepPoint()->GetKineticEnergy(); 
    
    //Get the volumes neutrons came from & the name of each volume:
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();
    G4String volumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
    
    //Save the energy and mother volumes in text file:
    static std::ofstream stuff("NeutronsInsertGe76.txt");
    static bool first = true;

    if (first)
  {
            first = false;
            stuff << "NeutronKinEn [MeV]" << std::setw(10) << ""
                  << "MotherVolume"        << std::setw(10)         
                  << std::endl;
  }
            
          stuff << std::setw(12) << Energy
                << std::setw(12) << ""
                << std::setw(12) << volumeName << std::endl;


    //General energy:
    fEventAction->Ge76NeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->Ge76NeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT:
    if (vertexVolume == fTiT){ fEventAction->Ge76NeutronEnergyfromTiT(Energy); }

    //Energy comes from Copper:
    if (vertexVolume == fCopper){ fEventAction->Ge76NeutronEnergyfromCopper(Energy); }   

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->Ge76NeutronEnergyNotFromMoAndCu(Energy); }

  }

  //--------------------------------------------------------------------------------
  //Al7 Foil:
  // Check if the particle is a neutron and if it reaches fAl7:
  if (volume != fAl7 && postvolume == fAl7)
  {
    //Get the energy of the neutrons which reach Al7 foil:
    G4double Energy = 0.;
    Energy = step->GetPreStepPoint()->GetKineticEnergy(); 
    
    //Get the volumes neutrons came from & the name of each volume:
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();
    G4String volumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
    
    //Save the energy and mother volumes in text file:
    static std::ofstream stuff("NeutronsInsertAl7.txt");
    static bool first = true;

    if (first)
  {
            first = false;
            stuff << "NeutronKinEn [MeV]"  << std::setw(10) << ""
                  << "MotherVolume"        << std::setw(10)         
                  << std::endl;
  }
            
          stuff << std::setw(12) << Energy
                << std::setw(12) << ""
                << std::setw(12) << volumeName << std::endl;


    //General energy:
    fEventAction->Al7NeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->Al7NeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT and flange:
    if (vertexVolume == fTiT) { fEventAction->Al7NeutronEnergyfromTiT(Energy); }
    
    //Energy comes from Copper:
    if (vertexVolume == fCopper){ fEventAction->Al7NeutronEnergyfromCopper(Energy); } 

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->Al7NeutronEnergyNotFromMoAndCu(Energy); }

  }
  
  }
}




