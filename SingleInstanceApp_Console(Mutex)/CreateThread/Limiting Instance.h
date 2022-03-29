
#ifndef __LimitSingleInstance_h__
#define __LimitSingleInstance_h__

#include <Windows.h>
#include <tchar.h>
#include <iostream>

class LimitSingleInstance
{
public:
    LimitSingleInstance(LPCTSTR pMutexName)
    {
        // Create a named mutex.
        m_hMutex = CreateMutex(NULL, FALSE, pMutexName);
        // Store the error for later used.
        m_bAlreadyExists = (ERROR_ALREADY_EXISTS == GetLastError());
    }   // LimitSingleInstance

    ~LimitSingleInstance()
    {
        if(m_hMutex != NULL)
        {
            CloseHandle(m_hMutex);
        }
    }   // ~LimitSingleInstance

    BOOL IsAnotherInstanceRunning()
    {
		
        return m_bAlreadyExists;
    }   // IsAnotherInstanceRunning

private:
    BOOL m_bAlreadyExists;
	HANDLE m_hMutex;

};  // class LimitSingleInstance

#endif