Based on the available information from the repository [Sim_19F_pg](https://github.com/skowrons94/Sim_19F_pg), here is a suggested `README.md` file:

```markdown
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

2. **Enter the Simulation Environment**:
   ```bash
   ./enter.sh
   ```
   This script sets up the necessary environment for running the simulation.

3. **Run the Simulation**:
   ```bash
   python run.py
   ```
   This Python script executes the simulation using the compiled code and specified macros.

If a newer version of SimLUNA is being used, substitute it in the ```code/``` directory. Additionally, provide a ```data/``` folder as described in the SimLUNA documentation.

## Docker Support

A `Dockerfile` is provided to create a containerized environment for the simulation. This ensures consistency across different systems. To build and run the Docker container:

1. **Build the Docker Image**:
   ```bash
   docker build -t simluna .
   ```

2. **Run the Docker Container**:
   ```bash
   docker run -it simluna
   ```

Inside the container, you can use the provided scripts (`build.sh`, `enter.sh`, `run.py`) to build and run the simulation as described above.

## Contributing

Contributions to enhance the simulation code, add new features, or improve documentation are welcome. Please fork the repository and submit a pull request with your changes.