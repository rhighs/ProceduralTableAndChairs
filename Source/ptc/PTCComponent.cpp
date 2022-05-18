#include "PTCComponent.h"
#include "BlockyFurniture.h"

UPTCComponent::UPTCComponent(const FObjectInitializer& objectInitializer)
    : UProceduralMeshComponent(objectInitializer)
{
    bUseAsyncCooking = true;
}

void UPTCComponent::Build(const FVector& tableSize, const FVector& chairSize)
{
    BlockyChair(_chairMesh, chairSize);
    auto transforms = ChairPositions(tableSize, chairSize);

    for (const auto &transform : transforms)
    {
        _chairMesh.Transform(transform);

        CreateMeshSection_LinearColor(
            (++_lastChairMeshSectionId),
            _chairMesh.Vertices,
            _chairMesh.Triangles,
            _chairMesh.Normals,
            _chairMesh.UVs,
            TArray<FLinearColor>(),
            _chairMesh.Tangents,
            false
        );

        _chairMesh.Transform(transform.Inverse());
    }

    CreateMeshSection_LinearColor(
        _tableMeshSectionId,
        _tableMesh.Vertices,
        _tableMesh.Triangles,
        _tableMesh.Normals,
        _tableMesh.UVs,
        TArray<FLinearColor>(),
        _tableMesh.Tangents,
        false
    );

    _lastTableSize = tableSize;
    _lastChairSize = chairSize;
    _lastChairMeshSectionId = 0;
}

// TODO: Perform an actual update using UpdateMeshSection (I still don't understand
//       how this can be of any convenience).
void UPTCComponent::Update(const FVector& tableSize, const FVector& chairSize)
{
    ClearAllMeshSections();

    if (_lastChairSize != chairSize || _lastTableSize != tableSize)
    {
        _chairMesh = {};
        BlockyChair(_chairMesh, chairSize);

        auto transforms = ChairPositions(tableSize, chairSize);

        UE_LOG(LogTemp, Warning, TEXT("Spawning n chairs: %d"), transforms.Num());

        for (const auto& transform : transforms) {
            _chairMesh.Transform(transform);

            CreateMeshSection_LinearColor(
                (++_lastChairMeshSectionId),
                _chairMesh.Vertices,
                _chairMesh.Triangles,
                _chairMesh.Normals,
                _chairMesh.UVs,
                TArray<FLinearColor>(),
                _chairMesh.Tangents,
                false
            );

            _chairMesh.Transform(transform.Inverse());
        }
    }

    if (_lastTableSize != tableSize)
    {
        _tableMesh = {};
        BlockyTable(_tableMesh, tableSize);

        CreateMeshSection_LinearColor(
            _tableMeshSectionId,
            _tableMesh.Vertices,
            _tableMesh.Triangles,
            _tableMesh.Normals,
            _tableMesh.UVs,
            TArray<FLinearColor>(),
            _tableMesh.Tangents,
            false
        );
    }

}