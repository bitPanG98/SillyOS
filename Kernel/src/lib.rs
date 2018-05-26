#![no_std]
#![feature(lang_items)]

#[macro_use]
extern crate x86;
#[macro_use]
extern crate rlibc;

mod boot;

#[no_mangle]
pub extern fn kinit(VERY_UNSAFE_SHIT: *const boot::BootInformation){
    //Making something dangerous to safe by blind our fucking eyes
    let boot_info: &boot::BootInformation = unsafe{&*VERY_UNSAFE_SHIT};
    let video_info: &boot::VideoInformation = unsafe{&*boot_info.VideoInfo};
    let frame_buffer = unsafe{&mut *video_info.FrameBufferBase};
    unsafe{rlibc::memset(frame_buffer, 0xff, video_info.FrameBufferSize as usize);}
    loop{}
}

#[lang = "eh_personality"] #[no_mangle] pub extern fn eh_personality() {}
#[lang = "panic_fmt"] #[no_mangle] pub extern fn panic_fmt() -> ! {loop{}}
