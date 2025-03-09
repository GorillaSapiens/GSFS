#ifndef _INCLUDE_GSFS_IO_H_
#define _INCLUDE_GSFS_IO_H_

#include <stdint.h>
#include <stdbool.h>

/// Initialize the narf_io layer
///
/// This is typically implemented by you for yor
/// hardware.
///
/// @return true on success
bool narf_io_open(void);

/// Deinitialize the narf_io layer
///
/// This is typically implemented by you for yor
/// hardware.
///
/// @return true on success
bool narf_io_close(void);

/// Get the size of the underlying hardware device in sectors
///
/// This is typically implemented by you for yor
/// hardware.
///
/// @return the number of sectors supported by the device
uint32_t narf_io_sectors(void);

/// Write a sector to the disk
/// 
/// This is typically implemented by you for your
/// hardware.
///
/// @param sector The address of the sector to access
/// @param data Pointer to 512 bytes of data to write
/// @return true on success
bool narf_io_write(uint32_t sector, uint8_t *data);

/// Read a sector from the disk
/// 
/// This is typically implemented by you for your
/// hardware.
///
/// @param sector The address of the sector to access
/// @param data Pointer to 512 bytes ed buffer
/// @return true on success
bool narf_io_read(uint32_t sector, uint8_t *data);

#endif

// vim:set ai softtabstop=3 shiftwidth=3 tabstop=3 expandtab: ff=unix
