#pragma once
#include <msclr\marshal_cppstd.h>  
#include <Windows.h>
using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Collections;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Reflection;
using namespace msclr::interop;

//���Լ���peid����������ע����peid������
//////////////////////////////////////////////
//#ifdef _DLLMACRO
//#define	 DllExport	__declspec(dllexport)
//#else
//#define	 DllExport	__declspec(dllimport)
//#endif
//
//DllExport DWORD DoMyJob(HWND hMainDlg, char *szFname, DWORD lpReserved, LPVOID lpParam);
//DllExport LPSTR LoadDll();

//DWORD DoMyJob(HWND hMainDlg, char *szFname, DWORD lpReserved, LPVOID lpParam)
//{
//	//hMainDlg: HWND of PEiD window
//	//szFname: Filename
//	//lpReserved: PEiD passes 'PEiD' as the value
//	//lpParam: NULL passed, for future use
//
//	// Write your main code here
//
//	return 1;
//}
//
//LPSTR LoadDll()
//{
//	return "Name of the plugin";
//}
///////////////////////////////////////////////////

// ����dllʱִ�У�����������ʾ�ڲ˵���,����������ʼ��
interface class IPluginBase
{
	String^ GetName();
};


// �й�dll�õ�
interface class IPlugin : public IPluginBase
{
public:
	void OnFileOpened(IntPtr peBuff, long long size, bool isReadonly); // ���ļ���ʱ����
	void OnFileClosed();
	List<ToolStripMenuItem^>^ GetMenus();
};



// ���й�dll�Ľӿ�ת��, Ҫ��extern "C" ������
// TODO: �ӿڴ��޸ģ��ȷ���
ref class UnManagedPlugin : public IPlugin
{
	// LPSTR GetName()
	typedef LPSTR(*GetNameDef)();
	GetNameDef getName;

	// void OnFileOpened(void*, long long, bool)
	typedef void(*OnFileOpenedDef)(void*, long long, bool);
	OnFileOpenedDef onFileOpened;

	// void OnFileClosed()
	typedef void(*OnFileClosedDef)();
	OnFileClosedDef onFileClosed;

	// LPSTR* GetMenuNamesDef() ���ز˵�����ָ������
	typedef LPSTR* (*GetMenuNamesDef)();
	GetMenuNamesDef getMenuNames;

	// MenuClickDef* GetMenuFunctionsDef() ���غ���ָ������,��������ΪMenuClickDef
	typedef void(*MenuClickDef)();
	typedef MenuClickDef* (*GetMenuFunctionsDef)();
	GetMenuFunctionsDef getMenuFunctions;

	// int GetMenuCountDef()
	typedef int(*GetMenuCountDef)();
	GetMenuCountDef getMenuCount;

	Dictionary<String^, Action^>^ funcMap;
	void OnClick(System::Object ^sender, System::EventArgs ^e);
	UnManagedPlugin();
public:
	static UnManagedPlugin^ CreateInstance(HMODULE dll);
	virtual void OnFileOpened(IntPtr base, long long size, bool isReadonly);
	virtual void OnFileClosed();
	virtual List<ToolStripMenuItem^>^ GetMenus();


	virtual String ^ GetName();

};


// �˵����������peid��
ref class PeidPlugin : public IPluginBase
{
	typedef LPSTR(__stdcall *LoadDllDef)();
	LoadDllDef loadDll;

	typedef DWORD  (__stdcall *DoMyJobDef)(HWND hMainDlg, char *szFname, DWORD lpReserved, LPVOID lpParam);
	DoMyJobDef doMyJob;

	PeidPlugin();
public:
	static PeidPlugin^ CreateInstance(HMODULE dll);
	virtual String^ GetName();

	int DoMyJob(IntPtr hMainDlg, String^ szFname, int lpReserved, IntPtr lpParam);
};

ref class PluginFactory
{
	PluginFactory();
	static void AddPlugin([In] Dictionary<String^, IPluginBase^>^ %dic, IPluginBase^ plugin);
	static bool IsSameMethod(MethodInfo^ method1, MethodInfo^ method2);
	static void LoadAssemblyPlugin(Assembly^ assembly, [In] Dictionary<String^, IPluginBase^>^ %result);
	static IPluginBase^ LoadUnManagedPlugin(String^ path);
	
public:
	static Dictionary<String^, IPluginBase^>^ GetPlugins(String^ dirName);


};

ref class PluginMenuManager
{
	IntPtr hMainDlg;
	String^ path;
	IntPtr base;
	long long size;
	bool isReadonly;
	bool isFileOpen;
	Dictionary<String^, IPluginBase^>^ plugins;
	ToolStripMenuItem^ menu;
	ToolStripMenuItem^ BuildMenu(String^ menuName, PeidPlugin^ plugin);
	ToolStripMenuItem^ BuildMenu(String^ menuName, IPlugin^ plugin);
	void RunPeidPlugin(Object^ plugin);
	void OnClick(System::Object ^sender, System::EventArgs ^e);
	void AddMenu(ToolStripMenuItem^ item);
public:
	PluginMenuManager(ToolStripMenuItem^ menu);
	void OnOpenFIle(IntPtr hMainDlg, String^ path, IntPtr base, long long size, bool isReadonly);
	void OnCloseFile();
};

