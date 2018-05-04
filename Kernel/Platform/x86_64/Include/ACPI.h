#pragma once
#include <Types.h>

namespace ACPI
{
    void Initialize(void *RSDP);
}

/*
    A lots of ACPI tables
GC: Holy shittt got a lot of things to implement from the spec.
*/
namespace ACPI::Tables{
//System Description Table Header
typedef struct
{
    u32 Signature;
    u32 Length;
    u8 Revision;
    u8 Checksum;
    u8 OEMID[6];
    u64 TableID;
    u32 TableRevision;
    u32 CreatorID;
    u32 CreateRevision;
} PACKED ACPI_SDTH;

//Root System Description Pointer
typedef struct
{
    u64 Signature;
    u8 Checksum;
    u8 OEMID[6];
    u8 Revision;
    u32 RsdtAddress; //we dont need this
    u32 Length;
    u64 XsdtAddress;
    u8 ExtendedChecksum;
    u8 Reserved[3];
} PACKED ACPI_RSDP;

//Fixed ACPI Description Table
typedef struct
{
    ACPI_SDTH Header;
    u32 FIRMWARE_CTRL;
    u32 DSDT;
    u8 ReservedA;
    u8 Preferred_PM_Profile;
    u16 SCI_INT;
    u32 SMI_CMD;
    u8 ACPI_ENABLE;
    u8 ACPI_DISABLE;
    u8 S4BIOS_REQ;
    u8 PSTATE_CNT;
    u8 PM1a_EVT_BLK;
    u8 PM1b_EVT_BLK;
    u32 PM1a_CNT_BLK;
    u32 PM1b_CNT_BLK;
    u32 PM2_CNT_BLK;
    u32 PM_TMR_BLK;
    u32 GPE0_BLK;
    u32 GPE1_BLK;
    u8 PM1_EVT_LEN;
    u8 PM1_CNT_LEN;
    u8 PM2_CNT_LEN;
    u8 PM_TMR_LEN;
    u8 GPE0_BLK_LEN;
    u8 GPE1_BLK_LEN;
    u8 GPE1_BASE;
    u8 CST_CNT;
    u16 P_LVL2_LAT;
    u16 P_LVL3_LAT;
    u16 FLUSH_SIZE;
    u16 FLUSH_STRIDE;
    u8 DUTY_OFFSET;
    u8 DUTY_WIDTH;
    u8 DAY_ALRM;
    u8 MON_ALRM;
    u8 CENTURY;
    u16 IAPC_BOOT_ARCH;
    u8 ReservedB;
    u32 Flags;
    u8 RESET_REG[12];
    u8 RESET_VALUE;
    u16 ARM_BOOT_ARCH;
    u8 MinorVersion;
    u64 X_FIRMWARE_CTRL;
    u64 X_DSDT;
    u8 X_PM1a_EVT_BLK[12];
    u8 X_PM1b_EVT_BLK[12];
    u8 X_PM1a_CNT_BLK[12];
    u8 X_PM1b_CNT_BLK[12];
    u8 X_PM2_CNT_BLK[12];
    u8 X_PM_TMR_BLK[12];
    u8 X_GPE0_BLK[12];
    u8 X_GPE1_BLK[12];
    u8 SLEEP_CONTROL_REG[12];
    u8 SLEEP_STATUS_REG[12];
    u8 HypervisorVendorID[12]; 
} PACKED ACPI_FADT;

//Firmware ACPI Control Structure
typedef struct
{
    u32 Signature;
    u32 Length;
    u32 HardwareSignature;
    u32 FirmwareWakingVector;
    u32 GlobalLock;
    u32 Flags;
    u64 XFirmwareWakingVector;
    u8 Version;
    u8 ReservedA[3];
    u32 OSPMFlags;
    u8 ReservedB[24];
} PACKED ACPI_FACS;

//Multiple APIC Description Table
typedef struct
{
    ACPI_SDTH Header;
    u32 LocalAPIC;
    u32 Flags;
    //A list of Interrupt Controller Structures here
} PACKED ACPI_MADT;
/*
//Differentiated System Description Table
typedef struct
{
    ACPI_SDTH Header;
    u32 Signature;
    u32 Length;
    u8 Revision;
    u8 Checksum;
    u8 OEMID[6];
    u64 OEMTableID;
    u32 OEMRevision;
    u32 CreatorID;
    u32 CreatorRevision;

} PACKED ACPI_DSDT;
*/

/*
//Smart Battery Table
typedef struct
{

} PACKED ACPI_SBST;

//Embedded Controller Boot Resources Table
typedef struct
{

} PACKED ACPI_ECDT;

//System Locality Distance Information Table
typedef struct
{

} PACKED ACPI_SLIT;

//System Resource Affinity Table
typedef struct
{

} PACKED ACPI_SRAT;

//Corrected Platform Error Polling Table
typedef struct
{

} PACKED ACPI_CPEP;

//Maximum System Characteristics Table
typedef struct
{

} PACKED ACPI_MSCT;

//ACPI RAS Feature Table
typedef struct
{

} PACKED ACPI_RASF;

//Memory Power StateTable
typedef struct
{

} PACKED ACPI_MPST;

//Platform Memory Topology Table
typedef struct
{

} PACKED ACPI_PMTT;

//Boot Graphics Resource Table
typedef struct
{

} PACKED ACPI_BGRT;

//Firmware Performance Data Table
typedef struct
{

} PACKED ACPI_FPDT;

//Generic Timer Description Table
typedef struct
{

} PACKED ACPI_GTDT;

//NVDIMM Firmware Interface Table
typedef struct
{

} PACKED ACPI_NFIT;

//Heterogeneous Memory Attributes Table
typedef struct
{

} PACKED ACPI_HMAT;

//Platform Debug Trigger Table
typedef struct
{

} PACKED ACPI_PDTT;

//Processor Properties Topology Table
typedef struct
{

} PACKED ACPI_PPTT;*/
}
/*
    Defined signatures by ACPI
    ACPI 6.2a spec. Table 5-30
*/
#define ACPI_RSDP_SIGNATURE "RSD PTR\0"
#define ACPI_MADT_SIGNATURE "APIC"
#define ACPI_BERT_SIGNATURE "BERT"
#define ACPI_BGRT_SIGNATURE "BGRT"
#define ACPI_CPEP_SIGNATURE "CPEP"
#define ACPI_DSDT_SIGNATURE "DSDT"
#define ACPI_ECDT_SIGNATURE "ECDT"
#define ACPI_EINJ_SIGNATURE "EINJ"
#define ACPI_ERST_SIGNATURE "ERST"
#define ACPI_FADT_SIGNATURE "FACP"
#define ACPI_FACS_SIGNATURE "FACS"
#define ACPI_FPDT_SIGNATURE "FPDT"
#define ACPI_GTDT_SIGNATURE "GTDT"
#define ACPI_HEST_SIGNATURE "HEST"
#define ACPI_MSCT_SIGNATURE "MSCT"
#define ACPI_MPST_SIGNATURE "MPST"
#define ACPI_NFIT_SIGNATURE "NFIT"
#define ACPI_OEMX_SIGNATURE "OEMx"
#define ACPI_PCCT_SIGNATURE "PCCT"
#define ACPI_PMTT_SIGNATURE "PMTT"
#define ACPI_PSDT_SIGNATURE "PSDT"
#define ACPI_RASF_SIGNATURE "RASF"
#define ACPI_RSDT_SIGNATURE "RSDT"
#define ACPI_SBST_SIGNATURE "SBST"
#define ACPI_SDEV_SIGNATURE "SDEV"
#define ACPI_SLIT_SIGNATURE "SLIT"
#define ACPI_SRAT_SIGNATURE "SRAT"
#define ACPI_SSDT_SIGNATURE "SSDT"
#define ACPI_XSDT_SIGNATURE "XSDT"
/*
    Reserved signatures by ACPI
    ACPI 6.2a spec. Table 5-31
*/
#define ACPI_RESERVED_SIGNATURE "BOOT"
#define ACPI_CSRT_SIGNATURE "CSRT"
#define ACPI_DBG2_SIGNATURE "DBG2"
#define ACPI_DBGP_SIGNATURE "DBGP"
#define ACPI_DMAR_SIGNATURE "DMAR"
#define ACPI_DPPT_SIGNATURE "DPPT"
#define ACPI_DRTM_SIGNATURE "DRTM"
#define ACPI_ETDT_SIGNATURE "ETDT"
#define ACPI_HPET_SIGNATURE "HPET"
#define ACPI_IBFT_SIGNATURE "IBFT"
#define ACPI_IORT_SIGNATURE "IORT"
#define ACPI_IVRS_SIGNATURE "IVRS"
#define ACPI_LPIT_SIGNATURE "LPIT"
#define ACPI_MCFG_SIGNATURE "MCFG"
#define ACPI_MCHI_SIGNATURE "MCHI"
#define ACPI_MSDM_SIGNATURE "MSDM"
#define ACPI_SDEI_SIGNATURE "SDEI"
#define ACPI_SLIC_SIGNATURE "SLIC"
#define ACPI_SPCR_SIGNATURE "SPCR"
#define ACPI_SPMI_SIGNATURE "SPMI"
#define ACPI_STAO_SIGNATURE "STAO"
#define ACPI_TCPA_SIGNATURE "TCPA"
#define ACPI_TPM2_SIGNATURE "TPM2"
#define ACPI_UEFI_SIGNATURE "UEFI"
#define ACPI_WAET_SIGNATURE "WAET"
#define ACPI_WDAT_SIGNATURE "WDAT"
#define ACPI_WDRT_SIGNATURE "WDRT"
#define ACPI_WPBT_SIGNATURE "WPBT"
#define ACPI_WSMT_SIGNATURE "WSMT"
#define ACPI_XENV_SIGNATURE "XENV"
