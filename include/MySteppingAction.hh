#include "G4UserSteppingAction.hh"

class MyEventAction;

/// Stepping action class.
///
/// In UserSteppingAction() there are collected the energy deposit and track
/// lengths of charged particles in Absober and Gap layers and
/// updated in B4aEventAction.

class MySteppingAction : public G4UserSteppingAction
{
public:
  MySteppingAction(MyEventAction* eventAction);
  virtual ~MySteppingAction();

  virtual void UserSteppingAction(const G4Step* step);

private:
  MyEventAction* fEventAction;
};
