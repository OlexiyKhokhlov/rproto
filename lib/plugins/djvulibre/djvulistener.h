#pragma once

#include <libdjvu/ddjvuapi.h>
#include <libdjvu/miniexp.h>

namespace RProto{

class DjVuListener
{
public:
    explicit DjVuListener(ddjvu_context_t *ctx);

    void error(const ddjvu_message_error_s*);
    void info(const ddjvu_message_info_s*);
    void newstream(const ddjvu_message_newstream_s*);
    void docinfo(const ddjvu_message_docinfo_s *);
    void pageinfo(const ddjvu_message_pageinfo_s *);
    void relayout(const ddjvu_message_relayout_s *);
    void redisplay(const ddjvu_message_redisplay_s *);
    void chunk(const ddjvu_message_chunk_s *);
    void thumbnail(const ddjvu_message_thumbnail_s *);
    void progress(const ddjvu_message_progress_s *);

protected:
    virtual void run();

private:
    ddjvu_context_t *djvu_context;
};

}
