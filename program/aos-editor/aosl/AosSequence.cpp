#include "AosSequence.h"
#include <QDomDocument>
#include <QDomElement>
#include <QDebug>

AosSequence::AosSequence()
{
}

//virtual
AosSequence::~AosSequence()
{
}

bool AosSequence::loadFrom(QIODevice* io)
{
	QDomDocument doc;
	if(!doc.setContent(io, true)) {
		return false;
	}
	QDomElement root = doc.documentElement();
	qDebug() << "root : " << root.tagName();
	if(root.tagName()=="sequence") {
		AosReadContext context(root);

		ex(context, m_id, "id");
		ex(context, m_name, "name");
		ex(context, m_library, "library");
		ex(context, m_canvas, "canvas");
	}
	return true;
}

void AosSequence::setName(const QString& name)
{
	m_name = name;
}
