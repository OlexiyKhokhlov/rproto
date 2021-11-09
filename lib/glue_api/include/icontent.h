#pragma once

#include <utility>
#include <string>

namespace RProto{

class IContentListener{
public:
    virtual ~IContentListener()= default;
    virtual void onSubcontentAdded(int subcontent_id) =0;
};

class IContent
{
public:
    virtual ~IContent()= default;

    virtual void addListener(RProto::IContentListener *listener) =0;
    virtual const std::string& title(int subcontent_id, int row) const =0;
    virtual int pageNumber(int subcontent_id, int row) const =0;
    virtual std::pair<int,int> parentId(int subcontent_id) const =0;
    virtual int childsId(int parent_id, int parent_row) const =0;
    virtual int rowCount(int subcontent_id) const =0;
};

}//namespace RProto
