#pragma once
#include <cassert>
#include <Windows.h>
#include <WinBase.h>
#include <WinTrust.h>
#include <memory>
namespace PE
{

	class DosHeader;
	class NtHeader;
	class SectionHeaders;
	class RelocDirectory;
	class ExportDirectory;
	class ImportDirectory;
	class ResourceDirectory;
	class EntryExceptionDirectory;
	class SecurityDirectory;
	class DebugDirectory;
	class ArchitectureDirectory;
	class GlobalptrDirectory;
	class TlsDirectory;
	class LoadConfigDirectory;
	class BoundImportDirectory;
	class IatDirectory;
	class DelayImportDirectory;
	class ComDescriptorDirectory;

	// PE������, ������������س�����ļ�
	// TODO: ����Ŀ¼����ֻ����˵��뵼����\��Դ\�ض�λ\�ڵĶ�ȡ��
	class PeDecoder
	{


		PBYTE base;

		bool isMapped;
		bool isPE;
		bool hasNtHeader32;
		bool isBinded;
		bool isAttached;
		void BindPtr();

	public:
		// �����ӳٴ����ӽṹ
		template<typename T>
		class LazyInstance
		{
			_STD shared_ptr<T> data;
			PeDecoder* peDecoder;
			void Bind(PeDecoder* val)
			{
				peDecoder = val;
			}
			void Reset()
			{
				data = NULL;
				/*if (data)
				{
					data->Reset();
				}*/
			}
			LazyInstance()
			{
				data = NULL;
			}
		public:
			friend PeDecoder;

			const _STD shared_ptr<T>& operator->()
			{
				if (!data && peDecoder->isAttached)
				{
					data = _STD make_shared<T>(*peDecoder);
				}
				return data;
			}
			const _STD shared_ptr<T>& operator()()
			{
				return this->operator->();
			}

		};
		PeDecoder();
		~PeDecoder() = default;
		void Clear();
		explicit PeDecoder(const PeDecoder & pe) = delete;
		bool Attach(PVOID base, bool isMapped);
		void Dettach();
		PVOID GetBase();
		LazyInstance<DosHeader> GetDosHeader;
		LazyInstance<NtHeader> GetNtHeader;
		LazyInstance<SectionHeaders> GetSection;
		LazyInstance<RelocDirectory> GetReloc;
		LazyInstance<ExportDirectory> GetExport;
		LazyInstance<ImportDirectory> GetImport;
		LazyInstance<ResourceDirectory> GetResource;
		LazyInstance<EntryExceptionDirectory> GetException;
		LazyInstance<SecurityDirectory> GetSecurity;
		LazyInstance<DebugDirectory> GetDebug;
		LazyInstance<ArchitectureDirectory> GetArchitecture;
		LazyInstance<GlobalptrDirectory> GetGlobalptr;
		LazyInstance<TlsDirectory> GetTls;
		LazyInstance<LoadConfigDirectory> GetLoadConfig;
		LazyInstance<BoundImportDirectory> GetBoundImport;
		LazyInstance<IatDirectory> GetIat;
		LazyInstance<DelayImportDirectory> GetDelayImport;
		LazyInstance<ComDescriptorDirectory> GetComDescriptor;

		bool IsMapped() const;
		bool HasNtHeader32() const;
		bool IsPE() const;
		bool IsAttached() const;
		PIMAGE_SECTION_HEADER RvaToSection(DWORD rva);
		PIMAGE_SECTION_HEADER OffsetToSection(DWORD fileOffset);
		DWORD RvaToOffset(DWORD rva);
		DWORD OffsetToRva(DWORD fileOffset);
		PVOID GetRvaData(DWORD rva);
		PIMAGE_DATA_DIRECTORY GetDataDirectory(DWORD index);
		PVOID DirectoryEntryToData(DWORD index, PDWORD* size);

		// TODO: ��Ҫ��ӵ����ݣ��뵽���ٲ���
		// ���ļ����뵽�ڴ����У��ɴ������ļ������������루������������飩����Ҫ�ض�λ��
		// �༭�����ӽṹ���ڸ�����֧������д�������ļ���F���к��ڴ棨M����
		// ͳ�ƽṹ��϶������peͷ�в���Ҫ�Ĳ��֣�FM
		// �ƶ���ڵ㣨�Ӵ��룬��Ҫ�Ҽ�϶����ӽڣ�FM
		// �ƶ���ڵ㣨���ƴ��룬��Ҫ�Ҽ�϶��ӽںͶ����볤�ȣ�hook������д�����ȣ������Ƶ��漰�ض�λ�ĵط���Ҫ����һ�£�FM
		// ������ӣ�FM
		// �޸�����
		// �����޸�

		// ����ÿ���ṹ�Դ� �Ĳ飨����д
		// ���������Դ�ɾ

		// DosHeader
		// ɾ��dos stub ����Ҫ�ض�λ���ƶ��ڣ�F

		// NtHeader
		// �ƶ�������ƶ����������Ľṹһ���ƶ���F

		// Section
		// �ƶ��ڵ�λ�ã���Ҫ�ض�λ��FM
		// ���ӣ�F
		// ɾ��������Ҫ�ܰ�ԭ�����ݺϲ��������ط�ȥ
		// �򵥼ӽ��ܣ���Ҫ��ӽ��ܴ�����Ϊ��ڵ㣨�ض�λ������Ҫ���沢ɾ����ʹ�ý��ܴ����ض�λ��F

		// Reloc
		// ���ļ�ӳ�䵽�ڴ��õ��ض�λ
		// �����ƶ�����Ҫ���ض�λ��FM
		// ���ӣ�F
		// ֻ��ֱ��ɾ������֮���ܲ�������

		// Export
		// �޸ĵ�������F
		// ��ӵ������ļ���������������F
		// ɾ������F

		// Import
		// ��ӵ��루F
		// ɾ�����루�����ɾ���еĵ����Ƚϸ��ӣ������ض�λ���Ҷ�Ӧλ�ã�����F

		// Resource
		// ��λ�޸����ã�F


	};

}  // namespace PE
