#pragma once
#include <Types.h>

//gdt.cxx
namespace CPU::GDT {
    extern "C" void FlushGDT(u16 code, u16 data);
/*
    Global Descriptor Table
    See Figure 5-1 on page 2829 of 'Intel's osdev bible'
*/
typedef struct {
    u16 Limit;
    u64 Base;
} __attribute__((packed)) GDT_PTR;

typedef struct {
    u16 LimitLow;
    u16 BaseLow;
    u8 BaseMid;
    u8 Access;
    u8 Flags;    
    u8 BaseHigh;
} __attribute__((packed)) GDT_ENTRY;


void Initialize();
void ReadGDT(GDT_PTR *);
void ApplyGDT(GDT_PTR *, u16, u16);
}

//cpuid.cxx
namespace CPU::CPUID {
u32 GetFeatures();
void CPUID(u32 func, u32 *ax, u32 *bx, u32 *cx, u32 *dx);

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

#define F1_ECX_SSE3 1 << 0
#define F1_ECX_PCLMULDQ 1 << 1
#define F1_ECX_DTES64 1 << 2
#define F1_ECX_MONITOR 1 << 3
#define F1_ECX_DS_CPL 1 << 4
#define F1_ECX_VMX 1 << 5
#define F1_ECX_SMX 1 << 6
#define F1_ECX_EIST 1 << 7
#define F1_ECX_TM2 1 << 8
#define F1_ECX_SSSE3 1 << 9 
#define F1_ECX_CNXT_ID 1 << 10
// #define F1_ECX_Reserved_bit11 1 << 11
#define F1_ECX_FMA 1 << 12
#define F1_ECX_CX16 1 << 13
#define F1_ECX_XTPR 1 << 14
#define F1_ECX_PDCM 1 << 15
// #define F1_ECX_Reserved_bit16 1 << 16
#define F1_ECX_PCID 1 << 17
#define F1_ECX_DCA 1 << 18
#define F1_ECX_SSE41 1 << 19
#define F1_ECX_SSE42 1 << 20
#define F1_ECX_x2APIC 1 << 21
#define F1_ECX_MOVBE 1 << 22
#define F1_ECX_POPCNT 1 << 23
#define F1_ECX_TSC_DEADLINE 1 << 24
#define F1_ECX_AES 1 << 25
#define F1_ECX_XSAVE 1 << 26
#define F1_ECX_OSXSAVE 1 << 27
#define F1_ECX_AVX 1 << 28
#define F1_ECX_F16C 1 << 29
#define F1_ECX_RDRAND 1 << 30
#define F1_ECX_ZERO 1 << 31

#define F1_EDX_FPU 1 << 0
#define F1_EDX_VME 1 << 1
#define F1_EDX_DE 1 << 2
#define F1_EDX_PSE 1 << 3
#define F1_EDX_TSC 1 << 4
#define F1_EDX_MSR 1 << 5
#define F1_EDX_PAE 1 << 6
#define F1_EDX_MCE 1 << 7
#define F1_EDX_CX8 1 << 8
#define F1_EDX_APIC 1 << 9
//#define Reserved_bit10 1 << 10
#define F1_EDX_SEP 1 << 11
#define F1_EDX_MTRR 1 << 12
#define F1_EDX_PGE 1 << 13
#define F1_EDX_MCA 1 << 14
#define F1_EDX_CMOV 1 << 15
#define F1_EDX_PAT 1 << 16
#define F1_EDX_PSE_36 1 << 17
#define F1_EDX_PSN 1 << 18
#define F1_EDX_CLFSH 1 << 19
// #define F1_EDX_Reserved_bit20 1 << 20
#define F1_EDX_DS 1 << 21
#define F1_EDX_ACPI 1 << 22
#define F1_EDX_MMX 1 << 23
#define F1_EDX_FXSR 1 << 24
#define F1_EDX_SSE 1 << 25
#define F1_EDX_SSE2 1 << 26
#define F1_EDX_SS 1 << 27
#define F1_EDX_HTT 1 << 28
#define F1_EDX_TM 1 << 29
// #define F1_EDX_Reserved_bit30 1 << 30
#define F1_EDX_PBE 1 << 31

/*
    NDY
*/
}

namespace CPU::MSR{
    //msr.cxx
    bool IsAvailable();
    void ReadMSR(u32 addr, u32 *high, u32 *low);
    void WriteMSR(u32 addr, u32 high, u32 low);
}

//io.asm
namespace CPU::IO {
    extern "C" u8 inb(u16 port);
    extern "C" u16 inw(u16 port);
    extern "C" u32 indw(u16 port);

    extern "C" void outb(u16 port, u8 data);
    extern "C" void outw(u16 port, u16 data);
    extern "C" void outdw(u16 port, u32 data);
}
