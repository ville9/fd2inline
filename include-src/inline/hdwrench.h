/* Automatically generated header! Do not edit! */

#ifndef _INLINE_HDWRENCH_H
#define _INLINE_HDWRENCH_H

#ifndef __INLINE_MACROS_H
#include <inline/macros.h>
#endif /* !__INLINE_MACROS_H */

#ifndef HDWRENCH_BASE_NAME
#define HDWRENCH_BASE_NAME HDWBase
#endif /* !HDWRENCH_BASE_NAME */

#define FindControllerID(devname, selfid) \
	LP2(0x9c, BOOL, FindControllerID, char *, devname, a0, ULONG *, selfid, a1, \
	, HDWRENCH_BASE_NAME)

#define FindDefaults(Optimize, Return) \
	LP2(0xa8, ULONG, FindDefaults, USHORT, Optimize, d0, struct DefaultsArray *, Return, a0, \
	, HDWRENCH_BASE_NAME)

#define FindDiskName(diskname) \
	LP1(0x96, BOOL, FindDiskName, char *, diskname, a0, \
	, HDWRENCH_BASE_NAME)

#define FindLastSector() \
	LP0(0xa2, ULONG, FindLastSector, \
	, HDWRENCH_BASE_NAME)

#define HDWCloseDevice() \
	LP0NR(0x24, HDWCloseDevice, \
	, HDWRENCH_BASE_NAME)

#define HDWOpenDevice(DevName, unit) \
	LP2(0x1e, BOOL, HDWOpenDevice, char *, DevName, a0, ULONG, unit, d0, \
	, HDWRENCH_BASE_NAME)

#define InMemMountfile(unit, mfdata, controller) \
	LP3(0x7e, ULONG, InMemMountfile, ULONG, unit, d0, char *, mfdata, a0, char *, controller, a1, \
	, HDWRENCH_BASE_NAME)

#define InMemRDBStructs(rdbp, sizerdb, unit) \
	LP3(0x84, ULONG, InMemRDBStructs, char *, rdbp, a0, ULONG, sizerdb, d0, ULONG, unit, d1, \
	, HDWRENCH_BASE_NAME)

#define LowlevelFormat(CallBack) \
	LP1FP(0xae, ULONG, LowlevelFormat, __fpt, CallBack, a0, \
	, HDWRENCH_BASE_NAME, long (*__fpt)(HDWCallbackMsg *msg))

#define OutMemMountfile(mfp, sizew, sizeb, unit) \
	LP4(0x8a, ULONG, OutMemMountfile, char *, mfp, a0, ULONG *, sizew, a1, ULONG, sizeb, d0, ULONG, unit, d1, \
	, HDWRENCH_BASE_NAME)

#define OutMemRDBStructs(rdbp, sizew, sizeb) \
	LP3(0x90, ULONG, OutMemRDBStructs, char *, rdbp, a0, ULONG *, sizew, a1, ULONG, sizeb, d0, \
	, HDWRENCH_BASE_NAME)

#define QueryCapacity(totalblocks, blocksize) \
	LP2(0x60, BOOL, QueryCapacity, ULONG *, totalblocks, a0, ULONG *, blocksize, a1, \
	, HDWRENCH_BASE_NAME)

#define QueryFindValid(ValidIDs, devicename, board, types, wide_scsi, CallBack) \
	LP6NRFP(0x5a, QueryFindValid, ValidIDstruct *, ValidIDs, a0, char *, devicename, a1, int, board, d0, ULONG, types, d1, BOOL, wide_scsi, d2, __fpt, CallBack, a2, \
	, HDWRENCH_BASE_NAME, long (*__fpt)(HDWCallbackMsg *msg))

#define QueryInquiry(inqbuf, errorcode) \
	LP2(0x4e, BOOL, QueryInquiry, BYTE *, inqbuf, a0, int *, errorcode, a1, \
	, HDWRENCH_BASE_NAME)

#define QueryModeSense(page, msbsize, msbuf, errorcode) \
	LP4(0x54, BOOL, QueryModeSense, BYTE, page, d0, int, msbsize, d1, BYTE *, msbuf, a0, int *, errorcode, a1, \
	, HDWRENCH_BASE_NAME)

#define QueryReady(errorcode) \
	LP1(0x48, BOOL, QueryReady, int *, errorcode, a0, \
	, HDWRENCH_BASE_NAME)

#define RawRead(bbk, size) \
	LP2(0x2a, USHORT, RawRead, BootBlock *, bbk, a0, USHORT, size, d0, \
	, HDWRENCH_BASE_NAME)

#define RawWrite(bb) \
	LP1(0x30, USHORT, RawWrite, BootBlock *, bb, a0, \
	, HDWRENCH_BASE_NAME)

#define ReadMountfile(unit, filename, controller) \
	LP3(0x66, ULONG, ReadMountfile, ULONG, unit, d0, char *, filename, a0, char *, controller, a1, \
	, HDWRENCH_BASE_NAME)

#define ReadRDBStructs(filename, unit) \
	LP2(0x6c, ULONG, ReadRDBStructs, char *, filename, a0, ULONG, unit, d0, \
	, HDWRENCH_BASE_NAME)

#define ReadRDBs() \
	LP0(0x3c, USHORT, ReadRDBs, \
	, HDWRENCH_BASE_NAME)

#define VerifyDrive(CallBack) \
	LP1FP(0xb4, ULONG, VerifyDrive, __fpt, CallBack, a0, \
	, HDWRENCH_BASE_NAME, long (*__fpt)(HDWCallbackMsg *msg))

#define WriteBlock(bb) \
	LP1(0x36, USHORT, WriteBlock, BootBlock *, bb, a0, \
	, HDWRENCH_BASE_NAME)

#define WriteMountfile(filename, ldir, unit) \
	LP3(0x72, ULONG, WriteMountfile, char *, filename, a0, char *, ldir, a1, ULONG, unit, d0, \
	, HDWRENCH_BASE_NAME)

#define WriteRDBStructs(filename) \
	LP1(0x78, ULONG, WriteRDBStructs, char *, filename, a0, \
	, HDWRENCH_BASE_NAME)

#define WriteRDBs() \
	LP0(0x42, USHORT, WriteRDBs, \
	, HDWRENCH_BASE_NAME)

#endif /* !_INLINE_HDWRENCH_H */
