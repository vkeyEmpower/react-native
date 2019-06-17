#pragma once

#import <memory>
#import <cxxreact/Bundle.h>
#import <cxxreact/BundleLoader.h>

#import <Foundation/Foundation.h>

NS_ENUM(NSInteger) {
  RCTNetworkBundleLoaderErrorURLLoadFailed = 3,
};

namespace facebook {
  namespace react {
    
    class RCTNetworkBundleLoader : public BundleLoader {
    public:
      
      RCTNetworkBundleLoader(//TODO //) {};
      ~RCTNetworkBundleLoader() {}
      
      std::unique_ptr<const Bundle> getBundle(std::string bundleURL) const override;
      std::string getBundleURLFromName(std::string bundleName) const override;
      
    };
    
  } // namespace react
} // namespace facebook
