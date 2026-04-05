A GEANT4 application to simulate the interaction of galactic cosmic rays with a 2U CubeSat in low earth orbit, specifically TRACE by TUDSaT e.V. [TUDSaT](https://tudsat.space/)

# Preliminary Satellite Trajectory
The preliminary satellite trajectory is defined as a circular, sun-synchronous orbit at an altitude of 520 km with an inclination of 97.48°, LTAN of 6:00 CEST and mission duration of 1 year from 2027-01-01 to 2028-01-01.

# Geometry
The geometry of the CubeSat is defined in the `DetectorConstruction` class. 
The CubeSat is modeled as a rectangular box with dimensions 10 cm x 10 cm x 20 cm, made of a space-grade aluminum alloy.
The interior of the CubeSat is filled with vacuum. Inside the satellite is a tube, which is designed to measure the flux of charged particles. 
The tube has a diameter of 12 mm and a length of 22 mm, and is made of copper with a thickness of 1 mm (thickness not accurate).

For testing purposes, the tube is currently made out of bone (G4_BONE_COMPACT_ICRU) and filled with brain tissue (G4_BRAIN_ICRP) to measure GCR effects on human tissue.

# Physics List
The physics list was chosen to be the 'QBBC' reference physics list, 
which is commonly used for space radiation simulations as it accurate results for low-energy transport of protons and works well with thin target experiments. 
See [QBBC](https://geant4.web.cern.ch/documentation/dev/plg_html/PhysicsListGuide/reference_PL/QBBC.html) and [Ivantchenko](https://pubmed.ncbi.nlm.nih.gov/21830895/).

# Primary Generator
The primary generator is defined in the `PrimaryGeneratorAction` class as a general particle source (GPS) that generates protons (84%), alpha particles (14%) and electrons (2%) with energies sampled from respective energy distributions. 
The distributions for protons and alpha particles were derived from SPENVIS, a web-based tool for space environment modeling and analysis (see [SPENVIS](https://www.spenvis.oma.be/)). 
For electrons, the distribution was taken from the Cosmic-Ray Database (CRDB) (see [CRDB](https://lpsc.in2p3.fr/crdb/), parameters: Solar Moodulation -> Ghelfi et al. (2017)).
For both data sources two python scripts (convert_spenvis_to_text.py, convert_crdb_to_text.py) are used to extract the relevant data and convert it into a format suitable for use in the GEANT4 simulation.

# Output
The output of the simulation is stored in a ROOT (analysis_gcr.root) file, which contains the energy deposition in the tube  itself and the tube filling for each event, as well as the track length for both sensitive areas, the event ID and the particle type of the detector hit. 
This allows for detailed analysis of the radiation environment inside the CubeSat and the potential effects on the tube and its contents.


# Running the Simulation
```bash
mkdir build && cd build
cmake ..
make
```
Interaction mode (Visualization):
```bash
./sim
```
Batch mode (no visualization):
```bash 
./sim [particle source macro file]
```

# ROOT - Data Analysis
A ROOT macro file (root_analysis.cc) is provided to analyze the output ntuples from the simulation.

To run: 
```bash
source /path/to/root/install/bin/thisroot.sh
g++ -o root_analysis root_analysis.cc `root-config --cflags --libs`
./root_analysis
```

# TODO
- Implement the actual geometry of the tube and its contents (currently modeled as bone and brain tissue for testing purposes).
- Implement the actual energy distributions for protons, alpha particles and electrons based on SPENVIS and CRDB data.
- Refine satellite trajectory and orbital parameters based on more detailed mission parameters.
- Include earth magnetic field effects in the simulation to account for the deflection of charged particles and the resulting changes in the radiation environment.
- Validate the physics list and primary generator against experimental data or other simulations to ensure accuracy.
- Consider implementing additional features such as secondary particle production, shielding effects, and the impact of solar activity on the radiation environment.
- Optimize the simulation for computational efficiency, potentially by implementing variance reduction techniques or parallel processing.