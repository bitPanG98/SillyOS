export PREFIX="$PWD/CC"
export LANGS=c,c++
export TARGET=x86_64-elf
export PATH="$PREFIX/bin:$PATH"

mkdir -p $PWD/CC
mkdir -p $PWD/CC/build-binutils
mkdir -p $PWD/CC/build-gcc

if [ ! -f "CC/binutils-*" ]
then
curl ftp://ftp.gnu.org/gnu/binutils/binutils-2.30.tar.gz | tar xz -C $PWD/CC
fi
if [ ! -f "CC/gcc-*" ]
then
curl ftp://ftp.gnu.org/gnu/gcc/gcc-7.3.0/gcc-7.3.0.tar.gz | tar xz -C $PWD/CC
fi

cd CC/build-binutils
../binutils-*/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
make install
cd ../build-gcc 

../gcc-*/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=$LANGS --without-headers
make all-gcc
make all-target-libgcc
make install-gcc
make install-target-libgcc
cd ../
rm -R build-*
rm -R binutils-*
rm -R gcc-*
