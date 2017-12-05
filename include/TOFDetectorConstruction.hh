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


#ifndef TOFDetectorConstruction_h
#define TOFDetectorConstruction_h 1

#include "globals.hh"
#include "G4VUserDetectorConstruction.hh"
#include "tls.hh"
#include "TOFscinSD.hh"

class G4VPhysicalVolume;
class G4LogicalVolume;
class G4Material;
class TOFDetectorMessenger;

class TOFDetectorConstruction : public G4VUserDetectorConstruction
{
    public:
        TOFDetectorConstruction();
        virtual ~TOFDetectorConstruction();

    public:
        virtual G4VPhysicalVolume* Construct();
        virtual void ConstructSDandField();
        void UpdateGeometry();
        
    // Set methods
    public:
        void SetFlightAngle(G4double data) {flightAngle = data;};
        void SetNumberOfS1(G4int data) { NumberOfS1 = data;};
        void SetNumberOfS2(G4int data) { NumberOfS2 = data;};
        
    private:
    // methods
        void DefineMaterials();
        void DefineVolumes();
        
    
    private:
    // data members
        G4VPhysicalVolume*  expHallPV;
    
        G4LogicalVolume*    expHallLV;
        G4LogicalVolume*    S1_scinLV;
        G4LogicalVolume*    S1_MSLV;
        G4LogicalVolume*    S1_LGLV;
        G4LogicalVolume*    S2_MSLV;
        G4LogicalVolume*    S2_scinLV;
        G4LogicalVolume*    S2_LGLV; 
        
        G4Material*     AirMaterial;
        G4Material*     ConcreteMaterial;
        G4Material*     S1Material; 
        G4Material*     S2Material;
        G4Material*     LGMaterial;
        G4Material*     MSMaterial;
        
        //TOFscinSD* S1_scinSD;
        //TOFscinSD* S2_scinSD;
        
        G4bool fCheckOverlaps;
    // gemometry parameter
        TOFDetectorMessenger * DetectorMessenger;
        G4double flightAngle;
        G4int NumberOfS1;
        G4int NumberOfS2;
        
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
