#pragma once
#include "Common.h"
#include "UnpackTupleInvoke.h"
#include "FiberBase.h"
namespace Process
{
	namespace Fiber
	{
		// ���н���ʱ��Ҫreturnһ��fiberָ�����л���������������������е�һ��ʱ����fiber�����ܱ�֤�����д�������ʱ��������
		// FIX: ���Ըĳ���function<void*()>�洢��Ȼ����bind�����죬���ǲ�����&&ʱ���벻��
		namespace Detail
		{

			template<typename TFunc, typename... TArgs>
			class Fiber :
				public Detail::FiberBase<
				Fiber<TFunc, TArgs...>,
				_STD tuple<TFunc&&, _STD tuple<TArgs&&...>>>
			{
			public:
				friend TFiberBase;
				Fiber(TFunc&& func, TArgs&&... args) :
					TFiberBase(_STD forward<TFunc>(func), _STD forward_as_tuple(_STD forward<TArgs>(args)...))
				{

				}

				~Fiber() = default;
				using FiberBase::Switch;

			protected:
				enum class _FiberTupleIndex :int
				{
					_Func,
					_Args
				};
				static void* WINAPI Callback(const TStoragePtr& storage)
				{
					assert(storage);

					auto& func = _STD get<static_cast<int>(_FiberTupleIndex::_Func)>(*storage);

					return Tuple::Invoke(func, _STD get<static_cast<int>(_FiberTupleIndex::_Args)>(*storage));
				}
			};
		}  // namespace Detail

		template<typename TFunc, typename... TArgs>
		Detail::Fiber<TFunc, TArgs...> MakeFiber(TFunc&& func, TArgs&&... args)
		{
			return Detail::Fiber<TFunc, TArgs...>(_STD forward<TFunc>(func), _STD forward<TArgs>(args)...);
		}


	}  // namespace Fiber
}  // namespace Process