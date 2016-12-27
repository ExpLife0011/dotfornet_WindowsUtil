// HookLibTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <Windows.h>
#include <WinBase.h>
#include <iostream>
#include <cassert>
#include <Hook\HookIat.h>
#include <Hook\HookEat.h>
#include <Hook\IatHook.h>
#include <Hook\HookApi.h>
using std::cout;
using std::endl;

using MBox = int WINAPI(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType);
int WINAPI MessageBoxAHook(
	_In_opt_ HWND hWnd,
	_In_opt_ LPCSTR lpText,
	_In_opt_ LPCSTR lpCaption,
	_In_ UINT uType
)
{
	cout << "Succeed" << endl;
	cout << lpCaption << " - " << lpText << endl;
	return ShellAboutA(hWnd, lpCaption, lpText, NULL);
}


using SW = BOOL WINAPI(
	_In_ HWND hWnd,
	_In_ int nCmdShow);

SW* oldShowWindow = nullptr;

BOOL
WINAPI
ShowWindowHook(
	_In_ HWND hWnd,
	_In_ int nCmdShow)
{
	cout << "ShowWindow - " << hWnd << " - " << nCmdShow << endl;
	if (oldShowWindow)
	{
		return oldShowWindow(hWnd, nCmdShow);
	}
	return true;
}



auto user32dll = "user32.dll";
auto user32dllW = L"user32.dll";
auto mboxName = "MessageBoxA";
auto oldText = "ԭʼ";
auto oldTitle = "ԭʼ";
auto newText = "Hook��";
auto newTitle = "�ɹ�";

void Faild()
{
	cout << "Faild" << endl;
}
void TestIatHook()
{
	MessageBoxA(NULL, oldText, oldTitle, MB_OK);
	auto trueValue = GetProcAddress(LoadLibraryA(user32dll), mboxName);
	PVOID unhookAddr;
	auto oldAddr = Hook::HookIat(NULL, user32dll, mboxName, MessageBoxAHook, &unhookAddr);
	// iathook������ö�̬����ȡ���ɵ�ַ
	if (oldAddr != nullptr && trueValue == oldAddr)
	{
		// ����õ�Hook��ĺ���
		MessageBoxA(NULL, newText, newTitle, MB_OK);
		// ʹ�þɺ���
		reinterpret_cast<MBox*>(oldAddr)(0, "ԭ�������ò���", "XXX", MB_OK);
		// unhook
		if (Hook::UnHookIat(unhookAddr, oldAddr))
		{
			// �ѻָ�
			MessageBoxA(NULL, "�ѻָ�", mboxName, MB_OK);
		}
	}
	else
	{
		Faild();
		return;
	}

	// hook shell32 iat -> user32 ShowWindow
	auto shell32 = LoadLibraryA("shell32.dll");
	oldShowWindow = (SW*)Hook::HookIat(shell32, user32dll, "ShowWindow", ShowWindowHook, NULL);
	if (oldShowWindow)
	{

		ShellAboutA(NULL, "�����������õ�ShowWindow", "=======", NULL);
		// hook����shell32��iat�������ﲻ�ᴥ��,���hook�������iat����ͻ��෴
		ShowWindow(0, 0);
	}
	else
	{
		Faild();
	}
}


void TestEatHook()
{
	MessageBoxA(NULL, oldText, oldTitle, MB_OK);
	auto dllModule = LoadLibraryA(user32dll);
	auto oldValue = GetProcAddress(dllModule, mboxName);

	PDWORD oldFuncRva;
	// 64λ�п����������������Զ��hookʧ�ܣ���Ҫ��������ʽ

	auto oldAddr = Hook::HookEat(dllModule, mboxName, MessageBoxAHook, &oldFuncRva);
	if (oldAddr)
	{
		// eat hook��̬����ȡ���ľͶ���MessageBoxAHook������ַ�ˣ�ֱ�ӵ���ûЧ������Ϊ��ַ��iat��
		auto newValue = GetProcAddress(dllModule, mboxName);
		if ((void*)newValue == (void*)MessageBoxAHook)
		{
			reinterpret_cast<MBox*>(newValue)(0, newText, newTitle, MB_OK);
		}

	}

}
void TestIatHookClass()
{
	do
	{

		auto hook = Hook::IatHook::Instance(NULL);
		assert(hook == Hook::IatHook::Instance(NULL));
		if (!hook->CanIatHook())
		{
			break;
		}
		assert(!hook->Hook(user32dll, "Not Exist", MessageBoxAHook));
		if (!hook->Hook(user32dll, mboxName, MessageBoxAHook))
		{
			break;
		}
		assert(!hook->Hook(user32dll, mboxName, MessageBoxAHook));
		assert(Hook::IatHook::Instance(NULL)->IsHooked(user32dll, mboxName));
		MessageBoxA(NULL, newText, newTitle, MB_OK);
		// ʹ�þɺ���
		reinterpret_cast<MBox*>(hook->GetOldFunction(user32dll, mboxName))(0, "ԭ�������ò���", "XXX", MB_OK);
		if (!hook->UnHook(user32dll, mboxName))
		{
			break;
		}
		// �ѻָ�
		MessageBoxA(NULL, "�ѻָ�", mboxName, MB_OK);
		assert(!Hook::IatHook::Instance(NULL)->IsHooked(user32dll, mboxName));



		// hook shell32 iat -> user32 ShowWindow
		auto shell32Ptr = Hook::IatHook::Instance(L"shell32.dll");
		auto shell32 = (*shell32Ptr)[user32dll];
		auto showWindow = shell32["ShowWindow"];
		auto notExist = shell32["XXXXX"];
		assert(!notExist);
		notExist = ShowWindowHook;
		assert(&notExist == nullptr);
		showWindow = ShowWindowHook;
		oldShowWindow = (SW*)(&showWindow);
		if (oldShowWindow)
		{
			ShellAboutA(NULL, "�����������õ�ShowWindow", "=======", NULL);

			// hook����shell32��iat�������ﲻ�ᴥ��,���hook�������iat����ͻ��෴
			ShowWindow(0, 0);
			return;
		}
	} while (false);
	MessageBoxA(NULL, "ʧ��", "ʧ��", MB_OK);
}

