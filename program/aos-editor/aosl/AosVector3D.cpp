#include "AosVector3D.h"

AosVector3D::AosVector3D()
{
}

//virtual
AosVector3D::~AosVector3D()
{
}

//virtual
bool AosVector3D::exchange(AosExchangeContext& context, const QString& name)
{
	AosExchangeContext myContext = context.child(name);
	if(!myContext.isValid()) {
		return false;
	}

	if(!ex(myContext, m_x, "x") ||
	   !ex(myContext, m_y, "y") ){
		return false;
	}

	ex(myContext, m_z, "z");
	return true;
}
