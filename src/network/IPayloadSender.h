// UnderStory
// An intuitive Pen & Paper experience
// Copyright (C) 2020-2021 Guillaume Vara <guillaume.vara@gmail.com>

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// Any graphical resources available within the source code may
// use a different license and copyright : please refer to their metadata
// for further details. Graphical resources without explicit references to a
// different license and copyright still refer to this GPL.

#pragma once

#include "IPayloadHandler.h"
#include "Payloads.h"

namespace UnderStory {

namespace Network {

template<class T = RawPayload>
class IPayloadSender : protected IPayloadHandler<T> {
 public:
    using SQueue = AtomicQueue<T>;
    IPayloadSender(const char* socketName, tcp::socket* socket, SQueue* senderQueue);

    void _sendPayload(const T& payload);

    virtual void _onPayloadSendError(const std::error_code &ec, const char* partStr);
    virtual void _onPayloadBytesUploaded(PayloadType type, size_t uploaded, size_t total);

 private:
    void _sendPayloadType();
    void _sendPayloadBytesSize();
    void _sendPayloadBytes();
};

}   // namespace Network

}   // namespace UnderStory
