#pragma once

#include "aosl/AosNode.h"
#include "aosl/AosResource.h"
#include <QList>

class AosLibrary : public AosNode
{
public:
    AosLibrary();
    virtual ~AosLibrary();
	virtual bool exchange(AosExchangeContext& context, const QString& name);
protected:
	AosResources m_resources;
};
