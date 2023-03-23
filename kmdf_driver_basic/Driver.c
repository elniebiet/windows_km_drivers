/**
* Basic windows driver
 */

#include <ntddk.h>	//contains core windows kernel definitions
#include <wdf.h>	//contains definitions for drivers based on the Windows Drivers Framework (WDF)

/* callback definitions */
DRIVER_INITIALIZE			DriverEntry;
EVT_WDF_DRIVER_DEVICE_ADD	KmdfBasicDriverEvtDeviceAdd;

/**
 * Entry point for driver
*/
NTSTATUS
DriverEntry(
    _In_ PDRIVER_OBJECT     DriverObject,
    _In_ PUNICODE_STRING    RegistryPath
)
{
    // NTSTATUS variable to record success or failure
    NTSTATUS status = STATUS_SUCCESS;

    // Allocate the driver configuration object
    WDF_DRIVER_CONFIG config;

    // Print message for DriverEntry
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfBasicDriver: DriverEntry\n"));

    // Initialize the driver configuration object to register the
    // entry point for the EvtDeviceAdd callback, KmdfBasicDriverEvtDeviceAdd
    WDF_DRIVER_CONFIG_INIT(&config,
        KmdfBasicDriverEvtDeviceAdd
    );

    // Finally, create the driver object
    status = WdfDriverCreate(DriverObject,
        RegistryPath,
        WDF_NO_OBJECT_ATTRIBUTES,
        &config,
        WDF_NO_HANDLE
    );
    return status;
}

NTSTATUS
KmdfBasicDriverEvtDeviceAdd(
    _In_    WDFDRIVER       Driver,
    _Inout_ PWDFDEVICE_INIT DeviceInit
)
{
    // We're not using the driver object,
    // so we need to mark it as unreferenced
    UNREFERENCED_PARAMETER(Driver);

    NTSTATUS status;

    // Allocate the device object
    WDFDEVICE hDevice;

    // Print message
    KdPrintEx((DPFLTR_IHVDRIVER_ID, DPFLTR_INFO_LEVEL, "KmdfBasicDriver: KmdfBasicDriverEvtDeviceAdd\n"));

    // Create the device object
    status = WdfDeviceCreate(&DeviceInit,
        WDF_NO_OBJECT_ATTRIBUTES,
        &hDevice
    );
    return status;
}