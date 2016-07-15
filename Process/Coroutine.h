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
		// ����������yield returnʱҪ��ȷ˵��
		// ���߳����δ���ԣ�������bug


		// ע�����������Ҫ��Э����ʹ��, ����õ��Ľ���ǲ�ȷ����
		// ��Ҫreturn��ͬ���͵Ķ���������Ҳ�ǲ�ȷ����
		template<typename TRet>
		_STD enable_if_t<Detail::IsPointerReturnType<TRet>::value> YieldReturn(TRet& ret)
		{
			
			auto data = Process::Fiber::GetFiberData<Detail::CoroutineStorageHead<TRet>>();
			assert(data);
			data->ContextPtr->Ret = &ret;

			Detail::_SwitchToLastFiber(data);
		}

		template<typename TRet>
		_STD enable_if_t<!Detail::IsPointerReturnType<TRet>::value> YieldReturn(TRet&& ret)
		{
			auto data = Process::Fiber::GetFiberData<Detail::CoroutineStorageHead<TRet>>();
			assert(data);
			data->ContextPtr->Ret = ret;

			Detail::_SwitchToLastFiber(data);
		}

		


		// ע��������˳����޸����ô��������ֵ���ڶ��ε�����ʱ������µ�ֵ
		template<typename TRet, typename TFunc, typename... TArgs>
		class Coroutine
		{
		public:
			typedef Detail::CoroutineIterator<TRet, TFunc, TArgs...> iterator;
			Coroutine(TFunc&& func, TArgs... args) :
				func_(
					_STD make_shared<Detail::CoroutineFuncStorage<TFunc, TArgs...>>(
						_STD move(func),
						_STD make_tuple(_STD forward<TArgs>(args)...)))
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
					_STD make_tuple<TArgs...>(_STD forward<TArgs>(args)...);
			}
		protected:
			Detail::CoroutineFuncStoragePtr<TFunc, TArgs...> func_;
		};

		template<typename TRet, typename TFunc, typename... TArgs>
		Coroutine<TRet, TFunc, TArgs...> MakeCoroutine(TFunc&& func, TArgs... args)
		{
			return Coroutine<TRet, TFunc, TArgs...>(_STD move(func), _STD forward<TArgs>(args)...);
		}
	}  // namespace Fiber
}  // namespace Process