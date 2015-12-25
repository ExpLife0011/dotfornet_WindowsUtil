#pragma once
#include <Windows.h>
#include "..\Common\PeStruct.h"
namespace PE
{
	class DataDirectoryBase :public PeStruct
	{
	protected:
		PIMAGE_DATA_DIRECTORY dataDirectory;
		PDWORD size;
	public:
		DataDirectoryBase(PeDecoder& pe);
		PVOID DirectoryEntryToData();
	};
	template<typename DataDirectoryChild, typename DataType>
	class DataDirectory_DataType :public DataDirectoryBase
	{
	protected:
		typedef DataDirectory_DataType<DataDirectoryChild, DataType> OverloadDirectoryEntryToData;
		DataType data;
		virtual void Init()
		{
			if (dataDirectory)
			{
				size = &dataDirectory->Size;
				DataDirectoryChild* child = static_cast<DataDirectoryChild*>(this);
				data = reinterpret_cast<DataType>(child->DirectoryEntryToData()); // ִ�������
			}
			else
			{
				size = NULL;
				data = NULL;
			}
		}
	public:
		// ��Ҫ���жϽṹ���ڲ��ܽ�����һ������
		bool IsExist()
		{
			return data != NULL;
		}
		DataDirectory_DataType(PeDecoder& pe) :DataDirectoryBase(pe)
		{
		}
	};
	// ��Indexȡ��PIMAGE_DATA_DIRECTORY������rvaָ�����ݴ洢��data��
	template<typename DataDirectoryChild, typename DataType, int Index>
	class DataDirectory :public DataDirectory_DataType<DataDirectoryChild, DataType>
	{
		friend DataDirectoryChild;
	public:
		typedef DataDirectory<DataDirectoryChild, DataType, Index> DataDirectoryBase;

		DataDirectory(PeDecoder& pe) :DataDirectory_DataType<DataDirectoryChild, DataType>(pe)
		{
			dataDirectory = peDecoder.GetDataDirectory(Index);
			Init();
		}


	};
}
