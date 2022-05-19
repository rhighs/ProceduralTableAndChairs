#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "PTCComponent.h"
#include "Resizable.h"
#include "TableAndChairs.generated.h"


UCLASS()
class PTC_API ATableAndChairs : public AActor, public IResizable
{
	GENERATED_BODY()

    UPROPERTY(VisibleAnywhere, Category="Mesh")
    UPTCComponent* _proceduralTableAndChairs;

    UPROPERTY(VisibleAnywhere, Category = "Collision")
    TArray<UBoxComponent*> _cornerBoxComponents;

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

    virtual void Resize(const FString& targetComponent, const FVector& upToPoint) override;
protected:
	virtual void BeginPlay() override;
    virtual void OnConstruction(const FTransform& transform) override;

#if WITH_EDITOR
    virtual void PostEditChangeProperty(FPropertyChangedEvent& event) override;
#endif

private:
    void _putCornerHitboxesInPlace();
public:
	virtual void Tick(float DeltaTime) override;
};
