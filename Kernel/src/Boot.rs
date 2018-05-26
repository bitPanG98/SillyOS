const MAGIC: u32 = 0x1a2b3c4d;
const PLATFORM_EFI: u8 = 0x1;
const CONTENT_VERSION: u8 = 0x1;

#[repr(C, packed)]
#[derive(Debug)]
pub struct VideoInformation {
    pub Checksum: u32,
    pub Height: u32,
    pub Width: u32,
    pub FrameBufferBase: *mut u8,
    pub FrameBufferSize: u64,
    pub PixelSize: u8,
    pub RedIndex: u8,
    pub GreenIndex: u8,
    pub BlueIndex: u8
}

#[repr(C, packed)]
#[derive(Debug)]
pub struct BootInformation {
    pub Magic: u32,
    pub Platform: u8,
    pub Checksum: u32,
    pub Version: u8,
    pub KernelAddress: u64,
    pub KernelSize: u64,
    pub VideoInfo: *mut VideoInformation,
    pub MemoryMap: *mut u8,
    pub MemoryMapSize: u64,
    pub MemoryDescriptorSize: u64,
    pub RSDP: *mut u8,
    pub RuntimeServices: *const u8
}
