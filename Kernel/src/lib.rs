#![no_std]
#![feature(lang_items)]
mod boot;
extern crate rlibc;
#[no_mangle]
pub unsafe extern "C" fn kernel_init(info: *const boot::BootloadInformation) {
     let video_info = (*info).VideoInfo;
     let max_x = (*video_info).MaxX;
     let mut base = (*video_info).FrameBufferBase as *mut u32;

        let mut i: u32 = 0;
        while i < max_x {
            rlibc::memset(((*video_info).FrameBufferBase + (i*4)as u64) as *mut u8, 0xff00ff, 1);
            i +=1;
        }
     
     loop {}
}

#[lang = "eh_personality"]
#[no_mangle]
pub extern "C" fn eh_personality() {}

#[lang = "panic_fmt"]
#[no_mangle]
pub extern "C" fn panic_fmt() {}
