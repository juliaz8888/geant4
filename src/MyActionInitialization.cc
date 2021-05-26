#include "MyActionInitialization.hh"
#include "MyPrimaryGeneratorAction.hh"
#include "MyRunAction.hh"
#include "MyEventAction.hh"
#include "MyTrackingAction.hh"
#include "MySteppingAction.hh"
#include "G4MTRunManager.hh"
#include "MyDetectorConstruction.hh"

MyActionInitialization::MyActionInitialization
                            (MyDetectorConstruction* detConstruction)
 : G4VUserActionInitialization(),
   fDetConstruction(detConstruction)
{}


MyActionInitialization::~MyActionInitialization()
{}


void MyActionInitialization::BuildForMaster() const
{
  SetUserAction(new MyRunAction(fDetConstruction));
}


void MyActionInitialization::Build() const
{
  SetUserAction(new MyPrimaryGeneratorAction);
  MyRunAction* fRunAction = new MyRunAction(fDetConstruction);
  SetUserAction(fRunAction);
  MyEventAction* fEventAction = new MyEventAction(fDetConstruction, fRunAction);
  SetUserAction(fEventAction);
  SetUserAction(new MyTrackingAction);
  SetUserAction(new MySteppingAction(fEventAction));
}
