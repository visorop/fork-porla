#include "torrentsresume.hpp"

#include "../sessions.hpp"

using porla::Methods::TorrentsResume;
using porla::Methods::TorrentsResumeReq;
using porla::Methods::TorrentsResumeRes;

TorrentsResume::TorrentsResume(porla::Sessions& sessions)
    : m_sessions(sessions)
{
}

void TorrentsResume::Invoke(const TorrentsResumeReq& req, WriteCb<TorrentsResumeRes> cb)
{
    auto const& torrents = m_sessions.Default()->torrents;
    auto status = torrents.find(req.info_hash);

    if (status == torrents.end())
    {
        return cb.Error(-1, "Torrent not found");
    }

    status->second.resume();

    cb.Ok(TorrentsResumeRes{});
}
