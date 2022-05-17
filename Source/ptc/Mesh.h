#pragma once

#include "CoreMinimal.h"
#include "ProceduralMeshComponent.h"

struct Mesh
{
	TArray<FVector> Vertices;
	TArray<int32> Triangles;
	TArray<FVector2D> UVs;
	TArray<FVector> Normals;
	TArray<FProcMeshTangent> Tangents;

	Mesh() = default;

	/** Ensure this mesh has enough memory allocated for the passed params
	* \param nVertices number of vertices
	* \param nTriangles number of triangles (not to think as "the number of ids")
	*/
	void Allocate(int32 nVertices, int32 nTriangles);

	/** Ensure this mesh has enough memory allocated for the passed params + the currently present elements
	* \param nVertices number of vertices
	* \param nTriangles number of triangles (not to think as "the number of ids")
	*/
    void AllocateBack(int32 nVertices, int32 nTriangles);

	/** Deallocate all buffers
	*/
	void Empty();

	/** Reset all buffers (preserve memory allocations)
	*/
	void Reset();

	/** Increment each vertex in `Vertices` by a given offset
	* \param offset vector to consider as offset
	*/
	void Translate(const FVector& offset);

	/** Rotate each vertex in `Vertices` by a given triplet of angles (in deg)
	* \param the vector to consider as triplet of angles
	*/
	void Rotate(const FVector& rotationDegrees);
};

/** Generate a cubic mesh given a size with origin (0, 0, 0)
* \param mesh mutable reference to a Mesh where the genereted cube will be added
* \param size cube size
*/
void CubeMesh(Mesh& mesh, const FVector& size);

/** Generate a cubic mesh given a size with origin at vertexOffset
* \param mesh mutable reference to a Mesh where the genereted cube will be added
* \param size cube size
* \param vertex origin offset
*/
void CubeMesh(Mesh& mesh, const FVector& size, const FVector& vertexOffset);

/** Generate a spherical mesh given a radius, number of parallels and number of meridians
* \param mesh mutable reference to a Mesh where the generated sphere will be added
* \param radius sphere radius
* \param parallels number of parallels
* \param meridians number of meridians
*/
void SphereMesh(Mesh& mesh, float radius, int32 parallels, int32 meridians);

/** Generate a spherical mesh given a radius, number of parallels and number of meridians
* \param mesh mutable reference to a Mesh where the generated sphere will be added
* \param radius sphere radius
* \param parallels number of parallels
* \param meridians number of meridians
* \param sphereOrigin origin offset
*/
void SphereMesh(Mesh& mesh, float radius, int32 parallels, int32 meridians, const FVector& sphereOrigin);

/** Add a 2D rectanle to a given mesh
* \param mesh mutable reference to a Mesh where the rectangel will be added
* \param bottomLeft vertex position
* \param bottomLeft vertex position
* \param topRight vertex position
* \param topLeft vertex position
* \param normal surface normal for the rectangle
* \param tanget surface tangent for the rectangle
*/
void AddRectangleTo(Mesh& mesh,
	const FVector& bottomLeft, const FVector& bottomRight,
	const FVector& topRight, const FVector& topLeft,
	const FVector& normal, const FProcMeshTangent& tangent);

/** Generate a cylindrical mesh
* TODO: finish docs
*/
void BuildCylinder(Mesh& mesh, int32 sides, FVector size, FVector location, bool withTopCap, bool withBottomCap);
