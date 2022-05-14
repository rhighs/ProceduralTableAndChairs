#include "TestActor.h"
#include "Mesh.h"

ATestActor::ATestActor()
{
	PrimaryActorTick.bCanEverTick = true;

    _proceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("Procedural Mesh"));
    RootComponent = _proceduralMesh;
}

void ATestActor::BeginPlay()
{
	Super::BeginPlay();
}

void ATestActor::OnConstruction(const FTransform& transform)
{
    Super::OnConstruction(transform);
    Mesh mesh;
    SphereMesh(mesh, 100.0f, 10, 10, FVector::ZeroVector);

    _proceduralMesh->CreateMeshSection(
        0,
        mesh.Vertices,
        mesh.Triangles,
        mesh.Normals,
        mesh.UVs,
        TArray<FColor>(),
        mesh.Tangents,
        false
    );
}
 
void ATestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
