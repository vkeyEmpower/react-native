#include "BasicBundle.h" 

namespace facebook {
namespace react {
    
  BasicBundle::BasicBundle(std::string sourceURL, std::unique_ptr<const JSBigString> script) {
    _sourceURL = sourceURL;
    _script = std::move(script);
  }

  std::string BasicBundle::getSourceURL() const {
    return _sourceURL;
  }

  std::shared_ptr<const JSBigString> BasicBundle::getScript() const {
    return _script;
  }

} // react
} // facebook