#pragma once
#include "DataPtr.h"
#include "GetOriginal.h"
namespace PeDecoder
{
	template<typename TThunkType>
	class ImportThunkIteratorBase
	{
	public:
		friend class ImportThunkIterator<TThunkType>;
		static_assert(_STD is_same<PIMAGE_THUNK_DATA32, TThunkType>::value ||
			_STD is_same<PIMAGE_THUNK_DATA64, TThunkType>::value, "type error");

		ImportThunkIteratorBase(PeImage& pe, TThunkType thunk, TThunkType originalThunk) :
			originalThunk_(originalThunk),
			thunk_(thunk),
			pe_(pe)
		{

		}
		TThunkType GetAddressThunk() const
		{
			return thunk_;
		}
		TThunkType GetNameThunk() const
		{
			return originalThunk_;
		}
		// false��ʾ����ṹ����GetImportByNameȡ������
		bool IsSnapByOrdinal() const
		{
			return GetThunkOrdinal<TThunkType>::IsSnapByOrdinal(originalThunk_);
		}
		// ���Ƚ���IsSnapByOrdinal()�ж�
		PIMAGE_IMPORT_BY_NAME GetImportByName() const
		{
			assert(originalThunk_->u1.AddressOfData != 0);
			assert(!IsSnapByOrdinal());
			return reinterpret_cast<PIMAGE_IMPORT_BY_NAME>(pe_.RvaToDataPtr(originalThunk_->u1.AddressOfData));
		}
		
		// ���Ƚ���IsSnapByOrdinal()�ж�
		typename GetThunkOrdinal<TThunkType>::TResult GetOrdinal() const
		{
			return GetThunkOrdinal<TThunkType>::GetOrdinal(originalThunk_);
		}
		

		PVOID GetFuncAddress() const
		{
			assert(thunk_->u1.Function != 0);
			return pe_.RvaToDataPtr(thunk_->u1.Function);
		}
	protected:
		
		PeImage& pe_;
		TThunkType thunk_;
		TThunkType originalThunk_;
	};

	template<typename TThunkType>
	class ImportThunkIterator :
		public iterator_facade<
		ImportThunkIterator<TThunkType>,
		ImportThunkIteratorBase<TThunkType>,
		forward_traversal_tag>
	{
	public:
		friend class iterator_core_access;

		ImportThunkIterator(PeImage& pe, TThunkType thunk, TThunkType originalThunk) :
			store_(pe, thunk, originalThunk)
		{
		}
	protected:
		bool equal(const ImportThunkIterator & val) const
		{
			return GetStore().originalThunk_ == val.GetStore().originalThunk_ &&
				GetStore().thunk_ == val.GetStore().thunk_;
		}
		void increment()
		{
			++GetStore().originalThunk_;
			++GetStore().thunk_;
			if (GetStore().originalThunk_->u1.AddressOfData == 0)
			{
				// ��ĩβ��
				GetStore().originalThunk_ = nullptr;
				GetStore().thunk_ = nullptr;
			}
		}


		ImportThunkIteratorBase<TThunkType>& dereference() const
		{
			return const_cast<ImportThunkIteratorBase<TThunkType>&>(GetStore());
		}
		ImportThunkIteratorBase<TThunkType>& GetStore()
		{
			return store_;
		}
		const ImportThunkIteratorBase<TThunkType>& GetStore() const
		{
			return store_;
		}
		ImportThunkIteratorBase<TThunkType> store_;
	};


	template<typename TThunkType>
	class ImportThunk
	{
	public:
		typedef ImportThunkIterator<TThunkType> iterator;
		// @firstThunk: address table
		// @firstOriginalThunk: name table �п����� Original
		ImportThunk(PeImage& pe, TThunkType firstThunk, TThunkType firstOriginalThunk) :
			firstOriginalThunk_(firstOriginalThunk),
			firstThunk_(firstThunk),
			pe_(pe)
		{
		}

		ImportThunkIterator<TThunkType> begin() const
		{
			return ImportThunkIterator<TThunkType>(pe_, firstThunk_, firstOriginalThunk_);
		}
		ImportThunkIterator<TThunkType> end() const
		{
			return ImportThunkIterator<TThunkType>(pe_, nullptr, nullptr);
		}
	protected:
		PeImage& pe_;
		TThunkType firstOriginalThunk_;
		TThunkType firstThunk_;
	};
}  // namespace PeDecoder
