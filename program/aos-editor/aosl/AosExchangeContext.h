#pragma once

#include <QDomElement>

class AosExchangeContext
{
public:
	enum Mode {
		Read = 0,
		Write,
	};
	AosExchangeContext(QDomElement& element = QDomElement(), Mode mode=Read)
		: m_mode(mode)
		, m_element(element)
	{
	};
	bool isReading() const {
		return m_mode==Read;
	}
	bool isValid() const {
		return !m_element.isNull();
	}
	QDomElement element() {
		return m_element;
	}
	const QDomElement& element() const {
		return m_element;
	}
	AosExchangeContext child(const QString& elementName) {
		QDomElement d;
		if(!m_childElementForContainerIter.isNull() &&
		   m_childElementForContainerIter.tagName()==elementName) {
			d = m_childElementForContainerIter;
		} else {
			d = m_element.firstChildElement(elementName);
		}
		return AosExchangeContext(d, m_mode);
	}
	void setFixedChild(QDomElement elem) {
		m_childElementForContainerIter = elem;
	}
	void resetFixedChild() {
		m_childElementForContainerIter = QDomElement();
	}
protected:
	Mode m_mode;
	QDomElement m_element;
	QDomElement m_childElementForContainerIter;
};

class AosReadContext : public AosExchangeContext
{
public:
	AosReadContext(QDomElement& element)
		: AosExchangeContext(element, AosExchangeContext::Read)
	{
	}
};

class AosWriteContext : public AosExchangeContext
{
public:
	AosWriteContext(QDomElement& element)
		: AosExchangeContext(element, AosExchangeContext::Write)
	{
	}
};
