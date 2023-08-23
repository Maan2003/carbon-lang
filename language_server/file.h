// Part of the Carbon Language project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#ifndef CARBON_LANGUAGE_SERVER_FILE_H_
#define CARBON_LANGUAGE_SERVER_FILE_H_

#include <memory>

#include "llvm/ADT/StringRef.h"
#include "toolchain/lexer/tokenized_buffer.h"
#include "toolchain/parser/parse_tree.h"
#include "toolchain/source/source_buffer.h"

namespace Carbon::LS {

class File {
 public:
  static auto New(llvm::StringRef path, std::string content)
      -> std::unique_ptr<File>;

  auto TokenizedBuffer() const -> const Carbon::TokenizedBuffer& {
    return this->tokenized_;
  }

  auto ParseTree() const -> const Carbon::ParseTree& {
    return this->parse_tree_;
  }

 private:
  std::unique_ptr<llvm::vfs::FileSystem> vfs_;
  std::string path_;
  Carbon::SourceBuffer buf_;
  Carbon::TokenizedBuffer tokenized_;
  Carbon::ParseTree parse_tree_;

  File(std::unique_ptr<llvm::vfs::FileSystem> vfs, llvm::StringRef path);

  friend std::unique_ptr<File>;
};

}  // namespace Carbon::LS

#endif  // CARBON_LANGUAGE_SERVER_FILE_H_
