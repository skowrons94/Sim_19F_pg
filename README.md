# Sim_19F_pg

This repository contains simulation code related to the study of the \(^{19}\)F(p,γ) reaction. The project includes source code, macros, and scripts to build and run the simulations.

## Repository Structure

- **code/**: Contains the main SimLUNA source code for the simulation.
- **macros/**: Includes macro files used to control various aspects of the simulation.
- **.gitignore**: Specifies files and directories to be ignored by Git.
- **Dockerfile**: Defines a Docker container for the simulation environment.
- **build.sh**: Shell script to build the simulation code.
- **enter.sh**: Shell script to enter the inside the docker.
- **run.py**: Python script to execute the simulation.

## Getting Started

To set up and run the simulation:

1. **Build the Simulation Code**:
   ```bash
   ./build.sh
   ```
   This script compiles the source code located in the `code/` directory.

3. **Run the Simulation**:
   ```bash
   python run.py
   ```
   This Python script executes the simulation using the compiled code and specified macros.

If a newer version of SimLUNA is being used, substitute it in the ```code/``` directory. Additionally, provide a ```data/``` folder as described in the SimLUNA documentation.

## Contributing

Contributions to enhance the simulation code, add new features, or improve documentation are welcome. Please fork the repository and submit a pull request with your changes.