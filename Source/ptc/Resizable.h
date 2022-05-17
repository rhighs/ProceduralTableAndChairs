#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Resizable.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UResizable : public UInterface
{
	GENERATED_BODY()
};



class PTC_API IResizable
{
	GENERATED_BODY()

public:
	virtual const FVector& GetSize();
	virtual void SetSize(const FVector& size);
	virtual void Resize(const FVector& newSize) PURE_VIRTUAL(IResizable::Resize, return;);
	virtual void Resize(float newX, float newY) PURE_VIRTUAL(IResizable::Resize, return;);
	virtual void Resize(const FString& targetComponent, const FVector& upToPoint) PURE_VIRTUAL(IResizable::Resize, return;)
private:
	FVector _size;
};
