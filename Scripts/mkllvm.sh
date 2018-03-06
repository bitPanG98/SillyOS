mkdir -p $PWD/cross-llvm/source
mkdir -p $PWD/cross-llvm/build/llvm

cd cross-llvm
if [ ! -f "source/llvm" ]
then
git clone  http://llvm.org/git/llvm.git source/llvm
fi

if [ ! -f "source/llvm/tools/clang" ]
then
git clone http://llvm.org/git/clang.git source/llvm/tools/clang
fi

if [ ! -f "source/llvm/projects/compiler-rt" ]
then
git clone http://llvm.org/git/compiler-rt.git source/llvm/projects/compiler-rt
fi

if [ ! -f "source/llvm/tools/lld" ]
then
git clone http://llvm.org/git/lld.git source/llvm/tools/lld
fi

cd build/llvm && cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$PWD/clang -DCMAKE_CXX_FLAGS="-std=c++11" -DLLVM_TARGETS_TO_BUILD="X86" ../../source/llvm && make && make install

# if [ ! -f "libcxx" ]
# then
# git clone http://llvm.org/git/libcxx.git libcxx
# fi

# cd libcxx/lib && 