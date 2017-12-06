
//  Tell compiler we are not gonna use std library.
#![no_std]
//  'language item' is required.
#![feature(lang_items)]
// Dont bother my identifier naming OKAY?
#![allow(non_snake_case)]

#[cfg(target_arch = "x86_64")]
extern crate x86_64;

// Entry point of Core
#[no_mangle]
pub extern "C" fn entry() {
    // Call from Boot Loader
    x86_64::donothing();
    loop {

    }
}


///
/// Implementations 
///
//not sure what is it, but it is needed.
#[lang = "eh_personality"]
extern fn eh_personality() {
    // leave me alone!
}

//panic handling implementation
#[lang = "panic_fmt"]
#[no_mangle]
pub extern "C" fn panic_fmt() -> ! {
    //some panic handle code here.
    loop {

    }
}
