#pragma once
#include <types.h>

namespace ACPI
{
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
} __attritube__((packed)) ACPI_SDTH;

//Root System Description Pointer
typedef struct
{
    u64 Signature;
    u8 Checksum;
    u8 OEMID[6];
    u8 Revision;
    u32 RsdtAddress;
    u32 Length;
    u64 XsdtAddress;
    u8 ExtendedChecksum;
    u8 Reserved[3];
} __attribute__((packed)) ACPI_RSDP;

//Root System Description Table
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
    u32 EntryStart;
} __attritube__((packed)) ACPI_RSDT;
/*
//Fixed ACPI Description Table
typedef struct
{

} __attritube__((packed)) ACPI_FADT;

//Firmware ACPI Control Structure
typedef struct
{

} __attritube__((packed)) ACPI_FACS;

//Differentiated System Description Table
typedef struct
{

} __attritube__((packed)) ACPI_DSDT;

//Secondary System Description Table
typedef struct
{

} __attritube__((packed)) ACPI_SSDT;

//Multiple APIC Description Table
typedef struct
{

} __attritube__((packed)) ACPI_MADT;

//Smart Battery Table
typedef struct
{

} __attritube__((packed)) ACPI_SBST;

//Extended System Description Table
typedef struct
{
    ACPI_SDTH Header;

} __attritube__((packed)) ACPI_XSDT;

//Embedded Controller Boot Resources Table
typedef struct
{

} __attritube__((packed)) ACPI_ECDT;

//System Locality Distance Information Table
typedef struct
{

} __attritube__((packed)) ACPI_SLIT;

//System Resource Affinity Table
typedef struct
{

} __attritube__((packed)) ACPI_SRAT;

//Corrected Platform Error Polling Table
typedef struct
{

} __attritube__((packed)) ACPI_CPEP;

//Maximum System Characteristics Table
typedef struct
{

} __attritube__((packed)) ACPI_MSCT;

//ACPI RAS Feature Table
typedef struct
{

} __attritube__((packed)) ACPI_RASF;

//Memory Power StateTable
typedef struct
{

} __attritube__((packed)) ACPI_MPST;

//Platform Memory Topology Table
typedef struct
{

} __attritube__((packed)) ACPI_PMTT;

//Boot Graphics Resource Table
typedef struct
{

} __attritube__((packed)) ACPI_BGRT;

//Firmware Performance Data Table
typedef struct
{

} __attritube__((packed)) ACPI_FPDT;

//Generic Timer Description Table
typedef struct
{

} __attritube__((packed)) ACPI_GTDT;

//NVDIMM Firmware Interface Table
typedef struct
{

} __attritube__((packed)) ACPI_NFIT;

//Heterogeneous Memory Attributes Table
typedef struct
{

} __attritube__((packed)) ACPI_HMAT;

//Platform Debug Trigger Table
typedef struct
{

} __attritube__((packed)) ACPI_PDTT;

//Processor Properties Topology Table
typedef struct
{

} __attritube__((packed)) ACPI_PPTT;*/
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
