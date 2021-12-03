#pragma once
#include <vector>
#include <map>
#include <deque>
#include <utility>
#include <fstream>
#include <limits>

class GraphMatcher
{
public:
    GraphMatcher();

    bool Init(const std::vector<std::vector<double> > &weights,
              const std::vector<std::vector<double> > &sign_distances,
              const double min_weight_th,
              const double consistency_dis_th);

    bool Match(std::vector<int> *_match_indices);

    /**@brief Get the matching result
     * @param[out] match_indices match_indices[i] means
     * the the ith of query elements correspond with
     * the match_indices[i] ref element
     * */
    bool GetMatchResult(std::vector<int> *match_indices);

private:
    void Match(size_t query_idx,
               size_t ref_idx,
               size_t match_index,
               double sum_weight);

    bool CheckConsistency(const size_t match_result);

    double consistency_dis_th_{0};
    double min_weight_th_{0};

    double max_weight_sum_{0};
    // TODO(@TangQing) change this indices representation
    // when there is lots of lines
    size_t max_match_indice_{0};
    size_t max_match_indice_th_{0};
    size_t max_line_num_{0};
    size_t query_num_{0};
    size_t ref_num_{0};
    size_t query_num_minus1_{0};
    size_t ref_num_minus1_{0};
    std::vector<std::vector<double> > weights_;
};
