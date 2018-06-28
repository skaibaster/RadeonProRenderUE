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
#include "RPRToolsModule.h"
#include "RPRITypedefs.h"
#include "RPRXTypedefs.h"

namespace RPRI
{
	RPRTOOLS_API void	DeleteContext(RPRI::FContext Context);
	RPRTOOLS_API void	DeleteMaterial(RPRX::FContext RPRXContext, RPRI::FExportMaterialResult ExportMaterialResult);
	RPRTOOLS_API bool	AllocateContext(RPRI::FContext& OutContext);
	RPRTOOLS_API bool	SetErrorOptions(RPRI::FContext Context, uint32 InfoVerbosity, bool bShouldBreakOnError, bool bShouldAbortOnError);
	RPRTOOLS_API bool	SetLoggers(RPRI::FContext Context, FRPRILogCallback InfoCallback, FRPRILogCallback WarningCallback, FRPRILogCallback ErrorCallback);
}
