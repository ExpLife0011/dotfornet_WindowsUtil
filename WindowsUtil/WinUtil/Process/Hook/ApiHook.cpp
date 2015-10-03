#include "ApiHook.h"

namespace Process
{
	namespace Hook
	{
#define E9_JMP_LEN 5
#define CALC_E9_JMP(codeAddr,desAddr) ((DWORD)((DWORD)(desAddr)-E9_JMP_LEN-(DWORD)(codeAddr)))

		using Process::Overwrite::_VirtualProtect;
		using Process::Hook::GetInstructionLen;

		PVOID _HookApi32(PVOID api, PVOID hook, int backupLen)
		{

			assert(backupLen >= E9_JMP_LEN);
			PBYTE result = new BYTE[backupLen + E9_JMP_LEN];
			// ����ԭ����
			memcpy(result, api, backupLen);

			DWORD oldProtect;
			// ���ñ��ݵ�ַ������
			if (!_VirtualProtect(result, backupLen + E9_JMP_LEN, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}

			// ����api����������
			if (!_VirtualProtect(api, backupLen, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}
			// ������ת->Hook
			((PBYTE)api)[0] = 0xe9;
			*(PDWORD)&((PBYTE)api)[1] = CALC_E9_JMP(api, hook);

			// �ָ�������
			if (!_VirtualProtect(api, backupLen, oldProtect, &oldProtect))
			{
				// ����ʧ�ܣ��ָ�����
				memcpy(api, result, backupLen);
				delete[] result;
				return NULL;
			}

			// ���ñ��ݴ�����ת(����
			result[backupLen] = 0xe9;
			PBYTE tmpAddr = result + backupLen + 1;
			*(PDWORD)tmpAddr = CALC_E9_JMP(result + backupLen, ((PBYTE)api) + backupLen);
			return result;
		}

		PVOID HookApi32(PVOID api, PVOID hook)
		{
			GetInstructionLen gil(true);
			int len = 0;
			int tmpLen = 0; // �ٶ�ÿһ��ָ���1BYTEʱ�ۼƵĳ���
			// ��ȡ����ͷ���ݳ���
			while (len < E9_JMP_LEN)
			{
				len += gil.GetLen((PBYTE)api + len);
				if (tmpLen++ >= E9_JMP_LEN)
				{
					// ��ȡʧ�ܣ�����ȡָ��Ȳ�����BUG������ԭ��
					return NULL;
				}
			}
			auto result = _HookApi32(api, hook, len);
			// �ض�λ����ͷ��ת,��ʵ���ظ�hook
			if (result)
			{
				tmpLen = 0;
				while (tmpLen < len)
				{
					// �޸���ת					
					_RelocJmp(result, api, tmpLen);
					tmpLen += gil.GetLen((PBYTE)result + tmpLen);
				}
			}
			return result;
		}

		// offsetΪָ�ʼλ��
		void _RelocJmp(PVOID des, PVOID oldAddr, int offset)
		{
			// E9			
			if (((PBYTE)des)[offset]==0xe9)
			{
				*(PDWORD)&((PBYTE)des)[offset + 1] += (DWORD)oldAddr- (DWORD)des;
			}
			// TODO: ����������ת���,�������ʹ�ò�ͬ��ʽhook��ʱ����Ҫע��
		}
		
	}
}