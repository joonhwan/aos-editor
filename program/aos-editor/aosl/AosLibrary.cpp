#include "AosLibrary.h"

AosLibrary::AosLibrary()
{
}

//virtual
AosLibrary::~AosLibrary()
{
}

//virtual
bool AosLibrary::exchange(AosExchangeContext& context, const QString& name)
{
	AosExchangeContext myContext = context.child(name);
	if(!myContext.isValid()) return false;

	if(!ex(myContext, m_resources, "resource")) return false;

	return true;
}
