# Building/Using Gdev with CMake

Follow the instruction below to use Gdev with OS runtime support. You
may be required to install additional software packages depending on
your environment. `$(TOPDIR)` represents your top working directory.

## 1. Download

Check out the Gdev\envytools\drm source code via `git`.

```sh
cd $(TOPDIR)
git clone git://github.com/juniorprincewang/gdev.git
git clone git://github.com/envytools/envytools.git
git clone https://gitlab.freedesktop.org/mesa/drm
```

## 2. envytools

[envytools](https://github.com/envytools/envytools/) is a rich set of open-source tools to compile or decompile
NVIDIA GPU program code, firmware code, macro code, and so on. It is
also used to generate C header files with GPU command definitions.
In addition, envytools document the NVIDIA GPU architecture details,
while are not disclosed to the public so far. If you are interested
in GPU system software development, this is what you should read!
Please follow the instruction below to install envytools.

Install dependencies:  
```sh
sudo apt-get install cmake flex libpciaccess-dev bison libx11-dev libxext-dev libxml2-dev libvdpau-dev python3-dev cython3
```

Build

```sh
cd $(TOPDIR)/envytools
mkdir build
cd build
cmake .. # may require some packages on your distro
make
sudo make install # will install tools to /usr/local/{bin,lib}
```

## 3. libdrm  

[libdrm](https://gitlab.freedesktop.org/mesa/drm) (Direct Rendering Manager) contains library and headers for user space nouveau driver.  
The library provides wrapper functions for the ioctls to avoid exposing the
kernel interface directly, and for chipsets with drm memory manager, support
for tracking relocations and buffers.
libdrm is a low-level library used by Gdev.  

Optional dependencies : `autoconf libboost-all-dev`

Build:  
```sh
cd $(TOPDIR)/
meson builddir/
ninja -C builddir/ install
```

## 4. Building Gdev

Gdev provides the build instruction with CMake.
Leveraging CMake, you can build/install Gdev and CUDA runtime.
The following options are supported.

| option | description | values |
| :-- | :-- | :-- |
| driver |select GPU driver. must set driver name in the user-space mode| `nouveau`,`pscnv`,`nvrm`,`barra` |
| user | user mode (default off) | ON/OFF |
| runtime | enable CUDA runtime API (default on)| ON/OFF |
| usched | enable user mode scheduler (default off)| ON/OFF |
| use\_as | use assembler (default off)| ON/OFF |

For example, you can pass the above options to CMake like below.  
Or you can just run `build.sh` script.

```sh
cmake -H. -Brelease \
    -Ddriver=nouveau \
    -Duser=ON \
    -Druntime=ON \
    -Dusched=OFF \
    -Duse_as=OFF \
    -DCMAKE_BUILD_TYPE=Release
make -C release
sudo make -C release install
```

This will mainly produce

1. user-space mode Gdev `libgdev.so` and
2. a limited set of CUDA Driver/Runtime API `libucuda.so`

`make` builds them with the specified options and they are installed under the directory `/usr/local/gdev`.

__CAUTION__:
Especially, the libraries are installed under the directory `/usr/local/gdev/lib64`.
So please remember to add `/usr/local/gdev/lib64` to `$LD_LIBRARY_PATH`.

## 5. Install Compiler  

Gdev takes nvidia-cuda-toolkit (nvcc) as its default CUDA compiler or Clang-CUDA.  


## 6. CUDA Driver API test (user-space programs)

You can build / test examples using CUDA Driver API. They are located under the directory `$(TOPDIR)/test/cuda/user/`.
Follow the instruction to build and use the examples.  
__NOTICE__:
Execute the test benchmark with root privilege.  

```sh
cd $(TOPDIR)/test/cuda/user/madd
make
sudo ./user_test 256 # a[256] + b[256] = c[256]
```
