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

std::unique_ptr<const JSBigString> StringBundle::getScript() const {
  // It might be used multiple times, so we don't want to move it, but instead copy it.
  std::unique_ptr<JSBigBufferString> script =
    std::make_unique<JSBigBufferString>(script_->size());
  std::memcpy(script->data(), script_->c_str(), script_->size());
  return std::move(script);
}

} // react
} // facebook