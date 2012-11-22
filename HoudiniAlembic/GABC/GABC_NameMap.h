/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * Produced by:
 *	Side Effects Software Inc
 *	477 Richmond Street West
 *	Toronto, Ontario
 *	Canada   M5V 3E7
 *	416-504-9876
 *
 * NAME:	GABC_NameMap.h ( GEO Library, C++)
 *
 * COMMENTS:	This is the base class for all triangle mesh types.
 */

#ifndef __GABC_NameMap__
#define __GABC_NameMap__

#include "GABC_API.h"
#include "GABC_Types.h"
#include <SYS/SYS_AtomicInt.h>
#include <UT/UT_SymbolTable.h>

class UT_JSONWriter;
class UT_JSONParser;

/// Map to translate from Alembic attribute names to Houdini names
class GABC_API GABC_NameMap
{
public:
    typedef UT_SymbolMap<UT_String>	MapType;

     GABC_NameMap();
    ~GABC_NameMap();

    /// Number of entries in the map
    exint	entries() const	{ return myMap.entries(); }

    /// Compare equality
    bool	isEqual(const GABC_NameMap &src) const;

    /// @{
    /// Equality operator
    bool	operator==(const GABC_NameMap &src) const
		    { return isEqual(src); }
    bool	operator!=(const GABC_NameMap &src) const
		    { return !isEqual(src); }
    /// @}

    /// Get the name mapping.  If the name isn't mapped, the original name
    /// will be returned.
    /// If the attribute should be skipped, a NULL pointer will be returned.
    const char	*getName(const char *name) const;
    const char	*getName(const std::string &name) const
			{ return getName(name.c_str()); }

    /// Add a translation from the abcName to the houdini attribute name
    void		 addMap(const char *abcName, const char *houdiniName);

    /// Avoid adding an attribute of the given name.  This is done by 
    void		 skip(const char *abcName)
			    { addMap(abcName, NULL); }

    /// @{
    /// JSON I/O
    bool	save(UT_JSONWriter &w) const;
    static bool	load(GABC_NameMapPtr &map, UT_JSONParser &p);
    /// @}

    /// @{
    /// Reference counting
    void	incref()	{ myRefCount.add(1); }
    void	decref()
		{
		    if (!myRefCount.add(-1))
			delete this;
		}
    /// @}

private:
    MapType		myMap;
    SYS_AtomicInt32	myRefCount;
};

static inline void intrusive_ptr_add_ref(GABC_NameMap *m) { m->incref(); }
static inline void intrusive_ptr_release(GABC_NameMap *m) { m->decref(); }

#endif