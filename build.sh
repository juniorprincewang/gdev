cmake -H. -Brelease \
    -Ddriver=nouveau \
    -Duser=ON \
    -Druntime=ON \
    -Dusched=OFF \
    -Duse_as=OFF \
    -DCMAKE_BUILD_TYPE=Release
make -C release
sudo make -C release install
