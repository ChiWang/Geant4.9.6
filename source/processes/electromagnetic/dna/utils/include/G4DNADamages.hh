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
// $Id: G4DNADamages.hh 65022 2012-11-12 16:43:12Z gcosmo $
//
#ifndef G4DNADAMAGES_HH
#define G4DNADAMAGES_HH 1

#include "G4Molecule.hh"

class G4VDNAHit
{
public :
    G4VDNAHit(){;}
    virtual ~G4VDNAHit(){;}
};

class G4DNAIndirectHit : public G4VDNAHit
{
public :
    G4DNAIndirectHit(const G4String& baseName, const G4Molecule* molecule,
                     const G4ThreeVector& position, G4double time);
    virtual ~G4DNAIndirectHit();

    inline const G4Molecule* GetMolecule() {return fpMolecule;}
    inline const G4ThreeVector& GetPosition() {return fPosition;}
    inline const G4String& GetBaseName() {return fBaseName;}
    inline double GetTime() {return fTime;}

    void Print();

protected :
    const G4Molecule* fpMolecule;
    G4ThreeVector fPosition;
    G4double fTime;
    G4String fBaseName;
};

class G4DNADamages
{
public:
    static G4DNADamages* Instance();
    static void DeleteInstance();

    virtual void Reset();

    //void AddDirectDamage();
    virtual void AddIndirectDamage(const G4String& baseName,const G4Molecule* molecule,
                           const G4ThreeVector& position, double time);

    inline const std::vector<G4DNAIndirectHit*>* GetIndirectHits();
    inline virtual int GetNIndirectHits() const
    {
        if(fJustCountDamage)
            return fNIndirectDamages;

        return fIndirectHits.size();
    }

    inline virtual void SetOnlyCountDamages(bool flag = true)
    {
        fJustCountDamage = flag;
    }

    inline virtual bool OnlyCountDamages() const
    {
        return fJustCountDamage;
    }

protected :
    G4DNADamages();
    static G4DNADamages* fpInstance;
    virtual ~G4DNADamages();

    G4bool fJustCountDamage;
    G4int fNIndirectDamages;
    std::vector<G4DNAIndirectHit*> fIndirectHits;
    std::map<G4Molecule, const G4Molecule*> fMolMap;
};

inline const std::vector<G4DNAIndirectHit*>* G4DNADamages::GetIndirectHits()
{
    return &fIndirectHits;
}

#endif // G4DNADAMAGES_HH
