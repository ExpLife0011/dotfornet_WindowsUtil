#include "ApiHook.h"

namespace Process
{
	namespace Hook
	{

		using Process::Overwrite::_VirtualProtect;
		using Process::Hook::GetInstructionLen;

		// jmp xxx
#define E9_JMP_LEN 5
		// jmp [xxx], ��Ҫ���϶�Ӧ��ַ�ĳ���
#define FF25_JMP_LEN 6

		// ��С���ݳ���
#ifdef _WIN64
		const int BACKUPLEN = FF25_JMP_LEN + sizeof(DWORD64);
#else
		const int BACKUPLEN = FF25_JMP_LEN + sizeof(DWORD);
#endif


		

		void _EmitE9Jmp(PVOID pos, PVOID des)
		{
			PBYTE& apiAddr = (PBYTE&)pos;
			apiAddr[0] = 0xe9;
			*(PDWORD)(&apiAddr[1]) = (PBYTE)des - (PBYTE)pos - E9_JMP_LEN;
		}

		void _EmitFF25Jmp(PVOID pos, PVOID des)
		{
			PBYTE& apiAddr = (PBYTE&)pos;
			apiAddr[0] = 0xff;
			apiAddr[1] = 0x25;
			apiAddr += 2;

			// 32д���Ե�ַ,64д��Ե�ַ, ָ������ָ��Ľ���λ��
#ifdef _WIN64
			*(PDWORD)apiAddr = (DWORD)0;
#else
			*(PDWORD)apiAddr = (DWORD)(apiAddr + sizeof(DWORD));
#endif
			apiAddr += sizeof(DWORD);
			// д��Ŀ���ַ
			*(HANDLE_PTR*)apiAddr = (HANDLE_PTR)des;

		}


		bool IsFF25Jmp(PVOID addr)
		{
			return ((PBYTE)addr)[0] == 0xff && ((PBYTE)addr)[1] == 0x25;
		}


		// offsetΪָ�ʼλ��
		// Ϊjmp��Ŀ�����������ָ�릤
		bool _RelocJmp(PBYTE des, PVOID oldAddr, int offset)
		{
			auto jmpPos = des + offset;
			if (IsFF25Jmp(jmpPos))
			{
				// ֻ֧�ֱ�hook
#ifndef _WIN64
				if (*(PDWORD)&jmpPos[2] != 0)
				{
					// �޸ľ���ƫ��,32λ����
					jmpPos += 2;
					*(PDWORD)jmpPos = (DWORD)(jmpPos + sizeof(DWORD));
				}
#endif
				return true;
		}
			return false;
			// TODO: ����������ת���,�������ʹ�ò�ͬ��ʽhook��ʱ����Ҫע��
	}


		int GetCodeBackupLen(PVOID api, int minLen)
		{
#ifdef _WIN64
			GetInstructionLen gil(false);
#else
			GetInstructionLen gil(true);
#endif
			int len = 0; // ʵ��ָ��ݳ���
			int loopTimes = 0;
			// ��ȡ����ͷ���ݳ���
			while (len < minLen)
			{
				if (loopTimes++>minLen)
				{
					return 0;
				}
				len += gil.GetLen((PBYTE)api + len);
			}
			return len;
		}

		PVOID _HookApi(PVOID api, PVOID hook, int backupLen)
		{
			assert(backupLen >= BACKUPLEN);
			PBYTE result = new BYTE[backupLen + BACKUPLEN];
			// ����ԭ����
			memcpy(result, api, backupLen);

			DWORD oldProtect;
			// ���ñ��ݵ�ַ������
			if (!_VirtualProtect(result, backupLen + BACKUPLEN, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}

			// ����api����������
			if (!_VirtualProtect(api, backupLen, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}
			// ������ת->Hook
			_EmitFF25Jmp(api, hook);

			// ���ñ��ݴ�����ת(����
			_EmitFF25Jmp(result + backupLen, ((PBYTE)api) + backupLen);

			// �ָ�������
			if (!_VirtualProtect(api, backupLen, oldProtect, &oldProtect))
			{
				// ����ʧ�ܣ��ָ�����
				memcpy(api, result, backupLen);
				delete[] result;
				return NULL;
			}
			return result;
		}
		
		PVOID HookApi(PVOID api, PVOID hook)
		{
#ifdef _WIN64
			GetInstructionLen gil(false);
#else
			GetInstructionLen gil(true);
#endif
			int len = 0;
			int tmpLen = 0; // �ٶ�ÿһ��ָ���1BYTEʱ�ۼƵĳ���
			if (IsFF25Jmp(api))
			{
				len = BACKUPLEN;
			}
			else
			{
				// ��ȡ����ͷ���ݳ���
				while (len < BACKUPLEN)
				{
					len += gil.GetLen((PBYTE)api + len);
					if (tmpLen++ >= BACKUPLEN)
					{
						// ��ȡʧ�ܣ�����ȡָ��Ȳ�����BUG������ԭ��
						return NULL;
					}
				}
			}
			auto result = _HookApi(api, hook, len);


			// �ض�λ����ͷ��ת,��ʵ���ظ�hook(���hook������ܲ���)
			if (result)
			{
				tmpLen = 0;
				while (tmpLen < len)
				{
					// �޸���ת					
					if (_RelocJmp((PBYTE)result, api, tmpLen))
					{
						break;
					}
					tmpLen += gil.GetLen((PBYTE)result + tmpLen);
				}
			}
			return result;
		}



		// ʹ��e9 jmp�İ汾,�������Զ������
		PVOID _HookApi_E9Jmp(PVOID api, PVOID hook, int backupLen)
		{
			PBYTE result = new BYTE[backupLen + BACKUPLEN]; // ʹ�õ�ǰ�ֳ�����󳤶�, ����������Ҫ��
			// ����ԭ����
			memcpy(result, api, backupLen);

			DWORD oldProtect;
			// ���ñ��ݵ�ַ������
			if (!_VirtualProtect(result, backupLen + BACKUPLEN, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}

			// ����api����������
			if (!_VirtualProtect(api, backupLen, PAGE_EXECUTE_READWRITE, &oldProtect))
			{
				return NULL;
			}
			// hook e9
			_EmitE9Jmp(api, hook);
			// ��������,��Ҫ���Ǿ���
			LONGLONG distance = (PBYTE)result - (PBYTE)api;
			distance = distance > 0 ? distance : -distance;
			if (distance<0x7fff0000)
			{
				_EmitE9Jmp(result + backupLen, (PBYTE)api + backupLen);
			}
			else
			{
				_EmitFF25Jmp(result + backupLen, (PBYTE)api + backupLen);
			}
			


			// �ָ�������
			if (!_VirtualProtect(api, backupLen, oldProtect, &oldProtect))
			{
				// ����ʧ�ܣ��ָ�����
				memcpy(api, result, backupLen);
				delete[] result;
				return NULL;
			}
			return result;
		}

		PVOID HookApiOnce(PVOID api, PVOID hook)
		{
			if (((PBYTE)api)[0]==0xe9 || IsFF25Jmp(api))
			{
				return NULL;
			}
			LONGLONG distance = (PBYTE)hook - (PBYTE)api;
			distance = distance > 0 ? distance : -distance;
			int codeLen = 0;
			if (distance<0x7fff0000)
			{
				// e9 jmp
				codeLen = GetCodeBackupLen(api, E9_JMP_LEN);
				return _HookApi_E9Jmp(api, hook, codeLen);
			}
			else
			{
				// ff25 jmp
				codeLen = GetCodeBackupLen(api, BACKUPLEN);
				return _HookApi(api, hook, codeLen);
			}
		}
	}
}