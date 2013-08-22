#include "AosNode.h"

AosNode::AosNode()
{
}

//virtual
bool AosNode::exchange(AosExchangeContext& context, const QString& name)
{
	AosExchangeContext myContext = context.child(name);
	if(!myContext.isValid()) return false;

	if(!ex(myContext, m_id, "id")) return false;

	return true;
}
