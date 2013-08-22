#pragma once

#include "aosl/AosExchangeable.h"

class AosArea : public AosExchangeable
{
public:
    AosArea();
    virtual ~AosArea();
	virtual bool exchange(AosExchangeContext& context, const QString& name);
protected:
	AosAttribute<double> m_x;
	AosAttribute<double> m_y;
};


