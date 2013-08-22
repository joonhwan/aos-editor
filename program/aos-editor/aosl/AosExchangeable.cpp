#include "AosExchangeable.h"

AosAttributeBase::AosAttributeBase()
{
}

bool ex(AosExchangeContext& context, AosExchangeable& value, const QString& name)
{
	return value.exchange(context, name);
};

bool ex(AosExchangeContext& context, QString& value, const QString& name)
{
	if(name=="@text@") {
		if(context.isReading()) {
			QDomElement elem = context.element();
			if(elem.isNull()) {
				return false;
			}
			value = elem.text();
		} else {
			// TODO IMPLEMENT ME
			Q_ASSERT(false);
		}
	}
	return true;
}

//virtual
bool AosAttributeBase::exchange(AosExchangeContext& context, const QString& name)
{
	QDomElement element = context.element();
	if(element.isNull()) {
		return false;
	}
	if(context.isReading()) {
		//Q_ASSERT(element.hasAttribute(name));
		if(!element.hasAttribute(name)) {
			return false;
		}
		m_value = QVariant::fromValue(element.attribute(name));
	} else {
		element.setAttribute(name, m_value.toString());
	}
	return true;
}
