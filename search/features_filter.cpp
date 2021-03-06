#include "search/features_filter.hpp"

#include "search/cbv.hpp"

#include "std/algorithm.hpp"
#include "std/vector.hpp"

namespace search
{
// FeaturesFilter ----------------------------------------------------------------------------------
FeaturesFilter::FeaturesFilter(CBV const & filter, uint32_t threshold)
  : m_filter(filter), m_threshold(threshold)
{
}

bool FeaturesFilter::NeedToFilter(CBV const & cbv) const
{
  if (cbv.IsFull())
    return true;
  return cbv.PopCount() > m_threshold;
}

// LocalityFilter ----------------------------------------------------------------------------------
LocalityFilter::LocalityFilter(CBV const & filter)
  : FeaturesFilter(filter, 0 /* threshold */)
{
}

CBV LocalityFilter::Filter(CBV const & cbv) const
{
  return m_filter.Intersect(cbv);
}

// ViewportFilter ----------------------------------------------------------------------------------
ViewportFilter::ViewportFilter(CBV const & filter, uint32_t threshold)
  : FeaturesFilter(filter, threshold)
{
}

CBV ViewportFilter::Filter(CBV const & cbv) const
{
  auto result = m_filter.Intersect(cbv);
  if (!result.IsEmpty())
    return result;

  return cbv.Take(m_threshold);
}
}  // namespace search
