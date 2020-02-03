git clone https://chromium.googlesource.com/chromium/tools/depot_tools.git
export PATH=$PATH:`pwd`/depot_tools
gclient config https://github.com/utah-scs/v8.git
gclient sync
cd v8
sudo apt-get update
./build/install-build-deps.sh
git clone https://gn.googlesource.com/gn
wget https://github.com/ninja-build/ninja/releases/download/v1.9.0/ninja-linux.zip
unzip ninja-linux.zip
sudo cp ninja /usr/local/bin/
sudo apt-get install clang
cd gn
python build/gen.py
sudo ninja -C out
sudo cp out/gn /usr/local/bin/
cd ../
./tools/dev/gm.py x64.release
cd ../
