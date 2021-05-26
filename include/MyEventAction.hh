#include "G4UserEventAction.hh"
#include "globals.hh"
class MyDetectorConstruction;
class MyRunAction;
class MyEventAction : public G4UserEventAction
{
  public:
    MyEventAction(const MyDetectorConstruction* ,MyRunAction*);
    virtual ~MyEventAction();

    virtual void  BeginOfEventAction(const G4Event* event);
    virtual void    EndOfEventAction(const G4Event* event);

    void AddE(G4int iLayer, G4double de);

  private:
    G4double*  fEventEdep;
    const G4int fNumOfLayers;
    MyRunAction* fRunAction;
};




//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


