#import "RCTNetworkBundleLoader.h"

#import "RCTMultipartDataTask.h"
#import <cxxreact/IndexedRAMBundle.h>
#import <cxxreact/BasicBundle.h>
#import <cxxreact/JSBigString.h>
#import "RCTUtils.h"

NSString *const RCTNetworkBundleLoaderErrorDomain = @"RCTNetworkBundleLoaderErrorDomain";


namespace facebook {
  namespace react {
    
    static NSDictionary *userInfoForRawResponse(NSString *rawText)
    {
      NSDictionary *parsedResponse = RCTJSONParse(rawText, nil);
      if (![parsedResponse isKindOfClass:[NSDictionary class]]) {
        return @{NSLocalizedDescriptionKey: rawText};
      }
      NSArray *errors = parsedResponse[@"errors"];
      if (![errors isKindOfClass:[NSArray class]]) {
        return @{NSLocalizedDescriptionKey: rawText};
      }
      NSMutableArray<NSDictionary *> *fakeStack = [NSMutableArray new];
      for (NSDictionary *err in errors) {
        [fakeStack addObject: @{
                                @"methodName": err[@"description"] ?: @"",
                                @"file": err[@"filename"] ?: @"",
                                @"lineNumber": err[@"lineNumber"] ?: @0
                                }];
      }
      return @{NSLocalizedDescriptionKey: parsedResponse[@"message"] ?: @"No message provided", @"stack": [fakeStack copy]};
    }
    
    std::unique_ptr<const Bundle> RCTNetworkBundleLoader::getBundle(std::string bundleURL) const {
      NSURL *sourceURL = [[NSURL alloc] initWithString:[NSString stringWithUTF8String:bundleURL.c_str()]];
      RCTMultipartDataTask *task = [[RCTMultipartDataTask alloc] initWithURL:sourceURL partHandler:^(NSInteger statusCode, NSDictionary *headers, NSData *data, NSError *error, BOOL done) {
        if (!done) {
//          if (onProgress) {
//            onProgress(progressEventFromData(data));
//          }
          return;
        }
        
        // Handle general request errors
        if (error) {
          if ([error.domain isEqualToString:NSURLErrorDomain]) {
            error = [NSError errorWithDomain:RCTNetworkBundleLoaderErrorDomain
                                        code:RCTNetworkBundleLoaderErrorURLLoadFailed
                                    userInfo:
                     @{
                       NSLocalizedDescriptionKey:
                         [@"Could not connect to development server.\n\n"
                          "Ensure the following:\n"
                          "- Node server is running and available on the same network - run 'npm start' from react-native root\n"
                          "- Node server URL is correctly set in AppDelegate\n"
                          "- WiFi is enabled and connected to the same network as the Node Server\n\n"
                          "URL: " stringByAppendingString:sourceURL.absoluteString],
                       NSLocalizedFailureReasonErrorKey: error.localizedDescription,
                       NSUnderlyingErrorKey: error,
                       }];
          }
//          onComplete(error, nil);
          return;
        }
        
        // For multipart responses packager sets X-Http-Status header in case HTTP status code
        // is different from 200 OK
        NSString *statusCodeHeader = headers[@"X-Http-Status"];
        if (statusCodeHeader) {
          statusCode = [statusCodeHeader integerValue];
        }
        
        if (statusCode != 200) {
          error = [NSError errorWithDomain:@"JSServer"
                                      code:statusCode
                                  userInfo:userInfoForRawResponse([[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding])];
//          onComplete(error, nil);
          return;
        }
        
        // Validate that the packager actually returned javascript.
        NSString *contentType = headers[@"Content-Type"];
        NSString *mimeType = [[contentType componentsSeparatedByString:@";"] firstObject];
        if (![mimeType isEqualToString:@"application/javascript"] &&
            ![mimeType isEqualToString:@"text/javascript"]) {
          NSString *description = [NSString stringWithFormat:@"Expected MIME-Type to be 'application/javascript' or 'text/javascript', but got '%@'.", mimeType];
          error = [NSError errorWithDomain:@"JSServer"
                                      code:NSURLErrorCannotParseResponse
                                  userInfo:@{
                                             NSLocalizedDescriptionKey: description,
                                             @"headers": headers,
                                             @"data": data
                                             }];
//          onComplete(error, nil);
          return;
        }
        
//        RCTSource *source = RCTSourceCreate(scriptURL, data, data.length);
//        parseHeaders(headers, source);
//        onComplete(nil, source);
      } progressHandler:^(NSDictionary *headers, NSNumber *loaded, NSNumber *total) {
        // Only care about download progress events for the javascript bundle part.
        if ([headers[@"Content-Type"] isEqualToString:@"application/javascript"]) {
//          onProgress(progressEventFromDownloadProgress(loaded, total));
        }
      }];
      
      [task startTask];
    }
    
    std::string RCTNetworkBundleLoader::getBundleURLFromName(std::string bundleName) const {
      //TODO
      //      return bundlesContainer_->getSourceURLByName(bundleName);
      return "index";
    }
    
  } // namespace react
} // namespace facebook
