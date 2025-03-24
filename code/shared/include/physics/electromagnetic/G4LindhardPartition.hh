/*
 *  Created by Marcus Mendenhall on 1/14/08.
 *  2008 Vanderbilt University, Nashville, TN, USA.
 *
 */

//

#include "globals.hh"

class G4Material;

class G4VNIELPartition 
{
public:
        G4VNIELPartition() { }
        virtual ~G4VNIELPartition() { }
        
        // return the fraction of the specified energy which will be deposited as NIEL
        // if an incoming particle with z1, a1 is stopped in the specified material
        // a1 is in atomic mass units, energy in native G4 energy units.
        virtual G4double PartitionNIEL(
                G4int z1, G4double a1, const G4Material *material, G4double energy
        ) const =0;
};

class G4LindhardRobinsonPartition : public G4VNIELPartition
{
public:
        G4LindhardRobinsonPartition();
        virtual ~G4LindhardRobinsonPartition() { }
        
        virtual G4double PartitionNIEL(
                G4int z1, G4double a1, const G4Material *material, G4double energy
        ) const ;
        
        G4double z23[120];
        size_t   max_z;
};

