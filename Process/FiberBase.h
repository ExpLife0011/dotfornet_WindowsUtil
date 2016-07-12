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
		using ::GetFiberData;
		template<typename T>
		inline T* GetFiberData()
		{
			return static_cast<T*>(::GetFiberData());
		}
		// ���ǿ�winnt�ó��Ľ���
		void SetCurrentFiberData(void* ptr);
		void SetFiberData(PVOID fiber, void* ptr);

		// ������ܲ��ԣ���һЩ��Ա��ֵ���ԣ�Ӧ����һ������teb������
		const PNT_TIB GetCurrentFiberContext();

		template<typename T>
		inline T* GetFiberData(PVOID fiber)
		{
			assert(fiber != nullptr);
			return static_cast<T*>(*(PVOID *)fiber);
		}




		namespace Detail
		{

			struct FiberDeletor
			{
				void operator()(void* fiber);
			};

			template<typename TChild, typename TStorage>
			class FiberBase
			{
			public:
				virtual ~FiberBase() = default;
				LPVOID NativeHandle()
				{
					return fiber_.get();
				}
			protected:
				typedef TStorage TStorage;
				typedef FiberBase Base;
				using TStoragePtr = _STD unique_ptr<TStorage>;
				using FiberPtr = _STD shared_ptr<void>;


				struct TStorageParam
				{
					PVOID Creator;
					TStoragePtr Storage;
				};

				FiberBase()
				{
				}

				// ע�ⴴ�������в��ܳ����쳣
				// ����Ĳ���ΪTStorage�Ĺ������
				template<typename... TArgs>
				FiberBase(TArgs... args)
				{
					assert(!fiber_);
					PVOID currentThreadFiber = nullptr;
					bool isThreadAFiber = Process::Fiber::IsThreadAFiber() != 0;
					if (isThreadAFiber)
					{
						currentThreadFiber = Process::Fiber::GetCurrentFiber();
					}
					else
					{
						currentThreadFiber = Process::Fiber::ConvertThreadToFiber(NULL);
						if (currentThreadFiber == nullptr)
						{
							return;
						}
					}
					assert(currentThreadFiber != nullptr);

					TStoragePtr storage(new TStorage(_STD forward<TArgs>(args)...));
					assert(storage);

					// ����Storage����ָ�룬�ûص�����ָ�븱�����ⲿ������
					auto param = new TStorageParam{ currentThreadFiber, _STD move(storage) };

					// Ĭ��stacksize
					fiber_ = FiberPtr(Process::Fiber::CreateFiber(0, Run, param), FiberDeletor());
					if (!fiber_)
					{
						return;
					}

					// �ȵ��ص����TStorageParam��delete�ˣ���ֹ��ʹ��ʱ���й¶
					Switch();

					if (!isThreadAFiber)
					{
						Process::Fiber::ConvertFiberToThread();
					}
				}




				void Switch()
				{
					// �л��̱߳���ת��Ϊfiber
					assert(Process::Fiber::IsThreadAFiber());

					assert(fiber_);
					Process::Fiber::SwitchToFiber(fiber_.get());
				}


				static void WINAPI Run(LPVOID param)
				{
					assert(param != nullptr);
					auto storageParam = static_cast<TStorageParam*>(param);
					auto creatorFiber = storageParam->Creator;
					// �ص�����Storage����ָ�룬
					auto storage = _STD move(storageParam->Storage);
					delete storageParam;

					// ��������fiberdata
					Process::Fiber::SetCurrentFiberData(storage.get());

					// �ٴ��лؾ����к���(��ʱ���ܻ�ָ�fiber��thread)
					Process::Fiber::SwitchToFiber(creatorFiber);

					// �������������Ԫ
					TChild::Callback(storage);
					// ���н�����δ����
					assert(false);
					__assume(false);
				}

				FiberPtr fiber_;
			};
		}  // namespace Detail
	}  // namespace Fiber
}  // namespace Process