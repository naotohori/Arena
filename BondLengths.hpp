/* Purpose: Optimize bond lengths
Ideal bond lengths are taken from the Amber forcefield parameters.
The order of each array along both rows and columns is in the standard PDB order, with hydrogen atoms omitted.
*/

#ifndef BondLengths_HPP
#define BondLengths_HPP 1

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

// A
// Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3' C2' O2' C1' N9 C8 N7 C5 C6 N6 N1 C2 N3 C4
float A_bonds[22][22] = {
	{0, 1.48, 1.48, 1.598, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.598, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1.438, 0, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1.521, 0, 1.438, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1.521, 0, 0, 1.438, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1.521, 0, 0, 1.418, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1.418, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1.438, 0, 0, 1.521, 0, 0, 1.467, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.467, 0, 1.371, 0, 0, 0, 0, 0, 0, 0, 1.359},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.371, 0, 1.279, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.279, 0, 1.368, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.368, 0, 1.403, 0, 0, 0, 0, 1.373},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.403, 0, 1.363, 1.296, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.363, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.296, 0, 0, 1.319, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.319, 0, 1.319, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.319, 0, 1.342},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.359, 0, 0, 1.373, 0, 0, 0, 0, 1.342, 0}
};

// C
// Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3' C2' O2' C1' N1 C2 O2 N3 C4 N4 C5 C6
float C_bonds[20][20] = {
	{0, 1.48, 1.48, 1.598, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.598, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1.438, 0, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1.521, 0, 1.438, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1.521, 0, 0, 1.438, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1.521, 0, 0, 1.418, 1.521, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1.418, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1.438, 0, 0, 1.521, 0, 0, 1.467, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.467, 0, 1.386, 0, 0, 0, 0, 0, 1.372},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.386, 0, 1.229, 1.358, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.229, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.358, 0, 0, 1.296, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.296, 0, 1.363, 1.442, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.363, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.442, 0, 0, 1.344},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.372, 0, 0, 0, 0, 0, 1.344, 0}
};

// G
// Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3' C2' O2' C1' N9 C8 N7 C5 C6 O6 N1 C2 N2 N3 C4
float G_bonds[23][23] = {
	{0, 1.48, 1.48, 1.598, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.598, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1.438, 0, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1.521, 0, 1.438, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1.521, 0, 0, 1.438, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1.521, 0, 0, 1.418, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1.418, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1.438, 0, 0, 1.521, 0, 0, 1.467, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.467, 0, 1.371, 0, 0, 0, 0, 0, 0, 0, 0, 1.359},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.371, 0, 1.279, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.279, 0, 1.368, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.368, 0, 1.439, 0, 0, 0, 0, 0, 1.373},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.439, 0, 1.229, 1.389, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.229, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.389, 0, 0, 1.361, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.361, 0, 1.363, 1.296, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.363, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.296, 0, 0, 1.342},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.359, 0, 0, 1.373, 0, 0, 0, 0, 0, 1.342, 0}
};

// U
//Atomic order: P OP1 OP2 O5' C5' C4' O4' C3' O3' C2' O2' C1' N1 C2 O2 N3 C4 O4 C5 C6
float U_bonds[20][20] = {
	{0, 1.48, 1.48, 1.598, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.48, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{1.598, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 1.438, 0, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 1.521, 0, 1.438, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 1.521, 0, 0, 1.438, 1.521, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1.438, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 1.521, 0, 0, 1.418, 1.521, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 1.418, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 1.438, 0, 0, 1.521, 0, 0, 1.467, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.467, 0, 1.386, 0, 0, 0, 0, 0, 1.372},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.386, 0, 1.229, 1.389, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.229, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.389, 0, 0, 1.389, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.389, 0, 1.229, 1.466, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.229, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.466, 0, 0, 1.344},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1.372, 0, 0, 0, 0, 0, 1.344, 0}
};

// Bond between P and O3' of the previous residue
float OSP = 1.610;

void fix_bond_lengths (ModelUnit &pep, float tolerance){
	// Iterate through chains
	bool pass = false;
	float b_ideal = 0;
	int a2 = 0;
	for (int c=0; c<pep.chains.size(); c++){
		// Iterate through residues
		for (int r=0; r<pep.chains[c].residues.size(); r++){
			string resname = pep.chains[c].residues[r].resn;
			// if (resname == '  A'){
			// 	int res_int = 1;
			// } else if (resname == '  C'){
			// 	int res_int = 2;
			// } else if (resname == '  G'){
			// 	int res_int = 3;
			// } else {
			// 	int res_int = 4;
			// }
			// Iterate through all pairs of atoms
			for (int a1=0; a1<pep.chains[c].residues[r].atoms.size(); a1++){
				for (a2=a1+1; a2<pep.chains[c].residues[r].atoms.size();a2++){
					// switch (res_int){
						// Check if atoms are connected and, if so, save their ideal bond length
					if (resname == "  A"){
						if (A_bonds[a1][a2]>0){
							pass = true;
							b_ideal = A_bonds[a1][a2];
						}
					} else if (resname == "  C"){
						if (C_bonds[a1][a2]>0){
							pass = true;
							b_ideal = C_bonds[a1][a2];
						}
					} else if (resname == "  G"){
						if (G_bonds[a1][a2]>0){
							pass = true;
							b_ideal = G_bonds[a1][a2];
						}
					} else if (resname == "  U"){
						if (U_bonds[a1][a2]>0){
							pass = true;
							b_ideal = U_bonds[a1][a2];
						}
					}
				}
					if (pass){
						// Get (x,y,z) coordinates of each atom
						float a1x = pep.chains[c].residues[r].atoms[a1].xyz[0];
						float a1y = pep.chains[c].residues[r].atoms[a1].xyz[1];
						float a1z = pep.chains[c].residues[r].atoms[a1].xyz[2];
						float a2x = pep.chains[c].residues[r].atoms[a2].xyz[0];
						float a2y = pep.chains[c].residues[r].atoms[a2].xyz[1];
						float a2z = pep.chains[c].residues[r].atoms[a2].xyz[2];
						// Calculate the current bond length
						float b = sqrt((a2x-a1x)*(a2x-a1x) + (a2y-a1y)*(a2y-a1y) + (a2z-a1z)*(a2z-a1z));
						//Calculate fractional difference between the current and ideal bond lengths
						float diff = abs(b - b_ideal) / b_ideal;
						// Check if difference is greater than or equal to 10%. If so, this will need to be fixed.
						if (diff >= tolerance){
							cout<<diff<<endl;
							// If greater than 10%, move one atom closer by the calculated distance
						// If less than 10%, continue to the next atom
						}
				
					}
				}
			}
		}
	}
#endif
