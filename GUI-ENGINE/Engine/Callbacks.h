#pragma once

#define     SCHEDULED_NORMAL      1

#define     MALICIOUS_IDENTIFID   10301
#define     MALICIOUS_PACKED      10212
#define     SCANNED_FOR_PC        24332

typedef void(*MalwareScan_OnNewFile)(void* context, const wchar_t* path, const wchar_t* extension, const wchar_t* hash);
typedef void(*MalwareScan_OnNewDupFile)(void* context, const wchar_t* path, unsigned long long size, const wchar_t* hash, int notificationType);
typedef void(*MalwareScan_OnMalicious)(void* context, const wchar_t* path, int type);
typedef void(*MalwareScan_OnScheduled)(void* context, const wchar_t* path, int type);
typedef void(*MalwareScan_OnStatus)(void* context, const wchar_t* status);
typedef void(*MalwareScan_OnError)(void* context, const wchar_t* status, int errorType);
typedef void(*MalwareScan_OnFinish)(void* context);
typedef void(*MalwareScan_OnDeleteFile)(void* context, int index);
typedef bool(*IsStopped)(void* context);

