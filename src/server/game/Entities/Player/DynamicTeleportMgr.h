/*******************************************************
 * File:'DynamicTeleportMgr.h'
 *
 * (c)2011 - Wolf Officious
 *******************************************************/

#ifndef _DYNTEL_H
#define _DYNTEL_H

#include <ace/Singleton.h>

#include "Common.h"
#include "World.h"
//#include "SQLStorage.h"

struct TeleportData
{
    uint32 entry;
    uint32 menu_parent;
     int32 menu_sub;
    uint8  icon;
    uint32 faction;
    std::string name;
};

struct TeleportLoc
{
    uint32 map;
    float position_x;
    float position_y;
    float position_z;
    float position_o;
};

typedef UNORDERED_MAP<uint32, TeleportData> TeleportDataMap;
typedef UNORDERED_MAP<uint32, TeleportLoc>  TeleportLocMap;

class DynamicTeleportMgr
{
public:
    DynamicTeleportMgr()
    {
        m_isLoaded = false;
    }
    ~DynamicTeleportMgr() {}

    bool Init();
    void Update();

    bool isLoaded() { return m_isLoaded; }

    inline
    TeleportData const* GetTeleportData(uint32 id) const
    {
        TeleportDataMap::const_iterator itr = mTeleportData.find(id);
        return itr != mTeleportData.end() ? &itr->second : NULL;
    }

    uint32 GetCount() { return mTeleportData.size(); }

    inline
    TeleportLoc const* GetTeleportLoc(uint32 id) const
    {
        TeleportLocMap::const_iterator itr = mTeleportLoc.find(id);
        return itr != mTeleportLoc.end() ? &itr->second : NULL;
    }

private:
    TeleportDataMap mTeleportData;
    TeleportLocMap  mTeleportLoc;

    bool m_isLoaded;
};

#define sDynamicTeleportMgr ACE_Singleton<DynamicTeleportMgr, ACE_Null_Mutex>::instance()

#endif // _DYNTEL_H
