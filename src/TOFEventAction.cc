//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
#include "G4RunManager.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4Event.hh"
#include "G4EventManager.hh"
#include "G4ios.hh"
#include "G4ParticleGun.hh"

#include "Analysis.hh"
#include "ionRESP.hh"
#include "TOFEventAction.hh"
#include "TOFscinHit.hh"
#include "TOFscinSD.hh"
#include "TOFPrimaryGeneratorAction.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......


TOFEventAction::TOFEventAction()
: G4UserEventAction()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

TOFEventAction::~TOFEventAction()
{
    G4int eventID = event->GetEventID();
    if (eventID % 10000 == 0)
    {
        G4cout << "eventID: " << eventID << G4endl;
    }
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TOFEventAction::BeginOfEventAction(const G4Event* event)
{
    
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void TOFEventAction::EndOfEventAction(const G4Event* event)
{   
    
    G4int eventID = event->GetEventID();
    // get particle energy
    TOFPrimaryGeneratorAction* generatorAction = (TOFPrimaryGeneratorAction*)
    (G4RunManager::GetRunManager()->GetUserPrimaryGeneratorAction());
    G4ParticleGun* particleGun = generatorAction->GetParticleGun();
    G4double particleEnergy = particleGun->GetParticleEnergy();
    
    // get analysis manager
    G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
    
    // Fill the histogram of the source energy distribution
    analysisManager->FillH1(0, particleEnergy);
    
    // Fill the ntuple for each event
    G4int s1_HCID = G4SDManager::GetSDMpointer()->GetCollectionID("s1_hitscollection");
	G4int s2_HCID = G4SDManager::GetSDMpointer()->GetCollectionID("s2_hitscollection");
	
	TOFscinHitsCollection* s1_HC = static_cast<TOFscinHitsCollection*>(event->GetHCofThisEvent()->GetHC(s1_HCID));
	TOFscinHitsCollection* s2_HC = static_cast<TOFscinHitsCollection*>(event->GetHCofThisEvent()->GetHC(s2_HCID));
    
    G4int Nohits_s1 = 0;
    G4int Nohits_s2 = 0;
	Nohits_s1 = s1_HC->entries();
	Nohits_s2 = s2_HC->entries();
 
            
	if (Nohits_s1 == 0)
	{
		return;
	}
	else if (Nohits_s2 == 0)
	{
		return;
	}
    
	G4double s1_time[5];
	G4double s2_time[40];
	G4double s1_phlight[5];
	G4double s2_phlight[40];
	//G4double sigma;
	//G4double tmean;
	//sigma = 0.6 / 2.35;
	//tmean=0.0;
    
    
    //G4cout << "Nohits_s1: " << Nohits_s1
    //       << " "
    //       << "Nohits_s2: " << Nohits_s2
    //       << G4endl; 
    
    //init
    for (G4int i = 0; i < 5; i++)
	{
		s1_time[i] = -1;
		s1_phlight[i] = 0;
	}
	
	for (G4int i = 0; i < 40; i++)
	{
		s2_time[i] = -10;
		s2_phlight[i] = 0;
	}
	
    
	for (int i = 0; i < Nohits_s1; i++)
	{
		G4int DetID = (*s1_HC)[i]->GetDetID();
		G4String Pname = (*s1_HC)[i]->GetPname();
		G4double Time = (*s1_HC)[i]->GetTime();
		G4double Edep = (*s1_HC)[i]->GetEdep();
		s1_phlight[DetID] += Songresp(Edep, Pname);
		if (s1_time[DetID] < 0 || Time < s1_time[DetID])
		{
			s1_time[DetID] = Time;
		} 
		 
	}
    
    
	for (int i = 0; i < Nohits_s2; i++)
	{
		G4int DetID = (*s2_HC)[i]->GetDetID();
		G4String Pname = (*s2_HC)[i]->GetPname();
		G4double Time = (*s2_HC)[i]->GetTime();
		G4double Edep = (*s2_HC)[i]->GetEdep();
        s2_phlight[DetID] += Songresp(Edep, Pname);
		if (s2_time[DetID] < 0 || Time < s2_time[DetID])
		{
			s2_time[DetID] = Time;
		} 
	}
    
    G4double s1PhThreshold = 10;
    G4double s2PhThreshold = 10;
	for(int iS1No = 0; iS1No < 5;iS1No++)
	{
		if ((s1_phlight[iS1No] > s1PhThreshold) && (s1_time[iS1No] > 0))
		{
			for (int iS2No = 0;iS2No < 40;iS2No++)
			{
				if ((s2_phlight[iS2No] > s2PhThreshold) && (s2_time[iS2No] > 0))
				{
					G4double tflight = s2_time[iS2No] - s1_time[iS1No];
                    analysisManager->FillNtupleDColumn(0, tflight);
                    analysisManager->FillNtupleDColumn(1, s1_phlight[iS1No]);
                    analysisManager->FillNtupleDColumn(2, s2_phlight[iS2No]);
                    analysisManager->FillNtupleIColumn(3, iS1No);
                    analysisManager->FillNtupleIColumn(4, iS2No);
                    analysisManager->FillNtupleIColumn(5, eventID);
                    analysisManager->AddNtupleRow();
				}
			}
			
		}
	} 
	
}  

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
