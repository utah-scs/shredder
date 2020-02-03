git submodule update --init --recursive
sudo apt-get install -y build-essential linux-image-extra-virtual
cd seastar
./install-dependencies.sh
./configure.py --enable-dpdk --mode=release --c-compiler=gcc-5
ninja
cd ..
