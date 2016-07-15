#pragma once
#include "Common.h"
#include "CallbackInstance.h"
#include "ThreadPoolApi.h"
namespace Process
{
	namespace Thread
	{
		namespace Detail
		{

			// function�Ḵ��һ�ݺ��������lambda��catch��ֻ��move�Ķ��󣬻ᵼ�±��벻��
			template<typename TFunc>
			void NTAPI _Callback(PTP_CALLBACK_INSTANCE instance, PVOID param)
			{
				assert(param != nullptr);
				auto data = static_cast<_STD tuple<_STD decay_t<TFunc>>*>(param);
				_STD decay_t<TFunc> func(_STD move(_STD get<0>(*data)));
				delete data;

				CallbackInstance inst(instance);
				func(inst);
			}

		}  // namespace Detail

		// FIX: �õ���API�����µģ���ҪŪһ���ɵİ汾
		// �������û��ʲô���壬ֱ����ppl�ͺ���
		class ThreadPool
		{
		public:
			template<typename T>
			static bool Submit(T& obj)
			{
				assert(obj.GetFunc());
				return obj.Submit(GetEnviron());
			}
			// ���ﴫ��ĺ�����������Ϊ CallbackInstance&
			template<typename TFunc>
			static bool SubmitCallback(TFunc&& func)
			{
				auto funcPtr = new _STD tuple<_STD decay_t<TFunc>>(_STD forward<TFunc>(func));
				assert(funcPtr);
				auto result = Detail::WinApi::TrySubmitThreadpoolCallback(Detail::_Callback<TFunc>, funcPtr, GetEnviron()) != FALSE;
				if (!result)
				{
					delete funcPtr;
				}
				return result;
			}


			template<typename T>
			static bool Register(T& obj)
			{
				assert(obj.GetFunc());
				return obj.Register(GetEnviron());
			}


			static void SetEnviron(PTP_CALLBACK_ENVIRON env);
			static PTP_CALLBACK_ENVIRON GetEnviron();
		protected:
			ThreadPool() = delete;
			~ThreadPool() = delete;
			static void NTAPI Callback(PTP_CALLBACK_INSTANCE instance, PVOID param);
			static PTP_CALLBACK_ENVIRON environ_;


		};

	}  // namespace Thread
}  // namespace Process