// Part of the Carbon Language project, under the Apache License v2.0 with LLVM
// Exceptions. See /LICENSE for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception

#include "language_server/file.h"

#include <memory>

#include "toolchain/diagnostics/null_diagnostics.h"
#include "toolchain/lexer/tokenized_buffer.h"
#include "toolchain/parser/parse_tree.h"

namespace Carbon::LS {

File::File(std::unique_ptr<llvm::vfs::FileSystem> vfs, llvm::StringRef path)
    : vfs_(std::move(vfs)),
      path_(path),
      buf_(std::move(*SourceBuffer::CreateFromFile(*vfs_, path))),
      tokenized_(TokenizedBuffer::Lex(buf_, NullDiagnosticConsumer())),
      parse_tree_(
          ParseTree::Parse(tokenized_, NullDiagnosticConsumer(), nullptr)) {}

auto File::New(llvm::StringRef path, std::string content)
    -> std::unique_ptr<File> {
  auto vfs = std::make_unique<llvm::vfs::InMemoryFileSystem>();

  vfs->addFile(path, /*mtime=*/0,
               llvm::MemoryBuffer::getMemBufferCopy(content));

  return std::unique_ptr<File>(new File(std::move(vfs), path));
}

}  // namespace Carbon::LS
