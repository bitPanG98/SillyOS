#![no_std]
#![feature(lang_items)]
mod boot;
mod Graphics;

extern crate rlibc;
#[no_mangle]
pub unsafe extern "C" fn kernel_init(info: *const boot::BootloadInformation) {
     let video_info = (*info).VideoInfo;
     let video = Graphics::Video{
            max_x: (*video_info).HorizontalResolution,
            max_y: (*video_info).VerticalResolution,
            pixel_size: (*video_info).PixelSize,
            red_index: (*video_info).RedIndex,
            green_index: (*video_info).GreenIndex,
            blue_index: (*video_info).BlueIndex,
            frame_buffer: (*video_info).FrameBufferBase,
            frame_buffer_size: (*video_info).FrameBufferSize
     };
    
    video.splash_screen(0xffffff);    
     
     loop {}
}

#[lang = "eh_personality"]
#[no_mangle]
pub extern "C" fn eh_personality() {}

#[lang = "panic_fmt"]
#[no_mangle]
pub extern "C" fn panic_fmt() {}