void TestHookApi()
{
	bool ret = false;
	if (Hook::IsLongDistance(MessageBoxA, MessageBoxAHook))
	{
		ret = Hook::HookApi_FF25(MessageBoxA, MessageBoxAHook, 0, nullptr);
	}
	else
	{
		ret = Hook::HookApi_E9(MessageBoxA, MessageBoxAHook, 0, nullptr);
	}
	if (ret)
	{
		MessageBoxA(NULL, newText, newTitle, MB_OK);
	}
	else
	{
		MessageBoxA(NULL, "ʧ��", "ʧ��", MB_OK);
	}
}
void TestHookApi2()
{
	// 32λ��64λ MessageBoxA �Ļ����룬����������㱸�ݳ���
	/* 32

		8B FF                mov         edi,edi
		55                   push        ebp
		8B EC                mov         ebp,esp				e9 32λ���ݵ���Ϊֹ
		6A 00                push        0
		FF 75 14             push        dword ptr [ebp+14h]	ff25 32λ���ݵ���Ϊֹ
		FF 75 10             push        dword ptr [ebp+10h]
		FF 75 0C             push        dword ptr [ebp+0Ch]
		FF 75 08             push        dword ptr [ebp+8]
		E8 18 00 00 00       call        74908860
		5D                   pop         ebp
		C2 10 00             ret         10h
	*/
	/* 64

		48 83 EC 38          sub         rsp,38h
		45 33 DB             xor         r11d,r11d							e9 64λ���ݵ���Ϊֹ
		44 39 1D FA 38 03 00 cmp         dword ptr [7FF8AD8DB928h],r11d		ff25 64λ���ݵ���Ϊֹ
		74 2E                je          00007FF8AD8A805E
		65 48 8B 04 25 30 00 00 00 mov         rax,qword ptr gs:[30h]
		4C 8B 50 48          mov         r10,qword ptr [rax+48h]
		33 C0                xor         eax,eax
		F0 4C 0F B1 15 18 4A 03 00 lock cmpxchg qword ptr [7FF8AD8DCA60h],r10
		4C 8B 15 19 4A 03 00 mov         r10,qword ptr [7FF8AD8DCA68h]
		41 8D 43 01          lea         eax,[r11+1]
		4C 0F 44 D0          cmove       r10,rax
		4C 89 15 0A 4A 03 00 mov         qword ptr [7FF8AD8DCA68h],r10
		83 4C 24 28 FF       or          dword ptr [rsp+28h],0FFFFFFFFh
		66 44 89 5C 24 20    mov         word ptr [rsp+20h],r11w
		E8 D2 02 00 00       call        00007FF8AD8A8340
		48 83 C4 38          add         rsp,38h
		C3                   ret
*/
	PVOID old = nullptr;
	bool ret = false;
	PVOID target = ShellAboutA; // MessageBoxAHook
	
	if (Hook::IsLongDistance(MessageBoxA, target))
	{
#if _WIN64
		ret = Hook::HookApi_FF25(MessageBoxA, target, 14, &old);
#else
		ret = Hook::HookApi_FF25(MessageBoxA, target, 10, &old);
#endif // _WIN64

	}
	else
	{
#if _WIN64
		// ����hook�������ƻ���api��Զ
		ret = Hook::HookApi_E9(MessageBoxA, target, 7, &old);
#else
		ret = Hook::HookApi_E9(MessageBoxA, target, 5, &old);
#endif // _WIN64

	}
	
	if (ret)
	{
		// ShellAboutA ���һ��������ָ�룬MB_OK = 0 ������ָ�����
		MessageBoxA(NULL, newText, newTitle, MB_OK);
		reinterpret_cast<MBox*>(old)(0, "ԭ�������ò���", "XXX", MB_OK);
		delete[] old;
	}
	else
	{
		MessageBoxA(NULL, "ʧ��", "ʧ��", MB_OK);
	}
}

int main()
{
	//if (false)
	//{
	//	TestHookApi();
	//}
	//else
	//{
	//	TestHookApi2();
	//}

	// TestIatHookClass();
	// TestIatHook();
	// TestEatHook();
	// delayimportҪ�޸ı���ѡ��Ȳ�����
	return 0;
}

