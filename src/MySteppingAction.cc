#include "MySteppingAction.hh"
#include "MyDetectorConstruction.hh"
#include "MyEventAction.hh"

#include "G4Step.hh"
#include "G4RunManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

MySteppingAction::MySteppingAction(MyEventAction* eventAction):
    G4UserSteppingAction(),
    fEventAction(eventAction)
{}

MySteppingAction::~MySteppingAction()
{}

void MySteppingAction::UserSteppingAction(const G4Step* step){
    auto pos = step->GetPreStepPoint()->GetPosition();
    auto detTime = step->GetDeltaTime();
    auto edep = step->GetTotalEnergyDeposit();
    auto volume = step->GetPreStepPoint()->GetTouchable()->GetVolume();
    G4int nCopy = -1;
    if(volume->GetName() == "Crystal"){
        nCopy = step->GetPostStepPoint()->GetTouchable()->GetReplicaNumber();
        fEventAction->AddE(nCopy, edep);
    }

// Verbose Mode:

   G4cout << G4BestUnit(pos, "Length") << " "
          << G4BestUnit(detTime, "Time") << " "
          << G4BestUnit(edep,"Energy") << G4endl;

}
