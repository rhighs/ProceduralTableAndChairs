#include "PTCPlayerController.h"
#include "DrawDebugHelpers.h"

void PrintDebugMessage(const FString& message, float displayTime = 10.f, FColor textColor = FColor::Yellow, int key = -1)
{
	if (GEngine) {
		GEngine->AddOnScreenDebugMessage(key, displayTime, textColor, message);
	}
}

APTCPlayerController::APTCPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	bMoveCamera = false;
	bCornerPressed = false;

#if 1 
	// probably they're all true by default
	bEnableClickEvents = true;
	bShowMouseCursor = true;
	bEnableMouseOverEvents = true;
#endif

	DefaultMouseCursor = EMouseCursor::Crosshairs;
}


void APTCPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	if (!bCornerPressed) return;

	FVector location;
	FVector direction;
	FHitResult hitResult;
	bool deprojected = DeprojectMousePositionToWorld(location, direction);
	if (!deprojected) return;

	float zPlane = _hitLocation.Z;
	FVector2D cursorCoordInZPlane = _whereLineIntersectsZPlane(zPlane, location, direction);
	if (_resizableActor != nullptr)
	{
		FVector cursorWorldPosition = FVector(cursorCoordInZPlane, zPlane);
		_resizableActor->Resize(_hitComponent, cursorWorldPosition);
	}

}


void APTCPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction("LeftMouseBtn", IE_Pressed, this, &APTCPlayerController::_mouseLeftButtonPressed);
	InputComponent->BindAction("LeftMouseBtn", IE_Released, this, &APTCPlayerController::_mouseLeftButtonReleased);
	InputComponent->BindAction("MoveCamera", IE_Pressed, this, &APTCPlayerController::_onMoveCameraPressed);
	InputComponent->BindAction("MoveCamera", IE_Released, this, &APTCPlayerController::_onMoveCameraReleased);
}


void APTCPlayerController::_onMoveCameraPressed()
{
	bMoveCamera = true;
}


void APTCPlayerController::_onMoveCameraReleased()
{
	bMoveCamera = false;
}

/// <summary>
/// Handles click on entities inside the viewport
/// Note: current max distance for clickable entities is 55000
/// </summary>
void APTCPlayerController::_mouseLeftButtonPressed()
{
	FVector location;
	FVector direction;
	FHitResult hitResult;

	float distance = 55000;
	DeprojectMousePositionToWorld(location, direction);
	FCollisionQueryParams queryParams(FName(TEXT("CornerTrace")), false, nullptr);
	bool hit = GetWorld()->LineTraceSingleByChannel(hitResult, location, (location + distance * direction), ECC_Visibility, queryParams);
	if (hit)
		PrintDebugMessage(TEXT("hit"));
	else
		PrintDebugMessage(TEXT("no hit"));

	auto hitActor = Cast<IResizable>(hitResult.Actor);
	if (!hitActor) {
		PrintDebugMessage("no actor");
		return;
	}

	auto hitComponent = Cast<UActorComponent>(hitResult.Component);
	if (!hitComponent) {
		PrintDebugMessage("component not found");
		return;
	}

	_resizableActor = hitActor;
	_hitLocation = hitResult.ImpactPoint;
	_hitComponent = hitComponent->GetName();

	bCornerPressed = true;
}

void APTCPlayerController::_mouseLeftButtonReleased()
{
	bCornerPressed = false;
}

FVector2D APTCPlayerController::_whereLineIntersectsZPlane(float Zvalue, FVector location, FVector direction)
{
	FVector2D result{};
	float zRatio = (Zvalue - location.Z);
	if (direction.Z != 0) {
		zRatio /= direction.Z;
	}
	result.X = location.X + direction.X * zRatio;
	result.Y = location.Y + direction.Y * zRatio;

	return(result);
}