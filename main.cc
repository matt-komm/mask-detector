#include "G4RunManager.hh"
#include "G4UImanager.hh"

#include "DetectorConstruction.hh"
#include "B2aDetectorConstruction.hh"
#include "B2MagneticField.hh"
#include "MaskDetector.hh"

#include "PhysicsList.hh"
#include "RunAction.hh"
#include "EventAction.hh"

#include "PrimaryGeneratorAction.hh"

#include "FTFP_BERT.hh"
#include "QGSP_BERT.hh"

#ifdef G4VIS_USE
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"
#endif

int main(int argc,char** argv)
{
  G4RunManager* runManager = new G4RunManager;
  MaskDetector* detector = new MaskDetector();
  runManager->SetUserInitialization(detector);
  //
  B2MagneticField* magField = new B2MagneticField();
  magField->SetMagFieldValue(0.1);
  magField->SetMagFieldValue(G4ThreeVector(0.0,0.0,0.5));
  G4VModularPhysicsList* physicsList = new QGSP_BERT;
  //physicsList->RegisterPhysics(new G4StepLimiterBuilder());
  runManager->SetUserInitialization(physicsList);
  
  RunAction* runAction = new RunAction();
  runManager->SetUserAction(runAction);
  
  EventAction* eventAction = new EventAction();
  runManager->SetUserAction(eventAction);
  //G4VUserPhysicsList* physics = new PhysicsList();
  //runManager->SetUserInitialization(physics);

  PrimaryGeneratorAction* gen_action = new PrimaryGeneratorAction();
  gen_action->addParticle(2212,G4ThreeVector(150*GeV,120*GeV,10*GeV));
  runManager->SetUserAction(gen_action);

  runManager->Initialize();

  
  
  #ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager = new G4VisExecutive;
  visManager->Initialize();
  
  G4UImanager* UImanager = G4UImanager::GetUIpointer();
  UImanager->ApplyCommand("/run/verbose 1");
  UImanager->ApplyCommand("/event/verbose 1");
  UImanager->ApplyCommand("/tracking/verbose 1");
  
  G4UIExecutive* ui = new G4UIExecutive(argc, argv);
  
  UImanager->ApplyCommand("/control/execute init_vis.mac");
  G4int numberOfEvent = 1;
  runManager->BeamOn(numberOfEvent);
  ui->SessionStart();
 
  delete visManager;
  #endif
  
  delete runManager;

  return 0;
}


