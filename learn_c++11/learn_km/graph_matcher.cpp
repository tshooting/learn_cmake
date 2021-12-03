#include "graph_matcher.hpp"
#include <limit>
#include <iostream>
using namespace std;
GraphMatcher::GraphMatcher()
{
    max_weight_sum_ = std::numeric_limits<double>::lowest();
    max_match_indice_th_ = std::numeric_limits<size_t>::max();
    max_match_indice_ = max_match_indice_th_;
}
// -1e-6 3.0
bool GraphMatcher::Init(const std::vector<std::vector<double> > &weights,
                        const std::vector<std::vector<double> > &sign_distances,
                        const double min_weight_th,
                        const double consistency_dis_th)
{
    query_size_ = weights.size();
    if (query_size_ == 0 || sign_distances.empty() ||
        query_size_ != sign_distances.size())
    {
        return false;
    }

    ref_size_ = weights[0].size();
    if (ref_size_ == 0 || sign_distances[0].empty() ||
        ref_size_ != sign_distances[0].size())
    {
        return false;
    }

    if (query_size_ < ref_size_)
    {
        max_line_size_ = ref_size_ + 1;
    }
    else
    {
        max_line_size_ = query_size_ + 1;
    }
    max_query_idx_ = query_size_ - 1;
    max_ref_idx_ = ref_size_ - 1;
    weights_ = weights;

    sign_distances_ = sign_distances;
    consistency_dis_th_ = consistency_dis_th;
    min_weight_th_ = min_weight_th;

    return true;
}

bool GraphMatcher::Match(std::vector<int> *_match_indices)
{
    size_t match_index = 1;
    Match(0, 0, match_index * max_line_size_ + 0, weights_[0][0]);
    for (size_t i = 1; i < ref_size_; ++i)
    {
        if (weights_[0][i] < min_weight_th_)
        {
            continue;
        }
        Match(0, i, match_index * max_line_size_ + i, weights_[0][i]);
    }

    if (!GetMatchResult(_match_indices))
    {
        return false;
    }

    return true;
}

// We save the match as number
// @param sum_weight: the old sum of weight before
// add weight[query_idx][ref_idx]
void GraphMatcher::Match(size_t query_idx,
                         size_t ref_idx,
                         size_t match_index,
                         double sum_weight)
{
    AD_LDEBUG(GraphMatcher) << query_idx << ", "
                            << ref_idx << ", m: " << match_index;
    // If reach the left end or right end
    // if (query_idx >= max_query_idx_ || ref_idx == max_ref_idx_) {
    size_t match_idx = match_index;
    if (ref_idx == max_ref_idx_)
    {
        size_t q_idx = query_idx;
        while (q_idx < max_query_idx_)
        {
            match_idx = match_idx * max_line_size_ + ref_size_;
            ++q_idx;
        }
    }

    if (!CheckConsistency(match_idx))
    {
        AD_LDEBUG(GraphMatcher) << "Failed to CheckConsistency";
        return;
    }
    AD_LDEBUG(GraphMatcher) << "one mature match " << match_idx
                            << ", weight: " << sum_weight;
    if (sum_weight > max_weight_sum_)
    {
        max_weight_sum_ = sum_weight;
        max_match_indice_ = match_idx;
    }

    // When only reach the left end, return
    if (query_idx >= max_query_idx_)
    {
        return;
    }

    size_t query_idx_plus = query_idx + 1;
    for (size_t j = ref_idx + 1; j < ref_size_; j++)
    {
        if (weights_[query_idx_plus][j] < min_weight_th_)
        {
            continue;
        }
        Match(query_idx_plus, j,
              match_index * max_line_size_ + j,
              sum_weight + weights_[query_idx_plus][j]);
    }

    // Discard the query_idx--ref_idx and add query_idx_plus--ref_idx
    size_t query_idx_reset_match =
        match_index / max_line_size_ * max_line_size_ + ref_size_;
    Match(query_idx_plus, ref_idx,
          query_idx_reset_match * max_line_size_ + ref_idx,
          sum_weight - weights_[query_idx][ref_idx] +
              weights_[query_idx_plus][ref_idx]);
    return;
}

bool GraphMatcher::GetMatchResult(std::vector<int> *_match_indices)
{
    if (_match_indices == nullptr)
        return false;

    if (max_match_indice_ == max_match_indice_th_)
    {
        AD_LINFO(SCENEMAPPING) << "Failed to match";
        return false;
    }

    size_t match_idx = max_match_indice_;
    int query_idx = query_size_;
    std::vector<int> match_indices(query_size_, -1);
    double max_dis = std::numeric_limits<double>::lowest();
    double min_dis = std::numeric_limits<double>::max();

    // Extract the match indices
    size_t valid_num = 0;
    while (--query_idx >= 0)
    {
        size_t ref_idx = match_idx % max_line_size_;
        match_idx /= max_line_size_;

        if (ref_idx == ref_size_)
            continue;
        if (weights_[query_idx][ref_idx] < min_weight_th_)
        {
            // return false;
            continue;
        }
        match_indices[query_idx] = ref_idx;
        double dis = sign_distances_[query_idx][ref_idx];

        if (dis > max_dis)
        {
            max_dis = dis;
        }
        if (dis < min_dis)
        {
            min_dis = dis;
        }
        ++valid_num;
    }

    if (valid_num == 0)
        return false;
    // check the movement consistency
    if (valid_num != 1 && std::abs(max_dis - min_dis) > consistency_dis_th_)
    {
        return false;
    }

    *_match_indices = std::move(match_indices);
    return true;
}

bool GraphMatcher::CheckConsistency(const size_t match_result)
{
    size_t match_idx = match_result;
    std::vector<double> delta_dis;
    delta_dis.reserve(query_size_);
    int query_idx = query_size_;
    double max_dis = std::numeric_limits<double>::lowest();
    double min_dis = std::numeric_limits<double>::max();
    AD_LDEBUG(GraphMatcher) << "one immature match " << match_result
                            << ", " << max_line_size_;

    // Extract the match indices
    size_t valid_num = 0;
    while (--query_idx >= 0)
    {
        size_t ref_idx = match_idx % max_line_size_;
        match_idx /= max_line_size_;
        if (ref_idx == ref_size_)
            continue;
        if (weights_[query_idx][ref_idx] < min_weight_th_)
        {
            AD_LDEBUG(GraphMatcher) << "skip since weight "
                                    << weights_[query_idx][ref_idx] << ", " << min_weight_th_;
            // return false;
            continue;
        }
        AD_LDEBUG(GraphMatcher) << query_idx << " vs. " << ref_idx;
        double dis = sign_distances_[query_idx][ref_idx];
        if (dis > max_dis)
        {
            max_dis = dis;
        }
        if (dis < min_dis)
        {
            min_dis = dis;
        }
        ++valid_num;
    }
    if (valid_num == 0)
        return false;
    if (valid_num != 1 && std::abs(max_dis - min_dis) > consistency_dis_th_)
    {
        AD_LDEBUG(GraphMatcher) << "return since max-min distance: "
                                << max_dis << ", " << min_dis;
        return false;
    }
    return true;
}
