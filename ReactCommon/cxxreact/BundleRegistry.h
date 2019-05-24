#pragma once

#include <memory>
#include <cxxreact/NativeToJsBridge.h>
#include "Bundle.h"
#include "Instance.h"

namespace facebook {
namespace react {

class BundleRegistry {
  public:
    struct BundleExecutionEnvironment {
      std::shared_ptr<MessageQueueThread> jsQueue;
      std::unique_ptr<NativeToJsBridge> nativeToJsBridge;
      std::weak_ptr<const Bundle> initialBundle;
    };

    BundleRegistry(JSExecutorFactory* jsExecutorFactory,
                   std::shared_ptr<ModuleRegistry> moduleRegistry,
                   std::shared_ptr<InstanceCallback> callback,
                   std::function<std::shared_ptr<MessageQueueThread>()> jsQueueFactory);
    BundleRegistry(const BundleRegistry&) = delete;
    BundleRegistry& operator=(const BundleRegistry&) = delete;
    ~BundleRegistry();

    void runNewExecutionEnvironment(std::unique_ptr<const Bundle> initialBundle,
                                    std::function<void()> callback);
    void disposeExecutionEnvironments();

  private:
    std::vector<BundleExecutionEnvironment> bundleExecutionEnvironments_;
    std::vector<std::shared_ptr<const Bundle>> bundles_;
    JSExecutorFactory* jsExecutorFactory_;
    std::shared_ptr<ModuleRegistry> moduleRegistry_;
    std::shared_ptr<InstanceCallback> callback_;
    std::function<std::shared_ptr<MessageQueueThread>()> jsQueueFactory_;
};

} // react
} // facebook

