#include "AosResource.h"
#include <QDebug>

AosResource::AosResource()
{
}

//virtual
AosResource::~AosResource()
{
}

//virtual
bool AosResource::exchange(AosExchangeContext& context, const QString& name)
{
	qDebug() << context.element().tagName();
	if(!AosNode::exchange(context, name)) {
		return false;
	}

	AosExchangeContext myContext = context.child(name);
	if(!myContext.isValid()) {
		return false;
	}
	ex(myContext, m_type, "type");
	ex(myContext, m_value, "@text@");

	return true;
}
