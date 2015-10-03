
#include "CppUnitTest.h"
#include <iostream>
#include <string>
#include <strstream>
#include <Process\LazyLoad\LazyLoadSystemApi.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;
namespace UnitTest1
{

	// ����32λ����
	TEST_CLASS(TestLoadWinApi)
	{

	public:
		
		TEST_METHOD(Load_MessageBoxA)
		{
			using namespace Process::LazyLoad;
			// ��һ�����õ�ȡPEB,����PEB,��ȡ�Ѿ������ntdll.dll���,ʹ��pe���������ldrloaddll����ָ��,
			if (!User32_Dll.Load())
			{
				Assert::Fail();
			}
			// ��һ���õ�ʹ�øú���ָ������user32.dll,��ʹ��pe������ȡmsgboxָ��
			if (!User32_Dll._MessageBoxA)
			{
				Assert::Fail();
			}
			
			// ��һ��ת���������ú���, ָ��������÷�ʽ��stdcall���ᵼ�³���
			User32_Dll._MessageBoxA(0, "�ɹ�", "��̬����", MB_OK);
		}
	private:
		
	};
}