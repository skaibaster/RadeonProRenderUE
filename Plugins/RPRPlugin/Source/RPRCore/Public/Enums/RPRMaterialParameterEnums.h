/**********************************************************************
* Copyright (c) 2018 Advanced Micro Devices, Inc. All rights reserved.
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
********************************************************************/
#pragma once
#include "Templates/UnrealTypeTraits.h"
#include "RprSupport.h"

UENUM(BlueprintType)
enum class ERPRReflectionMode : uint8
{
	PBR = RPRX_UBER_MATERIAL_REFLECTION_MODE_PBR,
	Metalness = RPRX_UBER_MATERIAL_REFLECTION_MODE_METALNESS,
};

UENUM(BlueprintType)
enum class ERPREmissionMode : uint8
{
	SingleSided = RPRX_UBER_MATERIAL_EMISSION_MODE_SINGLESIDED,
	DoubleSided = RPRX_UBER_MATERIAL_EMISSION_MODE_DOUBLESIDED
};

UENUM(BlueprintType)
enum class ERPRRefractionMode : uint8
{
	Separate = RPRX_UBER_MATERIAL_REFRACTION_MODE_SEPARATE,
	Linked = RPRX_UBER_MATERIAL_REFRACTION_MODE_LINKED
};

//Expose_TNameOf(ERPRReflectionMode)
//Expose_TNameOf(ERPREmissionMode)
//Expose_TNameOf(ERPRRefractionMode)

template<>
struct TNameOf<ERPRReflectionMode>
{
	FORCEINLINE static TCHAR const* GetName()
	{
		return TEXT("ERPRReflectionMode");
	}
};

template<>
struct TNameOf<ERPREmissionMode>
{
	FORCEINLINE static TCHAR const* GetName()
	{
		return TEXT("ERPREmissionMode");
	}
};

template<>
struct TNameOf<ERPRRefractionMode>
{ 
	FORCEINLINE static TCHAR const* GetName()
	{
		return TEXT("ERPRRefractionMode");
	}
};