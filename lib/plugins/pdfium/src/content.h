#pragma once

#include <icontent.h>
#include <fpdfview.h>
#include <vector>

class Content : public RProto::IContent
{
public:
    Content(FPDF_DOCUMENT doc);
    virtual ~Content();

    //Interface IContent
    virtual void addListener(RProto::IContentListener *listener) override;
    virtual const std::string& title(int subcontent_id, int row) const override;
    virtual int pageNumber(int subcontent_id, int row) const override;
    virtual std::pair<int,int> parentId(int subcontent_id) const override;
    virtual int childsId(int parent_id, int parent_row) const override;
    virtual int rowCount(int subcontent_id) const override;

private:
    FPDF_DOCUMENT pdf_doc;
    RProto::IContentListener *listener;

    struct Item{
        FPDF_BOOKMARK bookmark;
        std::string title;
        int page;
        int childs_id;
    };

    struct SubContent{
        int parent_id;
        int parent_row;
        std::vector<Item> items;
    };

    std::vector<SubContent>    content;
    static std::string empty;

    const Content::Item* getItem(int subcontent_id, int row) const;
    void loadContent();
    void fillItem(Item& item);
};
