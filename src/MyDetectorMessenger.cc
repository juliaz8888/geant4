#include "MyDetectorMessenger.hh"
#include "MyDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

MyDetectorMessenger::MyDetectorMessenger(MyDetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  fESCDirectory = new G4UIdirectory("/ESC/");
  fESCDirectory->SetGuidance("UI commands specific to this example.");

  fCrysMatCmd = new G4UIcmdWithAString("/ESC/setCrystalMaterial",this);
  fCrysMatCmd->SetGuidance("Select Material of the Crystal.");
  fCrysMatCmd->SetParameterName("choice",false);
  fCrysMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

  fListMatCmd = new G4UIcmdWithAString("/ESC/listMaterials",this);
  fListMatCmd->AvailableForStates(G4State_PreInit,G4State_Idle);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyDetectorMessenger::~MyDetectorMessenger()
{
  delete fESCDirectory;
  delete fCrysMatCmd;
  delete fListMatCmd;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void MyDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  if( command == fCrysMatCmd )
      fDetectorConstruction->SetCrystalMat(newValue);
  if( command == fListMatCmd){
      G4cout << "G4_GALLIUM_ARSENIDE" << G4endl;
      G4cout << "G4_CADMIUM_TELLURIDE" << G4endl;
      G4cout << "GaP" << G4endl;
      G4cout << "GaSb" << G4endl;
      G4cout << "PbSe" << G4endl;
      G4cout << "PbTe" << G4endl;
      G4cout << "BiTe3" << G4endl;
      G4cout << "InSb" << G4endl;
      G4cout << "CdSe" << G4endl;
      G4cout << "Lu2SiO5" << G4endl;
      G4cout << "Bi12SiO20" << G4endl;
      G4cout << "UO2" << G4endl;
      G4cout << "Bi4Ge3O12" << G4endl;
  }
}
