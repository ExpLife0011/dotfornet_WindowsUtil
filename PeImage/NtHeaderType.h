#pragma once
namespace PeDecoder
{
	// ��Ҫ�޸������˳��
	enum class NtHeaderType :
		unsigned char
	{
		UnKnown,
		Rom,
		NtHeader32,
		NtHeader64
	};
}  // namespace PeDecoder
