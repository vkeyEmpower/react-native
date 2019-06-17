#import "RCTFileBundleLoader.h"

#import <sys/stat.h>

#import <cxxreact/IndexedRAMBundle.h>
#import <cxxreact/BasicBundle.h>
#import "NSDataBigString.h"


NSString *const RCTFileBundleLoaderErrorDomain = @"RCTFileBundleLoaderErrorDomain";
static const int32_t JSNoBytecodeFileFormatVersion = -1;

//TODO FIGURE OUT ERRORS
namespace facebook {
  namespace react {
    
    std::unique_ptr<const Bundle> RCTFileBundleLoader::getBundle(std::string bundleURL) const {
      const uint32_t runtimeBCVersion = JSNoBytecodeFileFormatVersion;
      NSError *error;
      FILE *bundle = fopen(bundleURL.c_str(), "r");
      if (!bundle) {
        if (error) {
          error = [NSError errorWithDomain:RCTFileBundleLoaderErrorDomain
                                       code:RCTFileBundleLoaderErrorFailedOpeningFile
                                   userInfo:@{NSLocalizedDescriptionKey:
                                                [NSString stringWithFormat:@"Error opening bundle %s", bundleURL.c_str()]}];
        }
      }
      facebook::react::BundleHeader header;
      size_t readResult = fread(&header, sizeof(header), 1, bundle);
      fclose(bundle);
      if (readResult != 1) {
        if (error) {
          error = [NSError errorWithDomain:RCTFileBundleLoaderErrorDomain
                                       code:RCTFileBundleLoaderErrorFailedReadingFile
                                   userInfo:@{NSLocalizedDescriptionKey:
                                                [NSString stringWithFormat:@"Error reading bundle %s", bundleURL.c_str()]}];
        }
        return nil;
      }
      facebook::react::BundleType tag = facebook::react::Bundle::parseTypeFromHeader(header);
      switch (tag) {
        case facebook::react::BundleType::IndexedRAMBundle: {
          struct stat statInfo;
          if (stat(bundleURL.c_str(), &statInfo) != 0) {
            if (error) {
              error = [NSError errorWithDomain:RCTFileBundleLoaderErrorDomain
                                          code:RCTFileBundleLoaderErrorFailedStatingFile
                                      userInfo:@{NSLocalizedDescriptionKey:
                                                   [NSString stringWithFormat:@"Error stating bundle %s", bundleURL.c_str()]}];
            }
            return nil;
          }
          
          return std::make_unique<IndexedRAMBundle>(bundleURL.c_str(), bundleURL.c_str());
        }
          break;
        case facebook::react::BundleType::DeltaBundle:
        case facebook::react::BundleType::FileRAMBundle:
          // Not sure if delta or file RAM bundles are supported on iOS
          return nil;
        case facebook::react::BundleType::BasicBundle: {
#if RCT_ENABLE_INSPECTOR
          NSData *source = [NSData dataWithContentsOfFile:bundleURL
                                                  options:NSDataReadingMappedIfSafe
                                                    error:error];
          if (sourceLength && source != nil) {
            *sourceLength = source.length;
          }
          std::unique_ptr<const NSDataBigString> script = std::make_unique<const NSDataBigString>(source);
          std::unique_ptr<const BasicBundle> = std::make_unique<BasicBundle>(std::move(script), bundleURL);
          return ;
#else
          if (error) {
            error = [NSError errorWithDomain:RCTFileBundleLoaderErrorDomain
                                         code:RCTFileBundleLoaderErrorCannotBeLoadedSynchronously
                                     userInfo:@{NSLocalizedDescriptionKey:
                                                  @"Cannot load text/javascript files synchronously"}];
          }
          return nil;
#endif
        }
        // WHAT IS IT FOR?
        case facebook::react::BundleType::BCBundle:{
          if (runtimeBCVersion == JSNoBytecodeFileFormatVersion || runtimeBCVersion < 0) {
            if (error) {
              error = [NSError errorWithDomain:RCTFileBundleLoaderErrorDomain
                                           code:RCTFileBundleLoaderErrorBCNotSupported
                                       userInfo:@{NSLocalizedDescriptionKey:
                                                    @"Bytecode bundles are not supported by this runtime."}];
            }
            return nil;
          }
          else if ((uint32_t)runtimeBCVersion != header.version) {
            if (error) {
              NSString *errDesc =
              [NSString stringWithFormat:@"BC Version Mismatch. Expect: %d, Actual: %u",
               runtimeBCVersion, header.version];
              
              error = [NSError errorWithDomain:RCTFileBundleLoaderErrorDomain
                                           code:RCTFileBundleLoaderErrorBCVersion
                                       userInfo:@{NSLocalizedDescriptionKey: errDesc}];
            }
            return nil;
          }
          break;
        }
      }
    }
    
    std::string RCTFileBundleLoader::getBundleURLFromName(std::string bundleName) const {
      //TODO 
//      return bundlesContainer_->getSourceURLByName(bundleName);
      return "index";
    }
    
  } // namespace react
} // namespace facebook
