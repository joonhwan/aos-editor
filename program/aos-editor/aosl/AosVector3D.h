#pragma once

#include "aosl/AosExchangeable.h"

class AosVector3D : public AosExchangeable
{
public:
    AosVector3D();
    virtual ~AosVector3D();
	virtual bool exchange(AosExchangeContext& context);
protected:
	AosAttribute<double> m_x;
	AosAttribute<double> m_y;
	AosAttribute<double> m_z;
};


