#include "djvulistener.h"

using namespace RProto;

DjVuListener::DjVuListener(ddjvu_context_t *ctx)
  : djvu_context(ctx)
{
}

void DjVuListener::run()
{
    while(true){

    const ddjvu_message_t *msg;
    ddjvu_message_wait(djvu_context);
    while ((msg = ddjvu_message_peek(djvu_context)))
    {
      switch(msg->m_any.tag)
      {
      case DDJVU_ERROR:
//          qDebug() << "DJVULibre ERROR:";
//          qDebug() << "\tFile: " << reinterpret_cast<const ddjvu_message_error_s*>(msg)->filename;
//          qDebug() << "\tFunction: " << reinterpret_cast<const ddjvu_message_error_s*>(msg)->function;
//          qDebug() << "\tLine:" << reinterpret_cast<const ddjvu_message_error_s*>(msg)->lineno;
//          qDebug() << "\tMessage: " << reinterpret_cast<const ddjvu_message_error_s*>(msg)->message;
//          emit error(reinterpret_cast<const ddjvu_message_error_s*>(msg));
          break;
      case DDJVU_INFO:
//          qDebug() << "DJVULibre INFO: ";
//          qDebug() << "\tMessage:" << reinterpret_cast<const ddjvu_message_info_s*>(msg)->message;
//          emit info(reinterpret_cast<const ddjvu_message_info_s*>(msg));
          break;
      case DDJVU_NEWSTREAM:
//          qDebug() << "DJVULibre NEW STREAM: ";
//          qDebug() << "\tName: " << reinterpret_cast<const ddjvu_message_newstream_s*>(msg)->name;
//          qDebug() << "\tid=" << reinterpret_cast<const ddjvu_message_newstream_s*>(msg)->streamid;
//          qDebug() << "\tUrl: " << reinterpret_cast<const ddjvu_message_newstream_s*>(msg)->url;
//          emit newstream(reinterpret_cast<const ddjvu_message_newstream_s*>(msg));
          break;
      case DDJVU_DOCINFO:
//          qDebug() << "DJVULibre: DOC INFO";
//          emit docinfo(reinterpret_cast<const ddjvu_message_docinfo_s*>(msg));
          break;
      case DDJVU_PAGEINFO:
//          qDebug() << "DJVULibre: PAGE INFO";
//          emit pageinfo(reinterpret_cast<const ddjvu_message_pageinfo_s*>(msg));
          break;
      case DDJVU_RELAYOUT:
//          qDebug() << "DJVULibre: RELAYOUT";
//          emit relayout(reinterpret_cast<const ddjvu_message_relayout_s*>(msg));
          break;
      case DDJVU_REDISPLAY:
//          qDebug() << "DJVULibre: REDISPLAY";
//          emit redisplay(reinterpret_cast<const ddjvu_message_redisplay_s*>(msg));
          break;
      case DDJVU_CHUNK:
//          qDebug() << "DJVULibre: CHUNK";
//          emit chunk(reinterpret_cast<const ddjvu_message_chunk_s*>(msg));
          break;
      case DDJVU_THUMBNAIL:
//          qDebug() << "DJVULibre: THUMBNAIL";
//          emit thumbnail(reinterpret_cast<const ddjvu_message_thumbnail_s*>(msg));
          break;
      case DDJVU_PROGRESS:
//          qDebug() << "DJVULibre: PROGRESS";
//          emit progress(reinterpret_cast<const ddjvu_message_progress_s*>(msg));
          break;
      default:
//          qWarning() << "DJVULibre: OOps! unknown message" << msg->m_any.tag;
          break;
      }
      ddjvu_message_pop(djvu_context);
    }
    }

}
