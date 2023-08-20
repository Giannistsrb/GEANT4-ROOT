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
      fAu11(0),
      fTl1(0),
      fAl6(0),
      fGe76(0),
      fAl7(0),
      fAuX(0)

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

  if (!fAu11)
  {
    fAu11 = detectorConstruction->GetAu11Volume();
  }

  if(!fTl1)
  {
    fTl1= detectorConstruction->GetTl1Volume();
  }

  if(!fAl6)
  {
    fAl6 = detectorConstruction->GetAl6Volume();
  }

  if(!fGe76)
  {
    fGe76 = detectorConstruction->GetGe76Volume();
  }

  if(!fAl7)
  {
    fAl7 = detectorConstruction->GetAl7Volume();
  }

  if(!fAuX) 
  {
    fAuX = detectorConstruction->GetAuXVolume();
  }

  // get volume of the current step:
  G4LogicalVolume *volume = step->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();

  G4LogicalVolume *postvolume = 0;

  if (step->GetPostStepPoint()->GetTouchableHandle()->GetVolume())
  {
    postvolume = step->GetPostStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume();
  }

  // Watching for XS:
  G4int parent = step->GetTrack()->GetParentID();
  G4double weight = step->GetTrack()->GetWeight();

  //==============================================================
  // Molybdenum - Neutrons generated in the foil:
  //==============================================================
  if (volume == fMolybdenum && parent == 0)
  {
    auto secondaries = step->GetSecondary();

    if (secondaries)
    {
      size_t nSecondaries = secondaries->size();

      for (size_t i = 0; i < nSecondaries; i++)
      {
        G4Track *secTrack = secondaries->at(i);
        G4String secondariesName = secTrack->GetParticleDefinition()->GetParticleName();

        if (secondariesName == "neutron")
        {
          auto process = secTrack->GetCreatorProcess()->GetProcessName();

          G4double NeutronEnergy = 0.;

          NeutronEnergy = secTrack->GetKineticEnergy();
          auto position = secTrack->GetPosition();
          G4double posX = position.getX();
          G4double posY = position.getY();
          G4double posZ = position.getZ();
          //Attaching to event action:
          fEventAction->zPosMolyNeutronGenerated(posZ);

//===================================================
#ifdef G4MULTITHREADED
          static G4Mutex stuffMutex = G4MUTEX_INITIALIZER;
          G4AutoLock al(&stuffMutex);
#endif
//===================================================

          static std::ofstream stuff("NeutronsGeneratedinMolybdenum.txt");
          static bool first = true;

          if (first)
          {
            first = false;
            stuff << "positionX [cm]" << std::setw(10) << ""
                  << "positionY [cm]" << std::setw(10) << ""
                  << "positionZ [cm]" << std::setw(10) << ""
                  << "NeutronKinEn [MeV]" << std::setw(10) << ""
                  << "processName" << std::setw(10) << std::endl;
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
  
  //For deuterons in Copper:
  if (particle == "deuteron" && volume == fCopper)
  {
    G4double DeuteronEnergy = 0.;
    DeuteronEnergy = step->GetPreStepPoint()->GetKineticEnergy();
    fEventAction->DeuteronEnergy(DeuteronEnergy);
  }

  //============================================================================================================
  //Second part (5 extra foils):
  
  //--------------------------------------------------------------------------------
  //Au11 Foil:
  // Check if the particle is a neutron and if it reaches fAu11:
  if (particle == "neutron")
  {
  if (volume != fAu11 && postvolume == fAu11)
  {
    //Get the energy of the neutrons which reach Au11 foil:
    G4double Energy = 0.;
    Energy = step->GetPreStepPoint()->GetKineticEnergy(); 
    
    //Get the volumes neutrons came from & the name of each volume:
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();
    G4String volumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
    
    //Save the energy and mother volumes in text file:
    static std::ofstream stuff("NeutronsInsertAu11.txt");
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
    fEventAction->Au11NeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->Au11NeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT and flange:
    if (vertexVolume == fTiT) { fEventAction->Au11NeutronEnergyfromTiT(Energy); }
    
    //Energy comes from Copper:
    if (vertexVolume == fCopper){ fEventAction->Au11NeutronEnergyfromCopper(Energy); } 

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->Au11NeutronEnergyNotFromMoAndCu(Energy); }

  }

  //--------------------------------------------------------------------------------
  //Tl1 Foil:
  // Check if the particle is a neutron and if it reaches fTl1:
  if (volume != fTl1 && postvolume == fTl1)
  {
    //Get the energy of the neutrons which reach Au11 foil:
    G4double Energy = 0.;
    Energy = step->GetPreStepPoint()->GetKineticEnergy(); 
    
    //Get the volumes neutrons came from & the name of each volume:
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();
    G4String volumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
    
    //Save the energy and mother volumes in text file:
    static std::ofstream stuff("NeutronsInsertTl1.txt");
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
    fEventAction->Tl1NeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->Tl1NeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT and flange:
    if (vertexVolume == fTiT) { fEventAction->Tl1NeutronEnergyfromTiT(Energy); }
    
    //Energy comes from Copper:
    if (vertexVolume == fCopper){ fEventAction->Tl1NeutronEnergyfromCopper(Energy); } 

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->Tl1NeutronEnergyNotFromMoAndCu(Energy); }

  }

  //--------------------------------------------------------------------------------
  //Al6 Foil:
  // Check if the particle is a neutron and if it reaches fAl6:
  if (volume != fAl6 && postvolume == fAl6)
  {
    //Get the energy of the neutrons which reach Al6 foil:
    G4double Energy = 0.;
    Energy = step->GetPreStepPoint()->GetKineticEnergy(); 
    
    //Get the volumes neutrons came from & the name of each volume:
    auto vertexVolume = step->GetTrack()->GetLogicalVolumeAtVertex();
    G4String volumeName = step->GetTrack()->GetLogicalVolumeAtVertex()->GetName();
    
    //Save the energy and mother volumes in text file:
    static std::ofstream stuff("NeutronsInsertAl6.txt");
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
    fEventAction->Al6NeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->Al6NeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT and flange:
    if (vertexVolume == fTiT) { fEventAction->Al6NeutronEnergyfromTiT(Energy); }
    
    //Energy comes from Copper:
    if (vertexVolume == fCopper){ fEventAction->Al6NeutronEnergyfromCopper(Energy); } 

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->Al6NeutronEnergyNotFromMoAndCu(Energy); }

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
            stuff << "NeutronKinEn [MeV]" << std::setw(10) << ""
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

  

  //--------------------------------------------------------------------------------
  //AuX Foil:
  // Check if the particle is a neutron and if it reaches fAuX:
  if (volume != fAuX && postvolume == fAuX)
  {
    //Get the energy of the neutrons which reach GeNat foil:
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


    //General energy (from everywhere):
    fEventAction->AuXNeutronEnergy(Energy); 

    //Energy comes from Molybdenum:
    if (vertexVolume == fMolybdenum){ fEventAction->AuXNeutronEnergyfromMoly(Energy); }

    //Energy comes from TiT:
    if (vertexVolume == fTiT){ fEventAction->AuXNeutronEnergyfromTiT(Energy); }

    //Energy comes from Copper:
    if (vertexVolume == fCopper){ fEventAction->AuXNeutronEnergyfromCopper(Energy); }   

    //Energy comes from everywhere else except for Molybdenum and Copper:
    if (vertexVolume != fMolybdenum && vertexVolume != fCopper) { fEventAction->AuXNeutronEnergyNotFromMoAndCu(Energy); }

  }
  }
}