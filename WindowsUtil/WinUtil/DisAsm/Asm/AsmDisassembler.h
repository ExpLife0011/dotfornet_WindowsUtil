#pragma once
#include "..\Common\Common.h"
#include "AsmDisassembler_Trait.h"
#include "State\AsmStateFactory.h"
#include "Opcode\AsmOpcodeDataWapper.h"
#include "AsmStorage.h"
#include "AsmDisassembler.h"
#include "..\Common\DisassemblerBase.h"

namespace Disassembler
{
	class AsmDisassembler :
		public DisassemblerBase<AsmDisassembler>
	{
	public:
		// ֻ����32λ��64λ�Ļ�����
		AsmDisassembler(bool is32)
		{
			storage.SetSizeMode(is32);
		}

		~AsmDisassembler()
		{
			
		}
	
		
		virtual unique_ptr<IInstruction> GetResult() const override;
		
	};
}  // namespace Disassembler