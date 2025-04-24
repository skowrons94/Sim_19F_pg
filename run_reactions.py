import os
import sys
import docker

from tqdm import tqdm

reactions = ["14N_pg", "27Al_pg"] 

pwd = os.getcwd()

# Example usage
if __name__ == "__main__":

    for reaction in tqdm( reactions ):
    
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
        cmd += "./SimLUNA -m /workdir/macros/run_" + reaction + ".mac -s 0'"

        # Run the container
        container = docker_client.containers.run(
            "simluna",
            cmd,
            volumes={
                "{}/macros/".format(pwd): {"bind": "/workdir/macros/", "mode": "rw"},
                "{}/rootfiles/".format(pwd): {"bind": "/workdir/rootfiles/", "mode": "rw"},
                "{}/data/".format(pwd): {"bind": "/data/", "mode": "rw"}
            },
            remove=True,
            detach=False
        )
    
        filename = "{}.root".format(reaction)
        print(cmd)
        os.system("mv {}/rootfiles/SimLUNA.root {}/rootfiles/{}".format(pwd, pwd, filename))