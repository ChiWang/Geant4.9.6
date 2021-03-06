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
//
// $Id$
//
//---------------------------------------------------------------------------
//
// ClassName:   HadronPhysicsQGSP
//
// Author: 2002 J.P. Wellisch
//
// Modified:
// 21.11.2005 G.Folger:  migration to non static particles
// 08.06.2006 V.Ivanchenko: remove stopping
// 30.03.2007 G.Folger: Add code for quasielastic
// 12.11.2007 G.Folger: Add code for projectileDiffraction for proton/neutron
// 31.10.2012 A.Ribon: Use G4MiscBuilder
//
#include <iomanip>   

#include "HadronPhysicsQGSP.hh"

#include "globals.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4MesonConstructor.hh"
#include "G4BaryonConstructor.hh"
#include "G4ShortLivedConstructor.hh"

// factory
#include "G4PhysicsConstructorFactory.hh"
//
G4_DECLARE_PHYSCONSTR_FACTORY(HadronPhysicsQGSP);

HadronPhysicsQGSP::HadronPhysicsQGSP(G4int)
    :  G4VPhysicsConstructor("hInelastic QGSP")
    , theNeutrons(0)
    , theLEPNeutron(0)
    , theQGSPNeutron(0)
    , thePiK(0)
    , theLEPPiK(0)
    , theQGSPPiK(0)
    , thePro(0)
    , theLEPPro(0)
    , theQGSPPro(0) 
    , theMisc(0)
    , QuasiElastic(true)
    , ProjectileDiffraction(false)
{
}

HadronPhysicsQGSP::HadronPhysicsQGSP(const G4String& name, G4bool quasiElastic)
                 :  G4VPhysicsConstructor(name)
    , theNeutrons(0)
    , theLEPNeutron(0)
    , theQGSPNeutron(0)
    , thePiK(0)
    , theLEPPiK(0)
    , theQGSPPiK(0)
    , thePro(0)
    , theLEPPro(0)
    , theQGSPPro(0) 
    , theMisc(0)
    , QuasiElastic(quasiElastic)
    , ProjectileDiffraction(false)
{
}

void HadronPhysicsQGSP::CreateModels()
{
  theNeutrons=new G4NeutronBuilder;
  theQGSPNeutron=new G4QGSPNeutronBuilder(QuasiElastic, ProjectileDiffraction);
  theNeutrons->RegisterMe(theQGSPNeutron);
  theNeutrons->RegisterMe(theLEPNeutron=new G4LEPNeutronBuilder);
  theLEPNeutron->SetMaxInelasticEnergy(25*GeV);  

  thePro=new G4ProtonBuilder;
  theQGSPPro=new G4QGSPProtonBuilder(QuasiElastic, ProjectileDiffraction);
  thePro->RegisterMe(theQGSPPro);
  thePro->RegisterMe(theLEPPro=new G4LEPProtonBuilder);
  theLEPPro->SetMaxEnergy(25*GeV);
  
  thePiK=new G4PiKBuilder;
  theQGSPPiK=new G4QGSPPiKBuilder(QuasiElastic, false);
  thePiK->RegisterMe(theQGSPPiK);
  thePiK->RegisterMe(theLEPPiK=new G4LEPPiKBuilder);
  theLEPPiK->SetMaxEnergy(25*GeV);
  
  theMisc=new G4MiscBuilder;
}

HadronPhysicsQGSP::~HadronPhysicsQGSP()
{
   delete theMisc;
   delete theQGSPNeutron;
   delete theLEPNeutron;
   delete theQGSPPro;
   delete theLEPPro;
   delete thePro;
   delete theQGSPPiK;
   delete theLEPPiK;
   delete thePiK;
}


void HadronPhysicsQGSP::ConstructParticle()
{
  G4MesonConstructor pMesonConstructor;
  pMesonConstructor.ConstructParticle();

  G4BaryonConstructor pBaryonConstructor;
  pBaryonConstructor.ConstructParticle();

  G4ShortLivedConstructor pShortLivedConstructor;
  pShortLivedConstructor.ConstructParticle();  
}

#include "G4ProcessManager.hh"
void HadronPhysicsQGSP::ConstructProcess()
{
  CreateModels();
  theNeutrons->Build();
  thePro->Build();
  thePiK->Build();
  theMisc->Build();
}

