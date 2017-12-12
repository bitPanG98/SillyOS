
//  Tell compiler we are not gonna use std library.
#![no_std]
//  'language item' is required.
#![feature(lang_items)]
//  We would like to have some assembly :D
#![feature(asm)]
// Dont bother my identifier naming OKAY?
#![allow(non_snake_case)]

#[cfg(target_arch = "x86_64")]
extern crate x86_64;

// Entry point of Core
#[no_mangle]
//Assumed we got called by EFI, so we need a win64 call convention entry. 
pub extern "C" fn platform_rust_entry(magic: u32, table: *const u64) {
    // Call from Boot Loader
    if (magic != 0x1a2b3c4d){
        //  Wrong spell!
        x86_64::halt();
    }

    x86_64::halt();
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
