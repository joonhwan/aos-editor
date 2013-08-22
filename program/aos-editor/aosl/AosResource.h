#pragma once

#include "aosl/AosNode.h"
#include <QList>

class AosResource : public AosNode
{
public:
    AosResource();
    virtual ~AosResource();
	virtual bool exchange(AosExchangeContext& context, const QString& name);
	const QString& type() const {
		return m_type;
	}
	const QString& value() const {
		return m_value;
	}
protected:
	AosAttribute<QString> m_type;
	QString m_value;
};

class AosResources : public AosListContainer<AosResource>
{
public:
};

