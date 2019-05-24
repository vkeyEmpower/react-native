#pragma once

#include <memory>
#include <istream>
#include "RAMBundle.h"
#include "JSBigString.h"

namespace facebook {
namespace react {

class IndexedRAMBundle : public RAMBundle {
public:
  IndexedRAMBundle(std::string sourcePath, std::string sourceURL);

  // For Android IndexedRAMBundle loaded from Assets
  IndexedRAMBundle(std::string sourcePath,
                  std::string sourceURL,
                  std::unique_ptr<const JSBigString> script);

  std::string getSourceURL() const override;
  std::string getSourcePath() const override;
  std::shared_ptr<const JSBigString> getStartupScript() const override;
  Module getModule(uint32_t moduleId) const override;
  
  BundleType bundleType = BundleType::IndexedRAMBundle;
private:
  struct ModuleData {
    uint32_t offset;
    uint32_t length;
  };
  static_assert(
    sizeof(ModuleData) == 8,
    "ModuleData must not have any padding and use sizes matching input files");

  struct ModuleTable {
    size_t numEntries;
    std::unique_ptr<ModuleData[]> data;
    ModuleTable() : numEntries(0) {};
    ModuleTable(size_t entries) :
      numEntries(entries),
      data(std::unique_ptr<ModuleData[]>(new ModuleData[numEntries])) {};
    size_t byteLength() const {
      return numEntries * sizeof(ModuleData);
    }
  };

  std::string getModuleCode(const uint32_t id) const;
  void readBundle(char *buffer, const std::streamsize bytes) const;
  void readBundle(
    char *buffer, const
    std::streamsize bytes,
    const std::ifstream::pos_type position) const;

  std::string _sourceURL;
  std::string _sourcePath;
  std::shared_ptr<const JSBigString> m_startupScript;
  mutable std::unique_ptr<std::istream> m_bundle;
  ModuleTable m_table;
  size_t m_baseOffset;
};

} // react
} // facebook
