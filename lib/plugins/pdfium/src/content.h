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
    void addListener(RProto::IContentListener *listener) override;
    const std::string& title(int subcontent_id, int row) const override;
    int pageNumber(int subcontent_id, int row) const override;
    std::pair<int,int> parentId(int subcontent_id) const override;
    int childsId(int parent_id, int parent_row) const override;
    int rowCount(int subcontent_id) const override;

private:
    FPDF_DOCUMENT pdf_doc;
    RProto::IContentListener *listener;

    struct Item {
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
