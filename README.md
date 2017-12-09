# SillyOS
A silly operating system written in C and Rust.


## How to run SillyOS?

## Getting error when building EDK2 tools?
'''bash
error sections
'''
Go patch your edk2 Makefile with 
'''bash
$ patch  /<path of your edk2 dir>/BaseTools/Source/C/Makefiles/headers.makefile\
./Stuff/edk2_fix.patch
'''