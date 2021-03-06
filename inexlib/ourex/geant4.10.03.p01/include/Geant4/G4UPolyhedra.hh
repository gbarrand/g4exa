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
// $Id:$
//
// 
// --------------------------------------------------------------------
// GEANT 4 class header file
//
//
// G4UPolyhedra
//
// Class description:
//
//   Wrapper class for UPolyhedra to make use of it from USolids module.

// History:
// 31.10.13 G.Cosmo, CERN/PH
// --------------------------------------------------------------------
#ifndef G4UPOLYHEDRA_HH
#define G4UPOLYHEDRA_HH

#include "G4USolid.hh"

#if ( defined(G4GEOM_USE_USOLIDS) || defined(G4GEOM_USE_PARTIAL_USOLIDS) )

#include "UPolyhedra.hh"
#include "G4TwoVector.hh"
#include "G4PolyhedraSide.hh"
#include "G4PolyhedraHistorical.hh"
#include "G4Polyhedron.hh"

class G4EnclosingCylinder;
class G4ReduciblePolygon;

class G4UPolyhedra : public G4USolid
{
  public:  // with description

    G4UPolyhedra( const G4String& name, 
                     G4double phiStart,    // initial phi starting angle
                     G4double phiTotal,    // total phi angle
                     G4int numSide,        // number sides
                     G4int numZPlanes,     // number of z planes
               const G4double zPlane[],    // position of z planes
               const G4double rInner[],    // tangent distance to inner surface
               const G4double rOuter[]  ); // tangent distance to outer surface

    G4UPolyhedra( const G4String& name, 
                     G4double phiStart,    // initial phi starting angle
                     G4double phiTotal,    // total phi angle
                     G4int    numSide,     // number sides
                     G4int    numRZ,       // number corners in r,z space
               const G4double r[],         // r coordinate of these corners
               const G4double z[]       ); // z coordinate of these corners

   ~G4UPolyhedra();

    void ComputeDimensions(      G4VPVParameterisation* p,
                           const G4int n,
                           const G4VPhysicalVolume* pRep);

    G4VSolid* Clone() const;

    inline UPolyhedra* GetShape() const;

    G4int GetNumSide()        const;
    G4double GetStartPhi()    const;
    G4double GetEndPhi()      const;
    G4double GetSinStartPhi() const;
    G4double GetCosStartPhi() const;
    G4double GetSinEndPhi()   const;
    G4double GetCosEndPhi()   const;
    G4bool IsOpen()           const;
    G4bool IsGeneric()        const;
    G4int GetNumRZCorner()    const;
    G4PolyhedraSideRZ GetCorner( const G4int index ) const;
    G4PolyhedraHistorical* GetOriginalParameters() const;
    void SetOriginalParameters(G4PolyhedraHistorical* pars);

    G4bool Reset();

    inline G4GeometryType GetEntityType() const;

  public:  // without description

    G4UPolyhedra(__void__&);
      // Fake default constructor for usage restricted to direct object
      // persistency for clients requiring preallocation of memory for
      // persistifiable objects.

    G4UPolyhedra( const G4UPolyhedra &source );
    G4UPolyhedra &operator=( const G4UPolyhedra &source );
      // Copy constructor and assignment operator.

    void Extent(G4ThreeVector& pMin, G4ThreeVector& pMax) const;

    G4bool CalculateExtent(const EAxis pAxis,
                           const G4VoxelLimits& pVoxelLimit,
                           const G4AffineTransform& pTransform,
                           G4double& pMin, G4double& pMax) const;

    G4Polyhedron* CreatePolyhedron() const;

  private:

    G4double wrStart;
    G4double wrDelta;
    G4int    wrNumSide;
    std::vector<G4TwoVector> rzcorners;
};

// --------------------------------------------------------------------
// Inline methods
// --------------------------------------------------------------------

inline UPolyhedra* G4UPolyhedra::GetShape() const
{
  return (UPolyhedra*) fShape;
}

inline G4GeometryType G4UPolyhedra::GetEntityType() const
{
  return "G4Polyhedra";
}

#endif  // G4GEOM_USE_USOLIDS

#endif
