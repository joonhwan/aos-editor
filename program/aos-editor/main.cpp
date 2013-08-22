#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QXmlQuery>
#include <QXmlSerializer>
#include <QXmlStreamReader>
#include <QDomDocument>
#include <QDomElement>

#include "aosl/sequence.hpp"
#include "aosl/resource.hpp"
#include "aosl/aosl.hpp"

#include "aosl/AosSequence.h"

#include <xercesc/dom/DOMLocator.hpp>

class MyErrorHandler : public ::xercesc::DOMErrorHandler
{
public:
	virtual bool handleError(const ::xercesc::DOMError& domError) {
		auto* loc = domError.getLocation();
		qDebug() << QString::fromUtf16((const ushort*)domError.getMessage())
				 << "[line:" << loc->getLineNumber()
				 << ", col:" << loc->getColumnNumber() << "]"
			;
		return true;
	}
};


int main(int argc, char** argv)
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("joonhwan");
	QCoreApplication::setOrganizationDomain("www.joonhwan.org");
	QCoreApplication::setApplicationName("aos-editor");

	::xercesc::XMLPlatformUtils::Initialize();

	{
		MyErrorHandler handler;
		auto sequence = aosl::parse_sequence("c:/prj/oss/mine/aos-editor/program/aos-editor/sample/demo.aosl",
											 handler,
											 ::xml_schema::Flags::dont_validate);
		const auto& library = sequence->library();
		const auto& resources = library.resource();
		// for(const aosl::Resource& resource: resources) {
		for(const auto& resource: resources) {
			qDebug() << resource.id().data() << ", " << resource.type().data() << ", " << resource.c_str();
		}
	}
	QFile aosFile("c:/prj/oss/mine/aos-editor/program/aos-editor/sample/demo.aosl");
	aosFile.open(QIODevice::ReadOnly);

	AosSequence sequence;
	if(!sequence.loadFrom(&aosFile)) {
		return -1;
	}

	// QDomNode node = root.firstChild();
	// while(!node.isNull()) {
	// 	QDomElement elem = node.toElement();

	// QXmlStreamReader xml(&aosFile);
	// while(!xml.atEnd()) {
	// 	xml.readNext();
	// 	if(xml.isStartElement()) {
	// 		if(xml.name()=="sequence") {
	// 			sequence = new AosSequence;
	// 			sequence->exchange(xml);
	// 		}
	// 	} else if (xml.isEndElement()) {
	// 		if(xml.name()=="sequence") {
	// 		}
	// 	}
	// }

	// QFile testFile("test.xml");
	// testFile.open(QIODevice::ReadWrite);
	// QXmlNamePool namePool;
	// QXmlNodeModelIndex sequenceNode;
	// QXmlQuery query(namePool);
	// query.setQuery("declare variable $inuptDocument external;\n"
	// 			   "\n"
	// 			   "doc($inputDocument)/sequence\n");
	// 	//doc(file:///c:/prj/oss/mine/aos-editor/program/aos-editor/sample/demo.aosl)/$sequence");
	// //query.setFocus(QUrl::fromLocalFile("c:/prj/oss/mine/aos-editor/program/aos-editor/sample/demo.aosl"));
	// QXmlSerializer serializer(query, &testFile);
	// query.evaluateTo(&serializer);

	return 0;
	//return app.exec();
}
