#![no_std]
#![feature(lang_items)]
#[no_mangle]
pub extern "C" fn platform_init() {
     loop {}
}

#[lang = "eh_personality"]
pub extern "C" fn eh_personality() {}
#[lang = "panic_fmt"]
pub extern "C" fn panic_fmt() {}
