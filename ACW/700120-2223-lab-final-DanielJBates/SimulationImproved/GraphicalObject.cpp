#include "GraphicalObject.h"

GraphicalObject::~GraphicalObject() = default;

void GraphicalObject::reset()
{
	_mCurrentPosition = _mInitialPosition;
}
