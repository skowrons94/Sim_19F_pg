FROM ubuntu:22.04

RUN apt-get update
RUN apt-get install -y wget git dpkg-dev cmake g++ \
    gcc binutils libx11-dev libxpm-dev \
    libxft-dev libxext-dev gfortran libssl-dev libpcre3-dev \
    xlibmesa-glu-dev libglew-dev libftgl-dev \
    libmysqlclient-dev libfftw3-dev libcfitsio-dev \
    graphviz-dev libavahi-compat-libdnssd-dev \
    libldap2-dev python3-dev libxml2-dev libkrb5-dev \
    libgsl0-dev libxerces-c-dev qtbase5-dev qt5-qmake \
    emacs vim nano 

RUN rm /bin/sh && ln -s /bin/bash /bin/sh

WORKDIR /tmp
RUN git clone https://github.com/root-project/root &&\
    cd root && git checkout v6-26-16 && cd - &&\
    mkdir root-build && cd root-build &&\
    cmake ../root &&\
    cmake --build . -- -j24 &&\
    cmake -DCMAKE_INSTALL_PREFIX=/usr/local/root -P cmake_install.cmake &&\
    cd .. && rm -r root-build && rm -fr root 

WORKDIR /tmp

RUN git clone https://github.com/Geant4/geant4 &&\
    cd geant4 && git checkout geant4-11.0-release && cd - &&\
    mkdir geant4-build && cd geant4-build &&\
    cmake \
        -DCMAKE_INSTALL_PREFIX=/usr/local/geant4 \
        -DGEANT4_INSTALL_DATA=ON \
        -DGEANT4_BUILD_MUONIC_ATOMS_IN_USE=ON \
        -DGEANT4_USE_SYSTEM_ZLIB=ON \
        -DGEANT4_USE_QT=ON \
        -DGEANT4_USE_GDML=ON \
        -DGEANT4_BUILD_MULTITHREADED=ON \
        ../geant4 &&\
    make -j24 &&\
    make install &&\
    cd .. && rm -r geant4-build && rm -r geant4

WORKDIR /workdir

# Set environment variables
RUN echo "source /usr/local/geant4/bin/geant4.sh" >> ~/.bashrc &&\
    echo "source /usr/local/root/bin/thisroot.sh" >> ~/.bashrc &&\
    echo "export G4RADIATIVECAPTURE=/data/RadiativeCapture" >> ~/.bashrc &&\
    echo "export G4LENDDATA=/data/LEND_GND1.3_ENDF.BVII.1" >> ~/.bashrc &&\
    echo "export G4PARTICLEHPDATA=/data/G4TENDL1.4" >> ~/.bashrc &&\
    echo "export G4PARTICLEXSDATA=/data/G4PARTICLEXS4.0" >> ~/.bashrc &&\
    echo "export G4LEVELGAMMADATA=/data/PhotonEvaporation5.7" >> ~/.bashrc &&\
    echo "export G4RADIOACTIVEDATA=/data/RadioactiveDecay5.6" >> ~/.bashrc &&\

# Copy SimLUNA
COPY code/ /workdir/code/

# Build SimLUNA
RUN source ~/.bashrc &&\
    cmake ./code &&\
    make -j24 &&\
    make install

# Clean the directory
RUN rm -r code CMakeCache.txt Makefile cmake_install.cmake CMakeFiles install_manifest.txt