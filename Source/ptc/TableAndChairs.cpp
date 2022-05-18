#include "TableAndChairs.h"

ATableAndChairs::ATableAndChairs()
{
	PrimaryActorTick.bCanEverTick = true;
    _proceduralTableAndChairs = CreateDefaultSubobject<UPTCComponent>("ProceduralTableAndChairs");
    RootComponent = _proceduralTableAndChairs;
}

void ATableAndChairs::OnConstruction(const FTransform& transform)
{
    Super::OnConstruction(transform);

    if (_firstRender)
    {
        _firstRender = false;
        _proceduralTableAndChairs->Update(
            FVector(TableWidth, TableLength, TableHeight),
            FVector(ChairWidth, ChairLength, ChairHeight)
        );
    }
}

#if WITH_EDITOR
void ATableAndChairs::PostEditChangeProperty(FPropertyChangedEvent& event)
{
    FName propertyName = (event.Property != NULL) ? event.Property->GetFName() : NAME_None;
    bool anyPropChanged = propertyName == GET_MEMBER_NAME_CHECKED(ATableAndChairs, TableWidth)
        || propertyName == GET_MEMBER_NAME_CHECKED(ATableAndChairs, TableLength)
        || propertyName == GET_MEMBER_NAME_CHECKED(ATableAndChairs, TableHeight)
        || propertyName == GET_MEMBER_NAME_CHECKED(ATableAndChairs, ChairWidth)
        || propertyName == GET_MEMBER_NAME_CHECKED(ATableAndChairs, ChairLength)
        || propertyName == GET_MEMBER_NAME_CHECKED(ATableAndChairs, ChairHeight);

    if (anyPropChanged)
    {
        Update();
    }

    Super::PostEditChangeProperty(event);
}
#endif

void ATableAndChairs::Update()
{
    UE_LOG(LogTemp, Warning, TEXT("UPDATING PROCEDURAL MESH"));
    _proceduralTableAndChairs->Update(
        FVector(TableWidth, TableLength, TableHeight),
        FVector(ChairWidth, ChairLength, ChairHeight)
    );
}

void ATableAndChairs::BeginPlay()
{
	Super::BeginPlay();
}

void ATableAndChairs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
