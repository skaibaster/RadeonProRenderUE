#pragma once
#include "Typedefs/RPRTypedefs.h"
#include "Containers/Array.h"
#include "Typedefs/RPRXTypedefs.h"

namespace RPR
{
	class RPRTOOLS_API FSceneStandardizer
	{
	private:

		// Data struct to cache mesh data from mesh instance and re-use it for every instance
		struct FMeshData
		{
			TArray<FVector> Vertices;
			TArray<FVector> Normals;
			TArray<uint32> Indices;
			TArray<FVector2D> TexCoords;
			TArray<uint32> NumFacesVertices;
			RPRX::FMaterial Material;
		};

	public:
		static RPR::FResult	CreateStandardizedScene(RPR::FContext Context, RPRX::FContext RPRXContext, RPR::FScene Scene, RPR::FScene& OutNormalizedScene);

		// Delete all resources that could have been created during the standardized scene creation
		static RPR::FResult ReleaseStandardizedScene(RPRX::FContext RPRXContext, RPR::FScene Scene);

	private:

		// Copy shapes and transform shape instances into shape meshes
		static void StandardizeShapes(RPR::FContext Context, RPRX::FContext RPRXContext, RPR::FScene SrcScene, RPR::FScene DstScene);

		static FMeshData* FindOrCacheMeshShape(TMap<FShape, FMeshData>& MeshDataCache, RPRX::FContext rprxContext, FShape ShapeInstance, FShape MeshShape);

		static void CopyAllLights(RPR::FContext Context, RPR::FScene SrcScene, RPR::FScene DstScene);

		static void ScaleVectors(TArray<FVector>& Vectors, float Scale);

	};

}