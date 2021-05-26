#include "G4VModularPhysicsList.hh"
#include "globals.hh"

class G4VPhysicsConstructor;
class PhysicsListMessenger;
class MyPhysicsList: public G4VModularPhysicsList
{
public:
  MyPhysicsList();
  virtual ~MyPhysicsList();

  virtual void SetCuts();
};
