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
// 
// ------------------------------------------------------------
//      GEANT 4 class header file 
// ------------------------------------------------------------
// Function description:
// =====================
// Fast i^(1/3) for integer i=0-269 (limited accuracy, only for CHIPS)
//
// History: created 29.10.11 by M. Kosov
//
// ------------------------------------------------------------
#ifndef G4QTHD_HH
#define G4QTHD_HH

#include "globals.hh"
#include "Randomize.hh"
#include "G4ThreeVector.hh"

inline G4double G4QThd(G4int i) // Restricted accuracy only for physivcs
{
 //  0       1         2        3        4        5       6         7         8      9
 static G4double t[270]={0.,1.,1.25992,1.44225,1.5874,1.70998,1.81712,1.91293, 2., 2.08008,
  2.15443, 2.22398, 2.28943, 2.35133, 2.41014, 2.46621, 2.51984, 2.57128, 2.62074, 2.66840,
  2.71442, 2.75892, 2.80204, 2.84387, 2.88450, 2.92402, 2.96250, 3.00000, 3.03659, 3.07232,
  3.10723, 3.14138, 3.17480, 3.20753, 3.23961, 3.27107, 3.30193, 3.33222, 3.36198, 3.39121,
  3.41995, 3.44822, 3.47603, 3.50340, 3.53035, 3.55689, 3.58305, 3.60883, 3.63424, 3.65931,
  3.68403, 3.70843, 3.73251, 3.75629, 3.77976, 3.80295, 3.82586, 3.84850, 3.87088, 3.89300,
  3.91487, 3.93650, 3.95789, 3.97906, 4.00000, 4.02073, 4.04124, 4.06155, 4.08166, 4.10157,
  4.12129, 4.14082, 4.16017, 4.17934, 4.19834, 4.21716, 4.23582, 4.25432, 4.27266, 4.29084,
  4.30887, 4.32675, 4.34448, 4.36207, 4.37952, 4.39683, 4.41400, 4.43105, 4.44796, 4.46475,
  4.48140, 4.49794, 4.51436, 4.53065, 4.54684, 4.56290, 4.57886, 4.59470, 4.61044, 4.62607,
  4.64159, 4.65701, 4.67233, 4.68755, 4.70267, 4.71769, 4.73262, 4.74746, 4.76220, 4.77686,
  4.79142, 4.80590, 4.82028, 4.83459, 4.84881, 4.86294, 4.87700, 4.89097, 4.90487, 4.91868,
  4.93242, 4.94609, 4.95968, 4.97319, 4.98663, 5.00000, 5.01330, 5.02653, 5.03968, 5.05277,
  5.06580, 5.07875, 5.09164, 5.10447, 5.11723, 5.12993, 5.14256, 5.15514, 5.16765, 5.18010,
  5.19249, 5.20483, 5.21710, 5.22932, 5.24148, 5.25359, 5.26564, 5.27763, 5.28957, 5.30146,
  5.31329, 5.32507, 5.33680, 5.34848, 5.36011, 5.37169, 5.38321, 5.39469, 5.40612, 5.41750,
  5.42884, 5.44012, 5.45136, 5.46256, 5.47370, 5.48481, 5.49586, 5.50688, 5.51785, 5.52877,
  5.53966, 5.55050, 5.56130, 5.57205, 5.58277, 5.59344, 5.60408, 5.61467, 5.62523, 5.63574,
  5.64622, 5.65665, 5.66705, 5.67741, 5.68773, 5.69802, 5.70827, 5.71848, 5.72865, 5.73879,
  5.74890, 5.75897, 5.76900, 5.77900, 5.78896, 5.79889, 5.80879, 5.81865, 5.82848, 5.83827,
  5.84804, 5.85777, 5.86746, 5.87713, 5.88677, 5.89637, 5.90594, 5.91548, 5.92499, 5.93447,
  5.94392, 5.95334, 5.96273, 5.97209, 5.98142, 5.99073, 6.00000, 6.00925, 6.01846, 6.02765,
  6.03681, 6.04594, 6.05505, 6.06413, 6.07318, 6.08220, 6.09120, 6.10017, 6.10911, 6.11803,
  6.12693, 6.13579, 6.14463, 6.15345, 6.16224, 6.17101, 6.17975, 6.18846, 6.19715, 6.20582,
  6.21447, 6.22308, 6.23168, 6.24025, 6.24880, 6.25732, 6.26583, 6.27431, 6.28276, 6.29119, 
  6.29961, 6.30799, 6.31636, 6.32470, 6.33303, 6.34133, 6.34960, 6.35786, 6.36610, 6.37431,
  6.38250,6.39068, 6.39883, 6.40696, 6.41507, 6.42316, 6.43123, 6.43928, 6.44731, 6.45531};
 if(i>0 && i<270) return t[i];
 return 0.;
}

#endif  /* G4QTHD_HH */
