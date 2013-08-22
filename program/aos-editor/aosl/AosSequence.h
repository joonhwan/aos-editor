#pragma once

#include "aosl/AosNode.h"
#include "aosl/AosLibrary.h"
#include "aosl/AosCanvas.h"

class AosSequence : public AosNode
{
public:
    AosSequence();
    virtual ~AosSequence();
	bool loadFrom(QIODevice* io);
	QString name() const {
		return m_name.value();
	}
	void setName(const QString& name);
protected:
	AosAttribute<QString> m_name;
	AosLibrary m_library;
	AosCanvas m_canvas;
};
