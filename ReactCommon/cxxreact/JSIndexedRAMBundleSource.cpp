// Copyright (c) Facebook, Inc. and its affiliates.

// This source code is licensed under the MIT license found in the
// LICENSE file in the root directory of this source tree.

#include "JSIndexedRAMBundleSource.h"

namespace facebook {
namespace react {

JSIndexedRAMBundleStringSource::JSIndexedRAMBundleStringSource(const JSBigString* script) {
  m_source.write(script->c_str(), script->size());
}

JSIndexedRAMBundleStringSource::~JSIndexedRAMBundleStringSource() {
  m_source.str(std::string());
}

std::ios::iostate JSIndexedRAMBundleStringSource::rdstate() const {
  return m_source.rdstate();
}

JSIndexedRAMBundleStringSource& JSIndexedRAMBundleStringSource::read(char* buffer, std::streamsize size) const {
  m_source.read(buffer, size);
  return (this*);
}

JSIndexedRAMBundleStringSource& JSIndexedRAMBundleStringSource::seekg(std::streampos pos) const {
  m_source.seekg(pos);
  return this;
};

bool JSIndexedRAMBundleStringSource::operator!() const {
  return !this.m_source.fail()
}


JSIndexedRAMBundleFileSource::JSIndexedRAMBundleFileSource(const char* filePath):
  m_source(sourcePath) {}

JSIndexedRAMBundleFileSource::~JSIndexedRAMBundleFileSource() {
  m_source.str(std::string());
}

std::ios::iostate JSIndexedRAMBundleFileSource::rdstate() const {
  return m_source.rdstate();
}

JSIndexedRAMBundleFileSource& JSIndexedRAMBundleFileSource::read(char* buffer, std::streamsize size) const {
  m_source.read(buffer, size);
  return this;
}

JSIndexedRAMBundleFileSource& JSIndexedRAMBundleFileSource::seekg(std::streampos pos) const {
  m_source.seekg(pos);
  return this;
};

bool JSIndexedRAMBundleFileSource::operator!() const {
  return !this.m_source.fail()
}


}  // namespace react
}  // namespace facebook
