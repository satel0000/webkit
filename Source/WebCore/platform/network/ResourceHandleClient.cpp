/*
 * Copyright (C) 2013 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. AND ITS CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL APPLE INC. OR ITS CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "config.h"
#include "ResourceHandleClient.h"

#include "ResourceHandle.h"
#include "ResourceRequest.h"
#include "SharedBuffer.h"

namespace WebCore {

ResourceHandleClient::ResourceHandleClient()
{
}

ResourceHandleClient::~ResourceHandleClient()
{
}
    
ResourceRequest ResourceHandleClient::willSendRequest(ResourceHandle*, ResourceRequest&& request, ResourceResponse&&)
{
    return WTFMove(request);
}

void ResourceHandleClient::willSendRequestAsync(ResourceHandle* handle, ResourceRequest&& request, ResourceResponse&& /*redirectResponse*/)
{
    handle->continueWillSendRequest(WTFMove(request));
}

void ResourceHandleClient::didReceiveResponseAsync(ResourceHandle* handle, const ResourceResponse&)
{
    handle->continueDidReceiveResponse();
}

#if USE(PROTECTION_SPACE_AUTH_CALLBACK)
void ResourceHandleClient::canAuthenticateAgainstProtectionSpaceAsync(ResourceHandle* handle, const ProtectionSpace&)
{
    handle->continueCanAuthenticateAgainstProtectionSpace(false);
}
#endif

#if USE(CFNETWORK)
void ResourceHandleClient::willCacheResponseAsync(ResourceHandle* handle, CFCachedURLResponseRef response)
{
    handle->continueWillCacheResponse(response);
}
#elif PLATFORM(COCOA)
void ResourceHandleClient::willCacheResponseAsync(ResourceHandle* handle, NSCachedURLResponse *response)
{
    handle->continueWillCacheResponse(response);
}
#endif

void ResourceHandleClient::didReceiveBuffer(ResourceHandle* handle, Ref<SharedBuffer>&& buffer, int encodedDataLength)
{
    didReceiveData(handle, buffer->data(), buffer->size(), encodedDataLength);
}

}
