#pragma once
namespace PE
{
	class InitStruct
	{
	protected:
		bool isInitialized;
		virtual bool InitFunc() = 0;
	public:

		InitStruct();
		// ��ʼ��ʧ�ܷ���false
		bool Init();
		bool IsInit();
		virtual ~InitStruct();
	};

}  // namespace PE
