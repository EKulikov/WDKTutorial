#include "basic_driver.h"

typedef struct _BASIC_DEVICE_EXTENSION
{

} BASIC_DEVICE_EXTENSION, *PBASIC_DEVICE_EXTENSION;

EXTERN_C
NTSTATUS DriverEntry(
    PDRIVER_OBJECT DriverObject,
    PUNICODE_STRING RegistryPath)
{
#ifdef DBG
    DbgPrint("BasicDriver - DriverEntry");
#endif
    UNREFERENCED_PARAMETER(RegistryPath);

    DriverObject->MajorFunction[IRP_MJ_CREATE] = DriverCreate;
    DriverObject->MajorFunction[IRP_MJ_CLOSE] = DriverClose;
    DriverObject->MajorFunction[IRP_MJ_CLEANUP] = DriverCleanup;

    DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = DriverIoctl;
    DriverObject->MajorFunction[IRP_MJ_READ] = DriverRead;
    DriverObject->MajorFunction[IRP_MJ_WRITE] = DriverWrite;

    DriverObject->DriverUnload = DriverUnload;

    UNICODE_STRING DeviceName;
    RtlInitUnicodeString(&DeviceName, DEVICE_NAME);

    PDEVICE_OBJECT DeviceObject = NULL;
    NTSTATUS DeviceCreationStatus = IoCreateDevice(
        DriverObject,
        sizeof(BASIC_DEVICE_EXTENSION),
        &DeviceName,
        FILE_DEVICE_UNKNOWN,
        FILE_DEVICE_SECURE_OPEN,
        FALSE,
        &DeviceObject);

    if (NT_SUCCESS(DeviceCreationStatus))
    {
        DeviceObject->Flags |= DO_BUFFERED_IO;
    }
    else
    {
        return DeviceCreationStatus;
    }

    UNICODE_STRING DosDeviceName;
    RtlInitUnicodeString(&DosDeviceName, DEVICE_SYMLINK);

    NTSTATUS DeviceSymlinkCreationStatus = IoCreateSymbolicLink(&DosDeviceName, &DeviceName);

    if (!NT_SUCCESS(DeviceSymlinkCreationStatus))
    {
        IoDeleteDevice(DeviceObject);
        return DeviceSymlinkCreationStatus;
    }

    return STATUS_SUCCESS;
}

VOID DriverUnload(PDRIVER_OBJECT DriverObject)
{
#ifdef DBG
    DbgPrint("BasicDriver - DriverUnload");
#endif

    UNICODE_STRING DosDeviceName;
    RtlInitUnicodeString(&DosDeviceName, DEVICE_SYMLINK);

    IoDeleteSymbolicLink(&DosDeviceName);
    IoDeleteDevice(DriverObject->DeviceObject);
}

NTSTATUS DriverCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
#ifdef DBG
    DbgPrint("BasicDriver - DriverCreate");
#endif
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS DriverClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
#ifdef DBG
    DbgPrint("BasicDriver - DriverClose");
#endif
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS DriverCleanup(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
#ifdef DBG
    DbgPrint("BasicDriver - DriverCleanup");
#endif
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS DriverIoctl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
#ifdef DBG
    DbgPrint("BasicDriver - DriverIoctl");
#endif
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS DriverRead(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
#ifdef DBG
    DbgPrint("BasicDriver - DriverRead");
#endif
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}

NTSTATUS DriverWrite(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
#ifdef DBG
    DbgPrint("BasicDriver - DriverWrite");
#endif
    UNREFERENCED_PARAMETER(DeviceObject);

    Irp->IoStatus.Status = STATUS_SUCCESS;
    Irp->IoStatus.Information = 0;
    IoCompleteRequest(Irp, IO_NO_INCREMENT);

    return STATUS_SUCCESS;
}
