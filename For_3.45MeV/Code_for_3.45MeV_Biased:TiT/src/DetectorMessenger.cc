/// \file electromagnetic/TestEm11/src/DetectorMessenger.cc
/// \brief Implementation of the DetectorMessenger class


#include <sstream>
#include "DetectorMessenger.hh"
#include "B1DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcommand.hh"
#include "G4UIparameter.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

DetectorMessenger::DetectorMessenger(B1DetectorConstruction * Det)
:G4UImessenger(),fDetector(Det),
 fTestemDir(0),
 fDetDir(0), 
 fNbAbsorCmd(0),           
 fAbsorCmd(0),
 fNdivCmd(0),    
 fSizeYZCmd(0)
{ 
  //=========================================================================================
  fTestemDir = new G4UIdirectory("/tritium/");
  fTestemDir->SetGuidance(" detector control.");
  //=========================================================================================
  fDetDir = new G4UIdirectory("/tritium/det/");
  fDetDir->SetGuidance("detector construction commands");
  //=========================================================================================
  fNbAbsorCmd = new G4UIcmdWithAnInteger("/tritium/det/setNbOfAbsor",this);
  fNbAbsorCmd->SetGuidance("Set number of Absorbers.");
  fNbAbsorCmd->SetParameterName("NbAbsor",false);
  fNbAbsorCmd->SetRange("NbAbsor>0");
  fNbAbsorCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNbAbsorCmd->SetToBeBroadcasted(false);
  //=========================================================================================
  fAbsorCmd = new G4UIcommand("/tritium/det/setTrThickness",this);
  fAbsorCmd->SetGuidance("Set the tritium thickness.");
  fAbsorCmd->SetGuidance("  thickness (with unit) : t>0.");
  //=========================================================================================
  G4UIparameter* ThickPrm = new G4UIparameter("thickness",'d',false);
  ThickPrm->SetGuidance("thickness of absorber");
  ThickPrm->SetParameterRange("thickness>0.");
  fAbsorCmd->SetParameter(ThickPrm);
  //=========================================================================================
  G4UIparameter* unitPrm = new G4UIparameter("unit",'s',false);
  unitPrm->SetGuidance("unit of thickness");
  //=========================================================================================
  G4String unitList = G4UIcommand::UnitsList(G4UIcommand::CategoryOf("cm"));
  unitPrm->SetParameterCandidates(unitList);
  fAbsorCmd->SetParameter(unitPrm);
  //=========================================================================================
  fAbsorCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fAbsorCmd->SetToBeBroadcasted(false);
  //=========================================================================================
  fNdivCmd = new G4UIcommand("/tritium/det/nDivAbsor",this);
  fNdivCmd->SetGuidance("Divide the absor nb : number of divisions");
  fNdivCmd->SetGuidance("  absor number : from 1 to NbOfAbsor");
  fNdivCmd->SetGuidance("  number of divisions >= 0");
  //=========================================================================================
  G4UIparameter* AbsNbPar = new G4UIparameter("AbsorNb",'i',false);
  AbsNbPar->SetGuidance("absor number : from 1 to NbOfAbsor");
  AbsNbPar->SetParameterRange("AbsorNb>0");
  fNdivCmd->SetParameter(AbsNbPar);
  //=========================================================================================    
  G4UIparameter* NdivPrm = new G4UIparameter("NdivNb",'i',false);
  NdivPrm->SetGuidance("nb of divisions > 0");
  NdivPrm->SetParameterRange("NdivNb>0");
  fNdivCmd->SetParameter(NdivPrm);
  //=========================================================================================    
  fNdivCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fNdivCmd->SetToBeBroadcasted(false);
  //=========================================================================================    
  fSizeYZCmd = new G4UIcmdWithADoubleAndUnit("/tritium/det/setSizeYZ",this);
  fSizeYZCmd->SetGuidance("Set sizeYZ of the absorber");
  fSizeYZCmd->SetParameterName("SizeYZ",false);
  fSizeYZCmd->SetRange("SizeYZ>0.");
  fSizeYZCmd->SetUnitCategory("Length");
  fSizeYZCmd->AvailableForStates(G4State_PreInit,G4State_Idle);
  fSizeYZCmd->SetToBeBroadcasted(false);
            
}

DetectorMessenger::~DetectorMessenger()
{
  delete fNbAbsorCmd;
  delete fAbsorCmd;
  delete fNdivCmd;    
  delete fSizeYZCmd;
  delete fDetDir;  
  delete fTestemDir;
}

void DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{    
  if (command == fAbsorCmd)
   {
     G4double tick;
     G4String unt;

     std::istringstream is(newValue);
      is >> tick >> unt;

     tick *= G4UIcommand::ValueOf(unt);
   }
}
