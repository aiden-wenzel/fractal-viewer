git submodule init
git submodule update
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev
mkdir -p build
cd build
cmake ..
make
