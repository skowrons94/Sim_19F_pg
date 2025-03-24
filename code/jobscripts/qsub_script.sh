#PBS -V
#PBS -N SimLUNA
#PBS -S /bin/sh
#PBS -m a
#PBS -M xxx@yyy.zz
#PBS -q luna
#PBS -e localhost:/nfs/luna04/YOURDIRECTORY/gas_based-build/ER
#PBS -o localhost:/nfs/luna04/YOURDIRECTORY/gas_based-build/OU
source /nfs/luna04/GEANT4/geant4-v11.2.1-install/bin/geant4.sh
#/nfs/luna04/elekes-dev/gas_based-build/SimLUNA -m /nfs/luna04/elekes-dev/gas_based-build/macros/run.mac -u tcsh -s $SEED
/nfs/luna04/YOURDIRECTORY/BUILDDIRECTORY/SimLUNA -m /nfs/luna04/YOURDIRECTORY/BUILDDIRECTORY/macros/run.mac -u tcsh -s $SEED
