#pragma once

#include "Common.h"
#include "CallbackBase.h"
#include "CallbackInstance.h"
namespace Process
{
	namespace Thread
	{
		// �ӳٵ��ύʱ�Ŵ�����ע���һ���ύʱ���̰߳�ȫ�������ṹҲһ��
		class ThreadPoolWork :
			public Detail::CallbackBase<_STD function<void(CallbackInstance&, ThreadPoolWork&)>>
		{
		public:
			ThreadPoolWork(Func&& func);

			~ThreadPoolWork();
			void WaitForCallbacks(bool cancelPendingCallbacks = false);
			friend class ThreadPool;
		protected:
			bool Submit(PTP_CALLBACK_ENVIRON env);
			static void NTAPI Callback(PTP_CALLBACK_INSTANCE instance, PVOID param, PTP_WORK work);
			PTP_WORK work_;
		};
	}  // namespace Thread
}  // namespace Process