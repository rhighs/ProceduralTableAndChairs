#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "PTCComponent.h"

#include "TableAndChairs.generated.h"


UCLASS()
class PTC_API ATableAndChairs : public AActor
{
	GENERATED_BODY()

    UPTCComponent* _proceduralTableAndChairs;

    bool _firstRender = true;
	
public:	
	ATableAndChairs();

    UPROPERTY(EditAnywhere, meta = (ClampMin = "100", ClampMax = "100000", UIMin = "100", UIMax = "100000"))
    float TableWidth = 1000.0f;

    UPROPERTY(EditAnywhere, meta = (ClampMin = "100", ClampMax = "100000", UIMin = "100", UIMax = "100000"))
    float TableLength = 300.0f;

    UPROPERTY(EditAnywhere, meta = (ClampMin = "100", ClampMax = "100000", UIMin = "100", UIMax = "100000"))
    float TableHeight = 110.0f;

    UPROPERTY(EditAnywhere, meta = (ClampMin = "100", ClampMax = "1000", UIMin = "100", UIMax = "200"))
    float ChairWidth = 70.0f;

    UPROPERTY(EditAnywhere, meta = (ClampMin = "100", ClampMax = "1000", UIMin = "100", UIMax = "200"))
    float ChairLength = 70.0f;

    UPROPERTY(EditAnywhere, meta = (ClampMin = "100", ClampMax = "1000", UIMin = "100", UIMax = "200"))
    float ChairHeight = 150.0f;

    void Update();

protected:
	virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& transform) override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& event) override;
#endif

public:
	virtual void Tick(float DeltaTime) override;
};
