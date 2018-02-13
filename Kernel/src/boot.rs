const Version: u8 = 0x1;
const Magic: u32 = 0x1a2b3c4d;

pub enum BitMaskInfomation {
    EFI_RGBR = 1,
    EFI_BGRR,
    BITMASK
}

pub enum Platform {
    Legacy = 1,
    EFI,
    Grub
}

#[repr(C, packed)]
pub struct VideoInfomation {
    pub Checksum: u64,
    pub VerticalResolution: u32,
    pub HorizontalResolution: u32,
    pub FrameBufferBase: u64,
    pub FrameBufferSize: u64,
    pub MaxX: u32,
    pub PixelType: u8,
    pub BitMask: u32
}

#[repr(C, packed)]
pub struct InfoHeader {
    pub Magic: u32,
    pub Platform: u8,
    pub Checksum: u64,
    pub Version: u8
}

#[repr(C, packed)]
pub struct BootloadInformation {
    pub Header: *const InfoHeader,
    
    pub KernelAddress: u64,
    pub KernelSize: u64,

    pub VideoInfo: *const VideoInfomation,

    pub MemoryMap: u64,
    pub MemoryMapSize: u64,
    pub DescriptorSize: u64,

    pub AcpiVersion: u8,
    pub RSDP: *const u64,

    pubRuntimeServices: *const u64 
}