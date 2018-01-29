# SillyOS
A silly operating system fulfills my dream.

## How to run SillyOS?
1. Install needed packages
    * APT side:
        * nasm
        * gcc (version: 5+)
        * rustc
        * git (A MUST HAVE PACKAGE FOR UNIX USER!)
        * make (I had tried tup, python, lua. And found out make is the best. :expressionless: )
        * mtools (For .iso image)
        * qemu (For testing)
        * ovmf (Also for testing)
    * Cargo side:
        * xargo

2. Type ``` make all ``` for full system compilation. 
3. Type ``` make run ``` for emulating at host's qemu or virtualbox. (NDY!)
## Something goes wrong!
<details>
<summary>Getting error when building EDK2 tools?</summary>
<p>If you received errors like: 

```bash
In file included from ../Include/Common/UefiBaseTypes.h:19:0,
                 from GenSec.c:20:
    /*
        A lot of details here... Gonna skip it anyway.
        The following error is the reason it failed.
        |   |   |   |   |   |   |   |   |
        v   v   v   v   v   v   v   v   v
    */
cc1: all warnings being treated as errors
../Makefiles/footer.makefile:27: recipe for target 'GenSec.o' failed
make[2]: *** [GenSec.o] Error 1
```

* Go patch your edk2 Makefile with:
```bash
$ patch  /<path of your edk2 dir>/BaseTools/Source/C/Makefiles/headers.makefile\
./Stuff/edk2_fix.patch
```
</p>
</details>

## Milestone
<!--Boot loader-->
<details>
<summary>Boot Loader</summary>
<p>
    -   [x] Get the boot loader prints something<br>
    -   [x] Change video mode<br>
    -   [x] Get memory map<br>
    -   [x] Loading Kernel to RAM<br>
    -   [ ] Fetch ACPI tables
    -   [ ] Pass control to Kernel with packed info.<br>
    -   [ ] Loading and install mods<br>
</p>
</details>
<!--PSC contents-->
<details>
<summary>Platform Specified Code(PSC)</summary>
<p>
    -   [ ] 
</p>
</details>
<!--Core-->
<details>
<summary>Core</summary>
<p>
    -   [ ]
</p>
</details>

Currently working on: ___PSC___ & __Boot Loader__