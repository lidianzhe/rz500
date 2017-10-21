#ifndef __COMMUTEDATA_COLLECTION_RESPONSE_H__
#define __COMMUTEDATA_COLLECTION_RESPONSE_H__

#include <string>
#include <vector>

#include "umxCommonLib/cjson/cJSONpp.h"

template<class TItem>
struct CommuteDataCollectionResponse
{
    std::string _macAddr;
    std::vector<TItem> _Items;

    CommuteDataCollectionResponse<TItem>()
        : _macAddr("")
    {
    }

    static CommuteDataCollectionResponse<TItem> Parse(const std::string jsonString)
    {
        cjsonpp::JSONObject obj = cjsonpp::parse( jsonString );
        CommuteDataCollectionResponse<TItem> commuteDataCollectionResponse;
        commuteDataCollectionResponse.macAddr = obj.get<std::string>("macAddr");
        std::vector<cjsonpp::JSONObject> items = obj.get("commuteList").asArray<cjsonpp::JSONObject>();
        for(auto it = std::begin(items); it != std::end(items); ++it)
        {
            commuteDataCollectionResponse._Items.push_back(TItem::Parse(*it));
        }
        return commuteDataCollectionResponse;
    }

    const std::string AsJSONString() const
    {
        cjsonpp::JSONObject obj;
        obj.set("macAddr", _macAddr);
        cjsonpp::JSONObject array = cjsonpp::arrayObject();
        for(auto it = std::begin(_Items); it != std::end(_Items); ++it)
        {
            array.add(it->AsJSONObject());
        }
        obj.set("commuteList", array);
        return obj.print(false);
    }
};

#endif // __COMMUTEDATA_COLLECTION_RESPONSE_H__
