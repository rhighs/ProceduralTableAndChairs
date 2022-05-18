#include "TableAndChairs.h"

ATableAndChairs::ATableAndChairs()
{
	PrimaryActorTick.bCanEverTick = true;
    _proceduralTableAndChairs = CreateDefaultSubobject<UPTCComponent>("ProceduralTableAndChairs");
    RootComponent = _proceduralTableAndChairs;

    _cornerSphereComponents.Reserve(4);
    for (int i = 0; i < 4; ++i)
    {

        FString j = "Corner " + FString::FromInt(i+1);
        _cornerSphereComponents.Add(CreateDefaultSubobject<USphereComponent>(FName(*j)));

        _cornerSphereComponents[i]->SetupAttachment(_proceduralTableAndChairs);
        //_cornerSphereComponents[i]->SetSphereRadius(200);
    }
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

    _putCornerHitboxesInPlace();

    for (auto& corner : _cornerSphereComponents)
    {
        corner->SetSphereRadius(30);
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
        Resize(FVector(TableWidth, TableLength, TableHeight));
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

FVector ATableAndChairs::GetResizableLocation()
{
    FVector location = GetActorLocation();
    return location;
}

void ATableAndChairs::Resize(const FVector& newSize)
{
    SetSize(newSize);
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

    if (_cornerSphereComponents.Num() != quadrantsSigns.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("corner hitboxes can't be positioned"));
        return;
    }

    int32 id = 0;
    for (auto& corner : _cornerSphereComponents)
    {
        FVector sphereLocation = FVector(TableWidth / 2, TableLength / 2, TableHeight) * quadrantsSigns[id];
        corner->SetRelativeLocation(sphereLocation);

        ++id;
    }
}

void ATableAndChairs::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
