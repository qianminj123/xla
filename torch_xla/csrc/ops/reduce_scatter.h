#ifndef XLA_TORCH_XLA_CSRC_OPS_REDUCE_SCATTER_H_
#define XLA_TORCH_XLA_CSRC_OPS_REDUCE_SCATTER_H_

#include "torch_xla/csrc/cross_replica_reduces.h"
#include "torch_xla/csrc/ir.h"

namespace torch_xla {

class ReduceScatter : public XlaNode {
 public:
  ReduceScatter(AllReduceType reduce_type, const torch::lazy::Value& input,
                const torch::lazy::Value& token, double scale,
                int64_t scatter_dim, int64_t shard_count,
                std::vector<std::vector<int64_t>> groups, bool pin_layout,
                std::optional<int> channel_id = std::nullopt,
                std::optional<bool> use_global_device_ids = std::nullopt);
  ReduceScatter(AllReduceType reduce_type, const torch::lazy::Value& input,
                double scale, int64_t scatter_dim, int64_t shard_count,
                std::vector<std::vector<int64_t>> groups);

  std::string ToString() const override;

  torch::lazy::NodePtr Clone(torch::lazy::OpList operands) const override;

  XlaOpVector Lower(LoweringContext* loctx) const override;

  AllReduceType reduce_type() const { return reduce_type_; }

  double scale() const { return scale_; }

  const std::vector<std::vector<int64_t>>& groups() const { return groups_; }

  bool pin_layout() const { return pin_layout_; }

 private:
  AllReduceType reduce_type_;
  double scale_;
  int64_t scatter_dim_;
  int64_t shard_count_;
  std::vector<std::vector<int64_t>> groups_;
  bool pin_layout_;
  bool has_token_{true};
  std::optional<int> channel_id_;
  std::optional<bool> use_global_device_ids_;
};

class ReduceScatterCoalesced : public XlaNode {
 public:
  ReduceScatterCoalesced(AllReduceType reduce_type,
                         c10::ArrayRef<torch::lazy::Value> inputs,
                         const torch::lazy::Value& token, double scale,
                         int64_t scatter_dim, int64_t shard_count,
                         std::vector<std::vector<int64_t>> groups,
                         bool pin_layout);

  std::string ToString() const override;

  torch::lazy::NodePtr Clone(torch::lazy::OpList operands) const override;

  XlaOpVector Lower(LoweringContext* loctx) const override;

  AllReduceType reduce_type() const { return reduce_type_; }

  double scale() const { return scale_; }

  const std::vector<std::vector<int64_t>>& groups() const { return groups_; }

  bool pin_layout() const { return pin_layout_; }

 private:
  AllReduceType reduce_type_;
  double scale_;
  int64_t scatter_dim_;
  int64_t shard_count_;
  std::vector<std::vector<int64_t>> groups_;
  bool pin_layout_;
};

}  // namespace torch_xla

#endif  // XLA_TORCH_XLA_CSRC_OPS_REDUCE_SCATTER_H_
