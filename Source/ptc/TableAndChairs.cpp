#include "TableAndChairs.h"

ATableAndChairs::ATableAndChairs()
{
	PrimaryActorTick.bCanEverTick = true;
    _proceduralTableAndChairs = CreateDefaultSubobject<UPTCComponent>("ProceduralTableAndChairs");
    RootComponent = _proceduralTableAndChairs;

    _cornerBoxComponents.Reserve(4);
    for (int i = 0; i < 4; ++i)
    {

        FString j = "Corner " + FString::FromInt(i+1);
        _cornerBoxComponents.Add(CreateDefaultSubobject<UBoxComponent>(FName(*j)));

        _cornerBoxComponents[i]->SetupAttachment(_proceduralTableAndChairs);
    }
}

void ATableAndChairs::OnConstruction(const FTransform& transform)
{
    Super::OnConstruction(transform);

    if (_firstRender)
    {
        _firstRender = false;
        _proceduralTableAndChairs->Build(
            FVector(TableWidth, TableLength, TableHeight),
            FVector(ChairWidth, ChairLength, ChairHeight)
        );
    }

    _putCornerHitboxesInPlace();

    for (auto& corner : _cornerBoxComponents)
    {
        corner->SetBoxExtent(FVector(30,30,30), false);
        corner->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
    }

    SetActorEnableCollision(true);
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
        _putCornerHitboxesInPlace();
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

void ATableAndChairs::Resize(const FString& targetComponent, const FVector& cursorPosition)
{
    auto tableLocation = GetActorLocation();
    FVector2D newSize = 2 * (FVector2D(cursorPosition.X, cursorPosition.Y) - FVector2D(tableLocation.X, tableLocation.Y)).GetAbs();
    auto currentSize = FVector2D(TableWidth, TableLength);
    auto sizeDiff = newSize - currentSize;
    auto threshold = 5;
    if (sizeDiff.Size() < threshold)
        return;
    if (newSize.X < 100 || newSize.X > 100000)
        return;
    if (newSize.Y < 100 || newSize.Y > 100000)
        return;
    SetSize(FVector{ newSize, TableHeight });
    TableWidth = newSize.X;
    TableLength = newSize.Y;
    Update();
    _putCornerHitboxesInPlace();
}

void ATableAndChairs::BeginPlay()
{
	Super::BeginPlay();
}

void ATableAndChairs::_putCornerHitboxesInPlace()
{
    static TArray<FVector> quadrantsSigns{ FVector(1,  1, 1),
                                     FVector(-1,  1, 1),
                                     FVector(-1, -1, 1),
                                     FVector(1, -1, 1) };

    if (_cornerBoxComponents.Num() != quadrantsSigns.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("corner hitboxes can't be positioned"));
        return;
    }

    int32 id = 0;
    for (auto& corner : _cornerBoxComponents)
    {
        FVector boxLocation = FVector(TableWidth / 2 - 28, TableLength / 2 - 28, TableHeight - 28) * quadrantsSigns[id];
        corner->SetRelativeLocation(boxLocation);

        ++id;
    }
}

void ATableAndChairs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
