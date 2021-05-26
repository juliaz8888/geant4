#include "globals.hh"
#include "G4UImessenger.hh"

class MyDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithoutParameter;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/// Messenger class that defines commands for MyDetectorConstruction.
///
/// It implements commands:
/// - /ESC/setCrystalMaterial name


class MyDetectorMessenger: public G4UImessenger
{
  public:
    MyDetectorMessenger(MyDetectorConstruction* );
    virtual ~MyDetectorMessenger();
    virtual void SetNewValue(G4UIcommand*, G4String);

  private:
    MyDetectorConstruction*  fDetectorConstruction;
    G4UIdirectory*           fESCDirectory;
    G4UIcmdWithAString*      fCrysMatCmd;
    G4UIcmdWithAString*      fListMatCmd;
};
