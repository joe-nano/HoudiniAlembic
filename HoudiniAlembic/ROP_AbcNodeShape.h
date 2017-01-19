/*
 * Copyright (c) 2017
 *	Side Effects Software Inc.  All rights reserved.
 *
 * Redistribution and use of Houdini Development Kit samples in source and
 * binary forms, with or without modification, are permitted provided that the
 * following conditions are met:
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. The name of Side Effects Software may not be used to endorse or
 *    promote products derived from this software without specific prior
 *    written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY SIDE EFFECTS SOFTWARE `AS IS' AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN
 * NO EVENT SHALL SIDE EFFECTS SOFTWARE BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *----------------------------------------------------------------------------
 */

#ifndef __ROP_AbcNodeShape__
#define __ROP_AbcNodeShape__

#include "ROP_AbcNode.h"

#include <GABC/GABC_OGTGeometry.h>

#include "ROP_AbcUserProperties.h"

typedef GABC_NAMESPACE::GABC_OGTGeometry GABC_OGTGeometry;

/// Class describing geometry exported to an Alembic archive.
class ROP_AbcNodeShape : public ROP_AbcNode
{
public:
    ROP_AbcNodeShape(const std::string &name)
	: ROP_AbcNode(name), mySampleCount(0), myLocked(false) {}

    virtual OObject getOObject();
    virtual void clearData();
    virtual void setArchive(const ROP_AbcArchivePtr &archive);
    virtual void update();

    /// When locked update() uses the previously written sample instead of the
    /// current sample.
    void setLocked(bool locked);
    /// Sets the current user properties.
    void setUserProperties(const UT_String &vals, const UT_String &meta)
	    { myUserPropVals = vals; myUserPropMeta = meta; }
    /// Sets the current geometry.
    void setData(const GT_PrimitiveHandle &prim) { myPrim = prim; }

private:
    UT_UniquePtr<GABC_OGTGeometry> myWriter; 
    exint mySampleCount;

    UT_StringHolder myUserPropVals;
    UT_StringHolder myUserPropMeta;
    ROP_AbcUserProperties myUserProperties;

    GT_PrimitiveHandle myPrim;
    GT_PrimitiveHandle myCached;
    exint myCachedCount;
    bool myCachedVisDeferred;
    bool myLocked;
};

#endif
