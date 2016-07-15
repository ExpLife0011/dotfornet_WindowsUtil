#include "stdafx.h"
#include "ThreadPool.h"
void Process::Thread::ThreadPool::SetEnviron(PTP_CALLBACK_ENVIRON env)
{
	environ_ = env;
}

PTP_CALLBACK_ENVIRON Process::Thread::ThreadPool::GetEnviron()
{
	return environ_;
}
void Process::Thread::ThreadPool::Callback(PTP_CALLBACK_INSTANCE instance, PVOID param)
{
	assert(param != nullptr);
	
	auto funcPtr = static_cast<std::function<void(CallbackInstance&)>*>(param);
	// ����try/cacth����ֹ���������еĶ������쳣�ڴ�й¶������������˵
	std::function<void(CallbackInstance&)> func(_STD move(*funcPtr));

	delete funcPtr;
	CallbackInstance inst(instance);
	func(inst);
}
PTP_CALLBACK_ENVIRON Process::Thread::ThreadPool::environ_ = nullptr;