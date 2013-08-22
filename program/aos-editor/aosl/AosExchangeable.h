#pragma once

#include "aosl/AosExchangeContext.h"
#include <QVariant>

class AosExchangeable
{
public:
	virtual bool exchange(AosExchangeContext& context, const QString& name) = 0;
};

bool ex(AosExchangeContext& context, AosExchangeable& value, const QString& name);
bool ex(AosExchangeContext& context, QString& value, const QString& name);

class AosAttributeBase : public AosExchangeable
{
public:
	AosAttributeBase();
	virtual bool exchange(AosExchangeContext& context, const QString& name);
protected:
	QVariant m_value;
};

template<typename T>
class AosAttribute : public AosAttributeBase
{
public:
	AosAttribute()
	{
	}
	AosAttribute(const T& value)
		: m_valueT(value)
	{
		m_value = QVariant::fromValue(m_valueT);
	}
	virtual bool exchange(AosExchangeContext& context, const QString& name) {
		if(!context.isReading()) {
			m_value = QVariant::fromValue<T>(m_valueT);
		}
		if(!AosAttributeBase::exchange(context, name)) {
			return false;
		}
		if(context.isReading() && m_value.canConvert<T>()) {
			m_valueT = m_value.value<T>();
		}
		return true;
	}
	operator const T& () const {
		return value();
	}
	operator T& () {
		return value();
	}
	const T& value() const {
		return m_valueT;
	}
	T& value() {
		return m_valueT;
	}
	void setValue(const T& value) {
		m_valueT = value;
		m_value = QVariant::fromValue(m_valueT);
	}
	AosAttribute<T>& operator=(const T& value) {
		setValue(value);
		return *this;
	}
	bool operator==(const T& rhs) const {
		return this->value() == rhs;
	}
	bool operator!=(const T& rhs) const {
		return this->value() != rhs;
	}
protected:
	T m_valueT;
};

template<typename T>
class AosListContainer : public QList<T>
	 				   , public AosExchangeable
{
public:
	virtual bool exchange(AosExchangeContext& context, const QString& name)
	{
		QDomElement elem = context.element();

		if(context.isReading()) {
			this->clear();
			QDomElement child = elem.firstChildElement(name);
			while(!child.isNull()) {
				T item;
				context.setFixedChild(child);
				{
					if(item.exchange(context, name)) {
						(*this) << item;
					} else {
						// TODO handle this?
					}
				}
				context.resetFixedChild();
				child = child.nextSiblingElement();
			}
			return true;
		} else {
			// TODO IMPLEMENT ME
			return true;
		}

		return false;
	}
};


