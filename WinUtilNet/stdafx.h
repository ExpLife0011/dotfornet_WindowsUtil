#pragma once
// �����Ŀ��װpedecoderֻ����������c#��ʹ�ã�ֻ���ǽ���������һ�ζ���������), ֻ����غ�����װ�������ò����ľ����ˣ�
// ����һЩ����ʲô�ı����õ�����ģʽ��д�ģ����ֱ�ӵ������飨��Ϊ�ؼ�һ��ȫ����ʾ��

// �õ�������IntPtr�ڶ�ȡ�ļ�ʱ��ʾƫ���������ڴ�ʱ��ʾ�ڴ�ָ�룬���ֵ��ʱ���ȡ�����ֳ�������������64λ�¶�ȡ�ļ�ʱ��ʾ�ֳ�����
// ����ֻ��32λ�������ļ����������

// FIX: ��Ϊ��Ҫÿ��ֵ�������Offset�������PtrToStructureȡ���ݻ�ò���ָ�룬Ϊÿ����Ա��Ӽ���ƫ�����Ĵ�����Ҫд�ܶࣨ����û���ɣ������һ����ȡ�ָ������õĲ����
// ������ʱ���ñ�����ȡָ�룬���뵽���õ����滻

#include <PeImage\PeDecoder.h>
#define NAMESPACE Wrapper
namespace NAMESPACE {

	using namespace System;
	using namespace System::Diagnostics;
	using namespace System::Runtime::InteropServices;
	using namespace System::ComponentModel;
	// �������ļ�ʱ��Ҫִ��
	interface class IReset
	{
		void Reset() = 0;
	};


}


//#include "Converters.h"
//#include "StructOffset.h"
//#include "UITypeEditor.h"
//#include "UnmanagedMemory.h"
//#include "UnmanagedArray.h"
//#include "UnmanagedValue.h"
//#include "PeStructWrapper.h"
//#include "UnmanagedEnum.h"

