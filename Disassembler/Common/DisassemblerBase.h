#pragma once
#include "Common.h"

#include "Disassembler_Trait.h"
#include "Interface\IDisassembler.h"
#include "Interface\IStateUsed.h"
namespace Disassembler
{
	// ����Ϊ����
	template<typename TChild, typename TTrait = Disassembler_Trait<TChild>>
	class DisassemblerBase
		:public IDisassembler,
		protected IStateUsed<TTrait>
	{
	public:
		typedef TTrait TTrait;
		typedef typename TTrait::TOpcodeDataWapper TOpcodeDataWapper;
		typedef typename TTrait::TStorage TStorage;
		typedef typename TTrait::TStateFactory TStateFactory;
		DisassemblerBase()
		{
			_STATIC_ASSERT((std::is_base_of<IDisassembler, TChild>::value));
			
		}

		~DisassemblerBase()
		{
		}
		virtual unsigned int Parse(void * pos) override
		{
			auto storage = GetStorage();
			storage->SetInitialPosition(pos);
			TStateFactory::NextStateFunction getNextStateID = nullptr;
			auto stateUsed = dynamic_cast<TTrait::TStateUsed*>(this);

			for (auto i = TStateFactory::BeginStateID; i != TStateFactory::EndStateID; i = getNextStateID(stateUsed))
			{
				getNextStateID = TStateFactory::GetStateFunction(i);
				assert(getNextStateID);
			}

			if (storage->IsSuccess())
			{
				// TODO: �ڲ���ָ��ƫ�ƻ��кܶ�δ���
				return storage->GetCurrentPosition() - pos;
			}
			return 0;
		}
	protected:
		TOpcodeDataWapper opcodeDataWapper;
		TStorage storage;

		virtual TOpcodeDataWapper* GetOpcodeDataWapper() override
		{
			return &opcodeDataWapper;
		}
		virtual TStorage* GetStorage() override
		{
			return &storage;
		}
	};
}  // namespace Disassembler
