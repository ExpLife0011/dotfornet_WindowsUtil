#pragma once
#include "Common.h"
#include "FiberBase.h"
#include "CoroutineIterator.h"

namespace Process
{
	namespace Fiber
	{
		// Э�̣��÷��е�����c#��
		// ע��һ����ʼ�������߳̾ͻᱻתΪ�˳̣��о�ûʲôӰ�죬�Ͳ�ת����
		// ���ص��õ�һ���������Ǻ���ָ�룩����
		// ���߳����δ���ԣ�������bug
		// FIX: �����е�һ��ʱ����fiber����ʹ�ں����д�������ʱ����������fiber��Ҳ��������⣨windows�Ĺ�������ν��
		// ����ܿ���context��������fiberʱ���޸�eip��������returnӦ�ÿ���


		namespace Detail
		{

			template<typename TRet>
			_STD enable_if_t<IsSavePointer<TRet>::value>
				YieldReturn(CoroutineParamType<TRet> ret)
			{

				auto data = Process::Fiber::GetFiberData<Detail::CoroutineStorageHead<TRet>>();
				assert(data);
				assert(data->ContextPtr);

				data->ContextPtr->Ret = const_cast<CoroutineStorageType<TRet>>(&ret);

				Detail::_SwitchToLastFiber(data);
			}

			template<typename TRet>
			_STD enable_if_t<!IsSavePointer<TRet>::value>
				YieldReturn(CoroutineParamType<TRet> ret)
			{
				auto data = Process::Fiber::GetFiberData<Detail::CoroutineStorageHead<TRet>>();
				assert(data);
				assert(data->ContextPtr);
				data->ContextPtr->Ret = ret;

				Detail::_SwitchToLastFiber(data);
			}
			template<typename TRet>
			auto GetYieldReturnFunc()
			{
				return YieldReturn<TRet>;
			}
		}  // namespace Detail







		// ע��������˳����޸����ô��������ֵ���ڶ��ε�����ʱ������µ�ֵ
		template<typename TRet, typename TFunc, typename... TArgs>
		class Coroutine
		{
		public:

			using ReturnFunc = decltype(Detail::GetYieldReturnFunc<TRet>());
			typedef Detail::CoroutineIterator<TRet, TFunc, ReturnFunc, TArgs...> iterator;
			Coroutine(TFunc&& func, TArgs... args) :
				func_(_STD make_shared<Detail::CoroutineFuncStorage<TFunc, ReturnFunc, TArgs...>>(
					_STD move(func),
					_STD forward_as_tuple<ReturnFunc, TArgs...>(Detail::GetYieldReturnFunc<TRet>(), _STD forward<TArgs>(args)...)))
			{
			}

			iterator begin()
			{
				iterator result(func_);
				++result;
				return result;
			}
			iterator end()
			{
				return iterator();
			}

			void RetsetParams(TArgs... args)
			{
				_STD get<static_cast<int>(Detail::_CoroutineFuncStorageIndex::_Args)>(*func_) =
					_STD forward_as_tuple<ReturnFunc, TArgs...>(Detail::GetYieldReturnFunc<TRet>(), _STD forward<TArgs>(args)...);
			}
		protected:
			Detail::CoroutineFuncStoragePtr<TFunc, ReturnFunc, TArgs...> func_;
		};

		template<typename TRet, typename TFunc, typename... TArgs>
		Coroutine<TRet, TFunc, TArgs...> MakeCoroutine(TFunc&& func, TArgs... args)
		{
			return Coroutine<TRet, TFunc, TArgs...>(_STD move(func), _STD forward<TArgs>(args)...);
		}
	}  // namespace Fiber
}  // namespace Process