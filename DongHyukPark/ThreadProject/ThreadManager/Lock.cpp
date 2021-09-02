#include"Lock.h"

SRWLock::SRWLock() {
	InitializeSRWLock(&srwLock);
}

void SRWLock::AcquiredReadLock()noexcept {
	AcquireSRWLockShared(&srwLock);
}

void SRWLock::ReleaseReadLock()noexcept {
	ReleaseSRWLockShared(&srwLock);
}

void SRWLock::AcquireWrtieLock()noexcept {
	AcquireSRWLockExclusive(&srwLock);
}

void SRWLock::ReleaseWriteLock()noexcept {
	ReleaseSRWLockExclusive(&srwLock);
}

////////////////////////
/////////Lock//////////
///////////////////////

Lock::Lock() { InitializeCriticalSectionAndSpinCount(&cs, MAX_SPIN_COUNT); }
Lock::~Lock() { DeleteCriticalSection(&cs); }

void Lock::AcquiredLock() { EnterCriticalSection(&cs); }
void Lock::ReleaseLock() { LeaveCriticalSection(&cs); }


#define EXCLUSIVE_LOCK(x)		LockGuard(x)