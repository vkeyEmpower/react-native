// Copyright (c) Facebook, Inc. and its affiliates.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <folly/dynamic.h>
#include "JSBigString.h"
#include "RAMBundle.h"

namespace facebook {
namespace react {

// TODO: refactor
class JSDeltaBundleClient {
public:
  void patch(const folly::dynamic& delta);
  RAMBundle::Module getModule(uint32_t moduleId) const;
  std::unique_ptr<const JSBigString> getStartupCode() const;
  void clear();

private:
  std::unordered_map<uint32_t, std::string> modules_;
  std::string startupCode_;

  void patchModules(const folly::dynamic *delta);
};

// class JSDeltaBundleClientRAMBundle : public JSModulesUnbundle {
// public:
//   JSDeltaBundleClientRAMBundle(
//     std::shared_ptr<const JSDeltaBundleClient> client) : client_(client) {}

//   RAMBundle::Module getModule(uint32_t moduleId) const override {
//     return client_->getModule(moduleId);
//   }
// private:
//   const std::shared_ptr<const JSDeltaBundleClient> client_;
// };

} // namespace react
} // namespace facebook
