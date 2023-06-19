# Arena (Atomic Reconstruction of RNA)

Arena is a stand-alone program used for the full-atomic reconstruction of RNA structures from coarse-grained models. Arena can build in full-atomic detail for any residue with at least one heavy atom (of any identity). Arena takes an input in PDB format and first fills in the missing heavy atoms via superimposition. Arena iterates through three refinement steps to correct bond lengths and angles, correct base and base pair conformations, and remove atomic clashes. Structures generated by Arena are highly accurate in terms of RMSD (< 3.7 Å on average), contain almost no clashes, and run in < 3.5 sec on average. The runtime increases linearly with the length of the RNA; the longest RNA we tested was 692 nt and ran in < 35 sec. Arena can be downloaded from here and run locally or run via the [Arena webserver](https://zhanggroup.org/Arena/). We have provided example PDB structures to run with Arena in the "Examples" folder.

## Installation

Download Arena from GitHub into your desired location, such as your Desktop:
```
git clone https://github.com/pylelab/Arena.git
```

In the new Arena folder, compile with Clang:
```
cd Arena
make Arena
```

## Usage

Running Options:

The default Arena option (5) removes nonstandard atoms, fills in missing atoms for any residues with at least one input atom, and iteratively refines the placement of added atoms (no input atoms are moved). All benchmarking was performed with this option, and most users will find this option suitable for their needs.

The extended Arena option (7) first performs the default Arena run. Should there be any unresolved issues with the structure (discontinuous nucleotides or poor performance metrics), Arena will perform additional rounds of refinement, where the input atoms are also moved.

Additional running options are described below:
```
0 - only check missing atoms
1 - remove non-standard atoms
2 - remove non-standard atoms and residues with missing atoms
3 - remove non-standard atoms, fill atoms for residues with at least three atoms
4 - remove non-standard atoms, fill atoms for residues with at least three atoms, remove residues with less than three atoms
5 - (default) remove non-standard atoms, fill atoms for residues with at least one atom
7 - (extended) remove non-standard atoms, fill atoms for residues with at least one atom, (even for preexisting atoms) fix conformation
```

Run Arena (default) using one of the provided examples:
```
./Arena Examples/5osg2.P.pdb Examples/5osg2.output.pdb 5
```

To see the help menu:
```
./Arena
```
Note: If the RNA is interacting with other molecules (proteins, ligands, etc), the user must manually remove the non-RNA chains for the Arena standalone program. Arena can, however, handle multichain RNA inputs without user intervention (see Multiple Models below). On the other hand, the [Arena webserver](https://zhanggroup.org/Arena/) automatically excludes non-RNA residues.

## Special Case: Multiple Models

Split into separate model files, run Arena on individual models, and combine the output into one structure:
```
python3 split_models.py Examples/2koc.pdb Examples/2koc.output.pdb
```

## Benchmarking Scripts

Calculate root-mean-square-deviation (RMSD):
```
python calculate_RMSD.py -r Examples/5osg2.pdb -i Examples/5osg2.output.pdb
```

Calculate interaction network fidelity (INF):
```
python3 RNA_assessment/INF.py RNA_assessment/example/5osg2.pdb RNA_assessment/example/5osg2.index RNA_assessment/example/5osg2.output.pdb RNA_assessment/example/5osg2.index
```
Note: For calculation of INF, the PDB files must contain a chain ID and be within the example directory of [RNA_assessment](https://github.com/RNA-Puzzles/RNA_assessment/tree/master). 

Calculate number of clashes:
```
make Arena_counter
./Arena_counter Examples/5osg2.output.pdb Examples/5osg2.clashes.txt 5
```

Calculate mean absolute error (MAE):
```
python calculate_MAE.py -r Examples/5osg2.pdb -i Examples/5osg2.output.pdb
```

## Reference
Zion R Perry, Anna Marie Pyle, Chengxin Zhang (2023)
Arena: rapid and accurate reconstruction of full atomic RNA structures from coarse-grained models.

