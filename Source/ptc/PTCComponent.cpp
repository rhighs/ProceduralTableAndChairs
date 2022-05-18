#include "PTCComponent.h"
#include "BlockyFurniture.h"

UPTCComponent::UPTCComponent(const FObjectInitializer& objectInitializer)
    : UProceduralMeshComponent(objectInitializer)
{
    bUseAsyncCooking = true;
}

void UPTCComponent::Build(const FVector& tableSize, const FVector& chairSize)
{
    if (_firstRender)
    {
        Update(tableSize, chairSize);
        _firstRender = false;
    }
}

void UPTCComponent::Update(const FVector& tableSize, const FVector& chairSize)
{
    if (_lastChairSize != chairSize || _lastTableSize != tableSize)
    {
        if (_lastChairSize != chairSize)
        {
            _chairMesh = {};
            BlockyChair(_chairMesh, chairSize);
        }

        if (_lastTableSize != tableSize)
        {
            _tableMesh = {};
            BlockyTable(_tableMesh, tableSize);
        }

        _renderTable(_tableMesh);

        for (const auto& transform : ChairPositions(tableSize, chairSize))
        {
            _chairMesh.Transform(transform);
            _renderChair(_chairMesh);
            _chairMesh.Transform(transform.Inverse());
        }
    }

    _lastTableSize = tableSize;
    _lastChairSize = chairSize;

    _clearRemainingSections(_lastChairMeshSectionId);
    _maxReachedMeshSectionId = _lastChairMeshSectionId;
    _lastChairMeshSectionId = 1;
}

void UPTCComponent::_clearRemainingSections(int32 startingFromId)
{
    for (int32 i = startingFromId; i < _maxReachedMeshSectionId; ++i)
    {
        ClearMeshSection(i);
    }
}

void UPTCComponent::_renderTable(const Mesh& tableMesh)
{
    if (_firstRender)
    {
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
    else
    {
        UpdateMeshSection_LinearColor(
            _tableMeshSectionId,
            _tableMesh.Vertices,
            _tableMesh.Normals,
            _tableMesh.UVs,
            TArray<FLinearColor>(),
            _tableMesh.Tangents
        );
    }
}

void UPTCComponent::_renderChair(const Mesh& chairMesh)
{
    if (_lastChairMeshSectionId < _maxReachedMeshSectionId)
    {
        UpdateMeshSection_LinearColor(
            _lastChairMeshSectionId,
            _chairMesh.Vertices,
            _chairMesh.Normals,
            _chairMesh.UVs,
            TArray<FLinearColor>(),
            _chairMesh.Tangents
        );
    }
    else
    {
        CreateMeshSection_LinearColor(
            _lastChairMeshSectionId,
            _chairMesh.Vertices,
            _chairMesh.Triangles,
            _chairMesh.Normals,
            _chairMesh.UVs,
            TArray<FLinearColor>(),
            _chairMesh.Tangents,
            false
        );
    }

    _lastChairMeshSectionId++;
}
