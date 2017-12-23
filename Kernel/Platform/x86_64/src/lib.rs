#![feature(asm)]

#![no_std]
extern crate x86;
pub mod APIC;
pub mod ACPI;
pub mod Paging;

//EFI only
#[cfg(feature = "efi")]
pub mod EFI;
#[cfg(feature = "efi")]
pub fn platform_init(contents: EFI::BootContents){


}

#[cfg(not(feature = "efi"))]
pub fn platform_init(){


}

#[inline(always)]
//Less Jump Less Error
pub fn halt(){
    //shutdown interrupt
    unsafe{
        asm!("cli" : : :);
    }
    //Going~around~and around~
    loop{}
}