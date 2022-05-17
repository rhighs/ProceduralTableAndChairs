#include "Resizable.h"

const FVector& IResizable::GetSize()
{
	return _size;
}

void IResizable::SetSize(const FVector& size)
{
	_size = size;
}