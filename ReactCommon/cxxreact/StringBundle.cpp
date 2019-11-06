#include "StringBundle.h" 

namespace facebook {
namespace react {
 
StringBundle::StringBundle(std::unique_ptr<const JSBigString> script, std::string sourceURL) {
  sourceURL_ = sourceURL;
  script_ = std::move(script);
}

ScriptTag StringBundle::getBundleType() const {
  return ScriptTag::String;
}

std::string StringBundle::getSourceURL() const {
  return sourceURL_;
}

std::unique_ptr<const JSBigString> StringBundle::getScript() {
  return std::move(script_);
}

} // react
} // facebook