#pragma once

#include <QObject>

class QIODevice;
class QXmlStreamReader;

class AosDocument : public QObject
{
    Q_OBJECT
public:
    AosDocument(QObject* parent=0);
    virtual ~AosDocument();
	bool load(QIODevice* io);
signals:
public slots:
protected:
	QXmlStreamReader* m_reader;
};
