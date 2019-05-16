// Copyright (c) Facebook, Inc. and its affiliates.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#pragma once

#include <sstream>
#include <fstream>
#include <cxxreact/JSBigString.h>

#ifndef RN_EXPORT
#define RN_EXPORT __attribute__((visibility("default")))
#endif

namespace facebook {
namespace react {


class JSIndexedRAMBundleSource {
public:
  JSIndexedRAMBundleSource() = default;

  // Not copyable
  JSIndexedRAMBundleSource(const JSIndexedRAMBundleSource&) = delete;
  JSIndexedRAMBundleSource& operator=(const JSIndexedRAMBundleSource&) = delete;

  virtual ~JSIndexedRAMBundleSource() {}

  virtual std::ios::iostate rdstate() const = 0;

  virtual JSIndexedRAMBundleSource& read(char* buffer, std::streamsize size) const = 0;

  virtual JSIndexedRAMBundleSource& seekg(std::streampos pos) const = 0;

  virtual bool operator!() const = 0;
};


class RN_EXPORT JSIndexedRAMBundleFileSource : public JSIndexedRAMBundleSource {
public:
  JSIndexedRAMBundleFileSource(const char* filePath);
  
  ~JSIndexedRAMBundleFileSource();

  std::ios::iostate rdstate() const override;

  JSIndexedRAMBundleFileSource& read(char* buffer, std::streamsize size) const override;

  JSIndexedRAMBundleFileSource& seekg(std::streampos pos) const override;

  bool operator! () const override;
private:
  std::ifstream m_source;
};

class RN_EXPORT JSIndexedRAMBundleStringSource : public JSIndexedRAMBundleSource {
public:
  JSIndexedRAMBundleStringSource(const JSBigString* script);
  
  ~JSIndexedRAMBundleStringSource();

  std::ios::iostate rdstate() const override;

  JSIndexedRAMBundleStringSource& read(char* buffer, std::streamsize size) const override;

  JSIndexedRAMBundleStringSource& seekg(std::streampos pos) const override;

  bool operator! () const override;
private:
  mutable std::stringstream m_source;
};

}  // namespace react
}  // namespace facebook
  
  