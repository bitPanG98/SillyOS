#include <cpu.h>

namespace CPU::CPUID {
u32 get_cpu() {
    u32 regs[4];
    CPU::CPUID::run_cpuid(0x0, &regs[0], &regs[1], &regs[2], &regs[3]);
    // In fact we can tell which cpu we running on by compare single signature.
    // but Ughh whatever..
    if (regs[1] == 0x414d4469 && regs[2] == 0x73626574 &&
        regs[3] == 0x74657221) {
        return EARLY_AMD;
    } else if (regs[1] == 0x41757468 && regs[2] == 0x656e7469 &&
               regs[3] == 0x63414d44) {
        return AMD;
    } else if (regs[1] == 0x43656e74 && regs[2] == 0x61757248 &&
               regs[3] == 0x61756c73) {
        return CENTAUR;
    } else if (regs[1] == 0x43797269 && regs[2] == 0x78496e73 &&
               regs[3] == 0x74656164) {
        return CYRIX;
    } else if (regs[1] == 0x47656e75 && regs[2] == 0x696e6549 &&
               regs[3] == 0x6e74656c) {
        return INTEL;
    } else if (regs[1] == 0x5472616e && regs[2] == 0x736d6574 &&
               regs[3] == 0x61435055) {
        return TRANSMETA;
    } else if (regs[1] == 0x47656e75 && regs[2] == 0x696e6554 &&
               regs[3] == 0x4d783836) {
        return TRANSMETA_X86;
    } else if (regs[1] == 0x4d783836 && regs[2] == 0x65206279 &&
               regs[3] == 0x204e5343) {
        return NSC;
    } else if (regs[1] == 0x4e657847 && regs[2] == 0x656e4472 &&
               regs[3] == 0x6976656e) {
        return NEX_GEN;
    } else if (regs[1] == 0x52697365 && regs[2] == 0x52697365 &&
               regs[3] == 0x52697365) {
        return RISE;
    } else if (regs[1] == 0x53695320 && regs[2] == 0x53695320 &&
               regs[3] == 0x53695320) {
        return SIS;
    } else if (regs[1] == 0x554d4320 && regs[2] == 0x554d4320 &&
               regs[3] == 0x554d4320) {
        return UMC;
    } else if (regs[1] == 0x56494120 && regs[2] == 0x56494120 &&
               regs[3] == 0x56494120) {
        return VIA;
    } else if (regs[1] == 0x566f7274 && regs[2] == 0x65783836 &&
               regs[3] == 0x20536f43) {
        return VORTEX;
    } else if (regs[1] == 0x62687976 && regs[2] == 0x65206268 &&
               regs[3] == 0x79766520) {
        return BHYVE;
    } else if (regs[1] == 0x4b564d4b && regs[2] == 0x564d4b56 &&
               regs[3] == 0x4d000000) {
        return KVM;
    } else if (regs[1] == 0x4d696372 && regs[2] == 0x6f736f66 &&
               regs[3] == 0x74204876) {
        return M$_HV;
    } else if (regs[1] == 0x6c727065 && regs[2] == 0x70796820 &&
               regs[3] == 0x76720000) {
        return PARALLELS;
    } else if (regs[1] == 0x564d7761 && regs[2] == 0x7265564d &&
               regs[3] == 0x77617265) {
        return VM_WARE;
    } else if (regs[1] == 0x58656e56 && regs[2] == 0x4d4d5865 &&
               regs[3] == 0x6e564d4d) {
        return XEN_HVM;
    } else {
        return UNKNOWN;
    }
}

void run_cpuid(u32 func, u32 *ax, u32 *bx, u32 *cx, u32 *dx) {
    __asm__("cpuid" : "=a"(*ax), "=b"(*bx), "=c"(*cx), "=d"(*dx) : "a"(func));
}

}
