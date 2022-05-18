#pragma once

#include "CoreMinimal.h"
#include "Mesh.h"


/** Generate a chair using 6 cuboid meshes (4 legs a chair base and a chair back rest) 
* \param mesh mutable reference to a Mesh where the table will be added
* \param size the chair size
* \return the chair mesh buffers
*/
void BlockyChair(Mesh& mesh, const FVector& size);

/** Generate a table using 5 cuboid meshes (4 legs and 1 table top) 
* \param mesh mutable reference to a Mesh where the table will be added
* \param size the table size
* \return the table mesh buffers
*/
void BlockyTable(Mesh& mesh, const FVector& size);

/** Greedely generate spawn locations for chairs around a rectangluar table
* \param tableSize the table size
* \param chairSize the chairs size
* \return a transformation for each chair
*/
TArray<FTransform> ChairPositions(const FVector& tableSize, const FVector& chairSize);