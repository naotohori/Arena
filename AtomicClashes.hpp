/* Purpose: Fix atomic clashes */

#ifndef AtomicClashes_HPP
#define AtomicClashes_HPP 1

#include <math.h>
#include <stdbool.h>
#include <vector>
#include <cstdlib>
#include <string>
#include <cstring>
#include <fstream>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>

#include "GeometryTools.hpp"

using namespace std;

// The order of each array is the standard PDB order, with hydrogen atoms omitted. VDW radii are in units of Angstroms.

// A
// Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3' C2' O2' C1' N9 C8 N7 C5 C6 N6 N1 C2 N3 C4
float A_vdw[22] = {1.8, 1.52, 1.52, 1.52, 1.7, 1.7, 1.52, 1.7, 1.52, 1.7, 1.52, 1.7, 1.55, 1.7, 1.55, 1.7, 1.7, 1.55, 1.55, 1.7, 1.55, 1.7};

// C
// Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3' C2' O2' C1' N1 C2 O2 N3 C4 N4 C5 C6
float C_vdw[20] = {1.8, 1.52, 1.52, 1.52, 1.7, 1.7, 1.52, 1.7, 1.52, 1.7, 1.52, 1.7, 1.55, 1.7, 1.52, 1.55, 1.7, 1.55, 1.7, 1.7};

// G
// Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3' C2' O2' C1' N9 C8 N7 C5 C6 O6 N1 C2 N2 N3 C4
float G_vdw[23] = {1.8, 1.52, 1.52, 1.52, 1.7, 1.7, 1.52, 1.7, 1.52, 1.7, 1.52, 1.7, 1.55, 1.7, 1.55, 1.7, 1.7, 1.52, 1.55, 1.7, 1.55, 1.55, 1.7};

// U
// Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3' C2' O2' C1' N1 C2 O2 N3 C4 O4 C5 C6
float U_vdw[20] = {1.8, 1.52, 1.52, 1.52, 1.7, 1.7, 1.52, 1.7, 1.52, 1.7, 1.52, 1.7, 1.55, 1.7, 1.52, 1.55, 1.7, 1.52, 1.7, 1.7};


int fix_clashes (ModelUnit &pep){
	
	// Initialize variables
	float vdw1 = 0;
	float vdw2 = 0;

	int moved = 0;

	// OSP
	// Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3'
	float OSP_bonds[9][4] = {
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{0, 0, 0, 0},
		{2.648, 0, 0, 0},
		{1.610, 2.505, 2.505, 2.504}
	};

 	// Iterate through chains
	for (int c1=0; c1<pep.chains.size(); c1++){
		for (int c2=c1; c2<pep.chains.size(); c2++){	
			// Iterate through residues
			for (int r1=0; r1<pep.chains[c1].residues.size(); r1++){
				string resname1 = pep.chains[c1].residues[r1].resn;
				int resnumber1 = pep.chains[c1].residues[r1].resi;
				for (int r2=0; r2<pep.chains[c2].residues.size(); r2++){
					string resname2 = pep.chains[c2].residues[r2].resn;
					int resnumber2 = pep.chains[c2].residues[r2].resi;
					// check each combination of r1 and r2 only once
					if (c1 == c2 && r1 >= r2) continue;
						// Iterate through all pairs of atoms
						for (int a1=0; a1<pep.chains[c1].residues[r1].atoms.size(); a1++){
							string atom1 = pep.chains[c1].residues[r1].atoms[a1].name;
							for (int a2=0; a2<pep.chains[c2].residues[r2].atoms.size(); a2++){
								string atom2 = pep.chains[c2].residues[r2].atoms[a2].name;
								// don't check OSP bonds
								if (r1+1==r2 && c1==c2 && a1 < 9 && a2 < 4 && OSP_bonds[a1][a2] > 0) continue;
									// Get the VDW radius of each atom in the pair
				 					if (resname1 == "  A"){
				 						vdw1 = A_vdw[a1];
				 					} else if (resname1 == "  C"){
				 						vdw1 = C_vdw[a1];
				 					} else if (resname1 == "  G"){
				 						vdw1 = G_vdw[a1];
				 					} else if (resname1 == "  U"){
				 						vdw1 = U_vdw[a1];
				 					}
				 					if (resname2 == "  A"){
				 						vdw2 = A_vdw[a2];
				 					} else if (resname2 == "  C"){
				 						vdw2 = C_vdw[a2];
				 					} else if (resname2 == "  G"){
				 						vdw2 = G_vdw[a2];
				 					} else if (resname2 == "  U"){
				 						vdw2 = U_vdw[a2];
				 					}
				 					// calculate the clash distance
				 					float c = vdw1 + vdw2 - 0.4;
				 					// Get (x,y,z) coordinates
									float a1x = pep.chains[c1].residues[r1].atoms[a1].xyz[0];
									float a1y = pep.chains[c1].residues[r1].atoms[a1].xyz[1];
									float a1z = pep.chains[c1].residues[r1].atoms[a1].xyz[2];
									float a2x = pep.chains[c2].residues[r2].atoms[a2].xyz[0];
									float a2y = pep.chains[c2].residues[r2].atoms[a2].xyz[1];
									float a2z = pep.chains[c2].residues[r2].atoms[a2].xyz[2];
									// Calculate the atomic distance
									float d = sqrt((a2x-a1x)*(a2x-a1x) + (a2y-a1y)*(a2y-a1y) + (a2z-a1z)*(a2z-a1z));
					
									// Compare the atomic and clash distances
				 					if (d < c){
				 						cout << "clash" << resname1 << resnumber1 << atom1 << resname2 << resnumber2 << atom2 << "distance= " << d << ' ' << "vdw= " << c << endl;
				 						moved++;
				 					}
				 			}
				 		}
 				}
 			}
 		}
 	}
 	return moved;
}

#endif