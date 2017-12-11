#![feature(asm)]

#![no_std]
pub mod APIC;
pub mod ACPI;
pub mod Paging;

pub fn donothing(){
    
}

#[inline]
//Less Jump Less Error
pub fn halt(){
    //shutdown interrupt
    unsafe asm!("cli" : : :);
    //Going~around~and around~
    loop{}
}