
#include "Limiting Instance.h"
#include<conio.h>
#include"Limiting Instance.h"
/*int main(int argc, char* argv[])
{
	LimitSingleInstance g_Instance(L"MyMutex");
	_tprintf(L"DEBUGGING\n");
	  if(g_Instance.IsAnotherInstanceRunning())
    {
        return -1;
    }
	_getch();

    // Rest of the code
    // ...
}  */

/* #include <windows.h>
#include <stdio.h>

#define THREADCOUNT 2

HANDLE ghMutex;

DWORD WINAPI WriteToDatabase( LPVOID );

int main( void )
{
    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;

    // Create a mutex with no initial owner

    ghMutex = CreateMutex(
        NULL,              // default security attributes
        FALSE,             // initially not owned
        NULL);             // unnamed mutex

    if (ghMutex == NULL)
    {
        printf("CreateMutex error: %d\n", GetLastError());
        return 1;
    }

    // Create worker threads

    for( i=0; i < THREADCOUNT; i++ )
    {
        aThread[i] = CreateThread(
                     NULL,       // default security attributes
                     0,          // default stack size
                     (LPTHREAD_START_ROUTINE) WriteToDatabase,
                     NULL,       // no thread function arguments
                     0,          // default creation flags
                     &ThreadID); // receive thread identifier

        if( aThread[i] == NULL )
        {
            printf("CreateThread error: %d\n", GetLastError());
            return 1;
        }
    }

    // Wait for all threads to terminate

    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

    // Close thread and mutex handles

    for( i=0; i < THREADCOUNT; i++ )
        CloseHandle(aThread[i]);

    CloseHandle(ghMutex);

    return 0;
}

DWORD WINAPI WriteToDatabase( LPVOID lpParam )
{
    // lpParam not used in this example
    UNREFERENCED_PARAMETER(lpParam);

    DWORD dwCount=0, dwWaitResult;

    // Request ownership of mutex.

    while( dwCount < 20 )
    {
        dwWaitResult = WaitForSingleObject(
            ghMutex,    // handle to mutex
            INFINITE);  // no time-out interval

        switch (dwWaitResult)
        {
            // The thread got ownership of the mutex
            case WAIT_OBJECT_0:
                __try {
                    // TODO: Write to the database
                    printf("Thread %d writing to database...\n",
                            GetCurrentThreadId());
                    dwCount++;
                }

                __finally {
                    // Release ownership of the mutex object
                    if (! ReleaseMutex(ghMutex))
                    {
                        // Handle error.
                    }
                }
                break;

            // The thread got ownership of an abandoned mutex
            // The database is in an indeterminate state
            case WAIT_ABANDONED:
                return FALSE;
        }
    }
    return TRUE;
}*/

/*#include <windows.h>
#include <iostream>
using namespace std;

DWORD WINAPI Tf(LPVOID n)

{

    cout << "Thread Instantiated........." << endl;

    // Get the handler to the event for which we need to wait in

    //            this thread.

    HANDLE hEvent = OpenEvent(EVENT_ALL_ACCESS, false, L"MyEvent");

    if (!hEvent) { return -1; }

    // Loop through and wait for an event to occur

    for (char counter = 0; counter < 2; counter++)

    {

        // Wait for the Event

        WaitForSingleObject(hEvent, INFINITE);

        // We need to reset the event since the event is manual reset

        //            event

        ResetEvent(hEvent);

        cout << "Got The signal......." << endl;

    }

    CloseHandle(hEvent);

    cout << "End of the Thread......" << endl;

    return 0;

}



int main()

{

    //Create an Manual Reset Event where events must be reset

    // manually to non signalled state

    HANDLE hEvent = CreateEvent(NULL, TRUE, FALSE, L"MyEvent");
    if (!hEvent) return -1;

    // Create a Thread Which will wait for the events to occur

    DWORD Id;

    HANDLE hThrd = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Tf, 0, 0, &Id);

    if (!hThrd) { CloseHandle(hEvent); return -1; }

    // Wait for a while before continuing....

    Sleep(1000);

    // Give the signal twice as the thread is waiting for 2 signals to occur

    for (char counter = 0; counter < 2; counter++)

    {

        // Signal the event

        SetEvent(hEvent);

        // wait for some time before giving another signal

        Sleep(2000);

    }

    // Wait for the Thread to Die

    WaitForSingleObject(hThrd, INFINITE);



    CloseHandle(hThrd);

    CloseHandle(hEvent);

    cout << "End of Main ........" << endl;

    return 0;

}*/

