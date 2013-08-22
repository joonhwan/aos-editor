#pragma once

#include "aosl/AosNode.h"
#include "aosl/AosArea.h"
#include <QColor>

class AosCanvas : public AosExchangeable
{
public:
    AosCanvas();
    virtual ~AosCanvas();
	virtual bool exchange(AosExchangeContext& context, const QString& name);
protected:
	AosAttribute<QColor> m_color;
	AosArea m_area;
};
