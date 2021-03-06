// Copyright 2020 SkyAPM

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

//     http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <google/protobuf/message.h>
#include <grpcpp/grpcpp.h>

#include <memory>

using google::protobuf::Message;

namespace cpp2sky {

template <class RequestType, class ResponseType>
class TracerStub {
 public:
  virtual ~TracerStub() = default;

  /**
   * Initialize request writer.
   */
  virtual std::unique_ptr<grpc::ClientAsyncWriter<RequestType>> createWriter(
      grpc::ClientContext* ctx, ResponseType* response,
      grpc::CompletionQueue* cq, void* tag) = 0;
};

template <class RequestType, class ResponseType>
using TracerStubPtr = std::unique_ptr<TracerStub<RequestType, ResponseType>>;

template <class RequestType, class ResponseType>
class AsyncClient {
 public:
  virtual ~AsyncClient() = default;

  /**
   * Send the specified protobuf message
   */
  virtual void sendMessage(Message& message) = 0;

  /**
   * Get writer.
   */
  virtual std::unique_ptr<grpc::ClientAsyncWriter<RequestType>> createWriter(
      grpc::ClientContext* ctx, ResponseType* response, void* tag) = 0;

  /**
   * Peer address of current gRPC client..
   */
  virtual std::string peerAddress() = 0;
};

enum class Operation : uint8_t {
  Initialized = 0,
  Connected = 1,
  Idle = 2,
  WriteDone = 3,
  Finished = 4,
};

template <class RequsetType, class ResponseType>
using AsyncClientPtr = std::unique_ptr<AsyncClient<RequsetType, ResponseType>>;

class AsyncStream {
 public:
  virtual ~AsyncStream() = default;

  /**
   * Start stream. It will move the state of stream to Init.
   */
  virtual bool startStream() = 0;

  /**
   * Send message. It will move the state from Init to Write.
   */
  virtual void sendMessage(Message& message) = 0;

  /**
   * Handle incoming event related to this stream.
   */
  virtual bool handleOperation(Operation incoming_op) = 0;
};

using AsyncStreamPtr = std::shared_ptr<AsyncStream>;

template <class RequestType, class ResponseType>
class AsyncStreamFactory {
 public:
  virtual ~AsyncStreamFactory() = default;

  /**
   * Create async stream entity
   */
  virtual AsyncStreamPtr create(
      AsyncClient<RequestType, ResponseType>* client) = 0;
};

template <class RequestType, class ResponseType>
using AsyncStreamFactoryPtr =
    std::unique_ptr<AsyncStreamFactory<RequestType, ResponseType>>;

}  // namespace cpp2sky
