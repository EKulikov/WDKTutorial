#pragma once
#include <ntddk.h>

#define DEVICE_NAME L"\\Device\\BasicDriver"
#define DEVICE_SYMLINK L"\\Global??\\BasicDriverDevice"

EXTERN_C
DRIVER_INITIALIZE DriverEntry;

DRIVER_UNLOAD DriverUnload;

_Dispatch_type_(IRP_MJ_CREATE)
DRIVER_DISPATCH DriverCreate;

_Dispatch_type_(IRP_MJ_CLOSE)
DRIVER_DISPATCH DriverClose;

_Dispatch_type_(IRP_MJ_CLEANUP)
DRIVER_DISPATCH DriverCleanup;

_Dispatch_type_(IRP_MJ_DEVICE_CONTROL)
DRIVER_DISPATCH DriverIoctl;

_Dispatch_type_(IRP_MJ_READ)
DRIVER_DISPATCH DriverRead;

_Dispatch_type_(IRP_MJ_WRITE)
DRIVER_DISPATCH DriverWrite;
