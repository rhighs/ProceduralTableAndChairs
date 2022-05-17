#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Resizable.h"
#include "PTCPlayerController.generated.h"


UCLASS()
class PTC_API APTCPlayerController : public APlayerController
{
	GENERATED_BODY()
private:
	bool bMoveCamera;
	bool bCornerPressed;
public:
	APTCPlayerController();
protected:
	virtual void SetupInputComponent() override;
	virtual void PlayerTick(float DeltaTime) override;
private:
	void _onMoveCameraPressed();
	void _onMoveCameraReleased();
	void _mouseLeftButtonPressed();
	void _mouseLeftButtonReleased();
	FVector2D _whereLineIntersectsZPlane(float withZ, FVector lineStartingPoint, FVector lineDirection);

	IResizable* _resizableActor;
	FVector _hitLocation;
	FString _hitComponent;
};
