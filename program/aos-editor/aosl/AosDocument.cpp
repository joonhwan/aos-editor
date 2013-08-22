#include "AosDocument.h"
#include <QXmlStreamReader>
#include <QIODevice>

AosDocument::AosDocument(QObject* parent)
	: QObject(parent)
	, m_reader(new QXmlStreamReader)
{
}

//virtual
AosDocument::~AosDocument()
{
}

bool AosDocument::load(QIODevice* io)
{
	m_reader->setDevice(io);
	return false;
}
