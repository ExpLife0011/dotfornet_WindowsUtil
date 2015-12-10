#pragma once
#include "SectionIterator.h"
namespace PE
{
	
	
	class SectionHeaders :
		public PeStruct,
		public GetIterator<SectionIterator, SectionHeaders>
	{
		PIMAGE_SECTION_HEADER firstSectionHeader;
		PIMAGE_SECTION_HEADER lastSectionHeader;
		PDWORD sectionAlignment;
		PWORD sectionCount;
	public:
		friend class PeDecoder;
		friend GetIteratorBase::Iterator;
		SectionHeaders(PeDecoder& pe);

		~SectionHeaders();
		

	};

}