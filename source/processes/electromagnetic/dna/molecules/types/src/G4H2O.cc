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
// $Id: G4H2O.cc 64057 2012-10-30 15:04:49Z gcosmo $
//
// Author: Mathieu Karamitors 
//
// History:
// -----------
// 10 Oct 2011 M.Karamitros created
//
// -------------------------------------------------------------------

#include "G4H2O.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleTable.hh"

// ######################################################################
// ###                         Hydrogen                               ###
// ######################################################################
G4H2O* G4H2O::theInstance = 0;

G4H2O* G4H2O::Definition()
{
    if (theInstance !=0) return theInstance;
    const G4String name = "H_{2}O";
    // search in particle table]
    G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition* anInstance = pTable->FindParticle(name);
    if (anInstance ==0)
    {
        // create molecule
        //
//        G4MoleculeDefinition(G4String name,
//                             G4double mass,
//                             G4int    electronsNumber,
//                             G4int    electronicLevels,
//                             G4double diffCoeff,
//                             G4int atomsNumber = -1,
//                             G4double radius = -1,
//                             G4double lifetime = -1,
//                             G4String aType = "",
//                             G4MoleculeID ID = G4MoleculeID::Create()
//                             );

        G4double mass = 18.0153*g/Avogadro * c_squared;
        anInstance = new G4MoleculeDefinition(name, mass, 10, 8,
                                              2e-5*(cm*cm/s),
                                              3, 2.75 * angstrom, picosecond);

        ((G4MoleculeDefinition*) anInstance) ->SetLevelOccupation(0);
        ((G4MoleculeDefinition*) anInstance) ->SetLevelOccupation(1);
        ((G4MoleculeDefinition*) anInstance) ->SetLevelOccupation(2);
        ((G4MoleculeDefinition*) anInstance) ->SetLevelOccupation(3);
        ((G4MoleculeDefinition*) anInstance) ->SetLevelOccupation(4);

    }
    theInstance = reinterpret_cast<G4H2O*>(anInstance);
    return theInstance;
}
