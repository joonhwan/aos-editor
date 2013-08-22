#include "AosCanvas.h"

AosCanvas::AosCanvas()
{
}

//virtual
AosCanvas::~AosCanvas()
{
}

//virtual
bool AosCanvas::exchange(AosExchangeContext& context, const QString& name)
{
	AosExchangeContext myContext = context.child(name);
	if(!myContext.isValid()) return false;

	// attribute
	if(!ex(myContext, m_color, "color")) return false;

	// child
	if(!ex(myContext, m_area, "area")) return false;

	return true;
}
