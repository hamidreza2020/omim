#include "generator/sponsored_scoring.hpp"

#include "generator/opentable_dataset.hpp"
#include "generator/feature_builder.hpp"

namespace
{
// Calculated with tools/python/booking_hotels_quality.py.
double constexpr kOptimalThreshold = 0.304875;
}  // namespace

namespace generator
{
namespace sponsored_scoring
{
template <>
double MatchStats<OpentableRestaurant>::GetMatchingScore() const
{
  // TODO(mgsergio): Use tuner to get optimal function.
  return m_linearNormDistanceScore * m_nameSimilarityScore;
}

template <>
bool MatchStats<OpentableRestaurant>::IsMatched() const
{
  return GetMatchingScore() > kOptimalThreshold;
}

template <>
MatchStats<OpentableRestaurant> Match(OpentableRestaurant const & h, FeatureBuilder1 const & fb)
{
  MatchStats<OpentableRestaurant> score;

  auto const fbCenter = MercatorBounds::ToLatLon(fb.GetKeyPoint());
  auto const distance = ms::DistanceOnEarth(fbCenter.lat, fbCenter.lon, h.m_lat, h.m_lon);
  score.m_linearNormDistanceScore =
      impl::GetLinearNormDistanceScore(distance, OpentableDataset::kDistanceLimitInMeters);

  score.m_nameSimilarityScore =
      impl::GetNameSimilarityScore(h.m_name, fb.GetName(StringUtf8Multilang::kDefaultCode));

  return score;
}
}  // namespace sponsored_scoring
}  // namespace generator
