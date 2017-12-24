#![feature(asm)]
#![allow(non_snake_case)]
#![allow(non_camel_case_types)]
#![no_std]
extern crate x86;
use x86::current;

pub mod APIC;
pub mod ACPI;
pub mod Paging;

//EFI only
#[cfg(feature = "efi")]
pub mod EFI;
#[cfg(feature = "efi")]
pub fn platform_init(contents: EFI::BootContents){


}

//Non-EFI
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