#pragma once
#include <types.h>

namespace CPU::CPUID {
u32 get_cpu();
extern "C" void run_cpuid(u32 func, u32 *ax, u32 *bx, u32 *cx, u32 *dx);

enum CPU_VENDOR {
    UNKNOWN = 0,
    // Manufacturer
    EARLY_AMD,
    AMD,
    CENTAUR,
    CYRIX,
    INTEL,
    TRANSMETA,
    TRANSMETA_X86,
    NSC,
    NEX_GEN,
    RISE,
    SIS,
    UMC,
    VIA,
    VORTEX,
    // Virtual machine
    BHYVE,
    KVM,
    M$_HV,
    PARALLELS,
    VM_WARE,
    XEN_HVM
};

/*

    CPUID data below

*/
// When EAX = 1
typedef struct {
    u8 Stepping : 4;
    u8 Model : 4;
    u8 Family : 4;
    u8 Type : 2;
    u8 ExModel : 4;
    u8 ExFamily;
} __attribute__((packed)) CPUID_EAX_FEATURE_ONE;

typedef struct {
    u8 BrandID;
    u8 Chunks;
    u8 Count;
    u8 APIC_ID;
} __attribute__((packed)) CPUID_EBX_FEATURE_ONE;

typedef struct {
    u8 SSE3 : 1;
    u8 PCLMULDQ : 1;
    u8 DTES64 : 1;
    u8 MONITOR : 1;
    u8 DS_CPL : 1;
    u8 VMX : 1;
    u8 SMX : 1;
    u8 EIST : 1;
    u8 TM2 : 1;
    u8 SSSE3 : 1;
    u8 CNXT_ID : 1;
    u8 Reserved_bit11 : 1;
    u8 FMA : 1;
    u8 CX16 : 1;
    u8 xTPR : 1;
    u8 PDCM : 1;
    u8 Reserved_bit16 : 1;
    u8 PCID : 1;
    u8 DCA : 1;
    u8 SSE41 : 1;
    u8 SSE42 : 1;
    u8 x2APIC : 1;
    u8 MOVBE : 1;
    u8 POPCNT : 1;
    u8 TSC_DEADLINE : 1;
    u8 AES : 1;
    u8 XSAVE : 1;
    u8 OSXSAVE : 1;
    u8 AVX : 1;
    u8 F16C : 1;
    u8 RDRAND : 1;
    u8 ZERO : 1;
} __attribute__((packed)) CPUID_ECX_FEATURE_ONE;

typedef struct {
    u8 FPU : 1;
    u8 VME : 1;
    u8 DE : 1;
    u8 PSE : 1;
    u8 TSC : 1;
    u8 MSR : 1;
    u8 PAE : 1;
    u8 MCE : 1;
    u8 CX8 : 1;
    u8 APIC : 1;
    u8 Reserved_bit10 : 1;
    u8 SEP : 1;
    u8 MTRR : 1;
    u8 PGE : 1;
    u8 MCA : 1;
    u8 CMOV : 1;
    u8 PAT : 1;
    u8 PSE_36 : 1;
    u8 PSN : 1;
    u8 CLFSH : 1;
    u8 Reserved_bit20 : 1;
    u8 DS : 1;
    u8 ACPI : 1;
    u8 MMX : 1;
    u8 FXSR : 1;
    u8 SSE : 1;
    u8 SSE2 : 1;
    u8 SS : 1;
    u8 HTT : 1;
    u8 TM : 1;
    u8 Reserved_bit30 : 1;
    u8 PBE : 1;
} __attribute__((packed)) CPUID_EDX_FEATURE_ONE;

/*
    NDY
*/
}

namespace CPU::IO {
extern "C" u8 inb(u16 port);
extern "C" u16 inw(u16 port);
extern "C" u32 indw(u16 port);

extern "C" void outb(u16 port, u8 data);
extern "C" void outw(u16 port, u16 data);
extern "C" void outdw(u16 port, u32 data);
}
