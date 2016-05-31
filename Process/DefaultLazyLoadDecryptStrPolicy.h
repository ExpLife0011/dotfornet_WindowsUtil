#pragma once
namespace Process
{
	namespace LazyLoad
	{
		namespace Detail
		{
			// ������ӽ���
			struct DefaultLazyLoadDecryptStrPolicyW
			{
				typedef LPCWSTR EncryptStr;
				typedef LPCWSTR DecryptStr;
				// ��ָ�����ͽ���ΪĿ�����ͣ���string��
				static DecryptStr Decrypt(EncryptStr str);
				// ȡĿ������ȡ�ַ���ָ�루�ڲ�c_str���У�
				static LPCWSTR GetStr(DecryptStr& str);
			};
			struct DefaultLazyLoadDecryptStrPolicyA
			{
				typedef LPCSTR EncryptStr;
				typedef LPCSTR DecryptStr;
				static DecryptStr Decrypt(EncryptStr str);
				static LPCSTR GetStr(DecryptStr& str);
			};
		}  // namespace Detail


	}  // namespace LazyLoad
}  // namespace Process
