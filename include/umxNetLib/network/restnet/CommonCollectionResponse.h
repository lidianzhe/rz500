/**************************************************************************************************\

	Author:		Ralph
	Created:	06.06.2014

---------------------------------------------------------------------------------------------------

	Copyright (c) 2014 Smartsensors Ltd.

\**************************************************************************************************/

#ifndef __COMMON_COLLECTION_RESPONSE_H__
#define __COMMON_COLLECTION_RESPONSE_H__

#include <string>
#include <vector>

#include "umxCommonLib/cjson/cJSONpp.h"

template<class TItem>
struct CommonCollectionResponse
{
    int StatusCode;
    std::string ReasonPhrase;
    std::vector<TItem> Items;
    int Page;
    int PageSize;
    bool HasMore;
    int Total;

    CommonCollectionResponse<TItem>()
        : StatusCode(0), Page(0), PageSize(0), HasMore(false), Total(0)
    {
    };

    static CommonCollectionResponse<TItem> Parse(const std::string jsonString)
    {
        cjsonpp::JSONObject obj = cjsonpp::parse( jsonString );
        CommonCollectionResponse<TItem> commonCollectionResponse;
        commonCollectionResponse.StatusCode = obj.get<int>("status_code");
        commonCollectionResponse.ReasonPhrase = obj.get<std::string>("reason_phrase");
        std::vector<cjsonpp::JSONObject> items = obj.get("items").asArray<cjsonpp::JSONObject>();
        for(auto it = std::begin(items); it != std::end(items); ++it)
        {
            commonCollectionResponse.Items.push_back(TItem::Parse(*it));
        }
        return commonCollectionResponse;
    }

    const std::string AsJSONString() const
    {
        cjsonpp::JSONObject obj;
        obj.set("status_code", StatusCode);
        obj.set("reason_phrase", ReasonPhrase);
        cjsonpp::JSONObject array = cjsonpp::arrayObject();
        for(auto it = std::begin(Items); it != std::end(Items); ++it)
        {
            array.add(it->AsJSONObject());
        }
        obj.set("items", array);
        obj.set("page", Page);
        obj.set("page_size", PageSize);
        obj.set("has_more", HasMore);
        obj.set("total", Total);
        return obj.print(false);
    }
};

#endif // __COMMON_COLLECTION_RESPONSE_H__
