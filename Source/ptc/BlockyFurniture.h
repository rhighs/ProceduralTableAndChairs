#pragma once

#include "CoreMinimal.h"
#include "Mesh.h"


/** Generate a chair using 6 cuboid meshes (4 legs a chair base and a chair back rest) 
* \param size the chair size
* \return the chair mesh buffers
*/
Mesh BlockyChair(const FVector& size);

/** Generate a table using 5 cuboid meshes (4 legs and 1 table top) 
* \param size the table size
* \return the table mesh buffers
*/
Mesh BlockyTable(const FVector& size);

/** Greedely generate spawn locations for chairs around a rectangluar table
* \param tableSize the table size
* \param chairSize the chairs size
* \return a position and the rotation vector in deg for each chair
*/
TArray<TTuple<FVector, FVector>> ChairPositions(const FVector& tableSize, const FVector& chairSize);