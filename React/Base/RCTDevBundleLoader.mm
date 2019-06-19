#import "RCTDevBundleLoader.h"

#import "RCTMultipartDataTask.h"
#import <cxxreact/BasicBundle.h>
#import "NSDataBigString.h"
#import "RCTUtils.h"


namespace facebook {
  namespace react {
    
    RCTDevBundleLoader::RCTDevBundleLoader(NSDictionary<NSString *, RCTDevBundleSource *> *bundles) {
      _bundles = bundles;
    }
    
    std::unique_ptr<const Bundle> RCTDevBundleLoader::getBundle(std::string bundleURL) const {
      RCTDevBundleSource *bundleSource = [_bundles objectForKey:[NSString stringWithUTF8String:bundleURL.c_str()]];
      if(bundleSource) {
        std::unique_ptr<const NSDataBigString> script = std::make_unique<const NSDataBigString>([bundleSource data]);
        return std::make_unique<BasicBundle>(std::move(script), std::string([[[bundleSource url] absoluteString] UTF8String]));
      }
      return nil;
    }
    
    std::string RCTDevBundleLoader::getBundleURLFromName(std::string bundleName) const {
      //TODO
      //      return bundlesContainer_->getSourceURLByName(bundleName);
      return "index";
    }
    
  } // namespace react
} // namespace facebook
