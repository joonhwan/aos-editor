#include "AosArea.h"

AosArea::AosArea()
	: m_x(0.)
	, m_y(0.)
{
}

//virtual
AosArea::~AosArea()
{
}

//virtual
bool AosArea::exchange(AosExchangeContext& context, const QString& name)
{
	AosExchangeContext myContext = context.child(name);
	if(!myContext.isValid()) {
		return false;
	}

	if(!ex(myContext, m_x, "x")) return false;
	if(!ex(myContext, m_y, "y") ) return false;

	return true;
}
