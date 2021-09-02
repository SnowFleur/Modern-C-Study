#pragma once
#include<Windows.h>

/*
- Lock 프로젝트에서 가져옴
- Developer	PDH
*/

////////////////////////
///////// SRWLock///////
////////////////////////
struct SRWLock {
private:
	SRWLOCK	srwLock;
public:
	SRWLock();

	void AcquiredReadLock()noexcept;
	void ReleaseReadLock()noexcept;
	void AcquireWrtieLock()noexcept;
	void ReleaseWriteLock()noexcept;
};


////////////////////////
/////////Lock//////////
///////////////////////
constexpr int MAX_SPIN_COUNT = 4000;
struct Lock {
private:
	CRITICAL_SECTION cs;
public:

	Lock();
	~Lock();

	Lock(const Lock&)				= delete;
	Lock& operator=(const Lock&)	= delete;
	Lock& operator=(Lock&&)			= delete;
	Lock(Lock&&)					= delete;

	void AcquiredLock();
	void ReleaseLock();
};

struct LockGuard {
private:
	Lock& lockGuard;
public:
	LockGuard(const LockGuard&)				= delete;
	LockGuard& operator=(const LockGuard&)	= delete;
	LockGuard&& operator=(LockGuard&&)		= delete;
	LockGuard(LockGuard&&)					= delete;

	explicit LockGuard(Lock& lock) : lockGuard(lock) { lockGuard.AcquiredLock(); }
	~LockGuard() { lockGuard.ReleaseLock(); }
};


struct WriteLockGuard {
public:
	SRWLOCK& lockGuard;
public:
	WriteLockGuard(const WriteLockGuard&)				= delete;
	WriteLockGuard& operator=(const WriteLockGuard&)	= delete;
	WriteLockGuard&& operator=(WriteLockGuard&&)		= delete;
	WriteLockGuard(WriteLockGuard&&)					= delete;

	explicit WriteLockGuard(SRWLOCK& lock) : lockGuard(lock) { AcquireSRWLockExclusive(&lockGuard); }
	~WriteLockGuard() { ReleaseSRWLockExclusive(&lockGuard); }
};

struct ReadLockGuard {
public:
	SRWLOCK& lockGuard;
public:
	ReadLockGuard(const ReadLockGuard&)					= delete;
	ReadLockGuard& operator=(const ReadLockGuard&)		= delete;
	ReadLockGuard&& operator=(ReadLockGuard&&)			= delete;
	ReadLockGuard(ReadLockGuard&&)						= delete;

	explicit ReadLockGuard(SRWLOCK& lock) : lockGuard(lock) { AcquireSRWLockShared(&lockGuard); }
	~ReadLockGuard() { ReleaseSRWLockShared(&lockGuard); }
};
