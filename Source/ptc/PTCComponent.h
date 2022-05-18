#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"

#include "BlockyFurniture.h"

#include "PTCComponent.generated.h"


UCLASS()
class PTC_API UPTCComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()

    Mesh _tableMesh;
    Mesh _chairMesh;

    FVector _lastChairSize;
    FVector _lastTableSize;

    int32 _tableMeshSectionId = 0;
    int32 _lastChairMeshSectionId = 0;

public:
    UPTCComponent(const FObjectInitializer& objectInitializer);

    /** Should only be called at first render, builds table and chair meshes.
     * \param tableSize the table size
     * \param chairSize the size for each chair
     */
    void Build(const FVector& tableSize, const FVector& chairSize);

    /** Updates table and chair meshes. Meshes are rebuilt only if their size changes.
     * Table size (w, h) increases  -> more chairs are added to the table
     * Table size (w, h) decreases  -> chairs are removed
     * Chair size changes           -> all chairs get rebuilt
     * \param tableSize the table size
     * \param chairSize the size for each chair
     */
    void Update(const FVector& tableSize, const FVector& chairSize);
};
