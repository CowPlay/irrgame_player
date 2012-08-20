///*
// * irrgpspThread.h
// *
// *  Created on: Aug 13, 2012
// *      Author: gregorytkach
// */
//
//#ifndef IRRGPSPTHREAD_H_
//#define IRRGPSPTHREAD_H_
//
///*//http://easy-coding.blogspot.com/2009/01/blog-post_26.html
//
//#ifndef __IRR_THREAD_H_INCLUDED__
//#define __IRR_THREAD_H_INCLUDED__
//
//#include "IrrCompileConfig.h"
//#include "irrTypes.h"
//#include "delegate1.h"
//#ifdef _IRR_WINDOWS_
//#include <windows.h>
//#else
//#include "pspdebug.h"
//#include <pspkernel.h>
//#endif
//
//#include "os.h"
//
//namespace game
//{
//﻿  //dublicate attributes
//#ifdef _IRR_WINDOWS_
//﻿  /** Attribute for threads. */
//﻿  enum PspThreadAttributes
//﻿  {
//﻿  ﻿  /** Enable VFPU access for the thread. */
//﻿  ﻿  PSP_THREAD_ATTR_VFPU = 0x00004000,
//﻿  ﻿  /** Start the thread in user mode (done automatically
//﻿  ﻿  if the thread creating it is in user mode). */
//﻿  ﻿  PSP_THREAD_ATTR_USER = 0x80000000,
//﻿  ﻿  /** Thread is part of the USB/WLAN API. */
//﻿  ﻿  PSP_THREAD_ATTR_USBWLAN = 0xa0000000,
//﻿  ﻿  /** Thread is part of the VSH API. */
//﻿  ﻿  PSP_THREAD_ATTR_VSH = 0xc0000000,
//﻿  ﻿  /** Allow using scratchpad memory for a thread, NOT USABLE ON V1.0 */
//﻿  ﻿  PSP_THREAD_ATTR_SCRATCH_SRAM = 0x00008000,
//﻿  ﻿  /** Disables filling the stack with 0xFF on creation */
//﻿  ﻿  PSP_THREAD_ATTR_NO_FILLSTACK = 0x00100000,
//﻿  ﻿  /** Clear the stack when the thread is deleted */
//﻿  ﻿  PSP_THREAD_ATTR_CLEAR_STACK = 0x00200000,
//﻿  };
//#endif
//
//﻿  enum ETHREAD_PRIORITY
//﻿  {
//﻿  ﻿  ETP_LOW = 0x30,
//﻿  ﻿
//﻿  ﻿  ETP_ABOVE_LOW = 0x25,
//
//﻿  ﻿  ETP_MEDIUM = 0x20,
//
//﻿  ﻿  ETP_ABOVE_MEDIUM = 0x15,
//﻿
//﻿  ﻿  ETP_HIGH = 0x10,
//﻿  };
//
//#ifdef _IRR_WINDOWS_
//﻿  typedef HANDLE ThreadType;
//#else
//﻿  typedef SceUID ThreadType;
//#endif
//
//﻿  class irrThread
//﻿  {
//
//﻿  private:
//#ifdef _IRR_WINDOWS_
//﻿  ﻿  static void ThreadFunc(irrThread* who)
//﻿  ﻿  {
//﻿  ﻿  ﻿  (*(who->getCallback()))(who->getData());
//﻿  ﻿  };
//#else
//﻿  ﻿  static  int ThreadFunc(SceSize args, void *argp)
//﻿  ﻿  {
//﻿  ﻿  ﻿  irrThread* who = (irrThread*)argp;
//﻿  ﻿  ﻿  (*(who->getCallback()))(who->getData());
//﻿  ﻿  ﻿  return 0;
//﻿  ﻿  }
//#endif
//
//﻿  public:
//﻿  ﻿
//
//﻿  ﻿  irrThread(ETHREAD_PRIORITY initPriority, delegateThreadCallback* callback, const c8* name = "", void* data = NULL)
//﻿  ﻿  {
//﻿  ﻿  ﻿  Name = name;
//﻿  ﻿  ﻿  Callback = callback;
//﻿  ﻿  ﻿  Data=data;
//
//#ifdef _IRR_WINDOWS_
//﻿  ﻿  ﻿  Handle =  CreateThread(0, 0, reinterpret_cast<LPTHREAD_START_ROUTINE>(ThreadFunc), this, CREATE_SUSPENDED, &ThreadId);
//#else
//﻿  ﻿  ﻿  Handle = sceKernelCreateThread(Name, ThreadFunc, initPriority, 0x10000, PSP_THREAD_ATTR_USER|PSP_THREAD_ATTR_VFPU, 0);
//#endif
//﻿  ﻿  }
//
//﻿  ﻿  ~irrThread()
//﻿  ﻿  {
//#ifdef _IRR_WINDOWS_
//﻿  ﻿  ﻿  CloseHandle(Handle);
//#else
//
//#endif
//﻿  ﻿  ﻿  if(Callback)
//﻿  ﻿  ﻿  ﻿  delete Callback;
//﻿  ﻿  }
//
//﻿  ﻿  // Ôóíêöèÿ çàïóñêà ïîòîêà. Åå íåëüçÿ ñîâìåñòèòü ñ êîíñòðóêòîðîì
//﻿  ﻿  // êëàññà, òàê êàê ìîæåò ñëó÷èòüñÿ, ÷òî ïîòîê çàïóñòèòñÿ äî òîãî,
//﻿  ﻿  // êàê îáúåêò áóäåò ïîëíîñòüþ ñôîðìèðîâàí. À ýòî ìîæåò ñïîêîéíî
//﻿  ﻿  // ïðîèçîéòè, åñëè âûçâàòü pthread_create èëè CreateThread â
//﻿  ﻿  // â êîíñòðóêòîðå. À âûçîâ âèðòóàëüíîé ôóíêöèè â êîíñòðóêòîðå,
//﻿  ﻿  // äà åùå è â êîíñòðóêòîðå íåäîñôîðìèðîâàííîãî îáúåêòà,
//﻿  ﻿  // â ëó÷øåì ñëó÷àå ïðèâåäåò ê ôàòàëüíîé îøèáêå âûçîâà ÷èñòî
//﻿  ﻿  // âèðòóàëüíîé ôóíêöèè, ëèáî â õóäøåì ñëó÷àå ïàäåíèþ ïðîãðàììû
//﻿  ﻿  // ñ íàðóøåíèåì çàùèòû ïàìÿòè. Çàïóñê æå ïîòîêà ïîñëå ðàáîòû
//﻿  ﻿  // êîíñòðóêòîðà èçáàâëÿåò îò ýòèõ ïðîáëåì.
//﻿  ﻿  void start(void* data = NULL)
//﻿  ﻿  {
//#ifdef _IRR_WINDOWS_
//
//﻿  ﻿  ﻿  if(data)
//﻿  ﻿  ﻿  {
//﻿  ﻿  ﻿  ﻿  Data = data;
//﻿  ﻿  ﻿  }
//
//﻿  ﻿  ﻿  ResumeThread(Handle);
//#else
//﻿  ﻿  ﻿  sceKernelStartThread(Handle, sizeof(this), (void*)this);
//#endif
//﻿  ﻿  }
//
//﻿  ﻿  // Ãëàâíàÿ ôóíêöèÿ ïîòîêà, ðåàëèçóþùàÿ ðàáîòó ïîòîêà.
//﻿  ﻿  // Ïîòîê çàâåðøàåòñÿ, êîãäà ýòà ôóíêöèÿ çàêàí÷èâàåò ðàáîòó.
//﻿  ﻿  // Êðàéíå ðåêîìåíäóåòñÿ ëîâèòü ÂÑÅ èñêëþ÷åíèÿ â äàííîé ôóíêöèè
//﻿  ﻿  // ÷åðåç try-catch(...). Âîçíèêíîâåíèå íåëîâèìîãî íèêåì
//﻿  ﻿  // èñêëþ÷åíèÿ ïðèâåäåò ê ìîë÷àëèâîìó ïàäåíèþ ïðîãðàììû áåç
//﻿  ﻿  // âîçìîæíîñòè îáúÿñíèòü ïðè÷èíó.
//﻿  ﻿  //virtual void Execute() = 0;
//
//﻿  ﻿  // Ïðèñîåäèíåíèå ê ïîòîêó.
//﻿  ﻿  // Äàííàÿ ôóíêöèÿ âåðíåò óïðàâëåíèå òîëüêî êîãäà ïîòîê
//﻿  ﻿  // çàâåðøèò ðàáîòó. Ïðèìåíÿåòñÿ ïðè ñèíõðîíèçàöèè ïîòîêîâ,
//﻿  ﻿  // åñëè íàäî îòñëåäèòü çàâåðøåíèå ïîòîêà.
//﻿  ﻿  void join()
//﻿  ﻿  {
//#ifdef  _IRR_WINDOWS_
//﻿  ﻿  ﻿  WaitForSingleObject(Handle,  INFINITE);
//#else
//﻿  ﻿  ﻿  sceKernelWaitThreadEnd(Handle, NULL);
//#endif
//﻿  ﻿  }
//
//﻿  ﻿  // Óíè÷òîæåíèå ïîòîêà.
//﻿  ﻿  // Ïðèíóäèòåëüíî óíè÷òîæàåò ïîòîê èçâíå. Äàííûé ñïîñîá
//﻿  ﻿  // çàâåðøåíèÿ ïîòîêà ÿâëÿåòñÿ êðàéíå íåðåêîìåíäóåìûì.
//﻿  ﻿  // Ïðàâèëüíåå çàâåðøàòü ïîòîê ëîãè÷åñêè, ïðåäóñìîòðåâ
//﻿  ﻿  // â ôóíêöèè Execute() óñëîâèå äëÿ âûõîäà, òàê ñàìûì
//﻿  ﻿  // îáåñïå÷èâ ïîòîêó íîðìàëüíîå çàâåðøåíèå.
//﻿  ﻿  void Kill()
//﻿  ﻿  {
//#ifdef _IRR_WINDOWS_
//﻿  ﻿  ﻿  TerminateThread(Handle, 0);
//#else
//
//#endif
//
//﻿  ﻿  };
//
//﻿  ﻿  //Óñûïëÿåò òåêóùèé ïîòîê
//﻿  ﻿  static void sleep(int time)
//﻿  ﻿  {
//#ifdef _IRR_WINDOWS_
//﻿  ﻿  ﻿  Sleep(time);
//#else
//﻿  ﻿  ﻿  time *= 1000;
//﻿  ﻿  ﻿  sceKernelDelayThread(time);
//#endif
//﻿  ﻿  };
//
//﻿  ﻿  static u32 getCurrentThreadId()
//﻿  ﻿  {
//﻿  ﻿  ﻿  u32 result = 0;
//#ifdef _IRR_WINDOWS_
//﻿  ﻿  ﻿  //  result=GetCurrentThread();
//#else
//﻿  ﻿  ﻿  result = sceKernelGetThreadId();
//#endif
//﻿  ﻿  ﻿  return result;
//﻿  ﻿  }
//
//﻿  private:
//﻿  ﻿  delegateThreadCallback* Callback;
//
//﻿  ﻿  const c8* Name;
//
//﻿  ﻿  void* Data;
//
//﻿  ﻿  ThreadType Handle;
//
//#ifdef _IRR_WINDOWS_
//﻿  ﻿  DWORD ThreadId;
//#else
//﻿  ﻿  int ThreadId;
//#endif
//
//
//﻿  ﻿  delegateThreadCallback* getCallback()
//﻿  ﻿  {
//﻿  ﻿  ﻿  return Callback;
//﻿  ﻿  }
//
//﻿  ﻿  void* getData()
//﻿  ﻿  {
//﻿  ﻿  ﻿  return Data;
//﻿  ﻿  }
//
//﻿  ﻿  // Çàùèòà îò ñëó÷àéíîãî êîïèðîâàíèÿ îáúåêòà â C++
//﻿  ﻿  irrThread(const irrThread&)
//﻿  ﻿  {
//
//﻿  ﻿  }
//
//﻿  ﻿  void operator=(const irrThread&)
//﻿  ﻿  {
//
//﻿  ﻿  }
//﻿  };
//
//} // ext
//
//#endif*/
//
//
//#endif /* IRRGPSPTHREAD_H_ */
