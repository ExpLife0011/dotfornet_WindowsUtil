#pragma once
#include "..\LazyLoad\LazyLoadSystemApi.h"
namespace Process
{
	namespace Hook
	{
#pragma  pack(push)
#pragma pack(1)
#ifndef _WIN64

		typedef struct _CopyAsm
		{
			_CopyAsm()
			{
				Pushad = 0x60;
				Cld = 0xfc;
				MovEsi = 0xbe;
				MovEdi = 0xbf;
				XorEcxEcx[0] = 0x33;
				XorEcxEcx[1] = 0xc9;
				MovCl5[0] = 0xb1;
				MovCl5[1] = 0x5;
				RepMovsb[0] = 0xf3;
				RepMovsb[1] = 0xa4;
				Popad = 0x61;
			}
			void SetAddress(DWORD des, DWORD res)
			{
				EdiAddress = des;
				EsiAddress = res;
			}
			UINT8 Pushad;
			UINT8 Cld;
			UINT8 MovEsi;
			DWORD EsiAddress;
			UINT8 MovEdi;
			DWORD EdiAddress;
			UINT8 XorEcxEcx[2];
			UINT8 MovCl5[2];
			UINT8 RepMovsb[2];
			UINT8 Popad;
		};
		typedef struct _JmpAddrAsm
		{
			_JmpAddrAsm()
			{
				Code = 0xe9;
			}
			void SetDesAddr(DWORD currAddr, DWORD des)
			{
				Value = des - ((DWORD)currAddr + 5);
			}
			UINT8 Code;
			DWORD Value;
		};
		typedef struct _PushDwordAsm
		{
			_PushDwordAsm()
			{
				Code = 0x68;
			}
			void SetVal(DWORD val)
			{
				Value = val;
			}
			UINT8 Code;
			DWORD Value;
		};
		typedef struct _ApiHookStruct
		{
			void Init(PVOID apiAddress, PVOID hookFunc)
			{
				auto ggg =Process::LazyLoad::_VirtualProtect(apiAddress, sizeof(_JmpAddrAsm), PAGE_EXECUTE_READWRITE, NULL);
				this->ApiAddress = apiAddress;
				memcpy(SaveBuff, apiAddress, sizeof(SaveBuff));
				Hook.Ret = 0xc3;
				JmpUnHook.SetDesAddr((DWORD)apiAddress, (DWORD)&this->UnHook);
				UnHook.JmpHookFunc.SetDesAddr((DWORD)&this->UnHook.JmpHookFunc, (DWORD)hookFunc);

				UnHook.PushHook.SetVal((DWORD)&this->PushReturn);
				UnHook.Copy.SetAddress((DWORD)apiAddress, (DWORD)SaveBuff);
				Hook.Copy.SetAddress((DWORD)apiAddress, (DWORD)&this->JmpUnHook);

			}
			// ԭ����ָ��
			PVOID ApiAddress;

			// д��api��ͷ�Ĵ���
			_JmpAddrAsm JmpUnHook;

			// ����api��ͷ�Ĵ���
			UINT8 SaveBuff[5];

			// hook����
			_PushDwordAsm PushReturn;
			struct
			{
				_CopyAsm Copy;
				UINT8 Ret;
			}Hook;

			// unhook����, �滻���ص�ַΪhook
			struct
			{
				_CopyAsm Copy;
				// pop edx
				// mov [pushreturn+1],edx
				
				_PushDwordAsm PushHook;
				// ����hook����
				_JmpAddrAsm JmpHookFunc;
			}UnHook;

		}ApiHookStruct, *PApiHookStruct;

#endif
#pragma  pack(pop)
		// hook����������ԭ�Ⱥ���
		PApiHookStruct HookApi(PVOID desFunc, PVOID hookFunc);
	}
}