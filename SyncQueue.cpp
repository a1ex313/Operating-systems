#include <Windows.h>

class SyncQueue
{
private:
	int* queue;
	int nSize;
	int pushPos;
	int popPos;
	HANDLE isFull;
	HANDLE isEmpty;
	CRITICAL_SECTION cs;

public:
	SyncQueue(int size)
	{
		this->pushPos = 0;
		this->popPos = 0;
		this->nSize = size;
		this->queue = new int[size];

		InitializeCriticalSection(&cs);
		isFull = CreateSemaphore(NULL, 0, size, NULL);
		isEmpty = CreateSemaphore(NULL, size, size, NULL);
		
	}

	~SyncQueue()
	{
		DeleteCriticalSection(&cs);
		CloseHandle(isEmpty);
		CloseHandle(isFull);
		delete[]queue;
	}

	void Insert(int element)
	{
		WaitForSingleObject(isEmpty, INFINITE);

		EnterCriticalSection(&cs);
		queue[pushPos] = element;
		pushPos++;
		if (pushPos == nSize)
		{
			pushPos = 0;
		}
		LeaveCriticalSection(&cs);

		ReleaseSemaphore(isFull, 1, NULL);
	}

	int Remove()
	{
		WaitForSingleObject(isFull, INFINITE);

		EnterCriticalSection(&cs);
		int element = queue[popPos];
		popPos++;
		if (popPos == nSize)
		{
			popPos = 0;
		}
		LeaveCriticalSection(&cs);

		ReleaseSemaphore(isEmpty, 1, NULL);

		return element;
	}
};