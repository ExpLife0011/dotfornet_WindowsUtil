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
int main()
{
	// TestIatHookClass();
	//TestIatHook();
	// TestEatHook();
	// delayimportҪ�޸ı���ѡ��Ȳ�����
	return 0;
}

