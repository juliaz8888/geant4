#include "G4UserTrackingAction.hh"
#include "globals.hh"

class MyTrackingAction : public G4UserTrackingAction {

public:
  MyTrackingAction();
  virtual ~MyTrackingAction();

  virtual void PreUserTrackingAction(const G4Track*);
  virtual void PostUserTrackingAction(const G4Track*);

};
