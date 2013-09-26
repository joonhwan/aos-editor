#pragma once

#include "aosl/AosNode.h"

class AosObject : public AosNode
				, public AosExchangeable
{
public:
    AosObject();
    virtual ~AosObject();
	virtual bool exchange(AosExchangeContext& context, const QString& name);
	bool isSprite() const;
protected:
	AosAttribute<bool> m_active;
	AosAttribute<QString> m_resourceId;
};
