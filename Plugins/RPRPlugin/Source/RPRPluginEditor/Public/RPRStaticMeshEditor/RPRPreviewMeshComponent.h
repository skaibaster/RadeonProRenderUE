#pragma once
#include "RawMesh.h"
#include "ProceduralMeshComponent.h"
#include "RPRPreviewMeshComponent.generated.h"

UCLASS()
class RPRPLUGINEDITOR_API URPRMeshPreviewComponent : public UProceduralMeshComponent
{
	GENERATED_BODY()

private:

	struct FSectionData
	{
		int32 SectionStart;
		int32 SectionEnd;

		TArray<FVector> Vertices;
		TArray<int32> Triangles;
		TArray<FVector> Normals;
		TArray<FVector2D> UV;
		TArray<FColor> Colors;
		TArray<FProcMeshTangent> Tangents;
	};
	
	struct FVertexData
	{
		int32 OriginalVertexIndex;
		int32 VertexIndex;
		int32 TriangleIndex;
		FVector2D UV;
	};

public:

	URPRMeshPreviewComponent();

	void 			Regenerate();
	void			SetStaticMesh(UStaticMesh* InStaticMesh, FRawMesh* InRawMesh);
	UStaticMesh*	GetStaticMesh() const;

private:

	int32	CountNumMaterials() const;
	void	FindTrianglesBoundsBySection(int32 SectionIndex, int32& OutStartIndex, int32& OutEndIndex) const;
	void	BuildSection(int32 SectionIndex, FSectionData& OutSectionData);
	void	GenerateUVsAndAdaptMesh(FSectionData& SectionData);
	bool	ShareSameVertex(int32 VertexIndexA, int32 VertexIndexB) const;
	bool	AreUVIdentical(const FVector2D& uvA, const FVector2D& uvB) const;
	int32	FindDuplicatedVertexInfo(const TArray<FVertexData>& VertexInfos, int32 StartIndex, int32 VertexIndex, const FVector2D& UV) const;
	void	RemoveRedundantVerticesData(int32 NumVertices, TArray<FVertexData>& VertexInfos);
	void	GetUVsFromVerticesData(const TArray<FVertexData>& VerticesData, TArray<FVector2D>& UV) const;
	void	AssignMaterialFromStaticMesh();

private:

	UPROPERTY(Transient)
	UStaticMesh* StaticMesh;
	
	FRawMesh* RawMesh;

	TArray<FVector> MeshVertices;
	TArray<int32> MeshTriangles;
	TArray<FVector> MeshNormals;
	TArray<FVector2D> MeshUV;
	TArray<FProcMeshTangent> MeshTangents;

	TArray<FSectionData> SectionDatas;

};
