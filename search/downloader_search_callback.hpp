#pragma once

#include "storage/downloader_search_params.hpp"

#include "std/set.hpp"
#include "std/string.hpp"

class Index;

namespace storage
{
class CountryInfoGetter;
class Storage;
}  // namespace storage

namespace search
{
class Results;

// An on-results callback that should be used for the search in downloader.
//
// *NOTE* the class is NOT thread safe.
class DownloaderSearchCallback
{
public:
  class Delegate
  {
  public:
    virtual ~Delegate() = default;

    virtual void RunUITask(function<void()> fn) = 0;
  };

  DownloaderSearchCallback(Delegate & delegate, Index const & index,
                           storage::CountryInfoGetter const & infoGetter,
                           storage::Storage const & storage,
                           storage::DownloaderSearchParams params);

  void operator()(search::Results const & results);

private:
  set<storage::DownloaderSearchResult> m_uniqueResults;

  Delegate & m_delegate;
  Index const & m_index;
  storage::CountryInfoGetter const & m_infoGetter;
  storage::Storage const & m_storage;
  storage::DownloaderSearchParams m_params;
};
}  // namespace search
