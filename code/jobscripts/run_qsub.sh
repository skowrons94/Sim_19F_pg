rm ./ER/*.ER
rm ./OU/*.OU
rm ./rootfiles/SimLUNA.*.root
rm ./rootfiles/SimLUNA.root

for i in {1..100}
do
    SEED=$i LD_LIBRARY_PATH=/afs/lngs.infn.it/software/torque/almalinux9/lib64 /afs/lngs.infn.it/software/torque/almalinux9/bin/qsub -l mem=2gb ./jobscripts/qsub_script.sh
done
