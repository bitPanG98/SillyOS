/*
    Implementing EFI stuff
*/
extern crate x86;

#[repr(C)]
pub struct PixelBitmask {
    RedMask: u32,
    GreenMask: u32,
    BlueMask: u32,
    ReservedMask: u32
}

#[repr(C)]
pub enum ColorFormat {
    RGB_8,
    BGR_8,
    BIT_MASK,
    BLT,
    FORMAT_MAX
}

#[repr(C)]
pub struct EfiMemoryDescriptor {
    Type: u32,
    PhysStart: x86::current::paging::PAddr,
    VirtStart: x86::current::paging::PAddr,
    NumberOfPages: u64,
    Attribute: u64
}

pub const MIN_VERSION: u8 = 0x1a;
#[repr(C)]
pub struct BootContents {
    Platform: u8,
    Checksum: u32,
    Version: u8,
    //Kernel
    KernelAddress: x86::current::paging::PAddr,
    KernelSize: u64,
    //Video
    VideoHeight: u32,
    VideoWidth: u32,
    FrameBufferBase: x86::current::paging::PAddr,
    FrameBufferSize: x86::current::paging::PAddr,
    PixelPerScanLine: u64,
    ColorFormat: ColorFormat,
    Bitmask: PixelBitmask,
    //Memory
    MemoryMap: x86::current::paging::PAddr,
    MemoryMapSize: u64,
    MemoryDesSize: u64
}