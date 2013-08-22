#pragma once

#include "aosl/AosExchangeable.h"
#include <QString>

class AosNode : public AosExchangeable
{
public:
	AosNode();
	virtual bool exchange(AosExchangeContext& context, const QString& name);
	void setId(const QString& id) {
		m_id = id;
	}
	const QString& id() const {
		return m_id;
	}
protected:
	AosAttribute<QString> m_id;
};
