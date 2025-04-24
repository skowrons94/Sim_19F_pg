import os
import sys
import docker

from tqdm import tqdm

macro = "19F_pg"
transitions = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"] 

pwd = os.getcwd()

# Example usage
if __name__ == "__main__":

    for transition in tqdm( transitions ):
    
        os.system("cp {}/data/RadiativeCapture/proton/z10.a20_{} {}/data/RadiativeCapture/proton/z10.a20".format(pwd, transition, pwd))
    
        # Create a Docker client
        docker_client = docker.from_env()
    
        # Define the command to run inside the container
        cmd  = "bash -c 'source /usr/local/root/bin/thisroot.sh && "
        cmd += "source /usr/local/geant4/bin/geant4.sh && " 
        cmd += "export G4RADIATIVECAPTURE=/data/RadiativeCapture && "
        cmd += "export G4LENDDATA=/data/LEND_GND1.3_ENDF.BVII.1 && "
        cmd += "export G4PARTICLEHPDATA=/data/G4TENDL1.4 && "
        cmd += "export G4PARTICLEXSDATA=/data/G4PARTICLEXS4.0 && "
        cmd += "export G4LEVELGAMMADATA=/data/PhotonEvaporation5.7 && "
        cmd += "export G4RADIOACTIVEDATA=/data/RadioactiveDecay5.6 && "
        cmd += "./SimLUNA -m /workdir/macros/run_" + macro + ".mac -s 0'"
    
        print(cmd)

    #    # Run the container
    #    container = docker_client.containers.run(
    #        "simluna",
    #        cmd,
    #        volumes={
    #            "{}/macros/".format(pwd): {"bind": "/workdir/macros/", "mode": "rw"},
    #            "{}/rootfiles/".format(pwd): {"bind": "/workdir/rootfiles/", "mode": "rw"},
    #            "{}/data/".format(pwd): {"bind": "/data/", "mode": "rw"}
    #        },
    #        remove=True,
    #        detach=False
    #    )
    #
    #    filename = "{}_{}.root".format(macro, transition)
    #    os.system("mv {}/rootfiles/SimLUNA.root {}/rootfiles/{}".format(pwd, pwd, filename))

    #macro = "19F_pag"
    #transitions = ["1", "2", "3", "4"]
    #
    #for transition in tqdm( transitions ):
    #
    #    cmd = "zlib-flate -compress < data/G4TENDL1.4/Proton/Inelastic/F27/9_19_Fluorine_a{} > data/G4TENDL1.4/Proton/Inelastic/F27/9_19_Fluorine.z".format(transition)
    #
    #    os.system(cmd)
    #
    #    # Create a Docker client
    #    docker_client = docker.from_env()
    # 
    #    # Define the command to run inside the container
    #    cmd  = "bash -c 'source /usr/local/root/bin/thisroot.sh && "
    #    cmd += "source /usr/local/geant4/bin/geant4.sh && " 
    #    cmd += "export G4RADIATIVECAPTURE=/data/RadiativeCapture && "
    #    cmd += "export G4LENDDATA=/data/LEND_GND1.3_ENDF.BVII.1 && "
    #    cmd += "export G4PARTICLEHPDATA=/data/G4TENDL1.4 && "
    #    cmd += "export G4PARTICLEXSDATA=/data/G4PARTICLEXS4.0 && "
    #    cmd += "export G4LEVELGAMMADATA=/data/PhotonEvaporation5.7 && "
    #    cmd += "export G4RADIOACTIVEDATA=/data/RadioactiveDecay5.6 && "
    #    cmd += "export G4NEUTRONHPDATA=/data/G4NDL4.6 && "
    #    cmd += "./SimLUNA -m /workdir/macros/run_" + macro + ".mac -s 0'"
    #
    #    print(cmd)
    #
    #    # Run the container
    #    container = docker_client.containers.run(
    #        "simluna",
    #        cmd,
    #        volumes={
    #            "{}/macros/".format(pwd): {"bind": "/workdir/macros/", "mode": "rw"},
    #            "{}/rootfiles/".format(pwd): {"bind": "/workdir/rootfiles/", "mode": "rw"},
    #            "{}/data/".format(pwd): {"bind": "/data/", "mode": "rw"}
    #        },
    #        remove=True,
    #        detach=False
    #    )
    #
    #    filename = "{}_{}.root".format(macro, transition)
    #    os.system("mv {}/rootfiles/SimLUNA.root {}/rootfiles/{}".format(pwd, pwd, filename))

    #macro = "11B_pg"
    #transitions = ["0", "1"]
    #
    #for transition in tqdm( transitions ):
    #
    #    os.system("cp {}/data/RadiativeCapture/proton/z6.a12_{} {}/data/RadiativeCapture/proton/z6.a12".format(pwd, transition, pwd))
    #
    #    # Create a Docker client
    #    docker_client = docker.from_env()
    #
    #    # Define the command to run inside the container
    #    cmd  = "bash -c 'source /usr/local/root/bin/thisroot.sh && "
    #    cmd += "source /usr/local/geant4/bin/geant4.sh && " 
    #    cmd += "export G4RADIATIVECAPTURE=/data/RadiativeCapture && "
    #    cmd += "export G4LENDDATA=/data/LEND_GND1.3_ENDF.BVII.1 && "
    #    cmd += "export G4PARTICLEHPDATA=/data/G4TENDL1.4 && "
    #    cmd += "export G4PARTICLEXSDATA=/data/G4PARTICLEXS4.0 && "
    #    cmd += "export G4LEVELGAMMADATA=/data/PhotonEvaporation5.7 && "
    #    cmd += "export G4RADIOACTIVEDATA=/data/RadioactiveDecay5.6 && "
    #    cmd += "./SimLUNA -m /workdir/macros/run_" + macro + ".mac -s 0'"
    #
    #    # Run the container
    #    container = docker_client.containers.run(
    #        "simluna",
    #        cmd,
    #        volumes={
    #            "{}/macros/".format(pwd): {"bind": "/workdir/macros/", "mode": "rw"},
    #            "{}/rootfiles/".format(pwd): {"bind": "/workdir/rootfiles/", "mode": "rw"},
    #            "{}/data/".format(pwd): {"bind": "/data/", "mode": "rw"}
    #        },
    #        remove=True,
    #        detach=False
    #    )
    #
    #    filename = "{}_{}.root".format(macro, transition)
    #    os.system("mv {}/rootfiles/SimLUNA.root {}/rootfiles/{}".format(pwd, pwd, filename))