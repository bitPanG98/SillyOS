extern crate rlibc;

pub mod EDID;

pub struct Video {
    pub max_x: u32,    //unit: Pixel
    pub max_y: u32,
    pub pixel_size: u8,    //unit: Byte
    pub red_index: u8,
    pub green_index: u8,
    pub blue_index: u8,
    pub frame_buffer: u64,
    pub frame_buffer_size: u64, //unit: Pixel

}

impl Video {

    pub fn plot(&self, x: u32, y: u32, color: u32) {
        if x < 0 || x > self.max_x {return;}
        
        let offset =  (y * self.max_x + x) * self.pixel_size as u32;
        if offset as u64 > self.frame_buffer_size {return;}

        let buffer = self.frame_buffer + offset as u64;
        let red = (color & 0xff0000) >> 16;
        let green = color & 0xff00 >> 8;
        let blue = color & 0xff;
        unsafe{
            rlibc::memset((buffer + self.blue_index as u64) as *mut u8, blue as i32, 1);
            rlibc::memset((buffer + self.green_index as u64) as *mut u8, green as i32, 1);
            rlibc::memset((buffer + self.red_index as u64) as *mut u8, red as i32, 1);
        }
    }

    pub fn splash_screen(&self, color: u32) {
        for y in 0..self.max_y {
            for x in 0..self.max_x {
                self.plot(x, y, color);
            }
        }
    }

}
