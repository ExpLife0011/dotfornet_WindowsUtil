#pragma once
#include "Common.h"

namespace Process
{
	namespace Fiber
	{
		// fls�Ķ����ͺ��԰�
		using ::GetCurrentFiber;
		using ::SwitchToFiber;
		using ::ConvertFiberToThread;
		using ::ConvertThreadToFiber;
		using ::CreateFiber;
		using ::DeleteFiber;
		using ::IsThreadAFiber;
		template<typename T>
		T* GetFiberData()
		{
			return static_cast<T*>(::GetFiberData());
		}


		class Fiber
		{
		public:

			typedef _STD function<void()> Func;
			// ����������bind��lambda���������
			Fiber(Func&& func);
			~Fiber();

			void Switch();
			LPVOID GetAddress();
		protected:
			Fiber(const Fiber&) = delete;
			Fiber& operator=(const Fiber&) = delete;

			static void WINAPI Run(LPVOID param);
			// ��ǰfiberָ��
			LPVOID fiber_;
			// ִ����
			Func func_;
		};
	}  // namespace Fiber
}  // namespace Process