#include <windows.h>
#include <stdio.h>

#define MAX_SEM_COUNT 5
#define THREADCOUNT 5

HANDLE g_hSemaphore;

//fn declaration

DWORD WINAPI ThreadProc(LPVOID);


void main()

{

    HANDLE hThread[THREADCOUNT];
    DWORD ThreadID;
    int idx;

    // Create a semaphore with initial and max counts of MAX_SEM_COUNT

    g_hSemaphore = CreateSemaphore(

        NULL,           // default security attributes

        3,  // initial count
        MAX_SEM_COUNT,  // maximum count
        NULL);          // unnamed semaphore



    if (g_hSemaphore == NULL)

    {
        printf("CreateSemaphore error: %d\n", GetLastError());
        return;
    }

    // Create worker threads

    for (idx = 0; idx < THREADCOUNT; idx++)

    {

        hThread[idx] = CreateThread(

            NULL,       // default security attributes

            0,          // default stack size

            (LPTHREAD_START_ROUTINE)ThreadProc,

            NULL,       // no thread function arguments

            0,          // default creation flags

            &ThreadID); // receive thread identifier



        if (hThread[idx] == NULL)

        {

            printf("CreateThread error: %d\n", GetLastError());

            return;

        }

    }



    // Wait for all threads to terminate



    WaitForMultipleObjects(THREADCOUNT, hThread, TRUE, INFINITE);



    // Close thread and semaphore handles



    for (idx = 0; idx < THREADCOUNT; idx++)

        CloseHandle(hThread[idx]);



    CloseHandle(g_hSemaphore);

}





/* *************************************************************** */

/*                                                                                                                                                                                                                                               */

/*           Purpose :             Thread Function                                                                   */

/*           Return  : DWORD                                               */

/*           Note    :                                                                                                                     */

/*                                                                                                                                                                                                                                               */

/* *****************************************************************/

DWORD WINAPI ThreadProc(LPVOID lpParam)

{

    DWORD dwWaitResult;

    BOOL bContinue = TRUE;



    while (bContinue)

    {

        // Try to enter the semaphore gate.



        dwWaitResult = WaitForSingleObject(

            g_hSemaphore,   // handle to semaphore

            0L);           // zero-second time-out interval



        switch (dwWaitResult)

        {

            // The semaphore object was signaled.

        case WAIT_OBJECT_0:

            // TODO: Perform task

            printf("Thread %d: wait succeeded\n", GetCurrentThreadId());

            bContinue = FALSE;



            // Simulate thread spending time on task

            Sleep(5);



            // Relase the semaphore when task is finished



            if (!ReleaseSemaphore(

                g_hSemaphore,  // handle to semaphore

                1,            // increase count by one

                NULL))       // not interested in previous count

            {

                printf("ReleaseSemaphore error: %d\n", GetLastError());

            }

            break;



            // The semaphore was nonsignaled, so a time-out occurred.

        case WAIT_TIMEOUT:

            printf("Thread %d: wait timed out\n", GetCurrentThreadId());

            break;

        }

    }

    return TRUE;

}





/*Using Semaphore Objects

The following example uses a semaphore object to limit the number of threads that can perform a particular task. First, it uses the CreateSemaphore function to create the semaphore and to specify initial and maximum counts, then it uses the CreateThread function to create the threads.

Before a thread attempts to perform the task, it uses the WaitForSingleObject function to

determine whether the semaphore's current count permits it to do so.

The wait function's time-out parameter is set to zero, so the function returns immediately

if the semaphore is in the nonsignaled state.

When a thread completes the task, it uses the ReleaseSemaphore function to

increment the semaphore's count, thus enabling another waiting thread to perform the task.

*/