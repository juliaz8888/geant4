#include "MyEventAction.hh"
#include "MyRunAction.hh"
#include "MyAnalysis.hh"
#include "MyDetectorConstruction.hh"


#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

MyEventAction::MyEventAction(const MyDetectorConstruction* det, MyRunAction* run)
 : G4UserEventAction(),
   fNumOfLayers(det->GetNumOfLayers()),
   fEventEdep(nullptr),
   fRunAction(run)
{
}


MyEventAction::~MyEventAction()
{
    delete fEventEdep;
}


void MyEventAction::BeginOfEventAction(const G4Event* /*event*/)
{

    fEventEdep = new G4double[fNumOfLayers + 5];
    for(G4int i = 0; i < fNumOfLayers; i++)
      fEventEdep[i] = 0.;
    
    //Verbose Mode
    G4cout << "########Beginning of Event#########" << G4endl;
}


void MyEventAction::EndOfEventAction(const G4Event* /*event*/)
{
    for(G4int i = 0; i < fNumOfLayers; i++)
        fRunAction->fEdep[i].push_back(fEventEdep[i]);

}

void MyEventAction::AddE(G4int iLayer, G4double de) {
  fEventEdep[iLayer] += de;
}
